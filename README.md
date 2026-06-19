# 🐍 Bio-Inspired Snake Robot for Real-Time Victim Detection in Disaster Environments

<p align="center">

![Award](https://img.shields.io/badge/Award-Best%20Paper%20IEEE%20SISCON%202025-gold)
![Institution](https://img.shields.io/badge/Institution-Amrita%20Vishwa%20Vidyapeetham-blue)
![Timeline](https://img.shields.io/badge/Timeline-Dec%202024--Apr%202025-lightgrey)

</p>

## 🏆 Achievement

This project was awarded the **Best Paper Award at IEEE SISCON 2025** and developed as part of the IoT and Mobile Robotics curriculum at Amrita Vishwa Vidyapeetham.

The project combines:

* Bio-inspired robotics
* Embedded systems
* Computer vision
* Internet of Things (IoT)
* Search and rescue automation

to create an intelligent snake robot capable of navigating hazardous disaster environments and detecting trapped victims.

---

# 📌 Abstract

Search-and-rescue missions after earthquakes, landslides, and structural collapses often require navigating narrow and dangerous spaces inaccessible to humans.

Traditional wheeled robots struggle in highly unstructured environments.

This project introduces a **bio-inspired modular snake robot** capable of:

* Traversing confined spaces
* Detecting human victims
* Monitoring environmental hazards
* Streaming live telemetry
* Supporting rescue operations remotely

The system integrates Raspberry Pi based edge AI, Arduino-based motion control, environmental sensing, and cloud-connected IoT monitoring.

---

# 🌍 Problem Statement

During disasters, first responders face severe risks while searching through unstable debris.

Key challenges include:

* Narrow pathways
* Toxic gases
* Poor visibility
* Structural instability

The objective of this project is to develop a compact robotic platform that can safely explore these environments and assist rescue teams in locating victims quickly.

---

# 🧠 System Architecture

```text
Camera Module
      │
      ▼
YOLOv8 Human Detection
      │
      ▼
Raspberry Pi
      │
      ▼
Decision Module
      │
      ▼
Arduino Mega
      │
      ▼
MG996R Servo Network
      │
      ▼
Snake Locomotion

Environmental Sensors
(MQ2, DHT11, Ultrasonic)
      │
      ▼
Blynk IoT Dashboard
```

---

# ⚙️ Key Features

### 🐍 Bio-Inspired Locomotion

Implemented five locomotion modes:

* Slithering
* Sidewinding
* Rectilinear
* Concertina
* Rolling

---

### 🤖 AI-Powered Victim Detection

* YOLOv8n Human Detection
* Real-time Edge Inference
* Raspberry Pi Deployment
* Live Camera Streaming

---

### 🌡️ Environmental Monitoring

Integrated sensors:

* MQ2 Gas Sensor
* DHT11 Temperature Sensor
* DHT11 Humidity Sensor
* Ultrasonic Obstacle Detection

---

### ☁️ IoT Telemetry

Using Blynk IoT Platform:

* Remote monitoring
* Sensor visualization
* Live telemetry
* Robot status tracking

---

# 📊 AI Performance

| Metric         | Value        |
| -------------- | ------------ |
| Precision      | 92%          |
| Recall         | 85%          |
| Inference Time | ~80 ms/frame |
| Model          | YOLOv8n      |
| Deployment     | Raspberry Pi |

---

# 🔧 Technology Stack

## Programming

* Python
* Arduino C/C++

## AI & Computer Vision

* YOLOv8
* OpenCV
* Roboflow

## IoT

* Blynk Cloud
* Sensor Telemetry

## CAD & Mechanical Design

* SolidWorks
* 3D Printing

## Hardware

* Raspberry Pi
* Arduino Mega
* MG996R Servo Motors

---

# 🔩 Hardware Bill of Materials

| Component         | Purpose                  |
| ----------------- | ------------------------ |
| Raspberry Pi      | AI Processing            |
| Arduino Mega      | Motion Controller        |
| MG996R Servos     | Joint Actuation          |
| Camera Module     | Human Detection          |
| Ultrasonic Sensor | Obstacle Detection       |
| MQ2 Sensor        | Gas Detection            |
| DHT11 Sensor      | Environmental Monitoring |
| Li-ion Battery    | Power Supply             |

---

# 📁 Repository Structure

```text
Snake-rescue-robot
│
├── Arduino_Code
├── RaspberryPi_Code
├── YOLOv8_Model
├── CAD_Designs
├── Images
├── Videos
├── Research_Paper
├── Documentation
└── README.md
```

---

# 📸 Robot Design

## Top View Layout

![Top View](Images/top_view.jpg)

The top-view layout illustrates:

* Servo placement
* Wiring architecture
* Sensor distribution
* Modular body segmentation

---

## Active Head Module

![Head Module](Images/head_module.jpg)

The head module contains:

* Camera
* MQ2 Sensor
* DHT11 Sensor
* Ultrasonic Sensor

allowing environmental awareness and victim detection.

---

# 🎥 Locomotion Demonstrations

### Slithering Gait

[[Video Link](https://drive.google.com/file/d/1fyC0k1eySaU_47hNxujLM6OCG9r2XEzv/view?usp=drive_link)]

### Sidewinding Gait

[[Video Link](https://drive.google.com/file/d/15Du60AjsOeIPJqi3RpOS2Sn3gD9tG7Vu/view?usp=drive_link)]

### Rectilinear Gait

[[Video Link](https://drive.google.com/file/d/1SxPBMAPyzq9AAho9zV66Mh6Yw2aydoQi/view?usp=sharing)]

### Concertina Gait

[[Video Link](https://drive.google.com/file/d/1sujrtSKe8Wml_VD-i0kmtL74r71EWAN7/view?usp=drive_link)]

### Rolling Gait

[[Video Link](https://drive.google.com/file/d/1gm4oRElH7aiKm9JQyCPRzrn899uS_hea/view?usp=sharing)]

---

# 📈 Experimental Results

### Victim Detection

✅ Successful human detection in indoor and obstacle-rich environments.

### Obstacle Avoidance

✅ Real-time obstacle sensing and navigation.

### Environmental Monitoring

✅ Continuous telemetry of gas concentration, temperature, and humidity.

### Remote Monitoring

✅ Live sensor data visualized through Blynk IoT dashboard.

---

# 📄 Research Publication

**Title:** Bio-Inspired Snake Robot for Real-Time Victim Detection in Disaster Environments

🏆 Best Paper Award — IEEE SISCON 2025

Published in IEEE Xplore.

Paper and presentation materials are available in the repository documentation section.

---

# 🚀 Future Work

* Thermal Camera Integration
* LiDAR-based Mapping
* Autonomous Path Planning
* SLAM Navigation
* Multi-Robot Coordination
* Edge AI Optimization

---

# 👥 Team

### Jeevakamal K R
### Shatha Varsha Sree T
### Guhan K B
### Kavya Sri B


---

