void ledprint(char* str)
{
  byte shift = 0;
  
  for (int i = 0; i < strlen(str); i++)      //for each character in str
  {
    if (str[i] == '.')  // if there is a decimal point
    {
      alpha4.writeDigitAscii(i-1, str[i-1], true);  // go back and rewrite the last digit with the dec point
      shift++;  // increment the shift counter
    }
    else
    {
      alpha4.writeDigitAscii(i-shift, str[i]);  //write the character
    }
  } 
  alpha4.writeDisplay();  //write to the display.
}

void lcdSetup(){
  lcd.clear();
  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("Chamber Temp"); // write this string on the top row
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print("Beer Temp"); // pad string with spaces for centering
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("OutSide Temp"); // pad with spaces for centering
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print("Server Temp ");
  
  }

void Setup(){
  char displaybuffer[4] = {' ', ' ', ' ', ' '};
  
 if(digitalRead(UpButton) ==HIGH) 
{   
  
  Serial.print("The Current Temp is   ");
  SetTemp =SetTemp + .50;
  delay(500);
   dtostrf(SetTemp, 4, 2, charVal);  
 

   ledprint(charVal);
    delay(500);

}
 if(digitalRead(DownButton) ==HIGH) 
{   
  Serial.print("The Current Temp is   ");
  SetTemp =SetTemp - .50 ;
    dtostrf(SetTemp, 4, 2, charVal);  

   ledprint(charVal);

  delay(500);
}

}
