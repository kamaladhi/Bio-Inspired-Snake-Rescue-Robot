# Models — Snake Rescue Robot

## YOLOv8n Human Detection Model

| Attribute       | Value                       |
|-----------------|-----------------------------|
| Architecture    | YOLOv8n (nano)              |
| Task            | Object Detection (person)   |
| Input Size      | 640 × 640                   |
| Precision       | 92%                         |
| Recall          | 85%                         |
| Inference Speed | ~80 ms/frame (Raspberry Pi) |
| Dataset         | Roboflow Human Detection    |

## Model Weights

The trained weights file (`best.pt`) is **not included** in this repository
due to file size constraints.

**Download options:**

- 📦 [Google Drive — best.pt](https://drive.google.com/your-link-here) *(add your link)*
- 🔁 Retrain from scratch using the notebook in `training/`

Place the downloaded file at: `models/best.pt`

## Training

See [`training/human_detection_model.ipynb`](training/human_detection_model.ipynb)
for the full training pipeline:

1. Download dataset from Roboflow
2. Configure `data.yaml`
3. Train YOLOv8n with `ultralytics`
4. Evaluate and export

## Retraining on Your Own Data

```bash
# Install dependencies
pip install ultralytics roboflow python-dotenv

# Run training
yolo detect train \
  data=data.yaml \
  model=yolov8n.pt \
  epochs=50 \
  imgsz=640 \
  project=runs/detect \
  name=snake_robot
```

## Inference on Raspberry Pi

```bash
cd raspberry_pi/
pip install -r requirements.txt
python detect_human.py --model ../models/best.pt --show
```
