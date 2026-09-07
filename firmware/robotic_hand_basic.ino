// #include <Arduino.h>
// #include <ESP32Servo.h>

// const int NUM_SERVOS = 5;

// // GPIO pins connected to servos
// int servoPins[NUM_SERVOS] = {17, 15, 16, 8, 18};
// //int servoPins[NUM_SERVOS] = {16, 15, 17, 8, 18};

// // Create servo objects
// Servo servos[NUM_SERVOS];

// // OPTIONAL: invert direction per finger (adjust if needed)
// bool invert[NUM_SERVOS] = {false, false, false, false, false};
// // Set to false for any finger that doesn't need inversion

// void setup() {
//   Serial.begin(115200);

//   // Attach servos
//   for (int i = 0; i < NUM_SERVOS; i++) {
//     servos[i].attach(servoPins[i], 500, 2400);
//   }

//   // ---------- RESET SERVOS TO ZERO POSITION ----------
//   for (int i = 0; i < NUM_SERVOS; i++) {
//     servos[i].write(invert[i] ? 180 : 0);
//   }

//   // Give servos time to reach position
//   delay(1500);

//   //Serial.println("Servos reset to zero position");
// }

// void loop() {
//   if (Serial.available()) {
//     String line = Serial.readStringUntil('\n');
//     line.trim();
//     if (line.length() == 0) return;

//     int servoIndex = 0;
//     int start = 0;

//     while (servoIndex < NUM_SERVOS) {
//       int comma = line.indexOf(',', start);
//       String token;

//       if (comma == -1)
//         token = line.substring(start);
//       else
//         token = line.substring(start, comma);

//       int angle = token.toInt();
//       angle = constrain(angle, 0, 180);

//       // Apply inversion if needed
//       int finalAngle = invert[servoIndex] ? (180 - angle) : angle;

//       servos[servoIndex].write(finalAngle);

//       if (comma == -1) break;
//       start = comma + 1;
//       servoIndex++;
//     }
//   }
// }

#include <Arduino.h>
#include <ESP32Servo.h>

const int NUM_SERVOS = 5;

// GPIO pins connected to servos
int servoPins[NUM_SERVOS] = {8, 18, 17, 16, 15};

// Create servo objects
Servo servos[NUM_SERVOS];

// OPTIONAL: invert direction per finger (adjust if needed)
bool invert[NUM_SERVOS] = {false, true, false, true, false};
// Set to false for any finger that doesn't need inversion

void setup() {
  Serial.begin(1000000);

  // Attach servos
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i], 500, 2400);
  }

  // ---------- RESET SERVOS TO ZERO POSITION ----------
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(invert[i] ? 180 : 0);
  }

  // Give servos time to reach position
  delay(1500);

  Serial.println("Servos reset to zero position");
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) return;

    int servoIndex = 0;
    int start = 0;

    while (servoIndex < NUM_SERVOS) {
      int comma = line.indexOf(',', start);
      String token;

      if (comma == -1)
        token = line.substring(start);
      else
        token = line.substring(start, comma);

      int angle = token.toInt();
      angle = constrain(angle, 0, 180);

      // Apply inversion if needed
      int finalAngle = invert[servoIndex] ? (180 - angle) : angle;

      servos[servoIndex].write(finalAngle);

      if (comma == -1) break;
      start = comma + 1;
      servoIndex++;
    }
  }
}
