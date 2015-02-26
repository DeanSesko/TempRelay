void FermCheck(){
  
  if(digitalRead(Fermswitch) ==HIGH){
    Serial.println("Turning Fermenation on");
 
  Fermenting =1;
    myCoolon = SetTemp + .55;
    myCooloff =SetTemp + .05;
    myHeaton = SetTemp - .55;
    myHeatoff =SetTemp - .05;
  }
else
  {
 Serial.println("Turning Fermenation Off");  
     Fermenting =0;
  }
}
