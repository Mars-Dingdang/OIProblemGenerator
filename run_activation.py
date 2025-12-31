import sys
import os

# Add src to path so we can import modules from it
sys.path.append(os.path.join(os.getcwd(), "src"))

from src.activate_noi_papers import main

if __name__ == "__main__":
    print("Starting NOI Paper Activation...")
    main()
