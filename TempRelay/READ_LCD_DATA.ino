void ReadLCDDAta(){
  
char c ;
int i=0;
int x=0;

ReadLCData++;
if (ReadLCData >10) {
ReadLCData =0;
 if (client.connect(server, 80)) {
    // Make a HTTP request:
    client.println("GET /cgi-bin/text.txt");
    client.println();
    delay(1000);
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
    if (client.available()) {
    
 do 
  {
    if (i !=0 ){
    LCDString+= c;
    }
    i++;
        c = client.read();
        if (i==255){
          c='|';
        }
     } while (c != '|');  
 
  if (OldString  != LCDString){ 
      write_buf_index = 0;
 for (x = 0; x <=LCDString.length();x++){
   int num_presses;
  
  buffer[write_buf_index] = LCDString.charAt(x);
   write_buf_index++;
   }
         
        buffer[write_buf_index] = 0; 
        
         Serial.print("Process phrase: ");
         Serial.println((char *)buffer);
          display_state = ENTER_MENU;  // uses the write_buf_index as the total length.
  x=0;
  
  for (WordIndex=0; WordIndex< 4000; WordIndex++){ 
    delay(20);
  continue_processing_display_comm();
  reset_pulse();
  check_pause();
  }
  
  WordIndex=0;
  
  
 OldString = LCDString;
  }
  i=0;
    
    }
client.stop();
}
LCDString="";
 
}
