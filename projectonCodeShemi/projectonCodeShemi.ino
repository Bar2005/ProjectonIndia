
int rightMotorPwmPin = 11;
int rightMotorDirPin = 10;
int leftMotorPwmPin = 6;
int leftMotorDirPin = 5;
int trigPin = 8;
int echoPin = 9;
bool dir = true;
bool drive = true;
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
int motorSrtaightSpeed = 40;
int motorTurnSpeed = 30;
int stopDuration = 5000; // variable for the time it takes to stop the car
int turnDuration = 6000; // variable for the time it takes to turn
int motors [4] = {rightMotorPwmPin, rightMotorDirPin, leftMotorPwmPin, leftMotorDirPin}; 
int lastTime;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  for (int i = 0; i < 5; i++){
    pinMode (motors[i], OUTPUT);
    }
    digitalWrite (motors[1], 1);
    digitalWrite (motors[3],  1);
    // initializing all the pins needs initializing
}

void loop() {
  findDistance();
  analogWrite (motors[0], motorSrtaightSpeed);  
  analogWrite (motors[2], motorSrtaightSpeed);    // the car move forward till either it is too close to an object or we tell it to stop
  digitalWrite (motors[1], 1);
  digitalWrite (motors[3],  1);
  Serial.println ("distance:");
  Serial.println (distance);
  if (distance < 100){
    Serial.println ("h");
    //analogWrite (motors[0], 0);
    //analogWrite (motors[2], 0);   // stop the car!!
    turn(dir);
    dir = !dir;    // switch direction so that the next time it will turn the opposite side
    } 
}
void turn (bool directionToMove){
lastTime = millis();
int currentTime = millis() - lastTime;
  if (directionToMove){
    Serial.println ("a");
    Serial.println (currentTime);
    while (currentTime < turnDuration){
      Serial.println ("turn:");
      Serial.println (currentTime);
      currentTime = millis() - lastTime;
      digitalWrite (motors[3], 1);
      digitalWrite (motors[1], 0);
      analogWrite (motors[0], motorTurnSpeed);
      analogWrite (motors[2], motorTurnSpeed);
      }
    }
  if (!directionToMove){
    Serial.println ("b");
    Serial.println (currentTime);
    while (currentTime < turnDuration){
      Serial.println ("turn!");
      Serial.println (currentTime);
      currentTime = millis() - lastTime;
      digitalWrite (motors[1], 1);
      digitalWrite (motors[3], 0);
      analogWrite (motors[0], motorTurnSpeed);
      analogWrite (motors[2], motorTurnSpeed);
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
