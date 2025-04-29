import cv2
import numpy as np

from cavity_detection import detect_pin

color_map = {}
avoid_colors = [
    (24, 98, 167),  
    (0, 0, 0),     
    (255, 0, 0),    
]
image_path = "/home/hhg10/CableToCavityAllocation/Resources/Connectors/39T22+10T16.png"
original_image = cv2.imread(image_path)
_, pins = detect_pin(original_image)
pins.reverse()   

def get_random_color(min_distance=50):
    while True:
        color = tuple(int(x) for x in np.random.randint(0, 256, 3))
        min_dist = min(np.linalg.norm(np.array(color) - np.array(avoid)) for avoid in avoid_colors)
        if min_dist >= min_distance:
            return color

def visualize_connector(status):
    img = original_image.copy()

    for i, stat in enumerate(status):
        pos, _, r = pins[i]
        if stat == 0:
            continue  
        
        if stat not in color_map:
            color_map[stat] = get_random_color()
        
        color = color_map[stat]
        cv2.circle(img, pos, r+1, color, -1)

    cv2.imshow("Connector Status", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
