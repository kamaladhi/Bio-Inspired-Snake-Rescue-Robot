#!/usr/bin/env python3
# Runs YOLOv8n on the Pi camera feed and prints when a human is detected.
# Use --show to see the live window, --save to record clips to ./recordings/

import argparse
import os
import sys
import time
from datetime import datetime
from pathlib import Path

import cv2
from dotenv import load_dotenv
from ultralytics import YOLO

load_dotenv()

DEFAULT_MODEL = os.getenv("MODEL_PATH", "models/best.pt")
DEFAULT_CONF  = float(os.getenv("CONF_THRESH", "0.4"))
FRAME_WIDTH   = 640
FRAME_HEIGHT  = 480
TARGET_CLASS  = "person"

parser = argparse.ArgumentParser()
parser.add_argument("--model",  default=DEFAULT_MODEL, help="path to best.pt")
parser.add_argument("--conf",   default=DEFAULT_CONF,  type=float, help="confidence threshold")
parser.add_argument("--show",   action="store_true",   help="show live detection window")
parser.add_argument("--save",   action="store_true",   help="save clips to ./recordings/")
parser.add_argument("--source", default=0,             help="camera index or video path")
args = parser.parse_args()


def open_camera(source):
    cap = cv2.VideoCapture(source)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH,  FRAME_WIDTH)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT)
    if not cap.isOpened():
        print(f"Cannot open camera: {source}", file=sys.stderr)
        sys.exit(1)
    return cap


def setup_writer(output_dir):
    output_dir.mkdir(parents=True, exist_ok=True)
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    out_path  = output_dir / f"detection_{timestamp}.avi"
    fourcc    = cv2.VideoWriter_fourcc(*"XVID")
    writer    = cv2.VideoWriter(str(out_path), fourcc, 20.0, (FRAME_WIDTH, FRAME_HEIGHT))
    print(f"Saving to {out_path}")
    return writer


def annotate_frame(frame, result, fps):
    # Draw boxes around detected people and show FPS in corner
    human_count = 0
    for box in result.boxes:
        cls_id = int(box.cls[0])
        label  = result.names[cls_id]
        if label != TARGET_CLASS:
            continue
        conf = float(box.conf[0])
        x1, y1, x2, y2 = map(int, box.xyxy[0])
        human_count += 1
        cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
        cv2.putText(frame, f"{label} {conf:.0%}", (x1, y1 - 8),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)

    cv2.putText(frame, f"FPS: {fps:.1f}  Humans: {human_count}",
                (10, 25), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 200, 255), 2)
    return frame, human_count


def main():
    print(f"Loading model: {args.model}")
    model = YOLO(args.model)

    cap    = open_camera(args.source)
    writer = setup_writer(Path("recordings")) if args.save else None

    print("Running. Press Ctrl+C or q to stop.")
    prev_time = time.time()

    try:
        while True:
            ret, frame = cap.read()
            if not ret:
                print("Frame read failed, retrying...")
                time.sleep(0.05)
                continue

            results = model(frame, conf=args.conf, verbose=False)

            now  = time.time()
            fps  = 1.0 / max(now - prev_time, 1e-6)
            prev_time = now

            annotated, human_count = annotate_frame(frame, results[0], fps)

            # Print to stdout so blynk_telemetry.py can pick it up
            if human_count > 0:
                print(f"HUMAN_DETECTED:{human_count}", flush=True)

            if writer:
                writer.write(annotated)

            if args.show:
                cv2.imshow("Human Detection", annotated)
                if cv2.waitKey(1) & 0xFF == ord("q"):
                    break

    except KeyboardInterrupt:
        print("\nStopped.")
    finally:
        cap.release()
        if writer:
            writer.release()
        cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
