# 🚦 Smart 4-Way Traffic Light System

![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)
![Embedded Systems](https://img.shields.io/badge/Field-Embedded%20Systems-green)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Hardware](https://img.shields.io/badge/Focus-Hardware%20Integration-orange)

---

## 📖 Overview

The **Smart 4-Way Traffic Light System** is an Arduino Mega 2560 based intelligent traffic control platform designed to simulate a real-world intersection using embedded systems hardware and real-time traffic sequencing logic.

The project integrates traffic light control, pedestrian crossing systems, keypad-controlled maintenance and emergency modes, automatic sensor detection, LCD interfaces, audio alerts, and multi-subsystem embedded control into a unified hardware platform.

---

## ✨ Project Features

- 🚦 4-way traffic light sequencing
- ↔️ Independent North, East, South, and West traffic control
- 🚶 Pedestrian crossing request system
- 🚷 Dedicated pedestrian traffic LEDs
- 🔐 Keypad-controlled maintenance mode
- 🚨 Emergency override mode
- 📟 Dual LCD status displays
- 🔊 Audio alert speaker system
- 🌗 Vehicle/light detection using LM393 comparator circuits
- ⚡ ULN2803 LED driver integration
- ⏱ Real-time event sequencing and timing control
- 🧩 Multi-breadboard hardware integration

---

## 🛠 Hardware Used

- Arduino Mega 2560
- ULN2803 Driver ICs
- LM393 Comparator ICs
- LM386 Audio Amplifier
- LCD1602 Displays
- 4x4 Membrane Keypad
- Push Buttons
- LDR Photoresistors
- Potentiometers
- LEDs
- Speaker
- Breadboards

---

## 🔊 System Workflow

```text
Pedestrian Button / Sensor Input
→ Arduino Mega Processing
→ Traffic Sequencing Logic
→ ULN2803 Driver ICs
→ Traffic & Pedestrian LEDs
→ LCD Status Updates
→ Audio Alert Output
```

---

## 🧠 Engineering Concepts Demonstrated

- Embedded Systems
- Real-Time Control Systems
- Digital Logic
- Comparator Circuits
- LED Driver IC Integration
- Human Machine Interfaces (HMI)
- Sensor Signal Conditioning
- Traffic Flow State Machines
- Multi-Subsystem Integration
- Breadboard Prototyping
- Hardware Debugging & Validation

---

## 📂 Repository Structure

```text
Smart-4-Way-Traffic-Light-System/

├── Arduino_Code/
│   ├── v10.ino
│   └── v11.ino
│
├── Circuit_Diagrams/
├── Documentation/
├── IC_Chips/
├── Images/
├── Pin_Mapping/
├── Videos/
└── README.md
```

---

## ⚙️ Development Stages

### Stage 1 — Traffic Light Drivers
Initial LED driver integration and traffic sequencing logic.

### Stage 2 — Pedestrian System
Pedestrian crossing buttons and crossing indicator development.

### Stage 3 — Sensor Integration
LM393 comparator circuits and LDR detection subsystem testing.

### Stage 4 — LCD & Keypad Interface
LCD status displays, keypad integration, and maintenance controls.

### Final System
Integrated traffic control platform combining traffic sequencing, pedestrian systems, sensors, displays, and emergency control logic.

---

## 📊 Firmware & System Development

Arduino firmware was used for:

- Traffic sequencing
- Pedestrian request handling
- Sensor monitoring
- LCD display updates
- Keypad interaction
- Emergency override modes
- Real-time timing control
- Multi-subsystem hardware integration

---

## 📷 Project Photos

### Full System Build
![Full System](Images/full_system.jpg)

### Traffic Light Driver Section
![Traffic Drivers](Images/traffic_drivers.jpg)

### Sensor and Comparator Circuits
![Sensor Circuits](Images/sensor_circuit.jpg)

---

## 🎥 Demo Video

[Watch Project Demo](Videos/system_demo.mp4)

---

## 🚀 Future Improvements

- Custom PCB implementation
- Wireless monitoring system
- Camera-based vehicle detection
- AI-assisted traffic optimization
- OLED/touchscreen display upgrades
- Raspberry Pi analytics integration
- Web dashboard monitoring
- Smart intersection automation

---

## 👨‍💻 Author

**Philip Perry**  
Bachelor of Science in Electrical Power Engineering Technology @ University of Houston  
Minor in Computer Science Engineering Technology  
U.S. Army Veteran & Former Sergeant
