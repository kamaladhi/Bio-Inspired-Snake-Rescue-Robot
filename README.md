<p align="center">
  <img src="https://img.shields.io/badge/Award-🏆%20Best%20Paper%20IEEE%20SISCON%202025-FFD700?style=for-the-badge&labelColor=1a1a2e" alt="Best Paper Award">
  <img src="https://img.shields.io/badge/Published-IEEE%20Xplore-00629B?style=for-the-badge&logo=ieee&logoColor=white" alt="IEEE Xplore">
  <img src="https://img.shields.io/badge/License-MIT-22c55e?style=for-the-badge" alt="MIT License">
  <img src="https://img.shields.io/badge/Python-3.10%2B-3776AB?style=for-the-badge&logo=python&logoColor=white" alt="Python">
  <img src="https://img.shields.io/badge/Arduino-C%2FC%2B%2B-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino">
  <img src="https://img.shields.io/badge/YOLOv8-Ultralytics-purple?style=for-the-badge" alt="YOLOv8">
</p>

<h1 align="center">🐍 Bio-Inspired Snake Robot<br>for Real-Time Victim Detection in Disaster Environments</h1>

<p align="center">
  <b>Amrita School of AI · Amrita Vishwa Vidyapeetham, Coimbatore</b><br>
  IEEE SISCON 2025 · DOI: <a href="https://doi.org/10.1109/SISCON66686.2025.11409077">10.1109/SISCON66686.2025.11409077</a>
</p>

---

## 🏆 Achievement

This project received the **Best Paper Award at IEEE SISCON 2025** (1st International
Conference on Smart and Intelligent Systems), Marian Engineering College, Trivandrum.

> 📢 [LinkedIn Project Post](https://lnkd.in/p/gDC7JiFt) — 1,195+ reactions &nbsp;·&nbsp;
> 🏆 [Award Announcement](https://lnkd.in/p/gBD9azNT) — 78+ reactions

---

## 📌 Abstract

Search-and-rescue missions following earthquakes, landslides, and structural
collapses require navigating narrow, hazardous spaces inaccessible to humans
and conventional wheeled robots.

This project presents a **bio-inspired modular snake robot** that:

- 🐍 Traverses confined spaces using five locomotion gaits
- 👁️ Detects human victims in real-time using **YOLOv8n** edge AI
- 🌡️ Monitors environmental hazards (gas, temperature, humidity, obstacles)
- 📡 Streams live telemetry to rescuers via **Blynk IoT Cloud**
- 🔧 Uses a fully modular, 3D-printed chassis with MG996R servo joints

---

## 🧠 System Architecture

```
┌──────────────────────────────────────────────────────────────────┐
│                        SNAKE RESCUE ROBOT                        │
│                                                                  │
│  ┌──────────────┐    ┌─────────────────┐     ┌───────────────┐   │
│  │ Pi Camera v2 │──▶ │  Raspberry Pi 4 ───▶ │ Blynk Cloud   │   │
│  └──────────────┘    │  YOLOv8n        │     │  Dashboard    │   │
│                      │  detect_human.py│     └───────────────┘   │
│  ┌──────────────┐    │  blynk_telemetry│         ▲               │
│  │ DHT11  MQ2   │───▶│  .py            │         │              │
│  │ HC-SR04      │    └────────┬────────┘    Rescue Operator      │
│  └──────────────┘             │                                  │
│                               ▼ Serial (9600 baud)               │
│                      ┌─────────────────┐                         │
│                      │  Arduino Mega   │                         │
│                      │  Motion Control │                         │
│                      └────────┬────────┘                         │
│                               │ PWM                              │
│                    ┌──────────┴──────────┐                       │
│                 Servo 0-5 (MG996R × 6)                           │
│               (Vertical + Horizontal per segment)                │
└──────────────────────────────────────────────────────────────────┘
```

---

## 🐍 Locomotion Gaits

Five bio-inspired gaits implemented in Arduino C++:

| Gait | Sketch | Principle | Best For |
|------|--------|-----------|----------|
| **Slithering (Forward)** | `forward_backward.ino` | Lateral sinusoidal wave | Open corridors |
| **Slithering (Backward)** | `forward_backward.ino` | Reversed wave phase | Retreat |
| **Sidewinding** | `sidewind.ino` | Two orthogonal waves, π/2 phase-shifted | Sandy/uneven terrain |
| **Sidewinding Turn** | `sidewind_turn.ino` | Differential front/rear segment phases | Navigation & steering |

### Mathematical Basis

Each servo joint angle follows a travelling sinusoidal wave:

```
θ_j(t) = A · sin(ω·t + j·φ) + θ₀
```

where `A` = amplitude, `ω` = angular speed, `j` = segment index, `φ` = inter-segment phase lag, `θ₀` = neutral offset (90°).

See [`docs/locomotion_gaits.md`](docs/locomotion_gaits.md) for full derivations.

### 🎥 Gait Demonstrations

| Gait | Video |
|------|-------|
| Slithering | [▶ Watch](https://drive.google.com/file/d/1fyC0k1eySaU_47hNxujLM6OCG9r2XEzv/view?usp=drive_link) |
| Sidewinding | [▶ Watch](https://drive.google.com/file/d/15Du60AjsOeIPJqi3RpOS2Sn3gD9tG7Vu/view?usp=drive_link) |
| Rectilinear | [▶ Watch](https://drive.google.com/file/d/1SxPBMAPyzq9AAho9zV66Mh6Yw2aydoQi/view?usp=sharing) |
| Concertina | [▶ Watch](https://drive.google.com/file/d/1sujrtSKe8Wml_VD-i0kmtL74r71EWAN7/view?usp=drive_link) |
| Rolling | [▶ Watch](https://drive.google.com/file/d/1gm4oRElH7aiKm9JQyCPRzrn899uS_hea/view?usp=sharing) |

---

## 🤖 AI-Powered Victim Detection

| Attribute | Value |
|-----------|-------|
| Model | YOLOv8n |
| Task | Human (person) detection |
| Deployment | Raspberry Pi 4 (edge) |
| Inference Speed | ~80 ms/frame |
| Precision | **92%** |
| Recall | **85%** |
| Dataset | Roboflow Human Detection |

---

## 🌡️ Environmental Monitoring

| Sensor | Pin | Measures | Alert Threshold |
|--------|-----|----------|-----------------|
| DHT11 | D2 | Temperature (°C), Humidity (%) | — |
| MQ2 | A6 | Gas / smoke (raw ADC) | > 400 |
| HC-SR04 | D7 (TRIG), D8 (ECHO) | Obstacle distance (cm) | < 20 cm |

All readings are published to **Blynk Cloud** virtual pins every 2 seconds.

---

## 📁 Repository Structure

```
Snake-rescue-robot/
├── README.md
├── LICENSE                          — MIT License
├── .gitignore
├── .env.example                     — Template for secrets (copy to .env)
│
├── arduino/
│   ├── README.md                    — Pin mapping & upload instructions
│   ├── forward_backward/
│   │   └── forward_backward.ino    — Serpentine (slithering) gait
│   ├── sidewind/
│   │   └── sidewind.ino            — Sidewinding gait
│   ├── sidewind_turn/
│   │   └── sidewind_turn.ino       — Sidewinding with steering
│   └── sensor_module/
│       └── sensor_module.ino       — DHT11 + MQ2 + Ultrasonic → Serial CSV
│
├── raspberry_pi/
│   ├── detect_human.py             — YOLOv8n inference on Pi camera
│   ├── blynk_telemetry.py          — Sensor → Blynk Cloud relay
│   └── requirements.txt
│
├── models/
│   ├── README.md                   — Model card & training instructions
│   └── training/
│       └── human_detection_model.ipynb
│
├── cad_designs/
│   └── README.md                   — 3D print specs & assembly guide
│
├── docs/
│   └── locomotion_gaits.md         — Mathematical gait derivations
│
├── images/                         — Robot photos (add yours here)
│   └── README.md
│
└── research/
    └── README.md                   — IEEE paper citation & links
```

---

## 🔧 Hardware Bill of Materials

| Component | Qty | Purpose |
|-----------|-----|---------|
| Raspberry Pi 4 (2GB+) | 1 | Edge AI inference + IoT |
| Arduino Mega 2560 | 1 | Servo motion control |
| MG996R Servo Motor | 6 | Joint actuation (3 segments × 2 axes) |
| Pi Camera Module v2 | 1 | Human detection |
| DHT11 Sensor | 1 | Temperature & Humidity |
| MQ2 Gas Sensor | 1 | Smoke / gas detection |
| HC-SR04 Ultrasonic | 1 | Obstacle detection |
| Li-ion Battery Pack | 1 | 7.4V / 5000 mAh recommended |
| 3D Printed Chassis | — | PLA, 30–40% infill |

---

## ⚡ Quick Start

### 1. Clone the Repository

```bash
git clone https://github.com/kamaladhi/Snake-rescue-robot.git
cd Snake-rescue-robot
```

### 2. Set Up Credentials

```bash
cp .env.example .env
# Edit .env and fill in your BLYNK_TOKEN and ROBOFLOW_API_KEY
```

### 3. Upload Arduino Code

Open any sketch in `arduino/` with **Arduino IDE 2.x**, select board
**Arduino Mega 2560**, and upload.

### 4. Install Raspberry Pi Dependencies

```bash
cd raspberry_pi/
pip install -r requirements.txt
```

### 5. Run Human Detection

```bash
python detect_human.py --model ../models/best.pt --show
```

### 6. Run Blynk Telemetry

```bash
python blynk_telemetry.py
```

---

## 📄 Citation

If you use this project in your work, please cite:

```bibtex
@inproceedings{jeevakamal2025snake,
  title     = {Bio-Inspired Snake Robot for Real-Time Victim Detection in Disaster Environments},
  author    = {Jeevakamal, K R and Kavya Sri, B and Shatha Varsha Sree, T and Guhan, K B},
  booktitle = {2025 1st International Conference on Smart and Intelligent Systems (SISCON)},
  year      = {2025},
  publisher = {IEEE},
  doi       = {10.1109/SISCON66686.2025.11409077}
}
```

Full citation details: [`research/README.md`](research/README.md)

---

## 👥 Team

| Name | 
|------|
| **Jeevakamal K R** |
| **Kavya Sri B** | 
| **Shatha Varsha Sree T** | 
| **Guhan K B** | 

**Mentors:** Dr. Abhishek S · Akhil VM (PhD)  
**Institution:** Amrita School of AI, Amrita Vishwa Vidyapeetham, Coimbatore

---

## 🚀 Future Work

- 🌡️ Thermal camera (AMG8833 / MLX90640) for heat-signature victim detection
- 🗺️ LiDAR-based SLAM for autonomous navigation
- 🤝 Multi-robot coordination
- ⚡ Edge TPU (Coral) acceleration (~10 ms inference)
- 🤖 ROS2 integration

---

<p align="center">
  <a href="https://doi.org/10.1109/SISCON66686.2025.11409077">
    <img src="https://img.shields.io/badge/IEEE_Xplore-Read_Paper-00629B?style=flat-square&logo=ieee" alt="IEEE Paper">
  </a>
  &nbsp;
  <img src="https://img.shields.io/badge/License-MIT-22c55e?style=flat-square" alt="License">
</p>
