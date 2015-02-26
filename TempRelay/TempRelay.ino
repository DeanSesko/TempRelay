#include <SPI.h>
#include <OneWire.h>
#include <Ethernet.h>
#include <Stdio.h>
#include <String.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

//7 Segment
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

//LCD
#define I2C_ADDR    0x27  
#define BACKLIGHT_PIN 3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C lcd(I2C_ADDR,
                      En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin,
                      BACKLIGHT_PIN, POSITIVE);


//white Orange Stripe is for Heater ping 7
//White Blue Stripe is for Cooling pin 6
//Green is Ground 
// OneWIre is blue Pin 4
//Orage is 5V
//green cool goes to 6

// PIN Setup

int TempSetup = 9;
int Fermswitch =8;
int RelayHeater = 7;
int RelayCooling = 6;
int Fermenting =0;
OneWire  ow(2);
int DownButton =5;
int UpButton = 4;
char charVal[10];               

String stringVal = ""; 
int ClearLCD =0;

//Fermentation  Temps
float SetTemp = 77.00;
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

//Production MAC Address 
//byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xcc, 0x09 };

//IP Info 
byte ip[] = { 192, 168, 1, 33 };
byte gateway[] = { 192, 168, 1, 254 };
byte subnet[] = { 255, 255, 255, 0 };
byte server[] = { 192, 168, 1, 230 }; 
EthernetClient client;


//OneWire Addresses
byte ServerRoom[8] ={0x28, 0xB5, 0x0D, 0xCE, 0x03, 0x00, 0x00, 0xD6};
byte Chamber[8] ={0x28, 0x51, 0xA1, 0x7B, 0x02, 0x00, 0x00, 0x8A};
byte Beer[8] ={0x28, 0xCF, 0xA3, 0x7B, 0x02, 0x00, 0x00, 0xAB};
byte refrigerator[8] ={0x28, 0xDF, 0x7C, 0x7B, 0x02, 0x00, 0x00, 0xC1};
byte OutSide[8] ={0x28, 0xBE, 0x08, 0x81, 0x02, 0x00, 0x00, 0x2D};

void setup(void) {
  //Setup Serial
  Serial.begin(57600);
  alpha4.begin(0x70);  // pass in the address
  alpha4.clear();
  alpha4.writeDisplay();
  lcd.begin(20,4);        // 20 columns by 4 rows on display
  lcd.setBacklight(HIGH); // Turn on backlight, LOW for off
  lcdSetup();

  
  //Set initial States
  pinMode(RelayHeater, OUTPUT);   
  pinMode(RelayCooling, OUTPUT);  
  pinMode(Fermswitch,OUTPUT); 
  pinMode(UpButton,OUTPUT);  
  pinMode(DownButton,OUTPUT); 
  pinMode(TempSetup,OUTPUT);  
  digitalWrite(TempSetup, LOW); 
  digitalWrite(DownButton, LOW); 
  digitalWrite(UpButton, LOW);  
  digitalWrite(RelayHeater, LOW);   
  digitalWrite(RelayCooling, LOW);  
  Ethernet.begin(mac, ip, gateway, subnet);
  dtostrf(SetTemp, 4, 2, charVal);  
  ledprint(charVal);
  
}
 
void loop(void) {
  if(digitalRead(TempSetup) ==HIGH) {
   if(ClearLCD == 0){
     ClearLCD =1;
     lcd.clear();
      lcd.setCursor ( 0, 0 );      
      lcd.print("Setup Mode");
      lcd.setCursor ( 0, 2 );           
      lcd.print("Red = Temp UP");
      lcd.setCursor ( 0, 3 );
      lcd.print("Black = Temp Down");
       }
   
      Setup();
    }

  else {
    if (ClearLCD ==1){
 lcdSetup();
  ClearLCD =0;
    }
    
  Serial.println("Start Loop");
    FermCheck();
    PostTempData();
    ReadSQLRelayData();
    UpdateRelayData();
    }
}

