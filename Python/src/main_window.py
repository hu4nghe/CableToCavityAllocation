import sys
import os
import cv2
from PyQt6.QtWidgets import QApplication, QMainWindow, QFileDialog, QMessageBox
from PyQt6.QtGui import QPixmap, QImage
from PyQt6.uic import loadUi
import cavity_detection 
import cable_allocator_pybind11 as cable_allocator
import cable_manager_dialog as cable_manager

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        ui_path = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "UI", "main_window.ui"))
        loadUi(ui_path, self) 
        self.actionConnector_Image.triggered.connect(self.open_image)
            
        self.openCableManagerButton.clicked.connect(self.open_cable_manager)
        
        
    def open_image(self):
        file_name, _ = QFileDialog.getOpenFileName(self, "Choose a connector image.", "", "PNG Files (*.png)")
        if file_name:
            try:
                img = cv2.imread(file_name)
                processed_img, pins = cavity_detection.detect_pin(img)

                # Convert to Qt image format
                rgb_image = cv2.cvtColor(processed_img, cv2.COLOR_BGR2RGB)
                h, w, ch = rgb_image.shape
                bytes_per_line = ch * w
                qt_image = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format.Format_RGB888)

                self.imageLabel.setPixmap(QPixmap.fromImage(qt_image))
                self.imageLabel.adjustSize() 
                self.allocator = cable_allocator.CableAllocator(pins)
                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to process image: {e}")
        

    def open_cable_manager(self):
        self.dialog = cable_manager.CableManagerDialog(self.allocator)
        if(self.dialog.exec()):
            res = self.allocator.add_cable(self.dialog.cable_id, self.dialog.wires)
            print(res)
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
