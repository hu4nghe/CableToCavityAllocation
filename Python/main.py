from CavityDetection import DetecteCavity
from pathlib import Path
import cv2
import os

def CallDetecteFunction(iDir, oDir):
    os.makedirs(oDir, exist_ok=True)
    for File in os.listdir(iDir):
        if File.lower().endswith('.png'):
            # Read Img
            ImgPath = os.path.join(iDir, File)
            Img = cv2.imread(ImgPath)
            
            ResImg, Cavities = DetecteCavity(Img)
            
            # Save results
            output_path = os.path.join(oDir, f"Cavity_detected_{File}")
            cv2.imwrite(output_path, ResImg)
            
            # Print summary
            print(f"{File}: Detected {len(Cavities)} Cavities")
            for i, (Pos, r) in enumerate(Cavities, 0):
                print(f"cavities.emplace_back({len(Cavities) - i}, {r}, {Pos[0]}.0,{Pos[1]}.0);")

if __name__ == "__main__":
    root_path = Path(__file__).resolve().parent.parent
    iDir = root_path/"Resources"/ "Connectors"
    oDir = root_path/"Resources"/ "DetectionResults"
    
    CallDetecteFunction(iDir, oDir)
    print("Processing complete. Results saved to:", oDir)