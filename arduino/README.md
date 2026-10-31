# Arduino Code — Snake Rescue Robot

This directory contains all Arduino sketches for the snake robot's locomotion
and sensor systems.

## Directory Layout

```
arduino/
├── forward_backward/
│   └── forward_backward.ino   — Serpentine (slithering) gait, forward & backward
├── sidewind/
│   └── sidewind.ino           — Sidewinding gait (left / right)
├── sidewind_turn/
│   └── sidewind_turn.ino      — Sidewinding with directional steering turn
└── sensor_module/
    └── sensor_module.ino      — DHT11 + MQ2 + Ultrasonic → Serial CSV
```

## Hardware Requirements

| Component           | Quantity | Notes                              |
|---------------------|----------|------------------------------------|
| Arduino Mega 2560   | 1        | Main motion controller             |
| MG996R Servo Motors | 6        | Joints — 3 pairs (vertical + horiz)|
| DHT11               | 1        | Temperature & Humidity             |
| MQ2 Gas Sensor      | 1        | Smoke / LPG / CO detection         |
| HC-SR04 Ultrasonic  | 1        | Obstacle detection                 |

## Pin Mapping

### Locomotion Sketches (forward_backward, sidewind, sidewind_turn)

| Servo | Pin | Plane      | Segment |
|-------|-----|------------|---------|
| 0     | A0  | Vertical   | 1       |
| 1     | A1  | Horizontal | 1       |
| 2     | A2  | Vertical   | 2       |
| 3     | A3  | Horizontal | 2       |
| 4     | A4  | Vertical   | 3       |
| 5     | A5  | Horizontal | 3       |

### Sensor Module (sensor_module.ino)

| Sensor       | Pin       |
|--------------|-----------|
| DHT11        | Digital 2 |
| MQ2          | A6        |
| HC-SR04 TRIG | Digital 7 |
| HC-SR04 ECHO | Digital 8 |

## Arduino Library Dependencies

Install via Arduino IDE → Library Manager:
- `Servo` (built-in)
- `DHT sensor library` by Adafruit
- `Adafruit Unified Sensor` (dependency for DHT)

## Serial Output Format

`sensor_module.ino` outputs CSV on Serial at 9600 baud:

```
TEMP:28.5,HUM:62.0,GAS:312,DIST:45.3
ALERT:GAS_HIGH
ALERT:OBSTACLE
```

The Raspberry Pi reads this in `blynk_telemetry.py` and forwards to Blynk Cloud.

## Uploading

1. Open the `.ino` file in Arduino IDE 2.x
2. Select **Board**: Arduino Mega or Mega 2560
3. Select **Port**: your COM/ttyUSB port
4. Click **Upload** (Ctrl+U)
