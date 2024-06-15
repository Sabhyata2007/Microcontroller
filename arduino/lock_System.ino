
#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
int value1; //fp
#define SERVO_PIN  A0 
const int buzzer = A1;// fp
#define ROW_NUM    4 
#define COLUMN_NUM 4  
Servo servo; // servo motor
 int switch_value = A2
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password_1 = "ABC1234"; // change your password here
const String password_2 = "5642B";   // change your password here
const String password_3 = "9765";    // change your password here
String input_password;

int angle = 0; // the current angle of servo motor
unsigned long lastTime;

void setup() {
  Serial.begin(9600);
  input_password.reserve(32); // maximum password size is 32, change if needed

  servo.attach(SERVO_PIN);
  servo.write(0); // rotate servo motor to 0°
  lastTime = millis(); // fingerprint sensors 
  pinMode(buzzer, OUTPUT); 
  pinMode(switch_value , OUTPUT);
 
}

void loop() { 
 // generate a function for keypad
  int x = digitalRead(switch_value)
  if (x==HIGH){
     char key = keypad.getKey();
     if (key) {
        Serial.println(key);

         if (key == '*') {
             input_password = ""; // reset the input password
           }
         else if (key == '#') {
              if (input_password == password_1 || input_password == password_2 || input_password == password_3) {
                 Serial.println("The password is correct, rotating Servo Motor to 90°");
                 angle = 90;
                 servo.write(angle);
                 lastTime = millis();
                 } 
               else {
                  Serial.println("The password is incorrect, try again");
                    }

         input_password = ""; // reset the input password
         }
         else {
              input_password += key; // append new character to input password string
    }
  }

     if (angle == 90 && (millis() - lastTime) > 5000) { // 5 seconds
    angle = 0;
    servo.write(angle);
    Serial.println("Rotating Servo Motor to 0°");
  }
}
}
 else{
   // fingerprint sensor 
  Serial.print("Reading");
  while(Serial.available()==0);
  value1 = Serial.read();
  Serial.print(value1);
  if (value1==1)
  { 
    Serial.print("Unlocking");
     digitalWrite(buzzer, HIGH); 
     delay(2000);
     angle = 90;
     servo.write(angle);
     lastTime = millis();   
     digitalWrite(buzzer, LOW); 
   
  }
  if (value1==0)
  {
      digitalWrite(buzzer, HIGH);
      delay(2000);
     if (angle == 90 && (millis() - lastTime) > 5000) { // 5 seconds
        angle = 0;
        servo.write(angle);
        Serial.println("Rotating Servo Motor to 0°");
     }
      digitalWrite(buzzer, LOW);
      Serial.print("Locking");
  }
}







