from langchain_huggingface import HuggingFaceEmbeddings
from langchain_chroma import Chroma
from langchain_openai import ChatOpenAI
import os
from dotenv import load_dotenv

load_dotenv()

print("Testing LLM Connection...")
try:
    llm = ChatOpenAI(
        model="deepseek-chat",
        temperature=0.7,
        base_url=os.getenv("OPENAI_API_BASE"),
        api_key=os.getenv("OPENAI_API_KEY")
    )
    print("Invoking LLM...")
    response = llm.invoke("Hello")
    print(f"LLM Response: {response.content}")
except Exception as e:
    print(f"LLM Error: {e}")

print("\nLoading model...")
try:
    embeddings = HuggingFaceEmbeddings(model_name="all-MiniLM-L6-v2")
    # ... rest of the code
    print("Model loaded successfully.")
    
    if os.path.exists("./chroma_db"):
        print("Loading ChromaDB...")
        db = Chroma(persist_directory="./chroma_db", embedding_function=embeddings)
        print("ChromaDB loaded.")
        print("Searching...")
        results = db.similarity_search("test", k=1)
        print(f"Found {len(results)} results.")
    else:
        print("ChromaDB not found.")
        
except Exception as e:
    print(f"Error: {e}")
