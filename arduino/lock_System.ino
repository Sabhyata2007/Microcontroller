// two switch will be there for selecting keypad or rfid sensor 

int value1; //fp
const int buzzer = 7;// fp
#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 5
#define ROW_NUM    4 
#define COLUMN_NUM 4 
#define SERVO_PIN  A0 
#define SS_PIN 10 
#define RST_PIN 5 
MFRC522 rfid(SS_PIN, RST_PIN);// rfid function using these pins 
byte keyTagUID[4] = {0xFF, 0xFF, 0xFF, 0xFF};

Servo servo; // servo motor

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
 
  // rfid scanner( firstly generate the uid code for card from the blue token and then use the card to unlock the system )
  if(switch one is pressed){
   Serial.begin(9600);
   SPI.begin(); // init SPI bus
   rfid.PCD_Init(); // init MFRC522
   servo.attach(SERVO_PIN);
   servo.write(0); // rotate servo motor to 0°
   lastTime = millis();
   Serial.println("Tap RFID/NFC Tag on reader");
  }


  //Generate a function for keypad sensor 
  else if(switch two is pressed){
  Serial.begin(9600);
  input_password.reserve(32); // maximum password size is 32, change if needed

  servo.attach(SERVO_PIN);
  servo.write(0); // rotate servo motor to 0°
  lastTime = millis();
  }


  else{ // fingerprint sensors 
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT); 
  servo.attach(SERVO_PIN);
  servo.write(0); // rotate servo motor to 0°
  lastTime = millis();
  }
 
}

void loop() {
 
 // generate a function for rfid
 if (switch 1 is pressed){
   if (rfid.PICC_IsNewCardPresent()) { // new tag is available
      if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
            MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

             if (rfid.uid.uidByte[0] == keyTagUID[0] &&
                  rfid.uid.uidByte[1] == keyTagUID[1] &&
                  rfid.uid.uidByte[2] == keyTagUID[2] &&
                   rfid.uid.uidByte[3] == keyTagUID[3] ) {
                                Serial.println("Access is granted");
                                angle = 90;
                                servo.write(angle);
                                lastTime = millis();
                                
                                                         }
            else
                {
               Serial.print("Access denied for user with UID:");
               for (int i = 0; i < rfid.uid.size; i++) {
               Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
               Serial.print(rfid.uid.uidByte[i], HEX);
                                                        }
                Serial.println();
                 }

       rfid.PICC_HaltA(); // halt PICC
       rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
     if (angle == 90 && (millis() - lastTime) > 5000) { // 5 seconds
    angle = 0;
    servo.write(angle);
    Serial.println("Rotating Servo Motor to 0°");
  }
}

  
  // generate a function for keypad
  if(switch 2 is pressed){
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







