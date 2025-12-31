from pypdf import PdfReader

reader = PdfReader("knowledge_base/NOIpaper-main/国家集训队2013论文集.pdf")
page = reader.pages[4] # Page 5 (0-indexed)
print(page.extract_text())
