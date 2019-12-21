#include "configuration.h"

void pingFuc(){

  pinMode(pingPin, OUTPUT);
  //digitalWrite(pingPin, LOW);
  //delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  //delayMicroseconds(5);
  //digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  pingDuration = pulseIn(pingPin, HIGH, 0);

  //pingSmoothFuc();
}

void pingPrint(){
  Serial.println(pingDuration);
}

void pingSmoothFuc(){
  
  pingTotal = pingTotal - pingReadings[pingReadIndex]; // subtract the last reading:
  pingReadings[pingReadIndex] = pingDuration; // read from the sensor:
  pingTotal = pingTotal + pingReadings[pingReadIndex]; // add the reading to the total:
  pingReadIndex = pingReadIndex + 1; // advance to the next position in the array:
  
  if (pingReadIndex >= pingNumReadings) { // if we're at the end of the array...
    pingReadIndex = 0; // ...wrap around to the beginning:
  }
  pingDuration = pingTotal / pingNumReadings; // calculate the average:
}

void dodge(){
  //motorLvalue = 150;
  //motorRvalue = 60;
  motorFuc(150, 60);
  delay(650);

  //motorLvalue = 60;
  //motorRvalue = 150;
  motorFuc(60, 150);
  
  do{
    normalizationFuc();
    errorFuc();
  }while (sensorNormalization[2] < 0.9); //do while
}
