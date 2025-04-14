from CavityDetection import DetecteCavity
from pathlib import Path
import cv2
import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QLabel, QPushButton, 
                           QVBoxLayout, QWidget, QFileDialog)
from PyQt6.QtGui import QImage, QPixmap
from PyQt6.QtCore import Qt

class CavityDetectorGUI(QMainWindow):
    def __init__(self):
        super().__init__()
        self.root_path = Path(__file__).resolve().parent.parent
        self.initUI()
        
    def initUI(self):
        self.setWindowTitle('Cavity Detector')
        self.setGeometry(100, 100, 800, 600)

        # Create central widget and layout
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)

        # Create buttons
        self.select_btn = QPushButton('Select Connector Image', self)
        self.select_btn.clicked.connect(self.select_image)
        layout.addWidget(self.select_btn)

        # Create image display label
        self.image_label = QLabel(self)
        self.image_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(self.image_label)

    def select_image(self):
        file_name, _ = QFileDialog.getOpenFileName(
            self,
            "Select Connector Image",
            str(self.root_path/"Resources"/"Connectors"),
            "Images (*.png *.jpg)"
        )
        
        if file_name:
            # Process image
            img = cv2.imread(file_name)
            result_img, cavities = DetecteCavity(img)
            
            # Save detection results to CSV
            output_csv = self.root_path/"bin"/"cavities.csv"
            output_csv.parent.mkdir(exist_ok=True)
            
            with open(output_csv, 'w') as f:
                for i, (pos, r) in enumerate(cavities, 1):
                    # Determine gauge based on radius
                    if r == 11:
                        gauge = 22
                    elif r == 22 or r == 23:
                        gauge = 16
                    else:
                        print(f"Warning: Unknown radius {r}, skipping cavity")
                        continue
                    
                    f.write(f"{i},{gauge},{pos[0]:.1f},{pos[1]:.1f}\n")
            
            # Display result image
            height, width, channel = result_img.shape
            bytes_per_line = 3 * width
            
            # Convert BGR to RGB for Qt
            rgb_image = cv2.cvtColor(result_img, cv2.COLOR_BGR2RGB)
            qt_image = QImage(rgb_image.data, width, height, 
                            bytes_per_line, QImage.Format.Format_RGB888)
            
            # Scale image to fit window while maintaining aspect ratio
            scaled_pixmap = QPixmap.fromImage(qt_image).scaled(
                self.image_label.size(), 
                Qt.AspectRatioMode.KeepAspectRatio,
                Qt.TransformationMode.SmoothTransformation
            )
            
            self.image_label.setPixmap(scaled_pixmap)
            print(f"Detection results saved to: {output_csv}")

def main():
    app = QApplication(sys.argv)
    gui = CavityDetectorGUI()
    gui.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()