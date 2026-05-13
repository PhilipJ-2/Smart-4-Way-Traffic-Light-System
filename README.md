Smart 4-Way Traffic Light System

## Overview

An Arduino Mega 2560 based intelligent 4-way traffic light control system designed to simulate a real-world intersection using embedded systems hardware and custom traffic sequencing logic. The project integrates traffic light control, pedestrian crossing systems, keypad-controlled maintenance and emergency modes, automatic light detection, audio alerts, and LCD user interfaces.

This project was developed as a large-scale embedded systems and circuit integration build using multiple ICs, sensors, comparators, LED driver circuits, and real-time control logic.

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Project Features

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

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

System Demonstration

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

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Hardware Architecture

Traffic Light Control System

The project controls a full 4-way intersection with independent traffic light sequencing for each direction.

Each traffic lane contains:

* Red LED
* Yellow LED
* Green LED
* Blinking Green LED

The system uses ULN2803 IC driver chips to safely control all LED outputs from the Arduino Mega.

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Pedestrian Crossing System

The pedestrian subsystem includes:

* Dedicated pedestrian request buttons
* Red pedestrian stop LEDs
* Clear pedestrian crossing LEDs
* Crossing request indicators

Pedestrian requests are processed in software and synchronized with traffic light timing.

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Keypad Interface

A 4x4 membrane keypad was integrated into the system for:

* Maintenance mode activation
* Emergency override access
* System testing and control

Implemented keypad modes:

Maintenance Mode

Code: 1235#

Emergency Mode

Code: 9110#

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Comparator Sensor System

The system uses LM393 comparator IC circuits with LDR photoresistors to simulate automatic vehicle/light detection.

Each intersection direction includes:

* LDR sensor input
* Adjustable potentiometer threshold
* Comparator output
* Real-time traffic detection

This subsystem demonstrates:

* Signal conditioning
* Comparator threshold tuning
* Analog-to-digital style triggering
* Embedded sensor integration

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Audio Alert System

An LM386 audio amplifier circuit and 8-ohm speaker were added for:

* System alert sounds
* Pedestrian crossing audio notifications
* Debug/testing feedback

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Major Components Used

Component	Quantity
Arduino Mega 2560	1
ULN2803 Driver IC	3
LM393 Comparator IC	4
LM386 Audio Amplifier	1
LCD1602 Displays	2
4x4 Membrane Keypad	1
Push Buttons	4
LDR Photoresistors	4
Potentiometers	Multiple
LEDs	Multiple
Speaker	1
Breadboards	Multiple

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Engineering Concepts Demonstrated

This project demonstrates practical experience with:

* Embedded Systems
* Arduino Programming
* Real-Time Control Systems
* Digital Logic
* Comparator Circuits
* LED Driver IC Integration
* Human Machine Interfaces (HMI)
* Sensor Signal Conditioning
* Traffic Flow State Machines
* Multi-Subsystem Integration
* Breadboard Prototyping
* Debugging and Hardware Validation

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Software and Firmware

Two major firmware revisions were developed during the project:

* v10.ino
* v11.ino

The final implementation included:

* Traffic state sequencing
* Pedestrian request handling
* Keypad input processing
* LCD display updates
* Emergency and maintenance modes
* Sensor monitoring
* LED timing logic

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Wiring Documentation

The project includes full handwritten engineering documentation for:

* Arduino pin mappings
* ULN2803 driver wiring
* Pedestrian LED systems
* LCD1602 connections
* LM393 comparator circuits
* LM386 amplifier wiring
* System layout diagrams
* Breadboard placement references

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Project Photos

Main System Build

(Insert full system image here)

Traffic Light Driver Section

(Insert LED array close-up here)

Comparator and Sensor Subsystem

(Insert LM393/LDR close-up here)

LCD and Keypad Interface

(Insert keypad/LCD photo here)

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Repository Structure

Smart-4-Way-Traffic-Light-System/
│
├── README.md
├── Arduino_Code/
│   ├── v10.ino
│   └── v11.ino
│
├── Circuit_Diagrams/
│   ├── system_layout.pdf
│   ├── pin_mapping.pdf
│   ├── pedestrian_lights.pdf
│   ├── street_lights.pdf
│   ├── keypad_lcd.pdf
│   └── lm386_lm393.pdf
│
├── Images/
│   ├── full_system.jpg
│   ├── led_drivers.jpg
│   ├── sensor_section.jpg
│   ├── keypad_interface.jpg
│   └── comparator_closeup.jpg
│
├── Videos/
│   └── system_demo.mp4
│
└── Documentation/
    ├── component_list.pdf
    ├── engineering_notes.pdf
    └── traffic_flow_design.pdf

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Future Improvements

Planned future upgrades include:

* Custom PCB implementation
* Wireless monitoring system
* Camera-based vehicle detection
* AI-assisted traffic optimization
* OLED or touchscreen display upgrade
* Raspberry Pi traffic analytics integration
* Web dashboard for remote monitoring

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Development Notes

This project was fully hand-built and prototyped on breadboards during the development and testing process. Multiple hardware revisions and firmware iterations were created while integrating sensors, LED drivers, displays, comparators, keypad controls, and timing logic into a single embedded system.

The project was designed to emphasize practical embedded systems engineering, hardware debugging, subsystem integration, and real-world traffic control concepts.

⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻⸻

Author

Philip Perry
Bachelor of Science in Electrical Power Engineering Technology @ University of Houston
Minor in Computer Science Engineering Technology
U.S. Army Veteran & Former Sergeant
