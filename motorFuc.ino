#include "configuration.h"

void motorFuc(int motorLvalue, int motorRvalue){
  analogWrite(motorL, motorLvalue);
  analogWrite(motorR, motorRvalue/motorDeviation);
}

void motorValueLimit(){

  if(motorLvalue < 0){
    motorLvalue = 0;
  }
  else if (motorLvalue > motorSpeed)
    motorLvalue = motorSpeed;
  
  if(motorRvalue < 0){
    motorRvalue = 0;
  }
  else if (motorRvalue > motorSpeed)
    motorRvalue = motorSpeed;
}

void printMotorValue(){
  Serial.print("left motor: ");
  Serial.print(motorLvalue);
  Serial.print("\tright motor: ");
  Serial.println(motorRvalue);
}
