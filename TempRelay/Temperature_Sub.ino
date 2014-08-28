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
OutSidePost =UpdateTempData(temp,URLData,OutSidePost,SensorString);

//BEER
tmp2 = getTemperature(Beer);
temp = c2f(tmp2);
ChamberControl(temp);
URLData ="GET /cgi-bin/post.pl?S='Beer'&T=";
SensorString="Beer";
BeerPost=UpdateTempData(temp,URLData,BeerPost,SensorString);


//FREEZER
tmp2 = getTemperature(Freezer);
temp = c2f(tmp2);
URLData ="GET /cgi-bin/post.pl?S='Freezer'&T=";
SensorString="Freezer";
FreezerPost =UpdateTempData(temp,URLData,FreezerPost,SensorString);



//Chamber
tmp2 = getTemperature(Chamber);
temp = c2f(tmp2);
URLData ="GET /cgi-bin/post.pl?S='Chamber'&T=";
SensorString="Chamber";
ChamberPost =UpdateTempData(temp,URLData,ChamberPost,SensorString);

}


  

