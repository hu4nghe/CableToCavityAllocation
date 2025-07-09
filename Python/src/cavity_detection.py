import cv2
import numpy as np

def detect_pin(Img):
    HSV = cv2.cvtColor(Img, cv2.COLOR_BGR2HSV)

    lower_black = np.array([0, 0, 0])
    upper_black = np.array([180, 255, 30])
    lower_white = np.array([0, 0, 200])
    upper_white = np.array([180, 30, 255])
    #mask = cv2.inRange(HSV, lower_white, upper_white)
    mask = cv2.inRange(HSV, lower_black, upper_black)

    Ker = np.ones((3, 3), np.uint8)
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, Ker, iterations=2)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    pins = []
    for detected_contours in contours:
        area = cv2.contourArea(detected_contours)
        (x, y), r = cv2.minEnclosingCircle(detected_contours)
        perimetre = cv2.arcLength(detected_contours, True)
        if perimetre == 0:
            continue
        Circularity = 4 * np.pi * area / (perimetre * perimetre)
        if (r > 0 and r < 60 and Circularity > 0.5):
            centre = (int(x), int(y))
            r = int(r)
            pins.append((centre, r))

    def sort_pins_by_rows(pins, row_tol=20):
        centers = [p[0] for p in pins]
        rows = []
        for pt in centers:
            added = False
            for row in rows:
                if abs(pt[1] - row[0][1]) < row_tol:
                    row.append(pt)
                    added = True
                    break
            if not added:
                rows.append([pt])
        rows = sorted(rows, key=lambda row: np.mean([p[1] for p in row]))
        sorted_centers = []
        for row in rows:
            row_sorted = sorted(row, key=lambda p: p[0])
            sorted_centers.extend(row_sorted)
        center_to_pin = {p[0]: p for p in pins}
        return [center_to_pin[pt] for pt in sorted_centers]

    pins = sort_pins_by_rows(pins)

    for i, (Pos, r) in enumerate(pins, 1):
        #cv2.circle(Img, Pos, r, (0, 255, 0), 2)
        text_pos = (Pos[0], Pos[1] + 20)
        cv2.putText(Img, 
                    str(i), 
                    text_pos, 
                    cv2.FONT_HERSHEY_SIMPLEX, 
                    0.4, 
                    (255,255,255), 
                    1)

    def determine_gauge(r):
        match r:
            case 49:
                return 8
            case 35:
                return 10
            case 28:
                return 12
            case 22 | 23:
                return 16
            case 14:
                return 20
            case 11:
                return 22
            case _:
                return r
    cpp_result = []
    py_result = []
    pins.reverse()
    for i, (Pos, r) in enumerate(pins, 0):
        gauge = determine_gauge(r)
        cpp_result.append((len(pins) - i, gauge, Pos[0], Pos[1]))
        py_result.append((Pos, r))

    return Img, cpp_result, py_result