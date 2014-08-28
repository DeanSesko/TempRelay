#include <SPI.h>
#include <OneWire.h>
#include <Ethernet.h>
#include <Stdio.h>
#include <String.h>



//white Orange Stripe is for Heater ping 7
//White Blue Stripe is for Cooling pin 6
//Green is Ground 
// OneWIre is blue Pin 4
//Orage is 5V
//
//green cool goes to 6
int Fermenting =1;
int Kegging = 0;
int RelayHeater = 7;
int RelayCooling = 6;
float myCoolon ;
float myCooloff;
float myHeaton;
float myHeatoff;
int refrigeratorPost = 32; 
int OutSidePost = 34;
int BeerPost = 36;
int ServerRoomPost = 38;
int ChamberPost = 40;
int ReadData = 15;
int PostData = 15;
String URLData="";
String SensorString="";
int TempIndex=0;
String LCDString;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xcc, 0x09 };
byte ip[] = { 192, 168, 1, 32 };
byte gateway[] = { 192, 168, 1, 254 };
byte subnet[] = { 255, 255, 255, 0 };
byte server[] = { 192, 168, 1, 230 }; 
EthernetClient client;

OneWire  ow(4);

byte ServerRoom[8] ={0x28, 0xB5, 0x0D, 0xCE, 0x03, 0x00, 0x00, 0xD6};
byte Chamber[8] ={0x28, 0x51, 0xA1, 0x7B, 0x02, 0x00, 0x00, 0x8A};
byte Beer[8] ={0x28, 0xCF, 0xA3, 0x7B, 0x02, 0x00, 0x00, 0xAB};
byte refrigerator[8] ={0x28, 0xDF, 0x7C, 0x7B, 0x02, 0x00, 0x00, 0xC1};
byte OutSide[8] ={0x28, 0xBE, 0x08, 0x81, 0x02, 0x00, 0x00, 0x2D};



void setup(void) {
  Serial.begin(57600);
  pinMode(RelayHeater, OUTPUT);   
  pinMode(RelayCooling, OUTPUT);   
  digitalWrite(RelayHeater, LOW);   
  digitalWrite(RelayCooling, LOW);  
  Ethernet.begin(mac, ip, gateway, subnet);
  
  
  
  
 
if (Fermenting == 1){
 myCoolon = 70.55;
 myCooloff = 69.95;
 myHeaton = 69.55;
 myHeatoff = 69.95;
}
if (Kegging ==1){
 myCoolon = 44.00;
 myCooloff = 40.00;
}
    }
 

 
void loop(void) {
Serial.println("Start Loop");

PostTempData();
ReadSQLRelayData();
UpdateRelayData();





}

