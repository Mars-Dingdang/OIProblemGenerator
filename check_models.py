import os
from openai import OpenAI
from dotenv import load_dotenv

load_dotenv()

def list_models():
    client = OpenAI(
        api_key=os.getenv("OPENAI_API_KEY"),
        base_url=os.getenv("OPENAI_BASE_URL")
    )
    try:
        models = client.models.list()
        for model in models.data:
            print(model.id)
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    list_models()