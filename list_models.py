import os
from dotenv import load_dotenv
from google import genai

load_dotenv()

def list_models():
    client = genai.Client(api_key=os.getenv("OPENAI_API_KEY"))
    try:
        # The SDK might have a different way to list models.
        # Let's try client.models.list() if it exists, or check documentation (by guessing).
        # Based on typical Google SDKs:
        for model in client.models.list():
            print(f"Model: {model.name}")
            # print(f"  Display Name: {model.display_name}")
    except Exception as e:
        print(f"Error listing models: {e}")

if __name__ == "__main__":
    list_models()
