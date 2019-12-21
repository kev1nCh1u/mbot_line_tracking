#include "configuration.h"

void waitForButton(){
  Serial.println("waitForButton...");
  while(analogRead(buttonPin)){
    delay(1);
  }
  delay(1000);
}