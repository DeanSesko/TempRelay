#include <SPI.h>
#include <OneWire.h>
#include <Ethernet.h>
#include <Stdio.h>
#include <String.h>

//Yelllow is heat goes to 7
//green cool goes to 6
int Fermenting =1;
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
int PostData = 15;
String URLData="";
String SensorString="";
int TempIndex=0;

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
 myCoolon = 68.55;
 myCooloff = 67.95;
 myHeaton = 67.55;
 myHeatoff = 67.95;
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

