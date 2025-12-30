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

        # 处理结构化数据 (Structured Data)
        structured_dir = os.path.join(source_dir, "structured")
        if os.path.exists(structured_dir):
            print(f"📂 Scanning structured data in {structured_dir}...")
            structured_docs = self._load_structured_data(structured_dir)
            documents.extend(structured_docs)
            print(f"📄 Added {len(structured_docs)} structured documents.")

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

    def _load_structured_data(self, root_dir: str) -> List[Document]:
        """
        加载结构化知识库 (Level 1/2/3)
        """
        docs = []
        import json
        
        for root, dirs, files in os.walk(root_dir):
            # 检查是否存在 metadata.json，如果存在则认为是一个算法文件夹
            if "metadata.json" in files:
                try:
                    with open(os.path.join(root, "metadata.json"), "r", encoding="utf-8") as f:
                        meta = json.load(f)
                    
                    algo_name = meta.get("name", "Unknown Algorithm")
                    
                    # Level 1: Metadata
                    content_l1 = f"Algorithm: {algo_name}\nCategory: {meta.get('category')}\n"
                    content_l1 += f"Complexity: {meta.get('complexity')}\n"
                    content_l1 += f"Scenarios: {', '.join(meta.get('scenarios', []))}\n"
                    content_l1 += f"Extensions: {', '.join(meta.get('extensions', []))}"
                    
                    docs.append(Document(
                        page_content=content_l1,
                        metadata={"source": f"Structured KB - {algo_name} - Metadata", "type": "level1", "algorithm": algo_name}
                    ))
                    
                    # Level 2: Template
                    if "template.cpp" in files:
                        with open(os.path.join(root, "template.cpp"), "r", encoding="utf-8") as f:
                            template_code = f.read()
                        docs.append(Document(
                            page_content=f"Standard Template Code for {algo_name}:\n```cpp\n{template_code}\n```",
                            metadata={"source": f"Structured KB - {algo_name} - Template", "type": "level2", "algorithm": algo_name}
                        ))
                        
                    # Level 3: Tricks
                    if "tricks.md" in files:
                        with open(os.path.join(root, "tricks.md"), "r", encoding="utf-8") as f:
                            tricks_content = f.read()
                        docs.append(Document(
                            page_content=f"Advanced Tricks and Key Observations for {algo_name}:\n{tricks_content}",
                            metadata={"source": f"Structured KB - {algo_name} - Tricks", "type": "level3", "algorithm": algo_name}
                        ))
                        
                except Exception as e:
                    print(f"⚠️ Error loading structured data in {root}: {e}")
                    
        return docs
