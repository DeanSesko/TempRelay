void ChamberControl(float temp){
if (Fermenting == 1 ){
    if (temp < myHeaton) {
      digitalWrite(RelayHeater, HIGH);
    }
     else if (temp > myHeatoff){
       digitalWrite(RelayHeater, LOW);
      }
   
   if (temp >myCoolon){
     digitalWrite(RelayCooling, HIGH);
     }
    if (temp < myCooloff){
      digitalWrite(RelayCooling, LOW);
      }
    }

 if (Kegging == 1 ){
 
   if (temp >myCoolon){
     digitalWrite(RelayCooling, HIGH);
     digitalWrite(RelayHeater, LOW);
     }
   else if (temp < myCooloff){
      digitalWrite(RelayCooling, LOW);
      digitalWrite(RelayHeater, LOW);
 }
 }
}

