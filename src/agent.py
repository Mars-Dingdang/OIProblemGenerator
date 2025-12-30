import os
from langchain_openai import ChatOpenAI
from langchain_core.prompts import ChatPromptTemplate
# Import the custom Gemini wrapper or standard one if available
try:
    from langchain_google_genai import ChatGoogleGenerativeAI
except ImportError:
    ChatGoogleGenerativeAI = None

from src.knowledge_base import KnowledgeBase
from src.generator import ContentGenerator
from src.prompts import IDEATION_PROMPT_TEMPLATE, PROBLEM_SETTING_GUIDELINES

from langchain_core.output_parsers import JsonOutputParser
from pydantic import BaseModel, Field

class ProblemConcept(BaseModel):
    title: str = Field(description="The title of the problem")
    description: str = Field(description="A brief description of the problem story and task")
    input_format: str = Field(description="Description of the input format")
    output_format: str = Field(description="Description of the output format")
    constraints: str = Field(description="Numerical constraints for the input data")
    algorithm: str = Field(description="The core algorithm or data structure required")
    complexity: str = Field(description="Expected time and space complexity")

class OIProblemAgent:
    def __init__(self, model_name: str = "Qwen3-235B-A22B-Thinking-2507"):
        # 初始化 LLM
        print(f"🤖 Initializing Agent with model: {model_name}")
        
        if "gemini" in model_name.lower():
            if ChatGoogleGenerativeAI is None:
                raise ImportError("langchain_google_genai is not installed. Please install it to use Gemini models.")
            
            google_api_key = os.getenv("GOOGLE_API_KEY")
            if not google_api_key:
                raise ValueError("GOOGLE_API_KEY not found in environment variables.")
                
            # Map "gemini-3-pro-preview" to a valid model name if needed, 
            # or assume the user passes the correct string.
            # For now, we use the model_name passed in.
            self.llm = ChatGoogleGenerativeAI(
                model=model_name,
                google_api_key=google_api_key,
                temperature=0.7,
                max_retries=10, # Increase retries for rate limits
                request_timeout=60,
            )
        else:
            self.llm = ChatOpenAI(
                api_key=os.getenv("OPENAI_API_KEY"),
                base_url=os.getenv("OPENAI_BASE_URL"),
                model=model_name,
                temperature=0.7
            )
            
        self.knowledge_base = KnowledgeBase()
        self.generator = ContentGenerator(self.llm)

    def generate_problem(self, difficulty: str, topic: str):
        """
        生成一道完整的 OI 题目
        """
        print(f"🔍 Retrieving knowledge for {topic}...")
        context = self.knowledge_base.retrieve(topic)
        
        print(f"🧠 Ideating problem concept...")
        # 第一步：构思题目核心逻辑
        concept = self._ideate_problem(difficulty, topic, context)
        print(f"💡 Concept: {concept['title']}")

        # 第二步：生成题目描述 (LaTeX)
        print(f"📝 Generating problem statement...")
        statement = self.generator.generate_statement(concept)

        # 第三步：生成标程 (Std C++)
        print(f"💻 Generating standard solution...")
        std_code = self.generator.generate_std(concept)

        # 第四步：生成数据生成器 (Generator C++)
        print(f"⚙️ Generating test case generator...")
        data_gen_code = self.generator.generate_data_generator(concept)

        # 第五步：生成题解 (Editorial LaTeX)
        print(f"📖 Generating editorial...")
        editorial = self.generator.generate_editorial(concept)

        return {
            "title": concept.get("title", "Untitled"),
            "statement": statement,
            "std": std_code,
            "data_generator": data_gen_code,
            "editorial": editorial
        }

    def _ideate_problem(self, difficulty, topic, context) -> dict:
        """
        使用 LLM 构思题目的大致思路
        """
        parser = JsonOutputParser(pydantic_object=ProblemConcept)

        prompt = ChatPromptTemplate.from_template(IDEATION_PROMPT_TEMPLATE)
        
        chain = prompt | self.llm | parser
        
        print("DEBUG: Invoking LLM for ideation...")
        try:
            response = chain.invoke({
                "difficulty": difficulty,
                "topic": topic,
                "context": context,
                "guidelines": PROBLEM_SETTING_GUIDELINES,
                "format_instructions": parser.get_format_instructions()
            })
            print("DEBUG: Ideation successful.")
        except Exception as e:
            print(f"DEBUG: Ideation failed: {e}")
            raise e
        
        return response
