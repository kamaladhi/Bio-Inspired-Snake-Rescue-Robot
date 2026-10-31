
#include <Servo.h>

// ─── Pin Configuration ────────────────────────────────────────────────────────
static const int SERVO_PINS[6] = {A0, A1, A2, A3, A4, A5};

// ─── Motion Parameters ────────────────────────────────────────────────────────
static const float PI_F          = 3.14159f;
static const int   SERVO_COUNT   = 6;
static const int   SEGMENT_COUNT = 3;   // SERVO_COUNT / 2

static const float WAVE_SPEED    = 3.0f; // ω — angular speed multiplier
static const int   AMPLITUDE_V   = 40;   // Vertical plane amplitude (degrees)
static const int   AMPLITUDE_H   = 15;   // Horizontal stabilisation amplitude
static const int   CYCLE_STEPS   = 120;  // Steps per full locomotion cycle
static const int   STEP_DELAY_MS = 15;   // Delay per step (ms) — controls cadence

// ─── Phase offset between adjacent body segments (π/2 = 90°) ─────────────────
static const float PHASE_OFFSET  = PI_F / 2.0f;

// ─── Servo objects ────────────────────────────────────────────────────────────
Servo myServos[SERVO_COUNT];

// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < SERVO_COUNT; i++) {
    myServos[i].attach(SERVO_PINS[i]);
    myServos[i].write(90); // Centre all servos at startup
  }
  delay(500);
}

// Forward: wave propagates head → tail
void forward() {
  for (int i = 0; i < CYCLE_STEPS; i++) {
    float phase = 2.0f * PI_F * i / CYCLE_STEPS;

    for (int j = 0; j < SEGMENT_COUNT; j++) {
      float vertAngle  = 90 + AMPLITUDE_V * sin(WAVE_SPEED * phase + j * PHASE_OFFSET);
      float horizAngle = 90 + AMPLITUDE_H * cos(WAVE_SPEED * phase + j * PHASE_OFFSET);

      myServos[2 * j].write(constrain((int)vertAngle,  0, 180));
      myServos[2 * j + 1].write(constrain((int)horizAngle, 0, 180));
    }
    delay(STEP_DELAY_MS);
  }
}

// Backward: wave propagates tail → head
void backward() {
  for (int i = 0; i < CYCLE_STEPS; i++) {
    float phase = 2.0f * PI_F * i / CYCLE_STEPS;

    for (int j = 0; j < SEGMENT_COUNT; j++) {
      float vertAngle  = 90 + AMPLITUDE_V * sin(WAVE_SPEED * phase - j * PHASE_OFFSET);
      float horizAngle = 90 + AMPLITUDE_H * cos(WAVE_SPEED * phase - j * PHASE_OFFSET);

      myServos[2 * j].write(constrain((int)vertAngle,  0, 180));
      myServos[2 * j + 1].write(constrain((int)horizAngle, 0, 180));
    }
    delay(STEP_DELAY_MS);
  }
}

void loop() {
  forward();
  // backward(); // Uncomment to run backward gait instead
}
