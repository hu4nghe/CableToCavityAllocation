import sys
import cv2
import numpy as np
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QFileDialog
from PyQt6.QtGui import QImage, QPixmap
from PyQt6.QtCore import Qt
from cable_allocator_pybind11 import CableAllocator 
import os


def DetecteCavity(Img):
    HSV = cv2.cvtColor(Img, cv2.COLOR_BGR2HSV)
    LowerBlack = np.array([0, 0, 0])
    UpperBlack = np.array([180, 255, 30])
    Mask = cv2.inRange(HSV, LowerBlack, UpperBlack)

    Ker = np.ones((3,3), np.uint8)
    Mask = cv2.morphologyEx(Mask, cv2.MORPH_OPEN, Ker, iterations=2)

    Contours, _ = cv2.findContours(Mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    Cavities = []
    count = 0
    for DetectedCnt in Contours:
        Area = cv2.contourArea(DetectedCnt)
        (x,y), R = cv2.minEnclosingCircle(DetectedCnt)
        Perimeter = cv2.arcLength(DetectedCnt, True)
        if Perimeter == 0:
            continue
        Circularity = 4 * np.pi * Area / (Perimeter * Perimeter)

        if (R > 10 and R < 40 and Circularity > 0.7 and Area > 30):    
            count += 1
            Centre = (int(x), int(y))
            R = int(R)
            Cavities.append(( Centre, R))

    for i, (Pos, r) in enumerate(Cavities, 0):
        cv2.circle(Img, Pos, r, (0,255,0), 2)
        text_pos = (Pos[0], Pos[1])
        cv2.putText(Img, str(len(Cavities) - i), text_pos, 
                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,0,0), 2)

    return Img, Cavities

class CableAllocatorGUI(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Cable Allocator GUI")
        self.setGeometry(100, 100, 800, 600)

        self.layout = QVBoxLayout()

        self.select_button = QPushButton("Select PNG Image")
        self.select_button.clicked.connect(self.select_image)
        self.layout.addWidget(self.select_button)

        self.image_label = QLabel(self)
        self.layout.addWidget(self.image_label)

        self.allocator = None

        self.setLayout(self.layout)

    def select_image(self):
       
        file, _ = QFileDialog.getOpenFileName(self, "Open PNG Image", "", "PNG Files (*.png)")
        if file:
            img = cv2.imread(file)
            processed_img, cavities = DetecteCavity(img)

            
            allocator_input = []
            for i, ((x, y), r) in enumerate(cavities):
                cavity_id = 49 - i
                if (r > 20):
                    gauge = 16
                else: 
                    gauge = 22
        
                allocator_input.append((cavity_id, gauge, float(x), float(y)))

            
            self.allocator = CableAllocator(allocator_input)

            self.display_image(processed_img)

    def display_image(self, img):
        height, width, channel = img.shape
        bytes_per_line = 3 * width
        q_img = QImage(img.data, width, height, bytes_per_line, QImage.Format.Format_BGR888)
        pixmap = QPixmap.fromImage(q_img)
        self.image_label.setPixmap(pixmap)
        self.image_label.setAlignment(Qt.AlignmentFlag.AlignCenter)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = CableAllocatorGUI()
    window.show()
    sys.exit(app.exec())
