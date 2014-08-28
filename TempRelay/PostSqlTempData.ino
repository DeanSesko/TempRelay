int UpdateTempData(float temp,String URLData,int index, String SensorString ){
index++;
Serial.print(temp);
Serial.print(", ");
Serial.print(SensorString);
Serial.print(", ");
Serial.println(index);
  
 if (temp < 160){
   if (index > 45){ 
 
 if (client.connect(server, 80)) {
       // Make a HTTP request:
      client.print(URLData);
   client.println(temp);
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }

client.stop();
index=0;

}
 }
delay(1000); 
return index;
}


