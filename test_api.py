import os
from dotenv import load_dotenv
from langchain_openai import ChatOpenAI

load_dotenv()

print(f"Base URL: {os.getenv('OPENAI_API_BASE')}")
print(f"Key: {os.getenv('OPENAI_API_KEY')[:5]}...")

try:
    llm = ChatOpenAI(
        model="DeepSeek-V3.2-Thinking",
        temperature=0.7,
        base_url=os.getenv("OPENAI_API_BASE"),
        api_key=os.getenv("OPENAI_API_KEY")
    )
    print("Invoking LLM...")
    response = llm.invoke("Hello, are you working?")
    print(f"Response: {response.content}")
except Exception as e:
    print(f"Error: {e}")
