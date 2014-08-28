#include <SPI.h>
#include <OneWire.h>
#include <Ethernet.h>
#include <Stdio.h>
#include <String.h>

//Yelllow is heat goes to 7
//green cool goes to 6
int Fermenting =0;
int Kegging = 0;
int RelayHeater = 7;
int RelayCooling = 6;
float myCoolon ;
float myCooloff;
float myHeaton;
float myHeatoff;
int refrigeratorPost = 2; 
int OutSidePost = 4;
int BeerPost = 6;
int FreezerPost = 8;
int ChamberPost = 10;
int ReadData = 15;
char SensorString[] =""

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 177 };
byte gateway[] = { 192, 168, 1, 254 };
byte subnet[] = { 255, 255, 255, 0 };
byte server[] = { 192, 168, 1, 230 }; 
Client client(server, 80);
OneWire  ow(4);

byte Freezer[8] ={0x28, 0x9F, 0xA0, 0x7B, 0x02, 0x00, 0x00, 0xCB};
byte Chamber[8] ={0x28, 0x51, 0xA1, 0x7B, 0x02, 0x00, 0x00, 0x8A};
byte Beer[8] ={0x28, 0xCF, 0xA3, 0x7B, 0x02, 0x00, 0x00, 0xAB};
byte refrigerator[8] ={0x28, 0xDF, 0x7C, 0x7B, 0x02, 0x00, 0x00, 0xC1};
byte OutSide[8] ={0x28, 0xBE, 0x08, 0x81, 0x02, 0x00, 0x00, 0x2D};



void setup(void) {
  Serial.begin(9600);
  pinMode(RelayHeater, OUTPUT);   
  pinMode(RelayCooling, OUTPUT);   
  digitalWrite(RelayHeater, LOW);   
  digitalWrite(RelayCooling, LOW);  
  Ethernet.begin(mac, ip, gateway, subnet);
 
if (Fermenting == 1){
 myCoolon = 67.55;
 myCooloff = 66.55;
 myHeaton = 65.55;
 myHeatoff = 65.95;
}
if (Kegging ==1){
 myCoolon = 44.00;
 myCooloff = 40.00;
}
  
  }
    
    
    
 

 
void loop(void) {
Serial.println("Start Loop");

float temp;
float tmp2;
tmp2 = getTemperature(Beer);
temp = c2f(tmp2);
BeerPost = BeerPost +1;
 
if (temp < 130){
 if (BeerPost > 60){ 
  if (client.connect()) {
       // Make a HTTP request:
      client.print("GET /cgi-bin/post.pl?S='Beer'&T=");
   client.println(temp);
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }

client.stop();
BeerPost =0;
}

Serial.print(temp);
Serial.print(", Beer, ");
Serial.println(BeerPost);
  
  if (Fermenting == 1 ){
    if (temp < myHeaton) {
      digitalWrite(RelayHeater, HIGH);
    }
     else if (temp > myHeatoff){
       digitalWrite(RelayHeater, LOW);
      }
   
   if (temp >myCoolon){
     digitalWrite(RelayCooling, HIGH);
     }
    if (temp < myCooloff){
      digitalWrite(RelayCooling, LOW);
      }
    }

 if (Kegging == 1 ){
 
   if (temp >myCoolon){
     digitalWrite(RelayCooling, HIGH);
     digitalWrite(RelayHeater, LOW);
     }
   else if (temp < myCooloff){
      digitalWrite(RelayCooling, LOW);
      digitalWrite(RelayHeater, LOW);
 }
 }
 }

delay(1000);



tmp2 = getTemperature(Freezer);
temp = c2f(tmp2);
FreezerPost =FreezerPost + 1;

 if (FreezerPost > 60) { 

 if (client.connect()) {
       // Make a HTTP request:
     client.print("GET /cgi-bin/post.pl?S='Freezer'&T=");
   client.println(temp);
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
FreezerPost =0;
 }
 
Serial.print(temp);
Serial.print(", Freezer, ");
Serial.println(FreezerPost);

delay(1000);

tmp2 = getTemperature(Chamber);
temp = c2f(tmp2);
 ChamberPost = ChamberPost +1;

 if (ChamberPost > 60) { 

 if (client.connect()) {
    // Make a HTTP request:
      client.print("GET /cgi-bin/post.pl?S='Chamber'&T=");
   client.println(temp);
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
client.stop();
 ChamberPost =0;
 }
 
Serial.print(temp);
Serial.print(", Chamber, ");
Serial.println(ChamberPost);
delay(1000);


 
tmp2 = getTemperature(refrigerator);
temp = c2f(tmp2);
refrigeratorPost = refrigeratorPost + 1;
if (refrigeratorPost > 60) { 
 if (client.connect()) {
       // Make a HTTP request:
     client.print("GET /cgi-bin/post.pl?S='refrigerator'&T=");
   client.println(temp);
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  refrigeratorPost = 0;
client.stop();
}
Serial.print(temp);
Serial.print(", refrigerator, ");
Serial.println(refrigeratorPost);
delay(1000);






ReadData++;



    // do nothing forevermore:

  
if (RelayCooling == HIGH){  
  Serial.println("Updating Cooling Relay Status");
  if (client.connect()) {
       // Make a HTTP request:
     client.println("GET /cgi-bin/postrelay.pl?S='Cooling'&T='ON'");
  }
}
    else{
    if (client.connect()) {
      Serial.println("Updating Cooling Relay Status");
       // Make a HTTP request:
   client.println("GET /cgi-bin/postrelay.pl?S='Cooling'&T='OFF'");
    }
    
    
    }
    
    client.stop();  
    
    if (RelayHeater == HIGH){  
  Serial.println("Updating Heating Relay Status");
  if (client.connect()) {
       // Make a HTTP request:
     client.println("GET /cgi-bin/postrelay.pl?S='Heating'&T='ON'");
  }
}
    else{
    if (client.connect()) {
      Serial.println("Updating Heating Relay Status");
       // Make a HTTP request:
   client.println("GET /cgi-bin/postrelay.pl?S='Heating'&T='OFF'");
    }
    
    
    }
    
    client.stop();  
    
    
    }
    
 


