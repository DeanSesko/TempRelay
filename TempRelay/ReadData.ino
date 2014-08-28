void ReadTempData{
  Serial.print(ReadData);
Serial.println(" , Read Data");

if (ReadData > 20){
if (client.connect()) {
    // Make a HTTP request:
    client.println("GET /cgi-bin/gettemps.pl");
    client.println();
    delay(1000);
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");


  }
    if (client.available()) {
   for (int x = 1; x <6; x++){
    char c = client.read();
    Serial.print(c);
  }    
  Serial.println(", High Temp");
    
    }
client.stop();

ReadData=0;
}

