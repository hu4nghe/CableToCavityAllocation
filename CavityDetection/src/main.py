from CavityDetection import DetecteCavity
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
            for i, (Pos, r) in enumerate(Cavities, 1):
                print(f"  Circle {i}: Center({Pos[0]},{Pos[1]}), Radius {r}")

if __name__ == "__main__":
    iDir = "/home/hhg10/project/CavityDetection/Connectors"
    oDir = "/home/hhg10/project/CavityDetection/DetectionResults"
    
    CallDetecteFunction(iDir, oDir)
    print("Processing complete. Results saved to:", oDir)