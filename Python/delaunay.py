import cv2
import numpy as np
from scipy.spatial import Delaunay
from src.cavity_detection import detect_pin

img = cv2.imread('/home/hhg10/CableToCavityAllocation/Resources/Connectors/78T22.png') 
original = img.copy()

detectedImg,cavities = detect_pin(img)
centers = [pt for pt, _ in cavities]
cv2.imshow("DetectedImg", detectedImg)
cv2.waitKey(0)
for idx, ((x, y), value) in enumerate(cavities, 0):
    print(f"cavities.emplace_back({len(cavities) - idx}, {value}, {x}, {y});")

points = np.array(centers)
tri = Delaunay(points)

for triangle in tri.simplices:
    pts = points[triangle]
    cv2.line(img, tuple(pts[0]), tuple(pts[1]), (0, 0, 255), 1)
    cv2.line(img, tuple(pts[1]), tuple(pts[2]), (0, 0, 255), 1)
    cv2.line(img, tuple(pts[2]), tuple(pts[0]), (0, 0, 255), 1)

cv2.imshow("Delaunay Triangulation", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
