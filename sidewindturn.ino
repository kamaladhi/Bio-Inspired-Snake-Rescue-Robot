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
void sidewindTurn(String Direction) {
  if (Direction == "Left") { Multiplier = 1; }
  else if (Direction == "Right") { Multiplier = -1; }
  for (int i = 0; i < 360; i++) {
    rads = i * pi / 180.0;     //convert from degrees to radians
    for (int j = 0; j < 2; j++) {  //first 2 pairs move differently
      myServos[2 * j].write(90 + offset + amplitude * sin(Speed * rads + j * Wavelengths * shift + (Multiplier + 1) * pi / 4));
      myServos[2 * j + 1].write(90 + offset + amplitude * sin(Speed * rads + j * Wavelengths * shift - (Multiplier - 1) * pi / 4));
    }
    for (int j = 2; j < 3; j++) {  //last pair moves differently
      myServos[2 * j].write(90 + offset + amplitude * sin(Speed * rads + j * Wavelengths * shift - (Multiplier - 1) * pi / 4));
      myServos[2 * j + 1].write(90 + offset + amplitude * sin(Speed * rads + j * Wavelengths * shift + (Multiplier + 1) * pi / 4));
    }
    delay(10);
  }
}

void loop() {
    sidewindTurn("Left");
  //sidewindTurn("Right");

}