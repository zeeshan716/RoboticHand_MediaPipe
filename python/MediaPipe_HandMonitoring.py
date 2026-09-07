# === mediapipe_5_finger_servos.py ===
# Maps your real hand → 5 servo angles
# Uses Mediapipe + OpenCV + PySerial

import cv2
import mediapipe as mp
import serial
import time
import numpy as np

# ----------------- SERIAL SETTINGS -----------------
SERIAL_PORT = 'COM12'   # Change to your port
BAUDRATE = 1000000

ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)
time.sleep(2)

# ----------------- MEDIAPIPE INIT -----------------
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)

# ----------------- ANGLE FUNCTION ----------------
def joint_angle(a, b, c):
    a, b, c = np.array(a), np.array(b), np.array(c)
    ba = a - b
    bc = c - b
    cosang = np.dot(ba, bc) / (np.linalg.norm(ba) * np.linalg.norm(bc) + 1e-6)
    return np.degrees(np.arccos(np.clip(cosang, -1.0, 1.0)))

# ----------------- MAIN LOOP -----------------
with mp_hands.Hands(
        max_num_hands=1,
        min_detection_confidence=0.6,
        min_tracking_confidence=0.5) as hands:

    # Mediapipe landmark index groups
    FINGERS = {
        "thumb":  (2, 3, 4),
        "index":  (5, 6, 8),
        "middle": (9, 10, 12),
        "ring":   (13, 14, 16),
        "pinky":  (17, 18, 20)
    }

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        result = hands.process(rgb)

        if result.multi_hand_landmarks:
            hand = result.multi_hand_landmarks[0]
            h, w, _ = frame.shape

            angles = []

            # ---- Compute curl angle for each finger ----
            for finger, (a_idx, b_idx, c_idx) in FINGERS.items():
                pa = (hand.landmark[a_idx].x * w, hand.landmark[a_idx].y * h)
                pb = (hand.landmark[b_idx].x * w, hand.landmark[b_idx].y * h)
                pc = (hand.landmark[c_idx].x * w, hand.landmark[c_idx].y * h)

                angle_deg = joint_angle(pa, pb, pc)

                # Map human finger bend → servo angle
                servo_angle = int(np.interp(angle_deg, [10, 160], [0, 180]))
                angles.append(180 - servo_angle)

            # ---- Send CSV line to ESP32 ----
            packet = ",".join(str(a) for a in angles) + "\n"
            ser.write(packet.encode())
            #ser.write(bytes(angles))

            # Draw landmarks for debugging
            mp_drawing.draw_landmarks(frame, hand, mp_hands.HAND_CONNECTIONS)

        cv2.imshow("Hand Tracking", frame)
        if cv2.waitKey(1) & 0xFF == 27:  # ESC
            break

cap.release()
ser.close()
cv2.destroyAllWindows()
