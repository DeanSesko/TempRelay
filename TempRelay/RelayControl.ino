void ChamberControl(float temp){
if (Fermenting == 1 ){
    if (temp < myHeaton && temp > 33) {
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

}

