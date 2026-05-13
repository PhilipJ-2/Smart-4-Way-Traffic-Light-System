# 🚦 Smart 4-Way Traffic Light System

![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)

![Embedded Systems](https://img.shields.io/badge/Field-Embedded%20Systems-green)

![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

![Hardware](https://img.shields.io/badge/Focus-Hardware%20Integration-orange)

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

## 📖 Overview

This project is a fully integrated **Arduino Mega 2560 based intelligent 4-way traffic light control system** designed to simulate a real-world intersection using embedded systems hardware, custom traffic sequencing logic, sensor integration, and real-time control systems.

The system combines:

- 🚦 Traffic light sequencing

- 🚶 Pedestrian crossing systems

- 🔐 Keypad-controlled maintenance and emergency modes

- 🌗 Automatic light/vehicle detection

- 📟 LCD status interfaces

- 🔊 Audio alert systems

- ⚡ Real-time embedded control logic

This project was developed as a large-scale embedded systems and circuit integration build using multiple ICs, sensors, comparator circuits, LED drivers, and custom firmware architecture.

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

# ✨ Project Features

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

- 🧩 Multi-breadboard hardware integration# Project Features

* 4-way traffic light sequencing
* Independent North, East, South, and West traffic control
* Pedestrian crossing request system
* Dedicated pedestrian traffic LEDs
* Keypad-controlled maintenance mode
* Emergency override mode
* LCD status displays
* Audio alert speaker system
* Vehicle/light detection using LM393 comparator circuits
* ULN2803 LED driver integration
* Real-time event sequencing and timing control
* Multi-breadboard hardware integration

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

# 📷 System Demonstration

## 🖥 Full System Overview

The complete hardware system includes:

- Arduino Mega 2560

- Multiple breadboard subsystems

- ULN2803 LED driver ICs

- LM393 comparator circuits

- Dual LCD1602 displays

- 4x4 membrane keypad

- Traffic light LED arrays

- Pedestrian crossing indicators

- Audio speaker output

- Vehicle/light detection sensors Demonstration

Full System Overview

The complete hardware system includes:

* Arduino Mega 2560
* Multiple breadboard subsystems
* ULN2803 LED driver ICs
* LM393 comparator circuits
* Dual LCD1602 displays
* 4x4 membrane keypad
* Traffic light LED arrays
* Pedestrian crossing indicators
* Audio speaker output
* Vehicle/light detection sensors

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

## 📸 Project Photos

### 🔧 Main System Build

![Full System](Images/full_system.jpg)

### 🚦 Traffic Light Driver Section

![Traffic Lights](Images/traffic_lights.jpg)

### 🌗 Comparator and Sensor Circuitry

![Sensor Circuit](Images/sensor_circuit.jpg)

### 📟 LCD and Keypad Interface

![Keypad Interface](Images/keypad_interface.jpg)

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

# 🛠 Hardware Architecture

## 🚦 Traffic Light Control System

The project controls a complete 4-way intersection with independent traffic light sequencing for each direction.

Each traffic lane contains:

- 🔴 Red LED

- 🟡 Yellow LED

- 🟢 Green LED

- ✨ Blinking Green LED

The system uses **ULN2803 IC driver chips** to safely control all LED outputs from the Arduino Mega.

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

## 🚶 Pedestrian Crossing System

The pedestrian subsystem includes:

- 🚶 Dedicated pedestrian request buttons

- 🔴 Red pedestrian stop LEDs

- 🟢 Clear pedestrian crossing LEDs

- ⚠️ Crossing request indicators

Pedestrian requests are processed in software and synchronized with traffic light timing.

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

## 🔐 Keypad Interface

A 4x4 membrane keypad was integrated into the system for:

- Maintenance mode activation

- Emergency override access

- System testing and control

### 🔧 Maintenance Mode

```text

1235#

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻
