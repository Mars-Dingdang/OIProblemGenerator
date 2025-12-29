import os
from dotenv import load_dotenv
from langchain_google_genai import ChatGoogleGenerativeAI

load_dotenv()

print(f"Key: {os.getenv('OPENAI_API_KEY')[:5]}...")

try:
    llm = ChatGoogleGenerativeAI(
        model="gemini-1.5-flash", # Try standard model
        google_api_key=os.getenv("OPENAI_API_KEY")
    )
    print("Invoking LLM...")
    response = llm.invoke("Hello")
    print(f"Response: {response.content}")
except Exception as e:
    print(f"Error: {e}")
