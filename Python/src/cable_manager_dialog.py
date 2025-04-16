import os
from PyQt6.QtWidgets import QDialog, QTreeWidgetItem, QInputDialog, QMenu, QMessageBox
from PyQt6.QtCore import Qt
from PyQt6.uic import loadUi

class CableManagerDialog(QDialog):
    def __init__(self, allocator, parent=None):
        super().__init__(parent)

        ui_path = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "UI", "cable_manager.ui"))
        loadUi(ui_path, self)

        self.allocator = allocator
        self.wire_counter = 1
        self.cables = {}
        
        self.cableTreeWidget.customContextMenuRequested.connect(self.open_context_menu)
        self.buttonBox.accepted.connect(self.submit_cable)
        self.buttonBox.rejected.connect(self.reject)
        
    def open_context_menu(self, pos):
        item = self.cableTreeWidget.itemAt(pos)
        menu = QMenu()

        if item is None:
            menu.addAction("Add Cable", self.add_cable)
        elif item.parent() is None:
            menu.addAction("Add Wire", lambda: self.add_wire(item))
        menu.exec(self.cableTreeWidget.viewport().mapToGlobal(pos))

    def add_cable(self):
        cable_name, ok = QInputDialog.getText(
            self, "Add Cable", "Enter cable name:")
        if ok and cable_name:
            if cable_name in self.cables:
                QMessageBox.warning(self, "Error", "Cable name already exists!")
                return
            self.cables[cable_name] = []
            QTreeWidgetItem(self.cableTreeWidget, [cable_name])
            self.cable_id = len(self.cables)

    def add_wire(self, cable_item):
        cable_name = cable_item.text(0)
        gauge, ok = QInputDialog.getItem(
            self, "Add Wire", "Select gauge:",
            ["8", "10", "12", "14", "16", "18", "20", "22"], editable=False
        )
        if ok and gauge:
            wire_id = self.wire_counter
            self.wire_counter += 1
            self.cables[cable_name].append((wire_id, int(gauge)))
            cable_item.addChild(QTreeWidgetItem([f"Wire{wire_id}: gauge {gauge}"]))

    def submit_cable(self):
        print("Saved cables:", self.cables)
        self.accept()
