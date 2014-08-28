void PostSqlData(char SensorString, float currentTemp){
tmp2 = getTemperature(SensorString);
temp = c2f(tmp2);
OutSidePost = OutSidePost + 1;


if (OutSidePost > 60) { 

 if (client.connect()) {
      // Make a HTTP request:
    client.print("GET /cgi-bin/post.pl?S='OutSide'&T=");
   client.println(temp);
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 OutSidePost =0; 
}
client.stop();

Serial.print(temp);
Serial.print(", OutSide, ");
Serial.println(OutSidePost);
delay(1000);

}
