/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 27 bytes
  { 255,1,0,0,0,20,0,16,16,1,2,0,21,42,22,11,2,26,31,31,
  79,78,0,79,70,70,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


int rightMotorPwmPin = 1;
int rightMotorDirPin = 2;
int leftMotorPwmPin = 3;
int leftMotorDirPin = 4;
int trigPin;
int echoPin;
bool dir = 1;
bool drive = 1;
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
int motorSrtaightSpeed = 160;
int motorTurnSpeed = 120;
int stopDuration = 1000; // variable for the time it takes to stop the car
int turnDuration = 2000; // variable for the time it takes to turn
int motors [4] = {rightMotorPwmPin, rightMotorDirPin, leftMotorPwmPin, leftMotorDirPin}; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  for (int i = 0; i < 5; i++){
    pinMode (motors[i], OUTPUT);
    }
    digitalWrite (motors[1], 0);
    digitalWrite (motors[3], 0);
    // initializing all the pins needs initializing
}

void loop() {
  while (drive){
  analogWrite (motors[0], motorSrtaightSpeed);  
  analogWrite (motors[2], motorSrtaightSpeed);    // the car move forward till either it is too close to an object or we tell it to stop
  if (distance < 100){
    int currentTimeInLoop = millis();    // measure the time
    while (currentTimeInLoop < stopDuration){
      currentTimeInLoop = millis();
      analogWrite (motors[0], 0);
      analogWrite (motors[2], 0);   // stop the car!!
      }
    turn(dir);
    dir = !dir;    // switch direcction so that the next time it will turn the opposite side
    } 
    if (!RemoteXY.switch_1){
      drive = 0;
    }                     // in case we switch to off on our phone, it will turn off the car due to the condion in the while loop
  }
}
void turn (bool directionToMove){
  int currentTime = millis();
  analogWrite (motors[0], motorTurnSpeed);
  analogWrite (motors[2], motorTurnSpeed);
  if (directionToMove){
    while (currentTime < turnDuration){
      currentTime = millis();
      digitalWrite (motors[1], 0);
      }
    }
  if (!directionToMove){
    while (currentTime < turnDuration){
      currentTime = millis();
      digitalWrite (motors[3], 0);
      }
    }
  }
void findDistance (){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  }
