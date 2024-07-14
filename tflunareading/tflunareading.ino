#include <SoftwareSerial.h>
#include "TFMini.h"

SoftwareSerial mySerial(10, 11);     
TFMini tfmini;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println ("Initializing...");
  mySerial.begin(TFMINI_BAUDRATE);
  tfmini.begin(&mySerial);    
}


void loop() {
  uint16_t dist = tfmini.getDistance();
  uint16_t strength = tfmini.getRecentSignalStrength();

  Serial.print(dist);
  Serial.print(" cm      sigstr: ");
  Serial.println(strength);

  delay(25);  
}

