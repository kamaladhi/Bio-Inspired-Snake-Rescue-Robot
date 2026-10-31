
#include <Servo.h>

// ─── Pin Configuration ────────────────────────────────────────────────────────
static const int SERVO_PINS[6] = {A0, A1, A2, A3, A4, A5};

// ─── Motion Parameters ────────────────────────────────────────────────────────
static const float PI_F          = 3.14159f;
static const int   SERVO_COUNT   = 6;
static const int   SEGMENT_COUNT = 3;

static const float WAVE_SPEED    = 2.0f;
static const int   AMPLITUDE     = 50;
static const int   OFFSET        = 0;
static const float WAVELENGTHS   = 1.5f;
static const float BASE_SHIFT    = 2.0f * PI_F / (SERVO_COUNT / 2);

// ─── Servo objects ────────────────────────────────────────────────────────────
Servo myServos[SERVO_COUNT];

// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < SERVO_COUNT; i++) {
    myServos[i].attach(SERVO_PINS[i]);
    myServos[i].write(90);
  }
  delay(500);
}

// SidewindTurn: 'L' = left turn, 'R' = right turn
void sidewindTurn(char direction) {
  int M = (direction == 'L') ? 1 : -1;

  for (int i = 0; i < 360; i++) {
    float rads = i * PI_F / 180.0f;

    // Front two segments — swapped polarity for steering
    for (int j = 0; j < 2; j++) {
      float sp = WAVE_SPEED * rads + j * WAVELENGTHS * BASE_SHIFT;
      int vertAngle  = 90 + OFFSET + (int)(AMPLITUDE * sin(sp + (M + 1) * PI_F / 4.0f));
      int horizAngle = 90 + OFFSET + (int)(AMPLITUDE * sin(sp - (M - 1) * PI_F / 4.0f));
      myServos[2 * j].write(constrain(vertAngle,  0, 180));
      myServos[2 * j + 1].write(constrain(horizAngle, 0, 180));
    }

    // Rear segment — normal polarity
    for (int j = 2; j < SEGMENT_COUNT; j++) {
      float sp = WAVE_SPEED * rads + j * WAVELENGTHS * BASE_SHIFT;
      int vertAngle  = 90 + OFFSET + (int)(AMPLITUDE * sin(sp - (M - 1) * PI_F / 4.0f));
      int horizAngle = 90 + OFFSET + (int)(AMPLITUDE * sin(sp + (M + 1) * PI_F / 4.0f));
      myServos[2 * j].write(constrain(vertAngle,  0, 180));
      myServos[2 * j + 1].write(constrain(horizAngle, 0, 180));
    }
    delay(10);
  }
}

void loop() {
  sidewindTurn('L');
  // sidewindTurn('R'); // Uncomment to turn right
}
