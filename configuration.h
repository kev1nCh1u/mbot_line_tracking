#ifndef configuration_h
#define configuration_h

#include <Arduino.h>

const int buttonPin = A7;
const int analogOutPin = 13; //RGB
const int trackSensor[5] = {A4, A2, A3, A0, A1};
const int motorL = 6;
const int motorR = 5;
const int motorLdir = 7;
const int motorRdir = 4;
const int pingPin = 10;

int sensorValue[5];
int sensorMin[5] = {300, 300, 300, 300, 300}; //white
int sensorMax[5] = {700, 700, 700, 700, 700}; //black
double sensorNormalization[5]; //data Normalization
double sensorError = 0;
double sensorErrorLast = 0;
double sensorErrorSum = 0;
double sensorPass = 0;

int motorSpeed = 100; //60 100 150
const double motorDeviation = 0.98;
int motorLvalue = 50; //50
int motorRvalue = motorLvalue/motorDeviation;

const unsigned int SEnumReadings = 10;
double SEreadings[SEnumReadings];      // the readings from the sensorError
int SEreadIndex = 0;              // the index of the current reading
double SEtotal = 0;                  // the running total

const unsigned int pingNumReadings = 10;
double pingReadings[pingNumReadings];      // the readings from the sensorError
int pingReadIndex = 0;              // the index of the current reading
double pingTotal = 0;                  // the running total

long pingDuration; //ping value
int pingLoop = 0;

double kp = 0.5, ki = 0.001, kd = 1000; //kp = 60,75, ki = 0.005, kd = 1000


#endif
