int value1;

void setup()
void loop()
{
  Serial.print("Reading");
  while(Serial.available()==0);
  value1 = Serial.read();
  Serial.print(value1);
  if (value1==1)
  { 
Serial.print("Unlocking");
  }
  if (value1==0)
  {
      Serial.print("Locking");
  }
}
