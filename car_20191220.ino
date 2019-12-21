#include "configuration.h"

void setup() {

  Serial.begin(9600);

  pinMode(motorL, OUTPUT);
  pinMode(motorLdir, OUTPUT);
  pinMode(motorR, OUTPUT);
  pinMode(motorRdir, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.println("prepare...");
  Serial.println(0);

  while (0) //ping test
  {
    pingFuc();
    pingPrint();
  }

  waitForButton();
  for(int i=0; i<3; i++){
    rotationLimit(2500);
  }

  printLimit();
  normalizationFuc();

  while (0) //sensor test
  {
    waitForButton();
    rotationErrorTest(200);
  }
  
  waitForButton();
  Serial.println("start...");
}


void loop() {

  if(abs(sensorError) < 0.1){
    if(pingLoop++ > 10){
      pingFuc();
      if(pingDuration < 1300) //1450 1300
        dodge();
      pingLoop = 0;
    }
  }
  

  normalizationFuc();
  //if(sensorNormalization[2] > 0.9 || sensorNormalization[0] > 0.9 || sensorNormalization[1] 
  //> 0.9 || sensorNormalization[3] > 0.9 || sensorNormalization[4] > 0.9) //0.1 0.6 0.95
    errorFuc();

  //motorSpeed = map(abs(sensorError), 2, 0, 130, 150);

  if(abs(sensorError) < 0.1 && kp != 0.46)
    kp = 0.46;
  else if(kp != 0.5)
    kp = 0.5;

  motorLvalue = motorSpeed - (sensorError * motorSpeed * kp  + sensorErrorSum * ki + (sensorError - sensorErrorLast) * kd);
  motorRvalue = motorSpeed + (sensorError * motorSpeed * kp  + sensorErrorSum * ki + (sensorError - sensorErrorLast) * kd);

  motorValueLimit(); //0~255
  motorFuc(motorLvalue, motorRvalue);

  sensorErrorSum += sensorError;
  sensorErrorLast = sensorError;

}
