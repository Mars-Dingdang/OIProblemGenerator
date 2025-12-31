import fitz  # PyMuPDF
import os

pdf_path = "knowledge_base/NOIpaper-main/国家集训队2013论文集.pdf"

if not os.path.exists(pdf_path):
    print(f"File not found: {pdf_path}")
else:
    try:
        doc = fitz.open(pdf_path)
        # Print text of first 10 pages
        for i in range(10):
            page = doc.load_page(i)
            print(f"--- Page {i+1} ---")
            print(page.get_text())
            
    except Exception as e:
        print(f"Error: {e}")
