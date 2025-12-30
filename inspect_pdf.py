import fitz  # PyMuPDF

pdf_path = "knowledge_base/OI-wiki.pdf"

try:
    doc = fitz.open(pdf_path)
    toc = doc.get_toc()
    
    print(f"Total TOC entries: {len(toc)}")
    for level, title, page in toc[100:200]:  # Print entries 100-200
        print(f"{'  ' * (level - 1)}- {title} (Page {page})")
        
except Exception as e:
    print(f"Error: {e}")
