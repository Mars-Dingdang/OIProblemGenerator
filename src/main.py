import os
import sys
import argparse
from dotenv import load_dotenv

# 将项目根目录添加到 sys.path
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from src.agent import OIProblemAgent
from src.utils import save_file, compile_cpp, compile_latex, run_executable

# 加载环境变量
load_dotenv()

def main():
    parser = argparse.ArgumentParser(description="OI Problem Generator Agent")
    parser.add_argument("--difficulty", type=str, default="Codeforces 1500", help="Difficulty level (e.g., 'Codeforces 1500', 'Luogu Blue')")
    parser.add_argument("--topic", type=str, default="Dynamic Programming", help="Problem topic (e.g., 'Segment Tree', 'Network Flow')")
    parser.add_argument("--output_dir", type=str, default="./problems", help="Directory to save generated problems")
    parser.add_argument("--build_kb", action="store_true", help="Build/Rebuild the knowledge base from ./knowledge_base folder")
    
    args = parser.parse_args()

    if args.build_kb:
        print("🏗️ Building Knowledge Base...")
        # 临时初始化一个 KnowledgeBase 对象来构建
        from src.knowledge_base import KnowledgeBase
        kb = KnowledgeBase()
        kb.ingest_documents("./knowledge_base")
        print("✅ Knowledge Base build complete. You can now generate problems.")
        return

    print(f"🚀 Starting OI Problem Generator...")
    print(f"🎯 Target Difficulty: {args.difficulty}")
    print(f"📚 Topic: {args.topic}")

    agent = OIProblemAgent()
    
    # 运行 Agent 生成题目
    problem_data = agent.generate_problem(
        difficulty=args.difficulty,
        topic=args.topic
    )

    if problem_data:
        title_slug = problem_data.get('title', 'Untitled').replace(" ", "_").lower()
        base_path = os.path.join(args.output_dir, title_slug)
        
        print(f"✅ Problem generated successfully: {problem_data.get('title', 'Untitled')}")
        
        # 保存文件
        save_file(problem_data['statement'], os.path.join(base_path, "statement.tex"))
        save_file(problem_data['editorial'], os.path.join(base_path, "editorial.tex"))
        
        std_path = os.path.join(base_path, "std.cpp")
        save_file(problem_data['std'], std_path)
        
        gen_path = os.path.join(base_path, "generator.cpp")
        save_file(problem_data['data_generator'], gen_path)
        
        print(f"📂 Files saved to {base_path}")
        
        # 1. 编译 LaTeX 生成 PDF
        print("📄 Compiling LaTeX documents...")
        if compile_latex(os.path.join(base_path, "statement.tex")):
            print("✅ Statement PDF generated.")
        if compile_latex(os.path.join(base_path, "editorial.tex")):
            print("✅ Editorial PDF generated.")

        # 2. 验证并编译 C++ 代码
        print("🔨 Verifying and Compiling C++ code...")
        std_compiled = compile_cpp(std_path)
        gen_compiled = compile_cpp(gen_path)
        
        if std_compiled:
            print("✅ Standard solution compiled successfully.")
        else:
            print("❌ Standard solution compilation failed.")
            
        if gen_compiled:
            print("✅ Data generator compiled successfully.")
        else:
            print("❌ Data generator compilation failed.")

        # 3. 生成数据并测试 Std
        if std_compiled and gen_compiled:
            print("🧪 Generating test cases and running Std...")
            data_dir = os.path.join(base_path, "data")
            os.makedirs(data_dir, exist_ok=True)
            
            std_exe = std_path.replace(".cpp", ".exe")
            gen_exe = gen_path.replace(".cpp", ".exe")
            
            # 生成 5 组数据
            for i in range(1, 6):
                print(f"   Generating case {i}...")
                # 运行 generator 生成输入
                # 注意：目前的 generator 是一次性生成一个随机数据，我们运行多次
                input_data = run_executable(gen_exe)
                
                if input_data:
                    input_file = os.path.join(data_dir, f"{i}.in")
                    output_file = os.path.join(data_dir, f"{i}.out")
                    
                    with open(input_file, "w", encoding="utf-8") as f:
                        f.write(input_data)
                        
                    # 运行 std 生成输出
                    output_data = run_executable(std_exe, input_str=input_data)
                    if output_data is not None:
                        with open(output_file, "w", encoding="utf-8") as f:
                            f.write(output_data)
                    else:
                        print(f"   ❌ Failed to run Std for case {i}")
                else:
                    print(f"   ❌ Failed to generate input for case {i}")
            
            print(f"✅ Test cases generated in {data_dir}")
            
    else:
        print(f"❌ Failed to generate problem.")

if __name__ == "__main__":
    main()
