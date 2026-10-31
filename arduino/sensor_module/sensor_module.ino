
#include <DHT.h>

// ─── Pin Definitions ──────────────────────────────────────────────────────────
static const int DHT_PIN        = 2;
static const int MQ2_PIN        = A6;
static const int TRIG_PIN       = 7;
static const int ECHO_PIN       = 8;

// ─── DHT Configuration ────────────────────────────────────────────────────────
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// ─── Sampling ─────────────────────────────────────────────────────────────────
static const unsigned long SAMPLE_INTERVAL_MS = 2000; // 2 s between readings
static const int           GAS_ALERT_THRESHOLD = 400;  // raw ADC — tune for your environment
static const float         DIST_ALERT_CM       = 20.0; // cm — obstacle warning

static unsigned long lastSampleTime = 0;

// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  Serial.println("SENSOR_MODULE_READY");
  delay(2000); // DHT11 warm-up
}

// Returns distance in cm, or -1.0 on timeout
float readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30 ms timeout
  if (duration == 0) return -1.0;
  return (duration * 0.0343) / 2.0;
}

void loop() {
  unsigned long now = millis();
  if (now - lastSampleTime < SAMPLE_INTERVAL_MS) return;
  lastSampleTime = now;

  // --- DHT11 ---
  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT_ERROR");
    return;
  }

  // --- MQ2 Gas ---
  int gasRaw = analogRead(MQ2_PIN);

  // --- Ultrasonic ---
  float distanceCm = readUltrasonic();

  // --- Publish over Serial (CSV for Raspberry Pi to parse) ---
  Serial.print("TEMP:"); Serial.print(temperature, 1);
  Serial.print(",HUM:"); Serial.print(humidity, 1);
  Serial.print(",GAS:"); Serial.print(gasRaw);
  Serial.print(",DIST:"); Serial.println(distanceCm, 1);

  // --- Local alerts via Serial ---
  if (gasRaw > GAS_ALERT_THRESHOLD) {
    Serial.println("ALERT:GAS_HIGH");
  }
  if (distanceCm > 0 && distanceCm < DIST_ALERT_CM) {
    Serial.println("ALERT:OBSTACLE");
  }
}
