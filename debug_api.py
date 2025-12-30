import os
import requests
from dotenv import load_dotenv

load_dotenv()

api_key = os.getenv("OPENAI_API_KEY")
base_url = os.getenv("OPENAI_BASE_URL")

print(f"Testing API: {base_url}")
print(f"Key: {api_key[:5]}...")

try:
    response = requests.get(
        f"{base_url}/models",
        headers={"Authorization": f"Bearer {api_key}"}
    )
    print(f"Status: {response.status_code}")
    if response.status_code == 200:
        models = response.json()
        print("Available models:")
        for m in models.get('data', []):
            print(f" - {m['id']}")
    else:
        print(f"Error: {response.text}")
except Exception as e:
    print(f"Exception: {e}")

# Try a simple completion
print("\nTesting completion...")
try:
    response = requests.post(
        f"{base_url}/chat/completions",
        headers={
            "Authorization": f"Bearer {api_key}",
            "Content-Type": "application/json"
        },
        json={
            "model": "Qwen3-235B-A22B-Thinking-2507",
            "messages": [{"role": "user", "content": "Hello"}]
        }
    )
    print(f"Completion Status: {response.status_code}")
    print(f"Response: {response.text}")
except Exception as e:
    print(f"Exception: {e}")
