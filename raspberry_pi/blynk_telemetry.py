#!/usr/bin/env python3
# Reads sensor data from Arduino over Serial and pushes it to Blynk Cloud.
# Arduino sends lines like: TEMP:28.5,HUM:62.0,GAS:312,DIST:45.3
# Blynk virtual pins: V0=temp, V1=humidity, V2=gas, V3=distance, V4=human detected, V5=alert

import os
import re
import sys
import time
import threading
from datetime import datetime

import serial
from dotenv import load_dotenv
import BlynkLib

load_dotenv()

BLYNK_TOKEN = os.getenv("BLYNK_TOKEN")
SERIAL_PORT = os.getenv("SERIAL_PORT", "/dev/ttyUSB0")
BAUD_RATE   = int(os.getenv("BAUD_RATE", "9600"))

if not BLYNK_TOKEN:
    print("BLYNK_TOKEN not set. Add it to your .env file.", file=sys.stderr)
    sys.exit(1)

# Virtual pin numbers on Blynk dashboard
VP_TEMPERATURE = 0
VP_HUMIDITY    = 1
VP_GAS         = 2
VP_DISTANCE    = 3
VP_HUMAN       = 4
VP_ALERT       = 5

# Shared dict between the serial reader thread and Blynk push function
sensor_data = {
    "temp":  None,
    "hum":   None,
    "gas":   None,
    "dist":  None,
    "human": 0,
    "alert": "",
}
state_lock = threading.Lock()

# Regex to parse the CSV line from Arduino
SENSOR_PATTERN = re.compile(
    r"TEMP:(?P<temp>[\d.]+),HUM:(?P<hum>[\d.]+),GAS:(?P<gas>\d+),DIST:(?P<dist>[\d.]+)"
)


def parse_sensor_line(line):
    m = SENSOR_PATTERN.search(line)
    if not m:
        return None
    return {
        "temp": float(m.group("temp")),
        "hum":  float(m.group("hum")),
        "gas":  int(m.group("gas")),
        "dist": float(m.group("dist")),
    }


def serial_reader():
    # Runs in background thread, keeps reading Serial from Arduino
    print(f"Connecting to Arduino on {SERIAL_PORT} at {BAUD_RATE} baud...")
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=2)
    except serial.SerialException as e:
        print(f"Serial open failed: {e}", file=sys.stderr)
        sys.exit(1)

    print("Serial connected.")
    while True:
        try:
            raw = ser.readline().decode("utf-8", errors="ignore").strip()
            if not raw:
                continue

            if raw == "ALERT:GAS_HIGH":
                with state_lock:
                    sensor_data["alert"] = "Gas level HIGH!"
                print(f"[{datetime.now().strftime('%H:%M:%S')}] Alert: Gas high")
                continue

            if raw == "ALERT:OBSTACLE":
                with state_lock:
                    sensor_data["alert"] = "Obstacle detected!"
                print(f"[{datetime.now().strftime('%H:%M:%S')}] Alert: Obstacle nearby")
                continue

            parsed = parse_sensor_line(raw)
            if parsed:
                with state_lock:
                    sensor_data.update(parsed)
                    sensor_data["alert"] = ""  # clear old alert when fresh data arrives
                print(f"T={parsed['temp']}C  H={parsed['hum']}%  Gas={parsed['gas']}  Dist={parsed['dist']}cm")

        except Exception as e:
            print(f"Serial read error: {e}")
            time.sleep(1)


blynk = BlynkLib.Blynk(BLYNK_TOKEN)


@blynk.on("connected")
def blynk_connected(ping):
    print(f"Connected to Blynk (ping {ping}ms)")


def push_to_blynk():
    # Called by Blynk every 2 seconds to push latest readings
    with state_lock:
        data = sensor_data.copy()

    if data["temp"] is None:
        return  # no data yet, skip

    blynk.virtual_write(VP_TEMPERATURE, data["temp"])
    blynk.virtual_write(VP_HUMIDITY,    data["hum"])
    blynk.virtual_write(VP_GAS,         data["gas"])
    blynk.virtual_write(VP_DISTANCE,    data["dist"])
    blynk.virtual_write(VP_HUMAN,       data["human"])
    if data["alert"]:
        blynk.virtual_write(VP_ALERT, data["alert"])


blynk.set_user_task(push_to_blynk, 2000)


if __name__ == "__main__":
    reader_thread = threading.Thread(target=serial_reader, daemon=True)
    reader_thread.start()

    print("Starting Blynk loop...")
    try:
        blynk.run()
    except KeyboardInterrupt:
        print("\nStopped.")
