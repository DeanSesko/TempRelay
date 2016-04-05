void lcdSetupMain(){
  
  if(digitalRead(Fermswitch) ==HIGH){
    lcd.setCursor ( 0, 0 );          
    lcd.print("Beer Temp");
    lcd.setCursor ( 0, 1 );  
    lcd.print("Chamber Temp");
    lcd.setCursor ( 0, 2 ); 
    lcd.print("Server Temp ");
    lcd.setCursor ( 0, 3 );
    lcd.print("Fermenting is:"); 
  }
  else{
    
    lcd.setCursor ( 0, 0 );          
    lcd.print("Outdoor Temp");
    lcd.setCursor ( 0, 1 );  
    lcd.print("Chamber Temp");
    lcd.setCursor ( 0, 2 ); 
    lcd.print("Server Temp ");
    lcd.setCursor ( 0, 3 );
    lcd.print("Fermenting is:"); 
  
  }
  
  }
  
  
  
  void lcdSetupMode(){
    
      lcd.clear();
      lcd.setCursor ( 0, 0 );      
      lcd.print("Setup Mode");
      lcd.setCursor ( 0, 1 );           
      lcd.print("Red=UP / Black=Down" );
      lcd.setCursor ( 0, 3 );
      lcd.print("Ferm Temp       ");
      lcd.setCursor ( 15, 3 );
      lcd.print(SetTemp);
      
  }

void Setup(){
    
  
 if(digitalRead(UpButton) ==HIGH) 
{   
  
  Serial.print("The Current Temp is   ");
  SetTemp =SetTemp + 1;
  lcd.setCursor ( 15, 3 );
  lcd.print(SetTemp);
     
  delay(500);

}
 if(digitalRead(DownButton) ==HIGH) 
{   
  Serial.print("The Current Temp is   ");
  SetTemp =SetTemp - 1 ;
  lcd.setCursor ( 15, 3 );
  lcd.print(SetTemp);
      
  delay(500);
}

}
