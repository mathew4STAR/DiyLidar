//Encoder outputs in serial
//Motor turns in one direction, when reaches upperlimit rotates in other direction, and when in reaches lower limit goes back to original direction, keeps repeating
#include <Wire.h>
#include <AS5600.h>
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define SERIAL SerialUSB
  #define SYS_VOL   3.3
#else
  #define SERIAL Serial
  #define SYS_VOL   5
#endif

AMS_5600 ams5600;

#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

int step_number = 0;
float pred_angle = 0;
float step_angle = 0.17;
float angle;
bool go = true;
bool dir = true;



void setup() {
  SERIAL.begin(115200);
  Wire.begin();
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  SERIAL.println(">>>>>>>>>>>>>>>>>>>>>>>>>>> ");
  if (ams5600.detectMagnet() == 0) {
    while (1) {
      if (ams5600.detectMagnet() == 1) {
        SERIAL.print("Current Magnitude: ");
        SERIAL.println(ams5600.getMagnitude());
        break;
      } else {
        SERIAL.println("Can not detect magnet");
      }
      delay(1000);
    }
  }
}

void loop() {
  angle = convertRawAngleToDegrees(ams5600.getRawAngle());
  SERIAL.println("Actual: " + String(angle, DEC));
  if (angle > 359.0) {
    dir = false;
  }
  if (angle < 1.0) {
    dir = true;
  }
  Step(dir);
  delay(2);
}


float convertRawAngleToDegrees(word newAngle) {
  float retVal = newAngle * 0.087890625;
  return retVal;
}

void Step(bool dir) {
  if (go) {
    if (dir) {
      switch (step_number) {
        case 0:
          digitalWrite(STEPPER_PIN_1, HIGH);
          digitalWrite(STEPPER_PIN_2, LOW);
          digitalWrite(STEPPER_PIN_3, LOW);
          digitalWrite(STEPPER_PIN_4, LOW);
          break;
        case 1:
          digitalWrite(STEPPER_PIN_1, LOW);
          digitalWrite(STEPPER_PIN_2, HIGH);
          digitalWrite(STEPPER_PIN_3, LOW);
          digitalWrite(STEPPER_PIN_4, LOW);
          break;
        case 2:
          digitalWrite(STEPPER_PIN_1, LOW);
          digitalWrite(STEPPER_PIN_2, LOW);
          digitalWrite(STEPPER_PIN_3, HIGH);
          digitalWrite(STEPPER_PIN_4, LOW);
          break;
        case 3:
          digitalWrite(STEPPER_PIN_1, LOW);
          digitalWrite(STEPPER_PIN_2, LOW);
          digitalWrite(STEPPER_PIN_3, LOW);
          digitalWrite(STEPPER_PIN_4, HIGH);
          break;
      }
    } else {
      switch (step_number) {
        case 0:
          digitalWrite(STEPPER_PIN_1, LOW);
          digitalWrite(STEPPER_PIN_2, LOW);
          digitalWrite(STEPPER_PIN_3, LOW);
          digitalWrite(STEPPER_PIN_4, HIGH);
          break;
        case 1:
          digitalWrite(STEPPER_PIN_1, LOW);
          digitalWrite(STEPPER_PIN_2, LOW);
          digitalWrite(STEPPER_PIN_3, HIGH);
          digitalWrite(STEPPER_PIN_4, LOW);
          break;
        case 2:
          digitalWrite(STEPPER_PIN_1, LOW);
          digitalWrite(STEPPER_PIN_2, HIGH);
          digitalWrite(STEPPER_PIN_3, LOW);
          digitalWrite(STEPPER_PIN_4, LOW);
          break;
        case 3:
          digitalWrite(STEPPER_PIN_1, HIGH);
          digitalWrite(STEPPER_PIN_2, LOW);
          digitalWrite(STEPPER_PIN_3, LOW);
          digitalWrite(STEPPER_PIN_4, LOW);
      }
    }
  }
  step_number++;
  pred_angle = pred_angle + step_angle;
  if (step_number > 3) {
    step_number = 0;
  }
  if (pred_angle > 360) {
    pred_angle = 0;
  }
  SERIAL.println("Predicted: " + String(pred_angle));
}
