# RoboticHand_MediaPipe

> **Folder:** `RoboticHand_MediaPipe`  
> **Type:** Robotics Project  
> **Created:** 2026-09-07

---

## Description

<!-- Describe the robot's purpose, locomotion type, sensing capabilities,
     and the problem it is designed to solve. -->

---

## Hardware Requirements

| Component | Quantity | Notes |
|-----------|----------|-------|
| Microcontroller / SBC | 1 | e.g. Arduino Mega, Raspberry Pi, ESP32 |
| Motors / Servos | — | Specify type and count |
| Motor Driver | — | e.g. L298N, TB6612 |
| Sensors | — | e.g. ultrasonic, IR, IMU |
| Power Supply | 1 | e.g. LiPo 7.4 V 2200 mAh |
|              |   |       |

---

## Software Requirements

| Software / Library | Version | Purpose |
|--------------------|---------|---------|
| Arduino IDE | ≥ 2.0 | Firmware development |
| Python | ≥ 3.8 | High-level control / vision |
| numpy | latest | Numerical computation |
| pyserial | latest | Serial communication |
|          |        |         |

---

## Robot Architecture

<!-- Describe the overall system architecture: sensing, decision-making,
     actuation, and communication layers. -->

```
[Sensors]  →  [Microcontroller]  →  [Motor Drivers]  →  [Actuators]
                    ↕
             [Raspberry Pi / PC]  (optional high-level control)
```

### Kinematic Model

<!-- Describe the kinematic configuration (differential drive, Ackermann,
     multi-DoF arm, etc.) -->

---

## Wiring & Pin Mapping

| Pin / Port | Signal | Connected to |
|------------|--------|--------------|
|            |        |              |

---

## Installation

### 1. Clone the repository
```bash
git clone https://github.com/<your-username>/RoboticHand_MediaPipe.git
cd RoboticHand_MediaPipe
```

### 2. Install Python dependencies
```bash
pip install -r requirements.txt
```

### 3. Upload firmware
Open `code/firmware/` in Arduino IDE, select your board, and click **Upload**.

---

## Usage

```bash
# Run the high-level Python controller
python code/python/controller.py
```

<!-- Describe remote control, autonomous modes, or test routines. -->

---

## Simulation

<!-- Describe how to run the simulation (if applicable). -->

```bash
# Launch simulation
python simulation/run_sim.py
```

---

## Project Structure

```
RoboticHand_MediaPipe/
├── code/
│   ├── firmware/       # Microcontroller code (.ino / .cpp)
│   └── python/         # High-level control scripts
├── docs/               # Design docs, datasheets
├── media/              # Build photos, demo videos
├── hardware/           # Schematics, CAD files
├── simulation/         # Simulation configs and scripts
├── README.md
├── LICENSE
├── .gitignore
└── requirements.txt
```

---

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE)
file for details.
