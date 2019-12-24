#include <Servo.h> 

Servo myservo;  // create an object called myservo using the Servo library

int pos = 0;    // declare a variable for storing the position of the servo arm

void setup() 
{ 
  myservo.attach(9);  // attach the object myservo to the servo on pin 9 
} 


void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // go from 0° to 180°
  {                                  // one step at a time
    myservo.write(pos);              // go to the position stored in 'pos'
    delay(15);                       // wait 15ms for the servo to move to position
  } 
  for(pos = 180; pos>=1; pos-=1)     /// go from 180° to 0°
  {                                
    myservo.write(pos);              // go to the position stored in 'pos'
    delay(15);                       // wait 15ms for the servo to move to position
  } 
}