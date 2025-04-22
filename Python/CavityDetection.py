import cv2
import numpy as np

def DetecteCavity(Img) :
    HSV = cv2.cvtColor(Img, cv2.COLOR_BGR2HSV) # Convert to HSV for Mask 

    LowerBlack = np.array([0, 0, 0])
    UpperBlack = np.array([180, 255, 30])  # Only dark Area
    Mask = cv2.inRange(HSV, LowerBlack, UpperBlack)

    # Denoising
    Ker = np.ones((3,3), np.uint8)
    Mask = cv2.morphologyEx(Mask, cv2.MORPH_OPEN, Ker, iterations=2)

    # Find Contours
    Contours, _ = cv2.findContours(Mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)


    Cavities = []
    count = 0 ;
    for DetectedCnt in Contours:
       Area = cv2.contourArea(DetectedCnt)
       (x,y), R = cv2.minEnclosingCircle(DetectedCnt)
    
       # Calculate circularity
       Perimeter = cv2.arcLength(DetectedCnt, True)
       if Perimeter == 0:
           continue
       Circularity = 4 * np.pi * Area / (Perimeter * Perimeter)
    

       if (R > 10 and               
           R < 40 and              
           Circularity > 0.7 and        
           Area > 30): 
        
        count += 1;    
           
        Centre = (int(x), int(y))
        R = int(R)
        Cavities.append((Centre, R))
    #draw   
    for i, (Pos, r) in enumerate(Cavities, 0):
        cv2.circle(Img, Pos, r, (0,255,0), 2)
        text_pos = (Pos[0], Pos[1])
        cv2.putText(Img, str(len(Cavities) - i), text_pos, 
        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,0,0), 2)
    
    return Cavities
        