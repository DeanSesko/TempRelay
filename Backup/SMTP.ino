void SendSMTPMessage(float temp, String sensor,int FermError){
  
if(temp <= 32 || temp >=185 || FermError == 1) {
  MailFaultSent = MailFaultSent + 1;
  if ( MailFaultSent >= 150 ){
      MailFaultSent =1;
  }
  
  if(MailFaultSent <= 1){
  Serial.println("connecting...");
    byte SMTPserver[] = { 192,168,1,216 };
  
    if (client.connect(SMTPserver, 25)) {
     Serial.println("connected");
     client.println("EHLO");
     client.println("MAIL FROM:DeanSesko@PlanetSesko.com");
     client.println("RCPT TO:DeanSesko@PlanetSesko.com");
     client.println("DATA");
     client.println("SUBJECT: Temperature Issue");
     client.println();
     client.print("The ");
     client.print(sensor);
     client.print(" Sensor");
     client.println(" is out of temperature range.");
     client.print("The current temperature reading is: ");
     client.println(temp);
     client.println("");
     client.println("");
     client.println(".");
     client.println(".");
     client.stop();
    
   } 
   else {Serial.println("connection failed"); }
 }
}
else {MailFaultSent =0;}
}

