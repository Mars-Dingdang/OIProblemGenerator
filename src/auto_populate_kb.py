import os
import fitz  # PyMuPDF
import json
import argparse
import re
import concurrent.futures
import itertools
from tqdm import tqdm
from langchain_openai import ChatOpenAI
from langchain_core.prompts import ChatPromptTemplate
from langchain_core.output_parsers import JsonOutputParser
from pydantic import BaseModel, Field
from dotenv import load_dotenv

load_dotenv()

# Define Pydantic model for structured output
class AlgorithmData(BaseModel):
    english_name: str = Field(description="English name in snake_case for directory name (e.g. 'segment_tree')")
    metadata: dict = Field(description="Metadata including name, category, complexity, scenarios, extensions")
    template: str = Field(description="Standard C++ template code")
    tricks: str = Field(description="Advanced tricks and key observations in Markdown")

def get_llm(model_name="Qwen3-235B-A22B-Instruct-2507", api_key=None):
    # print(f"🤖 Using model: {model_name}")
    return ChatOpenAI(
        api_key=api_key or os.getenv("OPENAI_API_KEY"),
        base_url=os.getenv("OPENAI_BASE_URL"),
        model=model_name,
        temperature=0.3
    )

CATEGORY_MAP = {
    "算法基础": "basics",
    "搜索": "search",
    "动态规划": "dynamic_programming",
    "字符串": "string",
    "数学": "math",
    "数据结构": "data_structures",
    "图论": "graph_theory",
    "计算几何": "geometry",
    "杂项": "misc"
}

def clean_text(text):
    # Remove header/footer noise if possible
    lines = text.split('\n')
    # Simple heuristic: remove lines that look like page numbers or headers
    cleaned = [line for line in lines if not re.match(r'^\s*\d+\s*$', line)]
    return '\n'.join(cleaned)

def process_algorithm(llm, text, category_hint):
    parser = JsonOutputParser(pydantic_object=AlgorithmData)
    prompt = ChatPromptTemplate.from_template(
        """
        You are an expert in Competitive Programming.
        Analyze the following text from OI Wiki about an algorithm in the category '{category}'.
        
        Extract and generate structured information.
        1. **English Name**: Convert the algorithm name to snake_case English (e.g., "背包 DP" -> "knapsack_dp").
        2. **Metadata**: Key info.
        3. **Template**: A clean, standard C++ implementation. If the text doesn't have one, generate a standard one based on your knowledge.
        4. **Tricks**: Key observations, optimizations, or common problem transformation patterns mentioned in the text or known by you.
        
        Text (truncated):
        {text}
        
        {format_instructions}
        """
    )
    # Limit text to avoid context window issues, though Qwen has large context
    # Taking first 15000 chars should be enough for most sections
    chain = prompt | llm | parser
    try:
        return chain.invoke({
            "text": text[:15000], 
            "category": category_hint, 
            "format_instructions": parser.get_format_instructions()
        })
    except Exception as e:
        print(f"Error processing with LLM: {e}")
        return None

def process_single_task(args):
    text, category, model_name, api_key, output_dir, task_title = args
    try:
        llm = get_llm(model_name, api_key)
        data = process_algorithm(llm, text, category)
        
        if data:
            # Save to file
            algo_slug = data.get('english_name', 'unknown').lower().replace(" ", "_")
            save_path = os.path.join(output_dir, category, algo_slug)
            os.makedirs(save_path, exist_ok=True)
            
            with open(os.path.join(save_path, "metadata.json"), "w", encoding="utf-8") as f:
                json.dump(data['metadata'], f, indent=4, ensure_ascii=False)
                
            with open(os.path.join(save_path, "template.cpp"), "w", encoding="utf-8") as f:
                f.write(data['template'])
                
            with open(os.path.join(save_path, "tricks.md"), "w", encoding="utf-8") as f:
                f.write(data['tricks'])
                
            return f"✅ Saved {task_title} -> {save_path}"
        else:
            return f"❌ Failed to generate for {task_title}"
    except Exception as e:
        return f"❌ Error processing {task_title}: {str(e)}"

def main():
    parser = argparse.ArgumentParser(description="Auto-populate structured KB from OI Wiki PDF")
    parser.add_argument("--pdf_path", type=str, default="knowledge_base/OI-wiki.pdf")
    parser.add_argument("--output_dir", type=str, default="knowledge_base/structured")
    parser.add_argument("--limit", type=int, default=5, help="Limit number of algorithms to process per category")
    parser.add_argument("--model", type=str, default="Qwen3-235B-A22B-Instruct-2507", help="Model to use (e.g., DeepSeek-V3.2-Instruct, DeepSeek-V3.2-Exp)")
    parser.add_argument("--category", type=str, default=None, help="Filter by category (e.g., data_structures)")
    parser.add_argument("--api_keys", type=str, default=None, help="Comma-separated list of additional API keys")
    parser.add_argument("--workers", type=int, default=4, help="Number of parallel workers")
    args = parser.parse_args()

    if not os.path.exists(args.pdf_path):
        print(f"PDF not found at {args.pdf_path}")
        return

    # Setup API keys
    api_keys = []
    env_key = os.getenv("OPENAI_API_KEY")
    if env_key:
        api_keys.append(env_key)
    if args.api_keys:
        api_keys.extend([k.strip() for k in args.api_keys.split(',') if k.strip()])
    
    if not api_keys:
        print("No API keys found! Set OPENAI_API_KEY or pass --api_keys")
        return
        
    print(f"🔑 Using {len(api_keys)} API keys with {args.workers} workers")
    key_cycle = itertools.cycle(api_keys)

    print(f"📖 Opening PDF: {args.pdf_path}")
    doc = fitz.open(args.pdf_path)
    toc = doc.get_toc()
    
    # llm = get_llm(args.model) # Moved to worker
    
    # Build a hierarchy from TOC
    # We are looking for Level 1 Categories -> Level 2 Algorithms
    # Or Level 1 -> Level 2 -> Level 3 Algorithms
    
    tasks = []
    current_category = None
    current_category_en = None
    
    # Skip intro sections
    start_processing = False
    
    for i in range(len(toc)):
        level, title, page = toc[i]
        
        # Identify Category
        if level == 1:
            if title in CATEGORY_MAP:
                current_category = title
                current_category_en = CATEGORY_MAP[title]
                start_processing = True
                print(f"Found Category: {title} -> {current_category_en}")
            else:
                start_processing = False # Skip non-algorithm sections like "Intro"
                
        if not start_processing or not current_category:
            continue
            
        # Identify Algorithm (Level 2 or 3)
        # Heuristic: If it's a leaf node in TOC or has no children in the immediate next entry
        is_leaf = False
        if i + 1 >= len(toc):
            is_leaf = True
        elif toc[i+1][0] <= level:
            is_leaf = True
            
        if is_leaf and level >= 2:
            # It's an algorithm section
            start_page = page
            # Find end page
            if i + 1 < len(toc):
                end_page = toc[i+1][2]
            else:
                end_page = doc.page_count
            
            tasks.append({
                "title": title,
                "category": current_category,
                "category_en": current_category_en,
                "start_page": start_page,
                "end_page": end_page
            })

    print(f"Found {len(tasks)} potential algorithm sections.")
    
    # Group by category to apply limit
    tasks_by_category = {}
    for t in tasks:
        cat = t['category_en']
        
        # Apply category filter if specified
        if args.category:
            target_cats = args.category.split(',')
            if cat not in target_cats:
                continue
            
        if cat not in tasks_by_category:
            tasks_by_category[cat] = []
        tasks_by_category[cat].append(t)
        
    # Collect all tasks to process
    all_work_items = []
    
    for cat, cat_tasks in tasks_by_category.items():
        print(f"\nPreparing Category: {cat}")
        
        # Pre-load existing algorithms
        existing_algos = set()
        cat_dir = os.path.join(args.output_dir, cat)
        if os.path.exists(cat_dir):
            for d in os.listdir(cat_dir):
                meta_path = os.path.join(cat_dir, d, "metadata.json")
                if os.path.exists(meta_path):
                    try:
                        with open(meta_path, "r", encoding="utf-8") as f:
                            meta = json.load(f)
                            if "name" in meta:
                                existing_algos.add(meta["name"].strip())
                    except:
                        pass
        
        print(f"Found {len(existing_algos)} existing algorithms in {cat}")
        
        count = 0
        for task in cat_tasks:
            if count >= args.limit:
                break
            
            if task['title'].strip() in existing_algos:
                continue
                
            count += 1
            
            # Extract text (must be done in main thread)
            text = ""
            for p in range(task['start_page'] - 1, task['end_page'] - 1):
                if p < doc.page_count:
                    text += doc.load_page(p).get_text()
            
            text = clean_text(text)
            if len(text) < 100:
                continue
                
            # Assign an API key
            api_key = next(key_cycle)
            
            all_work_items.append((
                text, 
                task['category'], 
                args.model, 
                api_key, 
                args.output_dir, 
                task['title']
            ))

    print(f"\n🚀 Starting parallel processing of {len(all_work_items)} tasks with {args.workers} workers...")
    
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.workers) as executor:
        futures = [executor.submit(process_single_task, item) for item in all_work_items]
        
        for future in tqdm(concurrent.futures.as_completed(futures), total=len(futures)):
            result = future.result()
            if "❌" in result:
                tqdm.write(result) # Use tqdm.write to avoid breaking progress bar

if __name__ == "__main__":
    main()
