#include <Servo.h>
#define SERVO_PIN   10

Servo servo;                         
int angle = 0;     // initializing angle
void setup() {
  servo.attach(SERVO_PIN);            
  servo.write(angle);                   
  delay(2000);                         
}

void loop() {
  delay(1000);                          
  for (angle= 0; angle <= 180; angle+= 1) { // rotae 180 degree clockwise
  
    servo.write(angle);                 
    delay(15);                        
  }
  delay(1000);                          
  for (angle = 180; angle >= 0; angle-= 1) { // rotate 180 degree anticlockwise
    servo.write(angle);                 
    delay(15);                          
  }
}
