#include <Servo.h> 
#include <NewPing.h> 

// Define all the pins of the motor driver module L298N
#define in1 5
#define in2 6
#define in3 9
#define in4 10

#define trig_pin A1 
#define echo_pin A2
#define maximum_distance 200

Servo servo_motor; 

int distance = 100;
NewPing sonar(trig_pin, echo_pin, maximum_distance); //ultrasonic sensor function

void setup() {

  // Define if pins are input or output
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  Serial.begin(9600); //Start Serial Monitor

  servo_motor.attach(3); //Servo motor pin
  servo_motor.write(115); //Servo motor starting position (looking forward)
  delay(2000);
  distance = readPing(); //Reading the distance
  delay(100);
}

void loop() {

  int distanceRight = 0; //Initial right distance is 0
  int distanceLeft = 0; //Initial left distance is 0
  delay(50);

  if (distance <= 35){ 
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
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

 void Forward() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

 void Stop() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void Right() {
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void Left() {
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
  servo_motor.write(115); //Servo motor back to initial position
  return distance;
}

int lookLeft(){
  servo_motor.write(170); //Servo motor turn left
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115); //Servo motor back to initial position
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
