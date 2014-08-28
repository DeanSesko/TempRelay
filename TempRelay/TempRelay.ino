#include <SPI.h>
#include <OneWire.h>
#include <Ethernet.h>
#include <Stdio.h>
#include <String.h>
#define ON_OFF_PIN 2
#define UP_PIN 3
#define DOWN_PIN 5
#define PULSE_DUR 30 //20 // note: these delay times seem to be effected by battery level.
#define DEBUG_PRINT 0
int PAUSE_DUR  = 85;
int ReadLCData =0;
int WordIndex=0;
long lastTime;
long slowTimer;
long pulseStartTime;
long pauseStartTime;


char on_off_mode = 0;
char up_mode = 0;
char down_mode = 0;
String OldString;
char pulseActive = 0;
char pausing = 0;

unsigned char cur_letter_pos;
unsigned char target_letter_pos;

void ground_pin(unsigned char pin, unsigned char grounded);
void reset_pulse(void);
void pulse_pin(unsigned char pin);
void check_pause(void);
unsigned char get_num_presses(unsigned char);

enum DISPLAY_COMM_STATE {
  DO_NOTHING = 0,
  ENTER_MENU,
  SELECT_INPUT,
  ENTER_MSG_CHANGE,
  START_SCROLLING_TO_LETTER,
  SCROLLING
} display_state;



unsigned char buffer[256];
unsigned char sms_buffer[256];
int sms_buf_index;
int write_buf_index = 0;
int read_buf_index = 0;
char sms_ready_flag = 0;

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
  
  pinMode(ON_OFF_PIN,INPUT);
  pinMode(UP_PIN,INPUT);
  pinMode(DOWN_PIN,INPUT);
  digitalWrite(ON_OFF_PIN,0);
  digitalWrite(UP_PIN,0);
  digitalWrite(DOWN_PIN,0);

  // Note start time
  lastTime = 0;
  slowTimer = 0;
  pulseStartTime = 0;
  pauseStartTime = 0;
  
  display_state = DO_NOTHING;
  
  
  
 
if (Fermenting == 1){
 myCoolon = 65.55;
 myCooloff = 64.95;
 myHeaton = 64.55;
 myHeatoff = 64.95;
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
ReadLCDDAta();





}

