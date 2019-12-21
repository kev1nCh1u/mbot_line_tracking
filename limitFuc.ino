#include "configuration.h"

void findLimit(){
  for(int i=0; i<5; i++){
    sensorValue[i] = analogRead(trackSensor[i]);
    if(sensorValue[i] < sensorMin[i])
      sensorMin[i] = sensorValue[i];
    if(sensorValue[i] > sensorMax[i])
      sensorMax[i] = sensorValue[i];
  }
}

void rotationLimit(int t){
  Serial.println("rotationLimit...");
  digitalWrite(motorLdir, LOW);
  digitalWrite(motorRdir, LOW);
  //analogWrite(motorL, motorLvalue);
  //analogWrite(motorR, motorRvalue);
  motorFuc(motorLvalue, motorRvalue);
  for(int i=0; i<t; i++){
    findLimit();
  }

  digitalWrite(motorLdir, HIGH);
  digitalWrite(motorRdir, HIGH);
  //analogWrite(motorL, motorLvalue);
  //analogWrite(motorR, motorRvalue);
  motorFuc(motorLvalue, motorRvalue);
  for(int i=0; i<t; i++){
    findLimit();
  }
  
  digitalWrite(motorLdir, LOW);
  digitalWrite(motorRdir, HIGH);
  //analogWrite(motorL, 0);
  //analogWrite(motorR, 0);
  motorFuc(0, 0);
}

void printLimit(){
  Serial.print("min:\t");
  for(int i=0; i<5; i++){
    Serial.print(sensorMin[i]);
    Serial.print("\t");
  }
  Serial.print("max:\t");
  for(int i=0; i<5; i++){
    Serial.print(sensorMax[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void rotationErrorTest(int t){
  Serial.println("rotationErrorTest...");
  digitalWrite(motorLdir, LOW);
  digitalWrite(motorRdir, LOW);
  //analogWrite(motorL, motorLvalue);
  //analogWrite(motorR, motorRvalue);
  motorFuc(motorLvalue, motorRvalue);

  for(int i=0; i<t; i++){
    normalizationFuc(); 
    errorFuc();
    printErrorFuc();
  }

  digitalWrite(motorLdir, HIGH);
  digitalWrite(motorRdir, HIGH);
  //analogWrite(motorL, motorLvalue);
  //analogWrite(motorR, motorRvalue);
  motorFuc(motorLvalue, motorRvalue);
  for(int i=0; i<t; i++){
    normalizationFuc(); 
    errorFuc();
    printErrorFuc();
  }

  digitalWrite(motorLdir, LOW);
  digitalWrite(motorRdir, HIGH);
  //analogWrite(motorL, 0);
  //analogWrite(motorR, 0);
  motorFuc(motorLvalue, motorRvalue);
}
