import sys
import os
import cv2
from PyQt6.QtWidgets import QApplication, QMainWindow, QFileDialog, QMessageBox, QTreeWidgetItem
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
        self.potentialSolutionTreeWidget.customContextMenuRequested.connect(self.show_solution_context_menu)
        
        self.pins       = []
        self.allocations = []
        self.original_image = None
        self.current_preview_circles = []  
        self.confirmed_pins = set() 
        
    def open_image(self):
        file_name, _ = QFileDialog.getOpenFileName(self, "Choose a connector image.", "", "PNG Files (*.png)")
        if file_name:
            try:
                img = cv2.imread(file_name)
                self.original_image, self.pins = cavity_detection.detect_pin(img)
        
                self.cavity_id_to_index = {len(self.pins) - i + 1: i - 1 for i in range(1, len(self.pins) + 1)}
                cpp_pins_input_data = [(len(self.pins) - i + 1, gauge, x, y) for i, ((x, y), gauge) in enumerate(self.pins, start=1)]

                # Convert to Qt image format
                rgb_image = cv2.cvtColor(self.original_image, cv2.COLOR_BGR2RGB)
                h, w, ch = rgb_image.shape
                bytes_per_line = ch * w
                qt_image = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format.Format_RGB888)

                self.imageLabel.setPixmap(QPixmap.fromImage(qt_image))
                self.imageLabel.adjustSize() 
                self.allocator = cable_allocator.CableAllocator(cpp_pins_input_data )
                

                
            except Exception as e:
                QMessageBox.critical(self, "Error", f"Failed to process image: {e}")
        

    def open_cable_manager(self):
        self.dialog = cable_manager.CableManagerDialog(self.allocator)
        if(self.dialog.exec()):
            for(cable_id, wires) in self.dialog.cables.items():
                self.allocations = self.allocator.add_cable(self.dialog.cable_id, wires)
            self.potentialSolutionTreeWidget.clear()
            #print(self.allocations)
            for idx, allocation in enumerate(self.allocations):
                top_item = QTreeWidgetItem([f"Solution {idx+1}"])
                for wire_id, cavity_id in allocation.items():
                    child = QTreeWidgetItem([f"Wire {wire_id} → Cavity {cavity_id}"])
                    top_item.addChild(child)
                top_item.setExpanded(True)
                self.potentialSolutionTreeWidget.addTopLevelItem(top_item)
        
        
        
    def show_solution_context_menu(self, pos):
        from PyQt6.QtWidgets import QMenu

        item = self.potentialSolutionTreeWidget.itemAt(pos)
        if not item or item.parent():
            return  

        index = self.potentialSolutionTreeWidget.indexOfTopLevelItem(item)

        menu = QMenu()
        preview_action = menu.addAction("Preview")
        confirm_action = menu.addAction("Confirm")

        action = menu.exec(self.potentialSolutionTreeWidget.viewport().mapToGlobal(pos))

        if action == preview_action:
            self.preview_solution(index)
        elif action == confirm_action:
            self.confirm_solution(index)

    def draw_pins_overlay(self, preview_indexes=None):
        image = self.original_image.copy()

        for idx, ((x, y), _) in enumerate(self.pins):
            if idx not in self.confirmed_pins:
                cv2.circle(image, (int(x), int(y)), 10, (0, 255, 0), 2)

        for idx in self.confirmed_pins:
            x, y = self.pins[idx][0]
            cv2.circle(image, (int(x), int(y)), 10, (0, 0, 255), -1)

        if preview_indexes:
            for idx in preview_indexes:
                x, y = self.pins[idx][0]
                cv2.circle(image, (int(x), int(y)), 10, (0, 255, 255), 2)

        rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        h, w, ch = rgb_image.shape
        qt_image = QImage(rgb_image.data, w, h, ch * w, QImage.Format.Format_RGB888)
        self.imageLabel.setPixmap(QPixmap.fromImage(qt_image))


    def preview_solution(self, index):
        solution = self.allocations[index]
        preview_indexes = [self.cavity_id_to_index[cavity_id] for cavity_id in solution.values()]
        self.draw_pins_overlay(preview_indexes)

    def confirm_solution(self, index):
        solution = self.allocations[index]
        for cavity_id in solution.values():
            self.confirmed_pins.add(self.cavity_id_to_index[cavity_id])
        self.draw_pins_overlay()


        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
