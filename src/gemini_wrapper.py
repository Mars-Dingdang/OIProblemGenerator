import os
from typing import Any, List, Optional
from langchain_core.callbacks import CallbackManagerForLLMRun
from langchain_core.language_models import BaseChatModel
from langchain_core.messages import BaseMessage, HumanMessage, AIMessage, SystemMessage
from langchain_core.outputs import ChatResult, ChatGeneration
from google import genai
from google.genai import types

class Gemini3ChatModel(BaseChatModel):
    """Custom LangChain wrapper for Gemini 3 Pro using google-genai SDK."""
    
    api_key: str
    model_name: str = "gemini-flash-latest" # Default to Flash Latest
    temperature: float = 0.7
    
    def _generate(
        self,
        messages: List[BaseMessage],
        stop: Optional[List[str]] = None,
        run_manager: Optional[CallbackManagerForLLMRun] = None,
        **kwargs: Any,
    ) -> ChatResult:
        client = genai.Client(api_key=self.api_key)
        
        # Convert LangChain messages to Gemini format
        prompt_content = ""
        for msg in messages:
            if isinstance(msg, HumanMessage):
                prompt_content += f"User: {msg.content}\n"
            elif isinstance(msg, AIMessage):
                prompt_content += f"Model: {msg.content}\n"
            elif isinstance(msg, SystemMessage):
                prompt_content += f"System: {msg.content}\n"
        
        try:
            # Configure thinking if needed (commented out until model supports it fully)
            # config = types.GenerateContentConfig(
            #     thinking_config=types.ThinkingConfig(include_thoughts=True)
            # )
            
            print(f"DEBUG: Calling Gemini API with model {self.model_name}...")
            response = client.models.generate_content(
                model=self.model_name,
                contents=prompt_content,
                # config=config
            )
            print("DEBUG: Gemini API returned.")
            
            text = response.text
            
            return ChatResult(generations=[ChatGeneration(message=AIMessage(content=text))])
            
        except Exception as e:
            raise ValueError(f"Error calling Gemini API: {e}")

    @property
    def _llm_type(self) -> str:
        return "gemini-3-custom"
