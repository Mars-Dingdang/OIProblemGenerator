from langchain_core.language_models import BaseChatModel
from langchain_core.prompts import ChatPromptTemplate
from langchain_core.output_parsers import StrOutputParser

class ContentGenerator:
    def __init__(self, llm: BaseChatModel):
        self.llm = llm

    def _clean_output(self, text: str) -> str:
        """清理 LLM 输出的 Markdown 代码块标记及思考过程"""
        text = text.strip()
        
        # 移除 <think>...</think> 块
        import re
        text = re.sub(r'<think>.*?</think>', '', text, flags=re.DOTALL).strip()

        # 尝试找到代码块的开始和结束
        start_marker = "```"
        end_marker = "```"
        
        start_index = text.find(start_marker)
        if start_index != -1:
            # 找到代码块开始，跳过 ```xxx
            newline_index = text.find("\n", start_index)
            if newline_index != -1:
                content_start = newline_index + 1
            else:
                content_start = start_index + 3
            
            # 找到代码块结束
            end_index = text.rfind(end_marker)
            if end_index > content_start:
                text = text[content_start:end_index]
            else:
                # 只有开始没有结束，或者结束在开始之前（不应该发生），取剩余部分
                text = text[content_start:]
        
        return text.strip()

    def generate_statement(self, concept: dict) -> str:
        """生成 LaTeX 格式的题目描述"""
        prompt = ChatPromptTemplate.from_template(
            """
            You are an expert competitive programming problem setter.
            Generate a COMPLETE, COMPILABLE LaTeX document for the following problem.
            
            Concept:
            Title: {title}
            Description: {description}
            Input Format: {input_format}
            Output Format: {output_format}
            Constraints: {constraints}
            
            Requirements:
            1. **Story & Flavor**: Wrap the problem in an engaging, creative story (e.g., fantasy, sci-fi, or daily life). Do not just state the formal problem immediately. The story should naturally lead to the formal task.
            2. **Difficulty**: This is a high-difficulty problem (Codeforces 2400+). Ensure the tone is appropriate.
            3. **LaTeX Structure**:
               - Use `\\documentclass{{article}}`
               - Use `\\usepackage{{amsmath, amssymb, fullpage}}`
               - Include `\\begin{{document}}` and `\\end{{document}}`
               - Use `\\section*{{Problem Description}}`, `\\section*{{Input}}`, `\\section*{{Output}}`, `\\section*{{Constraints}}`, `\\section*{{Sample}}`
            4. **Sample**: Provide a valid sample input and output.
            
            Output ONLY the LaTeX code. Do not output any conversational text before or after.
            """
        )
        chain = prompt | self.llm | StrOutputParser()
        return self._clean_output(chain.invoke(concept))

    def generate_std(self, concept: dict) -> str:
        """生成 C++ 标程"""
        prompt = ChatPromptTemplate.from_template(
            """
            Write a standard solution (std) in C++ for the following problem.
            The solution must be correct, efficient, and well-commented.
            
            Problem Title: {title}
            Algorithm: {algorithm}
            Complexity: {complexity}
            Constraints: {constraints}
            Description: {description}
            
            Requirements:
            1. **Complete Code**: Include all necessary headers (`#include <bits/stdc++.h>`).
            2. **Fast I/O**: Use `cin.tie(0); ios::sync_with_stdio(0);`.
            3. **Style**: Use standard competitive programming style.
            4. **Correctness**: This is a hard problem. Ensure the logic handles edge cases and parity constraints correctly.
            
            Output ONLY the C++ code. Do not output any conversational text.
            """
        )
        chain = prompt | self.llm | StrOutputParser()
        return self._clean_output(chain.invoke(concept))

    def generate_data_generator(self, concept: dict) -> str:
        """生成 C++ 数据生成器"""
        prompt = ChatPromptTemplate.from_template(
            """
            Write a C++ test case generator for the following problem.
            The generator should output a SINGLE valid test case to stdout.
            
            Problem Title: {title}
            Input Format: {input_format}
            Constraints: {constraints}
            
            Requirements:
            1. **Complete Code**: Include headers.
            2. **Randomness**: Use `mt19937` with `chrono` seed.
            3. **Validity**: Ensure generated graph/data satisfies the constraints (e.g., connected if required, no self-loops if required).
            
            Output ONLY the C++ code.
            """
        )
        chain = prompt | self.llm | StrOutputParser()
        return self._clean_output(chain.invoke(concept))

    def generate_editorial(self, concept: dict) -> str:
        """生成 LaTeX 格式的题解"""
        prompt = ChatPromptTemplate.from_template(
            """
            Generate a COMPLETE, COMPILABLE LaTeX editorial for the following problem.
            
            Problem Title: {title}
            Algorithm: {algorithm}
            Complexity: {complexity}
            
            Requirements:
            1. **Structure**:
               - `\\documentclass{{article}}`
               - `\\usepackage{{amsmath, amssymb, fullpage}}`
               - `\\begin{{document}}` ... `\\end{{document}}`
               - Title: "Editorial: {title}"
            2. **Content**:
               - **Core Observation**: Explain the key insight required to solve the problem.
               - **Solution**: Step-by-step derivation.
               - **Complexity**: Detailed analysis.
            
            Output ONLY the LaTeX code.
            """
        )
        chain = prompt | self.llm | StrOutputParser()
        return self._clean_output(chain.invoke(concept))
