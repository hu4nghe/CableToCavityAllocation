import os
from PyQt6.QtWidgets import QDialog, QTreeWidgetItem, QInputDialog, QMenu
from PyQt6.QtCore import Qt
from PyQt6.uic import loadUi

class CableManagerDialog(QDialog):
    def __init__(self, allocator, parent=None):
        super().__init__(parent)

        ui_path = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "UI", "cable_manager.ui"))
        loadUi(ui_path, self)

        self.allocator = allocator
        self.cable_id = 1
        self.cable_item = QTreeWidgetItem([f"Cable{self.cable_id}"])
        self.cableTreeWidget.addTopLevelItem(self.cable_item)
        self.wire_counter = 1
        self.wires = []  # list of (wire_id, gauge)

        self.cableTreeWidget.setContextMenuPolicy(Qt.ContextMenuPolicy.CustomContextMenu)
        self.cableTreeWidget.customContextMenuRequested.connect(self.open_context_menu)

        self.buttonBox.accepted.connect(self.submit_cable)
        self.buttonBox.rejected.connect(self.reject)

    def open_context_menu(self, pos):
        item = self.cableTreeWidget.itemAt(pos)
        if item == self.cable_item:
            menu = QMenu()
            menu.addAction("Add Wire", self.add_wire)
            menu.exec(self.cableTreeWidget.viewport().mapToGlobal(pos))

    def add_wire(self):
        gauge, ok = QInputDialog.getInt(self, "Add Wire", "Enter gauge size:")
        if ok:
            wire_id = self.wire_counter
            self.wires.append((wire_id, gauge))
            wire_item = QTreeWidgetItem([f"Wire{wire_id}: gauge {gauge}"])
            self.cable_item.addChild(wire_item)
            self.wire_counter += 1

    def submit_cable(self):
        self.accept()
