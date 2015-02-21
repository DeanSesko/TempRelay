void Setup(){

 if(digitalRead(UpButton) ==HIGH) 
{   
  Serial.print("The Current Temp is   ");
  SetTemp =SetTemp + 1;
  delay(500);
  Serial.println(SetTemp);

}
 if(digitalRead(DownButton) ==HIGH) 
{   
  Serial.print("The Current Temp is   ");
  SetTemp =SetTemp - 1;
  Serial.println(SetTemp);
  delay(500);
}

}
