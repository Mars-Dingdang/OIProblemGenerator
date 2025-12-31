import os
import fitz  # PyMuPDF
import json
import re
import time
from typing import List, Dict, Optional
from tqdm import tqdm
from langchain_openai import ChatOpenAI
from langchain_core.messages import HumanMessage, SystemMessage
from langchain_core.output_parsers import JsonOutputParser
from pydantic import BaseModel, Field
from dotenv import load_dotenv

load_dotenv()

# Configuration
PDF_DIR = os.path.join(os.path.dirname(os.path.dirname(__file__)), "knowledge_base", "NOIpaper-main")
STRUCTURED_DIR = os.path.join(os.path.dirname(os.path.dirname(__file__)), "knowledge_base", "structured")
YEARS = range(2013, 2026)

# Categories
CATEGORY_MAP = {
    "basics": "算法基础",
    "search": "搜索",
    "dynamic_programming": "动态规划",
    "string": "字符串",
    "math": "数学",
    "data_structures": "数据结构",
    "graph_theory": "图论",
    "geometry": "计算几何",
    "misc": "杂项"
}
REVERSE_CATEGORY_MAP = {v: k for k, v in CATEGORY_MAP.items()}

class PaperMetadata(BaseModel):
    title: str = Field(description="Title of the paper")
    author: str = Field(description="Author of the paper")
    topic: str = Field(description="Main topic/category of the paper")

class PaperAnalysis(BaseModel):
    english_name: str = Field(description="English name for the algorithm/topic (snake_case), e.g., 'segment_tree_beats'")
    category: str = Field(description="Category from: basics, search, dynamic_programming, string, math, data_structures, graph_theory, geometry, misc")
    summary: str = Field(description="Brief summary of the paper")
    complexity: str = Field(description="Time/Space complexity if applicable")
    tricks: str = Field(description="Key thoughts, tricks, and observations in Markdown format")
    template: str = Field(description="C++ template code if available, else empty string")

def get_llm():
    """
    Returns the configured LLM instance.
    Uses Qwen-235B-A22B-Instruct-2507 as requested.
    """
    return ChatOpenAI(
        model="Qwen3-235B-A22B-Instruct-2507",
        api_key=os.getenv("OPENAI_API_KEY"),
        base_url=os.getenv("OPENAI_BASE_URL"),
        temperature=0.3
    )

def extract_toc(pdf_path: str, llm) -> List[Dict]:
    """Extracts list of papers from the PDF TOC."""
    doc = fitz.open(pdf_path)
    # Read first 15 pages
    text = ""
    for i in range(min(15, len(doc))):
        text += f"--- Page {i+1} ---\n{doc.load_page(i).get_text()}\n"
    
    prompt = f"""
    You are an assistant that extracts Table of Contents from a PDF text.
    The text below contains the beginning of a "National Olympiad in Informatics" paper collection.
    Find the Table of Contents and extract the list of papers.
    Return a JSON list of objects with keys: "title", "author", "page_number" (as integer).
    Ignore "Preface", "Foreword", etc. Only extract the actual technical papers.
    
    Text:
    {text}
    """
    
    try:
        response = llm.invoke([HumanMessage(content=prompt)])
        parser = JsonOutputParser()
        # Clean markdown code blocks if present
        content = response.content
        if "```json" in content:
            content = content.split("```json")[1].split("```")[0]
        elif "```" in content:
            content = content.split("```")[1].split("```")[0]
            
        toc_list = json.loads(content)
        return toc_list
    except Exception as e:
        print(f"Error extracting TOC: {e}")
        return []

def find_start_page(pdf_path: str, title: str, page_hint: int = -1) -> int:
    """Finds the PDF page number where the title appears as a header/title."""
    doc = fitz.open(pdf_path)
    
    # Define search order
    search_order = range(len(doc))
    if page_hint > 0:
        # PDF page is usually page_hint + offset. Offset is usually positive (cover pages).
        # Printed page 1 might be PDF page 5.
        # So PDF page ~ Printed Page + Offset.
        # We search around page_hint + 0 to page_hint + 20.
        
        center = page_hint + 2 # Guess small offset initially
        start = max(0, center - 10)
        end = min(len(doc), center + 30)
        
        # Prioritize this region
        priority = list(range(start, end))
        others = [i for i in range(len(doc)) if i not in priority]
        search_order = priority + others
    
    def normalize(s):
        # Remove all whitespace and convert to lower case
        return "".join(s.split()).lower()
        
    target = normalize(title)
    # print(f"DEBUG: Looking for '{target}' with hint {page_hint}")
    
    for i in search_order:
        # Skip very early pages if we have a hint that it's later
        if i < 3 and page_hint > 5: continue
        
        try:
            page_text = doc.load_page(i).get_text()
            norm_text = normalize(page_text)
            
            # if i == page_hint + 2: # Debug print for likely page
            #     print(f"DEBUG: Page {i} text (norm): {norm_text[:100]}...")
            
            # 1. Exact match of normalized string
            if target in norm_text:
                return i
            
            # 2. Fuzzy match
            # If the title is long enough, check if a large portion of it exists
            if len(target) > 8:
                # Check if the first 70% of the title is in the text
                cutoff = int(len(target) * 0.7)
                if target[:cutoff] in norm_text:
                    return i
                
                # Check if the last 70% of the title is in the text
                if target[-cutoff:] in norm_text:
                    return i
            
            # 3. Check if author is present on the page (if title fails but page hint is strong)
            # This is risky if multiple papers by same author, but rare in one collection.
            # We don't have author passed to this function though.
            
        except:
            continue
                
    return -1

def process_paper(pdf_path: str, start_page: int, end_page: int, metadata: Dict, llm):
    """Reads paper text and extracts structured knowledge."""
    doc = fitz.open(pdf_path)
    text = ""
    # Limit pages to avoid context overflow if paper is huge, but usually they are < 20 pages
    for i in range(start_page, min(end_page, len(doc))):
        text += doc.load_page(i).get_text()
        
    prompt = f"""
    Analyze the following algorithm paper from the National Olympiad in Informatics.
    Title: {metadata['title']}
    Author: {metadata['author']}
    
    Extract the following information into a JSON object:
    1. "english_name": A short, snake_case English name for the algorithm or topic (e.g. "segment_tree_beats").
    2. "category": One of [basics, search, dynamic_programming, string, math, data_structures, graph_theory, geometry, misc].
    3. "summary": A concise summary of the problem or algorithm.
    4. "complexity": Time and space complexity (e.g. "O(N log N)").
    5. "tricks": A Markdown string containing the key ideas, proofs, tricks, and observations. Be detailed here.
    6. "template": Standard C++ implementation code if present in the text. If not, leave empty.
    
    Paper Text:
    {text[:50000]} 
    """
    # Truncate text to 50k chars to be safe, though Gemini handles more.
    
    try:
        response = llm.invoke([HumanMessage(content=prompt)])
        content = response.content
        if "```json" in content:
            content = content.split("```json")[1].split("```")[0]
        elif "```" in content:
            content = content.split("```")[1].split("```")[0]
        
        data = json.loads(content)
        return PaperAnalysis(**data)
    except Exception as e:
        print(f"Error analyzing paper {metadata['title']}: {e}")
        return None

def save_to_kb(analysis: PaperAnalysis, original_metadata: Dict):
    """Saves the analyzed data to the structured KB."""
    # Determine path
    category_dir = os.path.join(STRUCTURED_DIR, analysis.category)
    algo_dir = os.path.join(category_dir, analysis.english_name)
    
    os.makedirs(algo_dir, exist_ok=True)
    
    # Metadata
    meta = {
        "name": analysis.english_name,
        "chinese_name": original_metadata['title'],
        "author": original_metadata['author'],
        "category": analysis.category,
        "complexity": analysis.complexity,
        "summary": analysis.summary
    }
    
    with open(os.path.join(algo_dir, "metadata.json"), "w", encoding="utf-8") as f:
        json.dump(meta, f, indent=4, ensure_ascii=False)
        
    # Tricks
    with open(os.path.join(algo_dir, "tricks.md"), "w", encoding="utf-8") as f:
        f.write(f"# {original_metadata['title']}\n\n")
        f.write(f"**Author:** {original_metadata['author']}\n\n")
        f.write(analysis.tricks)
        
    # Template
    if analysis.template and len(analysis.template.strip()) > 10:
        with open(os.path.join(algo_dir, "template.cpp"), "w", encoding="utf-8") as f:
            f.write(analysis.template)
            
    print(f"Saved {analysis.english_name} to {algo_dir}")

def is_paper_processed(title: str) -> bool:
    """Check if a paper with this title has already been processed."""
    # This is a bit tricky because we don't know the english_name yet.
    # We can search all metadata.json files for the chinese_name.
    for root, dirs, files in os.walk(STRUCTURED_DIR):
        if "metadata.json" in files:
            try:
                with open(os.path.join(root, "metadata.json"), "r", encoding="utf-8") as f:
                    meta = json.load(f)
                    if meta.get("chinese_name") == title:
                        return True
            except:
                pass
    return False

def main():
    llm = get_llm()
    
    # Get all PDF files
    pdf_files = []
    for root, dirs, files in os.walk(PDF_DIR):
        for file in files:
            if file.endswith(".pdf") and any(str(year) in file for year in YEARS):
                pdf_files.append(os.path.join(root, file))
    
    print(f"Found {len(pdf_files)} PDF files.")
    
    for pdf_path in pdf_files:
        print(f"Processing {os.path.basename(pdf_path)}...")
        
        # 1. Extract TOC
        toc = extract_toc(pdf_path, llm)
        print(f"Found {len(toc)} papers in TOC.")
        
        # 2. Find pages and process
        for i, paper in enumerate(toc):
            print(f"  Processing {paper['title']} (Page Hint: {paper.get('page_number')})...")
            
            if is_paper_processed(paper['title']):
                print(f"    Skipping {paper['title']} (already processed).")
                continue
            
            page_hint = paper.get('page_number', -1)
            if isinstance(page_hint, str) and page_hint.isdigit():
                page_hint = int(page_hint)
            elif not isinstance(page_hint, int):
                page_hint = -1
            start_page = find_start_page(pdf_path, paper['title'], page_hint)
            if start_page == -1:
                print(f"    Could not find start page for {paper['title']}, skipping.")
                continue
                
            # Determine end page (start of next paper or end of doc)
            # We need to find the start page of the next paper in the TOC
            next_start_page = len(fitz.open(pdf_path)) # Default to end
            
            # Look ahead in TOC for the next valid start page
            for j in range(i + 1, len(toc)):
                next_hint = toc[j].get('page_number', -1)
                if isinstance(next_hint, str) and next_hint.isdigit():
                    next_hint = int(next_hint)
                elif not isinstance(next_hint, int):
                    next_hint = -1
                    
                next_p = find_start_page(pdf_path, toc[j]['title'], next_hint)
                if next_p != -1 and next_p > start_page:
                    next_start_page = next_p
                    break
            
            # 3. Analyze
            analysis = process_paper(pdf_path, start_page, next_start_page, paper, llm)
            
            # 4. Save
            if analysis:
                save_to_kb(analysis, paper)
                
if __name__ == "__main__":
    main()
