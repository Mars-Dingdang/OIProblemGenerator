import os
import subprocess
import shutil

def save_file(content: str, filepath: str):
    """保存内容到文件，自动创建目录"""
    os.makedirs(os.path.dirname(filepath), exist_ok=True)
    with open(filepath, "w", encoding="utf-8") as f:
        f.write(content)

def compile_cpp(filepath: str) -> bool:
    """编译 C++ 文件"""
    output_exe = filepath.replace(".cpp", ".exe")
    try:
        # 使用 g++ 编译，假设 g++ 在 PATH 中
        result = subprocess.run(
            ["g++", filepath, "-o", output_exe, "-O2", "-std=c++17"],
            capture_output=True,
            text=True
        )
        if result.returncode == 0:
            return True
        else:
            print(f"Compilation failed for {filepath}:\n{result.stderr}")
            return False
    except FileNotFoundError:
        print("g++ not found. Please ensure MinGW or similar is installed and in PATH.")
        return False
    except Exception as e:
        print(f"Error compiling {filepath}: {e}")
        return False

def compile_latex(filepath: str) -> bool:
    """编译 LaTeX 文件生成 PDF"""
    try:
        # 检查 pdflatex 是否存在
        if not shutil.which("pdflatex"):
            print("⚠️ pdflatex not found. Skipping PDF generation.")
            return False

        work_dir = os.path.dirname(filepath)
        filename = os.path.basename(filepath)
        
        # 运行 pdflatex
        # -interaction=nonstopmode 防止报错时卡住
        result = subprocess.run(
            ["pdflatex", "-interaction=nonstopmode", filename],
            cwd=work_dir,
            capture_output=True,
            text=True
        )
        
        if result.returncode == 0:
            return True
        else:
            # LaTeX 经常会有警告也返回非0，或者有错误但仍生成PDF
            # 检查 PDF 是否生成
            pdf_path = filepath.replace(".tex", ".pdf")
            if os.path.exists(pdf_path):
                print(f"⚠️ LaTeX compilation had issues but PDF was generated.")
                return True
            print(f"❌ LaTeX compilation failed for {filepath}:\n{result.stdout[:500]}...") # 只打印前500字符
            return False
    except Exception as e:
        print(f"Error compiling LaTeX {filepath}: {e}")
        return False

def run_executable(exe_path: str, args: list = None, input_str: str = None, timeout: int = 5) -> str:
    """运行可执行文件并返回输出"""
    try:
        cmd = [exe_path]
        if args:
            cmd.extend(args)
            
        result = subprocess.run(
            cmd,
            input=input_str,
            capture_output=True,
            text=True,
            timeout=timeout
        )
        if result.returncode != 0:
            print(f"⚠️ Execution failed for {exe_path}: {result.stderr}")
            return None
        return result.stdout
    except subprocess.TimeoutExpired:
        print(f"❌ Execution timed out for {exe_path}")
        return None
    except Exception as e:
        print(f"Error running {exe_path}: {e}")
        return None
