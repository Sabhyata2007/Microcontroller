#include <Servo.h>
#define SERVO_PIN   A0
int value1;
const int buzzer = 7;
Servo servo;                         
int angle;  
unsigned long lastTime;   // initializing angle
void setup()
{
    Serial.begin(9600);
    servo.attach(SERVO_PIN);
    servo.write(0); // rotate servo motor to 0°
    lastTime = millis();                      
    pinMode(buzzer, OUTPUT); 
   
}
void loop()
{
  Serial.print("Reading");
  while(Serial.available()==0);
  value1 = Serial.read();
  Serial.print(value1);
  if (value1==1)
  { 
    Serial.print("Unlocking");
     angle = 90;
        servo.write(angle);
        lastTime = millis();                      

    digitalWrite(buzzer, HIGH); 
    delay(500);        
    digitalWrite(buzzer, LOW); 
    delay(3000);  
  }
  if (value1==0)
  {
       
       digitalWrite(buzzer, HIGH);
      delay(2000);        
      digitalWrite(buzzer, LOW);
      Serial.print("Locking");
  }
}




