void ChamberControl(float temp){
  
if(digitalRead(Fermswitch) ==HIGH){
  Serial.print ("Set Temp is :   ");
  Serial.println (temp);
    lcd.setCursor ( 15, 3 );
    lcd.print("ON "); 
    if (temp < (SetTemp - 5 ) || temp > (SetTemp + 5)){
      SendSMTPMessage(temp,"Beer",1);
      
    }
    if (temp < (SetTemp - .55) && temp > 33) {
      digitalWrite(RelayHeater, HIGH);
      Serial.println ("Turning Heeater On");
    }
     else if (temp > (SetTemp - .05)){
       digitalWrite(RelayHeater, LOW);
        Serial.println ("Heat Not Required ");
      }
   
   if (temp >(SetTemp + .55)){
     digitalWrite(RelayCooling, HIGH);
      Serial.println ("Turing Cooling On");
     }
    if (temp < (SetTemp + .05)){
      digitalWrite(RelayCooling, LOW);
      Serial.println ("Cooling not Required ");
      }
    }
    else { 
      digitalWrite(RelayHeater, LOW);
      digitalWrite(RelayCooling, LOW);
      Serial.println ("Turing Both Cooling and Heater Off");
      lcd.setCursor ( 15, 3 );
      lcd.print("OFF");
    }
}

