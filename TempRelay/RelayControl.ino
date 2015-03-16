void ChamberControl(float temp){
  
if(digitalRead(Fermswitch) ==HIGH){
    lcd.setCursor ( 15, 3 );
    lcd.print("ON "); 
  
    if (temp < (SetTemp - .55) && temp > 33) {
      digitalWrite(RelayHeater, HIGH);
    }
     else if (temp > (SetTemp - .05)){
       digitalWrite(RelayHeater, LOW);
      }
   
   if (temp >(SetTemp + .55)){
     digitalWrite(RelayCooling, HIGH);
     }
    if (temp < (SetTemp + .05)){
      digitalWrite(RelayCooling, LOW);
      }
    }
    else { 
      digitalWrite(RelayHeater, LOW);
      digitalWrite(RelayCooling, LOW);
      lcd.setCursor ( 15, 3 );
      lcd.print("OFF");
    }
}

