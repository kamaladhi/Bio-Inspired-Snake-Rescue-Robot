#include <Servo.h>
Servo myServos[6]; //create 6 servos

float pi = 3.14159;
int TotalNumberofServos = 6; //changed to 6 servos
int ServosPerSide = TotalNumberofServos / 2;
float shift = 2 * pi / ServosPerSide; // Phase lag between segments
int amplitude = 50;
int offset = 0;
float rads;
float Speed = 2;
float Wavelengths = 1.5;
int Multiplier;

void setup() {
  Serial.begin(9600);
  myServos[0].attach(A0);
  myServos[1].attach(A1);
  myServos[2].attach(A2);
  myServos[3].attach(A3);
  myServos[4].attach(A4);
  myServos[5].attach(A5);
}

void forward() {
  // Optimized parameters
  float waveSpeed = 3.0;      // Optimal speed for 6 servos
  int waveAmplitude = 40;     // Enough undulation for traction
  int cycleSteps = 120;       // Smoother motion with fewer steps
  int stepDelay = 15;         // Balanced speed
  
  for (int i = 0; i < cycleSteps; i++) {
    float phase = 2.0 * pi * i / cycleSteps;
    
    for (int j = 0; j < 3; j++) {
      // Vertical undulation (corrected phase relationship)
      float vertAngle = 90 + waveAmplitude * sin(waveSpeed * phase + j * pi/2);
      myServos[2*j].write(vertAngle);
      
      // Horizontal stabilization with slight lead/lag
      float horizAngle = 90 + 15 * cos(waveSpeed * phase + j * pi/2);
      myServos[2*j+1].write(horizAngle);
    }
    delay(stepDelay);
  }
}

void backward() {
  // Optimized parameters
  float waveSpeed = 3.0;      // Optimal speed for 6 servos
  int waveAmplitude = 40;     // Enough undulation for traction
  int cycleSteps = 120;       // Smoother motion with fewer steps
  int stepDelay = 15;         // Balanced speed
  
  for (int i = 0; i < cycleSteps; i++) {
    float phase = 2.0 * pi * i / cycleSteps;
    
    for (int j = 0; j < 3; j++) {
      // Vertical undulation (corrected phase relationship)
      float vertAngle = 90 + waveAmplitude * sin(waveSpeed * phase - j * pi/2);
      myServos[2*j].write(vertAngle);
      
      // Horizontal stabilization with slight lead/lag
      float horizAngle = 90 + 15 * cos(waveSpeed * phase - j * pi/2);
      myServos[2*j+1].write(horizAngle);
    }
    delay(stepDelay);
  }
}

void loop() {
  forward();
  //backward(); 
}