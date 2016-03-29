int UpdateTempData(float temp,String URL,int index,String sensorString){
  

Serial.print(temp);
Serial.print(", ");
Serial.print(sensorString);
Serial.print(", ");
Serial.println(index);

 if (temp < 160){
   if (index > 45){ 
      if (client.connect(server, 80)) {
       // Make a HTTP request:
         client.print(URL);
         client.println(temp);
        } 
      else {
          // kf you didn't get a connection to the server:
            Serial.println("connection to HTTP Server failed");
          }

      client.stop();
      index=0;

  }
}
  delay(1000); 
 

}


