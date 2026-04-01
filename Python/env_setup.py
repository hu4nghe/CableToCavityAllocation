import sys
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
VENV = ROOT / "Python" / "DSLyon"

def run(cmd):
    print(">", " ".join(cmd))
    subprocess.check_call(cmd)

def main():
    python = sys.executable

    if not VENV.exists():
        run([python, "-m", "venv", str(VENV)])

    pip = VENV / ("Scripts/pip.exe" if sys.platform == "win32" else "bin/pip")

    run([str(pip), "install", "--upgrade", "pip"])
    run([str(pip), "install", "-r", str(ROOT / "Python" / "requirements.txt")])

    print("\n✓ Python environment ready")
    print(f"  Python: {VENV}")

if __name__ == "__main__":
    main()
