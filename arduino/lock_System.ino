
#include <Keypad.h> // keypad header file 
#include <Servo.h>   // Servo motor header file
#include <LiquidCrystal.h> // Lcd header file 
#define SERVO_PIN 5
#define buzzer A0
#define switch_1 A1


Servo myservo; // initializing servo motor 
int value1 = 0;// initializing bluetooth value as 0
int pos = 0; // initializing angle of servo motor to be zero 
const int ROW_NUM = 4; // Four rows
const int COLUMN_NUM = 4; // Four columns
const int rs = 3, en = 2, d4 = A2, d5 = A3, d6 = A4, d7 = A5; // lcd pin interface
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pin_rows[ROW_NUM] = {13, 12, 11, 10}; // defining  row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {9, 8, 7, 6}; // defining  column pinouts of the keypad


Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
const String password_1 = "ABC1234"; //  password one
const String password_2 = "56420";   // password two
const String password_3 = "9765";    // password three
String input_password;


void setup() {
  Serial.begin(9600);
  input_password.reserve(32);// max size of password 32 bit 
  myservo.attach(SERVO_PIN); // Attach the servo on pin 5 to the servo object
  myservo.write(pos); // Go to position zero first
  delay(2000);
  pinMode(buzzer, OUTPUT);  // buzzer as output
  pinMode(switch_1, INPUT);  // switch as input 
  lcd.begin(16, 2); 
}

void loop() {
  bool switchState = digitalRead(switch_1);
  if (switchState == HIGH) {
    KeypadInputLock();
  } else {
    BluetoothInputLock();
  }
}

void KeypadInputLock() {
 char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    lcd.setCursor(0, 0);   
    lcd.print(key);
    if (key == '*') {
      input_password = "";  // Reset the input password
    } else if (key == '#') {
      if (input_password == password_1 || input_password == password_2 || input_password == password_3) {
        unlockDoor();
      } else {
        incorrectPassword();
      }
      input_password = "";  // Reset the input password
    } else if (key == 'D') {
      lockDoor();
    } else {
      input_password += key; // Append new character to input password string
    }
  }
}
   void unlockDoor() { // for unlocking door using keypad 
  Serial.println("The password is correct, Door is unlocking");
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  lcd.setCursor(0, 0);      
  lcd.print("DOOR");        
  lcd.setCursor(2, 1);           
  lcd.print("UNLOCKING");
  delay(1000);
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees in steps of 1 degree
    myservo.write(pos);                 
    delay(15);                         
  }
  delay(1000);                          
  lcd.clear();
  delay(1000);
}

void lockDoor() {  // for locking door using keypad 
  Serial.println("Locking door");
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  lcd.setCursor(0, 0);           
  lcd.print("DOOR"); 
  lcd.setCursor(2, 1);          
  lcd.print("LOCKING");
  delay(1000);
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 to 0 degrees in steps of 1 degree
    myservo.write(pos);                
    delay(15);
  }
  delay(1000);                         
  lcd.clear();
  delay(1000);
}

void incorrectPassword() {  // incorrect password generation 
  Serial.println("The password is incorrect, try again");
  lcd.setCursor(0, 0);           
  lcd.print("PASSWORD");
  lcd.setCursor(2, 1);           
  lcd.print("INCORRECT");
}



void BluetoothInputLock() {
  Serial.print("Reading");
         while(Serial.available()==0);
         value1 = Serial.read();
         Serial.print(value1);
        if (value1==1)
         { 
        Serial.print("Unlocking"); 
        digitalWrite(buzzer, HIGH); 
       delay(1000);        
      digitalWrite(buzzer, LOW); 
      delay(1000); 
         lcd.setCursor(0,0);           
        lcd.print("DOOR"); 
       lcd.setCursor(2,1);         
       lcd.print("UNLOCKING");
       delay(1000);
        for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees in steps of 1 degree
                myservo.write(pos);                
                delay(15);                         
                  }
                delay(1000);                         
                

      lcd.clear();
      delay(1000)  ;                   

       
     
      }
    if (value1==0)
    {
       
       digitalWrite(buzzer, HIGH);
      delay(1000);        
      digitalWrite(buzzer, LOW);
      Serial.print("Locking");
      delay(1000); 
         lcd.setCursor(0,0);           
        lcd.print("DOOR"); 
       lcd.setCursor(2,1);         
       lcd.print("LOCKING");
       for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees
                myservo.write(pos);                 
                delay(15); } 
    }
    lcd.clear();
}
