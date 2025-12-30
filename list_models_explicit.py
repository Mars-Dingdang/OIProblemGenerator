import os
import requests

api_key = "sk-fHNEKsxvzI640DmFafNafw"
base_url = "https://llmapi.paratera.com/v1"

print(f"Checking models at {base_url}...")

try:
    response = requests.get(
        f"{base_url}/models",
        headers={"Authorization": f"Bearer {api_key}"}
    )
    if response.status_code == 200:
        models = response.json()
        print("Available models:")
        for m in models.get('data', []):
            mid = m['id']
            if "deepseek" in mid.lower() or "qwen" in mid.lower():
                print(f" - {mid}")
    else:
        print(f"Error: {response.status_code} {response.text}")
except Exception as e:
    print(f"Exception: {e}")
