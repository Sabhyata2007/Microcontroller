#include <Keypad.h>
#include <Servo.h>

#define SERVO_PIN 5
#define buzzer A0
#define SWITCH_PIN A1

int value1 = 0;

Servo myservo;

int pos = 0;
const int ROW_NUM = 4; // Four rows
const int COLUMN_NUM = 4; // Four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {13, 12, 11, 10}; // Connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {9, 8, 7, 6}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
const String password_1 = "ABC1234"; // Change your password here
const String password_2 = "5642B";   // Change your password here
const String password_3 = "9765";    // Change your password here
String input_password;

void setup() {
  Serial.begin(9600);
  input_password.reserve(32);
  myservo.attach(SERVO_PIN); // Attach the servo on pin 5 to the servo object
  myservo.write(pos); // Go to position zero first
  delay(2000);
  pinMode(buzzer, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}

void loop() {
  bool switchState = digitalRead(SWITCH_PIN);
  Serial.print("Switch State: ");
  Serial.println(switchState);

  if (switchState == HIGH) {
    handleKeypadInput();
  } else {
    handleBluetoothInput();
  }
}

void handleKeypadInput() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    if (key == '*') {
      input_password = ""; // Reset the input password
    } else if (key == '#') {
      if (input_password == password_1 || input_password == password_2 || input_password == password_3) {
        Serial.println("The password is correct, Door is unlocking");
        delay(1000);
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(buzzer, LOW);
      
      } else {
        Serial.println("The password is incorrect, try again");
      }
      input_password = ""; // Reset the input password
    } else {
      input_password += key; // Append new character to input password string
    }
  }
}

void handleBluetoothInput() {
  Serial.print("Reading");
         while(Serial.available()==0);
         value1 = Serial.read();
         Serial.print(value1);
        if (value1==1)
         { 
        Serial.print("Unlocking");                     

       digitalWrite(buzzer, HIGH); 
       delay(500);        
      digitalWrite(buzzer, LOW); 
      delay(1000); 
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
                myservo.write(pos);                 // tell servo to go to position in variable 'pos'
                delay(15);                          // waits 15 ms for the servo to reach the position
                  }
                delay(1000);                          // delay of 1 second before changing direction of rotation
                for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
                myservo.write(pos);                 // tell servo to go to position in variable 'pos'
                delay(15); }  

      }
    if (value1==0)
    {
       
       digitalWrite(buzzer, HIGH);
      delay(2000);        
      digitalWrite(buzzer, LOW);
      Serial.print("Locking");
    }
}





