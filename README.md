# RoboticHand_MediaPipe

> **Type:** Vision-Controlled Robotic Hand Project  
> **Created:** 2026-09-07

---

## Description

The **RoboticHand_MediaPipe** project is a real-time, vision-controlled robotic hand system. It leverages computer vision and deep learning via **Google MediaPipe** and **OpenCV** to track a human hand through a webcam. The software computes individual finger curl angles in real time and streams these values over a serial connection to an **ESP32-S3** microcontroller. The microcontroller drives five **MG90** servos connected via nylon thread tendons to actuate a custom-built mechanical robotic hand, mirroring human finger movements seamlessly.

---

## Hardware Requirements

| Component | Quantity | Notes |
|-----------|----------|-------|
| Microcontroller / SBC | 1 | ESP32-S3 Development Board |
| Actuators (Servos) | 5 | MG90 Hobby Servos connected via nylon thread tendons |
| Power Supply (Logic) | 2 | Lithium-ion cells paired with a buck converter supplying 5V to the ESP32-S3 5V pin |
| Power Supply (Servos) | 2 | High-current-rated Lithium-ion battery set dedicated to powering the servos |
| Camera | 1 | Laptop integrated webcam (or external USB webcam via `cv2.VideoCapture(0)`) |
| Mechanical Chassis / Hand | 1 | Thermocol sheet structure for the base/palm, and cardboard for the fingers (custom designs also supported) |
| Connecting Wires & Breadboard | — | Jumper wires, power distribution bus |

---

## Software Requirements

| Software / Library | Version | Purpose |
|--------------------|---------|---------|
| Arduino IDE / PlatformIO | ≥ 2.0 | ESP32-S3 firmware development and flashing |
| Python | ≥ 3.8 | Computer vision, MediaPipe pipeline, and serial streamer |
| OpenCV (`cv2`) | latest | Video stream capture and landmark visualization |
| MediaPipe (`mp`) | latest | Real-time 21-point hand tracking & landmark extraction |
| PySerial (`serial`) | latest | Serial communication with the microcontroller |
| NumPy | latest | Vector math and joint angle calculations |
| ESP32Servo Library | latest | Hardware PWM servo control on ESP32-S3 |

---

## Robot Architecture

```
[Webcam Feed]  →  [OpenCV + MediaPipe (PC)]  →  [Serial Stream]  →  [ESP32-S3 Microcontroller]  →  [5x MG90 Servos & Nylon Tendons]
```

### Kinematic Model
* **Configuration:** 5-Degree-of-Freedom (5-DOF) robotic hand.
* **Sensing Layer:** Monocular vision stream processed using MediaPipe Hands ML pipeline, extracting 3D hand landmarks (`mp.solutions.hands`).
* **Control Mapping:** Computes 3-point joint angles ($A, B, C$) per finger using vector dot products and arccosines, mapped linearly via `np.interp` from human joint bend ranges ($[10^\circ, 160^\circ]$) to servo actuation angles ($[0^\circ, 180^\circ]$).
* **Actuation Layer:** Tendon-driven finger joints controlled via PWM servo signals on the ESP32-S3, with per-finger software inversion logic (`invert[]`) to accommodate opposing tendon routing.

---

## Wiring & Pin Mapping

| ESP32-S3 GPIO Pin | Signal / Function | Connected To |
|-------------------|-------------------|--------------|
| GPIO 8            | PWM Servo Output  | Thumb Servo |
| GPIO 18           | PWM Servo Output  | Index Finger Servo |
| GPIO 17           | PWM Servo Output  | Middle Finger Servo |
| GPIO 16           | PWM Servo Output  | Ring Finger Servo |
| GPIO 15           | PWM Servo Output  | Pinky Finger Servo |
| UART TX / RX      | Serial Stream     | PC USB Port |

---

## Installation & Setup

### 1. Clone the repository
```bash
git clone https://github.com/<your-username>/RoboticHand_MediaPipe.git
cd RoboticHand_MediaPipe
```

### 2. Install Python dependencies
```bash
pip install opencv-python mediapipe pyserial numpy
```

### 3. Upload Firmware to ESP32-S3
1. Open Arduino IDE.
2. Install the **ESP32Servo** library through the Library Manager.
3. Open the firmware file located under `firmware/`.
4. Select your ESP32-S3 board and correct port, then click **Upload**.

---

## Usage

1. Connect your ESP32-S3 to your computer via USB and verify the assigned serial port.
2. Update the serial port configuration variable in `python/MediaPipe_HandMonitoring.py` if necessary.
3. Run the python control script:
```bash
python python/MediaPipe_HandMonitoring.py
```
4. Place your hand in front of the webcam (either your built-in laptop webcam or a connected USB webcam). Flex or extend your fingers; the robotic hand will mirror your movements in real-time. Press `ESC` to exit the application.

---

## Project Structure

```
RoboticHand_MediaPipe/
├── firmware/         # ESP32-S3 C++ firmware (.ino) using ESP32Servo
├── python/           # Python vision and serial streaming script
├── media/            # Demo videos and build photos
├── .gitignore        # Git ignore rules
├── LICENSE           # MIT License
└── README.md         # Project documentation
```

---

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.
