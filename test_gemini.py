import os
from dotenv import load_dotenv
from src.gemini_wrapper import Gemini3ChatModel
from langchain_core.messages import HumanMessage

load_dotenv()

def test():
    print("Testing Gemini Wrapper...")
    llm = Gemini3ChatModel(
        api_key=os.getenv("OPENAI_API_KEY"),
        model_name="gemini-flash-latest",
        temperature=0.7
    )
    
    messages = [HumanMessage(content="Hello, say 'Gemini is working' if you can hear me.")]
    
    try:
        response = llm.invoke(messages)
        print("Response:", response.content)
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    test()
