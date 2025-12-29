import os
import glob
from typing import List
from tqdm import tqdm
from langchain_community.document_loaders import PyMuPDFLoader
from langchain_text_splitters import RecursiveCharacterTextSplitter
from langchain_chroma import Chroma
from langchain_huggingface import HuggingFaceEmbeddings
from langchain_core.documents import Document

class KnowledgeBase:
    def __init__(self, persist_directory: str = "./chroma_db"):
        self.persist_directory = persist_directory
        # 使用本地 HuggingFace 模型生成 Embedding，避免消耗 API 额度且速度快
        self.embedding_function = HuggingFaceEmbeddings(model_name="all-MiniLM-L6-v2")
        
        # 初始化向量数据库
        if os.path.exists(persist_directory):
            self.vector_store = Chroma(
                persist_directory=persist_directory,
                embedding_function=self.embedding_function
            )
        else:
            self.vector_store = None

    def retrieve(self, query: str, k: int = 3) -> str:
        """
        根据查询检索相关知识
        """
        if not self.vector_store:
            return "Knowledge base not initialized. Please run with --build_kb first."
            
        print(f"🔍 Searching knowledge base for: {query}")
        results = self.vector_store.similarity_search(query, k=k)
        
        context = "\n\n".join([f"--- Source: {doc.metadata.get('source', 'Unknown')} ---\n{doc.page_content}" for doc in results])
        return context

    def ingest_documents(self, source_dir: str):
        """
        从指定目录读取文档并存入向量数据库
        """
        print(f"📂 Scanning {source_dir} for documents...")
        
        documents = []
        
        # 递归查找所有 PDF 文件
        pdf_files = []
        for root, dirs, files in os.walk(source_dir):
            for file in files:
                if file.lower().endswith(".pdf"):
                    pdf_files.append(os.path.join(root, file))
        
        print(f"📄 Found {len(pdf_files)} PDF files.")
        
        for pdf_path in tqdm(pdf_files, desc="Loading PDFs"):
            try:
                loader = PyMuPDFLoader(pdf_path)
                documents.extend(loader.load())
            except Exception as e:
                print(f"⚠️ Error loading {pdf_path}: {e}")

        if not documents:
            print("❌ No documents found to ingest.")
            return

        print(f"✂️ Splitting {len(documents)} pages into chunks...")
        text_splitter = RecursiveCharacterTextSplitter(
            chunk_size=1000,
            chunk_overlap=200,
            separators=["\n\n", "\n", " ", ""]
        )
        chunks = text_splitter.split_documents(documents)
        
        print(f"💾 Storing {len(chunks)} chunks into ChromaDB...")
        
        # Batch processing to avoid memory issues and show progress
        batch_size = 100
        for i in tqdm(range(0, len(chunks), batch_size), desc="Embedding Batches"):
            batch = chunks[i:i + batch_size]
            if self.vector_store is None:
                self.vector_store = Chroma.from_documents(
                    documents=batch,
                    embedding=self.embedding_function,
                    persist_directory=self.persist_directory
                )
            else:
                self.vector_store.add_documents(batch)
                
        print("✅ Knowledge base built successfully!")
