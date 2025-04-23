# delaunay_visualizer.py

import cv2
import numpy as np
from scipy.spatial import Delaunay
from CavityDetection import DetecteCavity

img = cv2.imread('/home/hhg10/CableToCavityAllocation/Resources/Connectors/12T16+25T20.png') 
original = img.copy()

cavities = DetecteCavity(img)
centers = [pt for pt, _ in cavities]

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
