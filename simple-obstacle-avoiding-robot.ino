#include <Servo.h> 
#include <NewPing.h> 

// Define all the pins of the motor driver module L298N
#define ena 9
#define enb 10
#define in1 2
#define in2 3
#define in3 4
#define in4 5


#define trigPin A0 
#define echoPin A1
#define maxDistance 200

Servo servo_motor; 

int distance = 100;
NewPing sonar(trigPin, echoPin, maxDistance); //ultrasonic sensor function

void setup() {

  // Define if pins are input or output
  pinMode(ena, OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600); //Start Serial Monitor

  servo_motor.attach(11); //Servo motor pin
  servo_motor.write(90); //Servo motor starting position (looking forward)
  delay(2000);
  distance = readPing(); //Reading the distance
  delay(100);
}

void loop() {

  int distanceRight = 0; //Initial right distance is 0
  int distanceLeft = 0; //Initial left distance is 0
  delay(50);

  if (distance <= 30){ 
    Stop();
    delay(300);
    Backward();
    delay(400);
    Stop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft){
      Right();
      delay(250);
      Stop();
    }
    else{
      Left();
      delay(250);
      Stop();
    }
  }

  else{
    Forward();
    delay(250);
    Stop();
  }

  distance = readPing();
}

// FUNCTIONS TO CHANGE THE DIRECTION OF THE WHEELS
void Backward() {
  //Control Speed (Adjust values between 0 and 255)
  analogWrite(ena, 180);
  analogWrite(enb,180);

  //Set Direction (All motors Backward)
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

 void Forward() {
  //Control Speed (Adjust values between 0 and 255)
  analogWrite(ena, 180);
  analogWrite(enb,180);

  //Set Direction (All motors Forward)
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

 void Stop() {
  //Control Speed (Adjust values between 0 and 255)
  analogWrite(ena, 0);
  analogWrite(enb,0);

  //Set Direction (All motors Stop)
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void Right() {
  //Control Speed (Adjust values between 0 and 255)
  analogWrite(ena, 180);
  analogWrite(enb,180);

  //Set Direction (Left motors forward)
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void Left() {
  //Control Speed (Adjust values between 0 and 255)
  analogWrite(ena, 180);
  analogWrite(enb,180);

  //Set Direction (Right motors Forward)
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

int lookRight(){  
  servo_motor.write(50); //Servo motor turn right
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90); //Servo motor back to initial position
  return distance;
}

int lookLeft(){
  servo_motor.write(160); //Servo motor turn left
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90); //Servo motor back to initial position
  return distance;
}

int readPing(){ //converting distance values into centimetres
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){ //error (distance cannot be 0)
    cm=250; //safe distance value for clear path
  }
  return cm;
}
