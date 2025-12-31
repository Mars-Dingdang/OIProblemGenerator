import os
import shutil
import sys

# Add src to path
sys.path.append(os.path.join(os.getcwd(), "src"))

from src.knowledge_base import KnowledgeBase

def rebuild_kb():
    persist_dir = "./chroma_db"
    source_dir = "./knowledge_base"
    
    # 1. Clear existing DB
    if os.path.exists(persist_dir):
        print(f"🗑️ Removing existing database at {persist_dir}...")
        try:
            shutil.rmtree(persist_dir)
        except Exception as e:
            print(f"⚠️ Could not remove directory: {e}")
            # On Windows, sometimes file locking prevents deletion. 
            # We might need to just proceed and hope Chroma handles it or fail.
            return

    # 2. Initialize KB
    print("🆕 Initializing Knowledge Base...")
    kb = KnowledgeBase(persist_directory=persist_dir)
    
    # 3. Ingest Documents
    print(f"🚀 Starting ingestion from {source_dir}...")
    kb.ingest_documents(source_dir)
    
    print("✨ Knowledge Base Rebuild Complete!")

if __name__ == "__main__":
    rebuild_kb()
