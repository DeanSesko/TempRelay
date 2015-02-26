void PostTempData (){
float temp;
float tmp2;
delay(1000);

//refrigerator
tmp2 = getTemperature(refrigerator);
temp = c2f(tmp2);
URLData = "GET /cgi-bin/post.pl?S='Refrigerator'&T=";
SensorString="refrigerator";
refrigeratorPost =UpdateTempData(temp,URLData,refrigeratorPost,SensorString);

//OutSide
tmp2 = getTemperature(OutSide);
temp = c2f(tmp2);
URLData ="GET /cgi-bin/post.pl?S='Outside'&T=";
SensorString="OutSide";
lcd.setCursor (15,2);        
lcd.print(temp);
OutSidePost =UpdateTempData(temp,URLData,OutSidePost,SensorString);

//BEER
tmp2 = getTemperature(Beer);
temp = c2f(tmp2);
ChamberControl(temp);
URLData ="GET /cgi-bin/post.pl?S='Beer'&T=";
SensorString="Beer";
lcd.setCursor (15,1);        
lcd.print(temp);
BeerPost=UpdateTempData(temp,URLData,BeerPost,SensorString);

//ServerRoom
tmp2 = getTemperature(ServerRoom);
temp = c2f(tmp2);
URLData ="GET /cgi-bin/post.pl?S='ServerRoom'&T=";
SensorString="ServerRoom";
lcd.setCursor (15,3);        
lcd.print(temp);
ServerRoomPost =UpdateTempData(temp,URLData,ServerRoomPost,SensorString);

//Chamber
tmp2 = getTemperature(Chamber);
temp = c2f(tmp2);
URLData ="GET /cgi-bin/post.pl?S='Chamber'&T=";
SensorString="Chamber";
lcd.setCursor (15,0);        
lcd.print(temp);
ChamberPost =UpdateTempData(temp,URLData,ChamberPost,SensorString);

}


  

