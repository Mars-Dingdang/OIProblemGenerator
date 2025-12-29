import os
from dotenv import load_dotenv
from src.gemini_wrapper import Gemini3ChatModel

load_dotenv()

from langchain_core.prompts import ChatPromptTemplate
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

def test():
    llm = Gemini3ChatModel(
        api_key=os.getenv("OPENAI_API_KEY"),
        model_name="gemini-2.5-flash",
        temperature=0.7
    )
    
    parser = JsonOutputParser(pydantic_object=ProblemConcept)
    
    prompt = ChatPromptTemplate.from_template(
        """
        You are an expert competitive programming problem setter (Codeforces Grandmaster level).
        Your task is to design a NOVEL, HIGH-QUALITY OI problem based on the following requirements:
        
        Difficulty: {difficulty} (Target: Codeforces 2400+)
        Topic: {topic}
        
        Relevant Knowledge/Context:
        {context}
        
        Requirements:
        1. **High Thinking Difficulty**: The problem should NOT be a standard template application. It must require deep insight, ad-hoc reasoning, or a clever transformation.
        2. **Novelty**: Avoid common clichés. Combine the topic with interesting constraints or a secondary mechanic (e.g., parity, bitmasks, game theory).
        3. **Solvability**: Ensure the problem is solvable within standard time limits (1-2s) using an efficient algorithm (not exponential).
        4. **Story Potential**: Design the core logic such that it can be wrapped in an interesting story later (e.g., graph nodes as cities, edges as roads with specific rules).
        
        Please provide a high-level summary of the problem.
        
        {format_instructions}
        """
    )
    
    # chain = prompt | llm | parser
    chain = prompt | llm
    
    print("Invoking chain...")
    try:
        response = chain.invoke({
            "difficulty": "Codeforces 2400",
            "topic": "Shortest Path with Parity Constraints (Simple Path)",
            "context": "Some context about BFS and Dijkstra...",
            "format_instructions": "Return JSON" # parser.get_format_instructions()
        })
        print("Response:", response.content)
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    test()
