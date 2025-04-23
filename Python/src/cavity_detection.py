import cv2
import numpy as np

def detect_pin(Img) :
    HSV = cv2.cvtColor(Img, cv2.COLOR_BGR2HSV) # Convert to HSV for mask 

    lower_black = np.array([0, 0, 0])
    upper_black = np.array([180, 255, 30])  # Only dark area
    mask = cv2.inRange(HSV, lower_black, upper_black)

    # Denoising
    Ker = np.ones((3,3), np.uint8)
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, Ker, iterations=2)

    # Find contours
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)


    pins = []
    count = 0 
    for detected_contours in contours:
       area = cv2.contourArea(detected_contours)
       (x,y), r = cv2.minEnclosingCircle(detected_contours)
    
       # Calculate circularity
       perimetre = cv2.arcLength(detected_contours, True)
       if perimetre == 0:
           continue
       Circularity = 4 * np.pi * area / (perimetre * perimetre)
    

       if (r > 5 and               
           r < 60 and              
           Circularity > 0.5 ): 
        
        count += 1;    
           
        centre = (int(x), int(y))
        r = int(r)       
        
        pins.append((centre, r))
    #draw   
    for i, (Pos, r) in enumerate(pins, 0):
        cv2.circle(Img, Pos, r, (0,255,0), 2)
        text_pos = (Pos[0], Pos[1])
        cv2.putText(Img, str(len(pins) - i), text_pos, 
        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,0,0), 2)
    
    def determine_gauge(r):
            match r:
                case 49:
                    return 8
                case 35:
                    return 10
                case 28:
                    return 12
                case 22:
                    return 16
                case 23:
                    return 16
                case 14:
                    return 20
                case 11:
                    return 22
                case _: 
                    return r
    
    for i in range(len(pins)):
        coords, value = pins[i]
        pins[i] = (coords, determine_gauge(value))
        
    return Img, pins
        