void UpdateRelayData(){

  PostData++;

if (PostData >20) {
  PostData =0;
if (digitalRead(RelayCooling)  == HIGH){  
  Serial.println("Updating Cooling Relay Status");
  if (client.connect(server, 80)) {
       // Make a HTTP request:
     client.println("GET /cgi-bin/postrelay.pl?S='Cooling'&T='ON'&U=2");
  }
}
    else{
     if (client.connect(server, 80)) {
      Serial.println("Updating Cooling Relay Status");
       // Make a HTTP request:
   client.println("GET /cgi-bin/postrelay.pl?S='Cooling'&T='OFF'&U=2");
    }
    
    
    }
    
    client.stop();  
    if (digitalRead(RelayHeater)  == HIGH){  
  Serial.println("Updating Heating Relay Status");
   if (client.connect(server, 80)) {
       // Make a HTTP request:
     client.println("GET /cgi-bin/postrelay.pl?S='Heating'&T='ON'&U=2");
  }
}
    else{
    if (client.connect(server, 80)) {
      Serial.println("Updating Heating Relay Status");
       // Make a HTTP request:
   client.println("GET /cgi-bin/postrelay.pl?S='Heating'&T='OFF'&U=2");
    }
    
    
    }
    
    client.stop();  
    
}


}
