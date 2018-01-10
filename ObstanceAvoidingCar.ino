#include <Servo.h>
Servo myservo;
//Motor A(Front Left)
const int motorPin1  = 37;  
const int motorPin2  = 39;  
//Motor B(Front Right)
const int motorPin3  = 50; 
const int motorPin4  = 48; 
//Motor C(Back Left)
const int motorPin5  = 11;  
const int motorPin6  =10;  
//Motor D(Back Right)
const int motorPin7  = 5; 
const int motorPin8  = 6;
//Constants for Servo and Ultrasonic
int pos = 0; 
const int trigPin = 25;
const int echoPin = 27;
const int min = 1;
const int max = 60;
long duration;
int distance;
int distance1;
int distance2;
void setup() {
  //Sets motor pins as Output
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(motorPin5, OUTPUT);
  pinMode(motorPin6, OUTPUT);
  pinMode(motorPin7, OUTPUT);
  pinMode(motorPin8, OUTPUT);
  //Setup for Servo and Ultrasonic
  myservo.attach(45); //Sets Initial Position of Servo at 45 degrees
  pinMode(trigPin, OUTPUT); //Sets trigPin as output
  pinMode(echoPin, INPUT); //Sets echoPin as input
  Serial.begin(9600); //Begins serial transmission at 9600 bits/seconds
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  moveForward();
  distance = calculateDistance(); //Calcutes the distance of the nearest obstacle using Ultrasonic sensor
  Serial.print("Distance: "); 
  Serial.println(distance);   
  delay(5);
  if(distance>=min && distance<=max){ //Checks if distance is in the range
       Stop();
       //delay(5000);
       for (pos = 90; pos <= 150; pos += 1) { //If yes, Servo turns left
        myservo.write(pos);              
        delay(10);                     
        }
      delay(1000);
      distance1 = calculateDistance(); //Caculates the distance on the left side
      Serial.print("Distance: ");
      Serial.println(distance1);
      for (pos = 150; pos >= 90; pos -= 1) {  //Servo returns to its original position
        myservo.write(pos);              
        delay(10);                     
      }
      if(distance1>max && distance1!=0){ //If the distance on left is not in range, moves left.
          moveLeft();
          delay(1100);
        }
       if(distance1>=min && distance1<=max){ //Else Servo turns right
          for(pos = 90; pos >= 30; pos -=1){
          myservo.write(pos);              
          delay(10);  
        }
      delay(1000);
      distance2 = calculateDistance(); //Calculates the distance on the right side
      Serial.print("Distance: ");
      Serial.println(distance2);
        for (pos = 30; pos <= 90; pos += 1) { //Servo returns to its original position
          myservo.write(pos);              
          delay(10);                     
        }
        if(distance2>=min && distance2<=max){ //If distance on the right is also in the range, moves back and then right.
            moveBackward();
            delay(2000);
            moveRight();
            delay(2200);
          }
        if(distance2!= 0 && distance2>max){ //If the distance on the right is not in range, moves right.
            moveRight();
            delay(1100);
          }
      }
   }
}
void moveForward(){ //Function for moving forward
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    digitalWrite(motorPin5, HIGH);
    digitalWrite(motorPin6, LOW);
    digitalWrite(motorPin7, HIGH);
    digitalWrite(motorPin8, LOW);
  }
void moveBackward(){ //Function for moving backward
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    digitalWrite(motorPin5, LOW);
    digitalWrite(motorPin6, HIGH);
    digitalWrite(motorPin7, LOW);
    digitalWrite(motorPin8, HIGH);
  }
void moveLeft(){ //Function for moving left
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    digitalWrite(motorPin5, LOW);
    digitalWrite(motorPin6, HIGH);
    digitalWrite(motorPin7, HIGH);
    digitalWrite(motorPin8, LOW);
  }
void moveRight(){ //Function for moving right
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    digitalWrite(motorPin5, HIGH);
    digitalWrite(motorPin6, LOW);
    digitalWrite(motorPin7, LOW);
    digitalWrite(motorPin8, HIGH);
  }
void Stop(){ //Function for stopping the car to wait for scan
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    digitalWrite(motorPin5, LOW);
    digitalWrite(motorPin6, LOW);
    digitalWrite(motorPin7, LOW);
    digitalWrite(motorPin8, LOW);
  }
int calculateDistance(){ //Function to calculate the distance of the nearest object
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2; //Formula to calculate the distance based on the time duration of the ultrasonic sensor signal.
  return distance;
  }
