#include "configuration.h"

void normalizationFuc(){
  for(int i=0; i<5; i++){
    sensorValue[i] = analogRead(trackSensor[i]);
    sensorNormalization[i] = (double(sensorValue[i]) - sensorMin[i]) / (sensorMax[i] - sensorMin[i]);
  }
}

void printnormalizationFuc(){
  Serial.println("normalization...");
  for(int i=0; i<5; i++){
    Serial.print(sensorNormalization[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void errorFuc(){
  //if(sensorNormalization[1] < sensorNormalization[0]) //only outside sensor
  //  sensorNormalization[1] = sensorNormalization[0];
  //if(sensorNormalization[3] < sensorNormalization[4])
  //  sensorNormalization[3] = sensorNormalization[4];

  if(sensorNormalization[1] < sensorNormalization[0] || sensorNormalization[3] < sensorNormalization[4]){
    sensorNormalization[1] = sensorNormalization[0]; //only outside sensor
    sensorNormalization[3] = sensorNormalization[4];
  }

  if(sensorNormalization[0] > 0.9 && sensorNormalization[1] > 0.9 && sensorNormalization[4] < 0.9)
    sensorNormalization[3] = 0; //4 sensor same time

  if(sensorNormalization[3] > 0.9 && sensorNormalization[4] > 0.9 && sensorNormalization[0] < 0.9)
    sensorNormalization[1] = 0; //4 sensor same time

  if(sensorNormalization[1] > 0.5 && sensorPass != 2) //last sensor error
    sensorPass = 2;
  else if (sensorNormalization[3] > 0.5 && sensorPass != -2)
    sensorPass = -2;
  
  sensorError = sensorNormalization[0] + sensorNormalization[1] - sensorNormalization[3] - sensorNormalization[4];

  if(sensorNormalization[2] < 0.5 && sensorNormalization[0] < 0.5 && sensorNormalization[1] 
  < 0.5 && sensorNormalization[3] < 0.5 && sensorNormalization[4] < 0.5 && abs(sensorError > 0.1))
    sensorError = sensorPass;
  
  //SEsmoothFuc();
}

void printErrorFuc(){
  //Serial.println("Mix...");
  Serial.println(sensorError*200);
}

void SEsmoothFuc(){ //sensorError smooth
  
  SEtotal = SEtotal - SEreadings[SEreadIndex]; // subtract the last reading:
  SEreadings[SEreadIndex] = sensorError; // read from the sensor:
  SEtotal = SEtotal + SEreadings[SEreadIndex]; // add the reading to the total:
  SEreadIndex = SEreadIndex + 1; // advance to the next position in the array:
  
  if (SEreadIndex >= SEnumReadings) { // if we're at the end of the array...
    SEreadIndex = 0; // ...wrap around to the beginning:
  }
  sensorError = SEtotal / SEnumReadings; // calculate the average:
}
