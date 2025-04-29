# visualizer.py
import cv2
import numpy as np

from Python.src.cavity_detection import detect_pin

image_path = "39T22+10T16.png"
original_image = cv2.imread(image_path)
_, pins = detect_pin(original_image)
cavity_positions = [pos for (pos, gauge) in pins]  
def visualize_connector(status):
    img = original_image.copy()

    for i, stat in enumerate(status):
        pos = cavity_positions[i]
        if stat == 0:
            continue  
        
        cv2.circle(img, pos, 10, (0, 0, 255), 2)
        cv2.putText(img, f"C{stat}", (pos[0]+5, pos[1]), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,0,255), 1)

    cv2.imshow("Connector Status", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
