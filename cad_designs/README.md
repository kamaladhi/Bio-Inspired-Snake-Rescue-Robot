# CAD Designs — Snake Rescue Robot

## ⚠️ Design Attribution

> **The mechanical design used in this project is NOT original work.**
> It is based on the open-source **"Bioinspired Robotic Snake"** project
> published on Instructables:
>
> 🔗 **Source:** [Bioinspired Robotic Snake — Instructables](https://www.instructables.com/Bioinspired-Robotic-Snake/)
>
> All credit for the mechanical/CAD design goes to the original Instructables
> author. This repository adapts that hardware platform for a search-and-rescue
> application with the addition of edge AI (YOLOv8), environmental sensing,
> and IoT telemetry.

---

## What This Project Added

The Instructables design provided the **mechanical chassis**. This project
contributed the following on top of that foundation:

| Our Contribution | Description |
|------------------|-------------|
| AI inference layer | YOLOv8n human detection via Raspberry Pi camera |
| Environmental sensing | DHT11 + MQ2 + HC-SR04 integration |
| IoT telemetry | Blynk Cloud dashboard for remote monitoring |
| Locomotion software | Arduino C++ gait implementations (sinusoidal wave equations) |
| System integration | Full Raspberry Pi ↔ Arduino serial communication pipeline |

---

## Design Overview

The snake robot body (from the Instructables design) consists of modular
segments connected by servo brackets. Adapted for this project:

- **3 body segments**, each with 2 × MG996R servo motors (vertical + horizontal plane)
- **Head module** extended to house Pi camera, MQ2, DHT11, and HC-SR04

---

## Printing Specifications

*(Based on original Instructables build, adapted where needed)*

| Parameter       | Recommendation        |
|-----------------|-----------------------|
| Material        | PLA (standard)        |
| Infill          | 30–40%                |
| Layer Height    | 0.2 mm                |
| Supports        | Yes (for servo holes) |
| Nozzle Diameter | 0.4 mm                |

---

## Assembly Order

1. Follow the **step-by-step assembly guide** at the [Instructables page](https://www.instructables.com/Bioinspired-Robotic-Snake/)
2. After mechanical assembly, mount the Raspberry Pi and sensor board in the head
3. Route all servo cables through the internal channels to the Arduino Mega
4. Refer to [`arduino/README.md`](../arduino/README.md) for pin mapping

---

## Hardware Fasteners

| Item | Qty | Purpose |
|------|-----|---------|
| M3 × 10mm screws | 24 | Servo mounts |
| M2.5 × 6mm screws | 12 | Servo horn attachments |
| Servo extension cables (30 cm) | 6 | Servo to Arduino routing |

---

## STL Files

The original STL files are available through the Instructables project page linked above.
This repository does not redistribute them — please download directly from the source.
