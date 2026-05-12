/*
  SMART 4-WAY (FINAL vSMART)
  ✅ Smart-skip based on LM393 vehicle sensors (D47-D50) + ped requests
  ✅ Vehicle waiting shown on LCD1 top line (mini indicators)
  ✅ Ped request popup on LCD2 after button press
  ✅ Maintenance RGB LED is PURPLE (solid)
  ✅ Vehicle detect is ACTIVE LOW (LM393 open-collector): LOW = vehicle present (LED ON)
  ✅ Emergency exit: 9110#
  ✅ Maintenance toggle: 1235#

  PINS (YOUR SETUP)
  Ped Buttons (INPUT_PULLUP, button to GND):
    W=D2, N=D51, S=D52, E=D53

  LM393 vehicle sensors (bare LM393 output with pull-up + LED):
    N=D47, E=D48, S=D49, W=D50
*/

#include <LiquidCrystal.h>
#include <Keypad.h>

/* ===================== LCDs ===================== */
LiquidCrystal lcd1(11, 12, 13, 14, 15, 16);          // Traffic LCD
LiquidCrystal lcd2(A0, A1, A2, A3, A4, A5);          // Ped LCD

/* ===================== Speaker ===================== */
const int SPK = 46;
unsigned long beepLast = 0;
void stopBeep() { noTone(SPK); }
void slowBeep() {
  unsigned long now = millis();
  if (now - beepLast >= 1000) { beepLast = now; tone(SPK, 2000, 120); }
}
void fastBeep() {
  unsigned long now = millis();
  if (now - beepLast >= 350) { beepLast = now; tone(SPK, 2200, 90); }
}

/* ===================== Keypad ===================== */
const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {3,4,5,6};
byte colPins[COLS] = {7,8,9,10};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String codeBuffer = "";
const String MAINT_CODE = "1235#";
const String EMERG_EXIT_CODE = "9110#";

/* ===================== RGB Status LED ===================== */
const int RGB_R = A6;
const int RGB_G = A7;
const int RGB_B = A8;
const bool RGB_COMMON_ANODE = false;

void rgbWrite(bool r, bool g, bool b) {
  if (!RGB_COMMON_ANODE) {
    digitalWrite(RGB_R, r ? HIGH : LOW);
    digitalWrite(RGB_G, g ? HIGH : LOW);
    digitalWrite(RGB_B, b ? HIGH : LOW);
  } else {
    digitalWrite(RGB_R, r ? LOW : HIGH);
    digitalWrite(RGB_G, g ? LOW : HIGH);
    digitalWrite(RGB_B, b ? LOW : HIGH);
  }
}
void rgbOff()    { rgbWrite(false,false,false); }
void rgbRed()    { rgbWrite(true,false,false); }
void rgbPurple() { rgbWrite(true,false,true); }   // ✅ Maintenance LED color

/* ===================== Emergency PIR inputs ===================== */
const int PIR_NS = A10;
const int PIR_EW = A11;
bool pirArmed = true;

/* ===================== LM393 vehicle sensors (digital OUT) ===================== */
const int VS_N = 47;
const int VS_E = 48;
const int VS_S = 49;
const int VS_W = 50;

/*
  ✅ ACTIVE LOW because LM393 OUT is open collector and your "vehicle detected" LED is wired:
     +5V -> resistor -> LED -> OUT (pin 1)  (LED ON when OUT sinks LOW)
  So Arduino reads LOW when vehicle is detected.
*/
const bool VEH_ACTIVE_LOW = true;

bool vehicleDetected(int pin) {
  int v = digitalRead(pin);
  return VEH_ACTIVE_LOW ? (v == LOW) : (v == HIGH);
}

/* ===================== Traffic lights ===================== */
const int N_RED=22,N_YEL=23,N_GRN=24,N_TURN=25;
const int E_RED=26,E_YEL=27,E_GRN=28,E_TURN=29;
const int S_RED=30,S_YEL=31,S_GRN=32,S_TURN=33;
const int W_RED=34,W_YEL=35,W_GRN=36,W_TURN=37;

/* ===================== Pedestrians ===================== */
const int PED_N_WALK=38, PED_N_STOP=39;
const int PED_E_WALK=40, PED_E_STOP=41;
const int PED_W_WALK=42, PED_W_STOP=43;
const int PED_S_WALK=44, PED_S_STOP=45;

/* ===================== Ped Buttons + Request LEDs ===================== */
const int PED_BTN_W = 2;
const int PED_BTN_N = 51;
const int PED_BTN_S = 52;
const int PED_BTN_E = 53;

const int PED_REQ_LED_N = 17;
const int PED_REQ_LED_E = 18;
const int PED_REQ_LED_S = 19;
const int PED_REQ_LED_W = 20;

bool pedReqN=false, pedReqE=false, pedReqS=false, pedReqW=false;

/* ===================== LCD2 Request Popup ===================== */
bool pedMsgActive = false;
unsigned long pedMsgStart = 0;
String pedMsgLine1 = "";
String pedMsgLine2 = "";
const unsigned long PED_MSG_TIME = 2000;

/* ===================== Timing ===================== */
const unsigned long ALL_RED_TIME=700;
const unsigned long TURN_TIME=11000;
const unsigned long GREEN_TIME=18000;
const unsigned long YELLOW_TIME=6000;
const unsigned long TURN_BLINK_MS=350;
const unsigned long PED_BLINK_MS=400;
const unsigned long PED_WALK_BLINK_LAST_MS=5000;

/* ===================== Modes ===================== */
bool maintenanceMode=false;

enum EmergDir { EM_NONE, EM_NS, EM_EW };
bool emergencyMode=false;
EmergDir emergencyDir=EM_NONE;
unsigned long emergencyStart=0;
const unsigned long EMERGENCY_CLEAR_MS = 1200;

/* ===================== Phase machine ===================== */
enum Phase {
  P_ALL_RED_1,
  P_NS_TURN,
  P_NS_GREEN,
  P_NS_YELLOW,
  P_ALL_RED_2,
  P_EW_TURN,
  P_EW_GREEN,
  P_EW_YELLOW
};
Phase phase=P_ALL_RED_1;
unsigned long phaseStart=0;

/* ===================== LCD helpers ===================== */
String last1r0="", last1r1="", last2r0="", last2r1="";
unsigned long lcdLast=0;

String pad16(const String& s){
  if(s.length()>=16) return s.substring(0,16);
  String out=s;
  while(out.length()<16) out += " ";
  return out;
}
void lcd1SetRows(const String& r0, const String& r1){
  String a=pad16(r0), b=pad16(r1);
  if(a!=last1r0){ lcd1.setCursor(0,0); lcd1.print(a); last1r0=a; }
  if(b!=last1r1){ lcd1.setCursor(0,1); lcd1.print(b); last1r1=b; }
}
void lcd2SetRows(const String& r0, const String& r1){
  String a=pad16(r0), b=pad16(r1);
  if(a!=last2r0){ lcd2.setCursor(0,0); lcd2.print(a); last2r0=a; }
  if(b!=last2r1){ lcd2.setCursor(0,1); lcd2.print(b); last2r1=b; }
}
uint16_t ceilSecondsRemaining(unsigned long ms){
  return (uint16_t)((ms + 999UL)/1000UL);
}
unsigned long phaseDuration(){
  switch(phase){
    case P_ALL_RED_1: return ALL_RED_TIME;
    case P_NS_TURN:   return TURN_TIME;
    case P_NS_GREEN:  return GREEN_TIME;
    case P_NS_YELLOW: return YELLOW_TIME;
    case P_ALL_RED_2: return ALL_RED_TIME;
    case P_EW_TURN:   return TURN_TIME;
    case P_EW_GREEN:  return GREEN_TIME;
    case P_EW_YELLOW: return YELLOW_TIME;
  }
  return 1000;
}

/* ===================== Output helpers ===================== */
void trafficAllOff(){
  int pins[] = {
    N_RED,N_YEL,N_GRN,N_TURN,
    E_RED,E_YEL,E_GRN,E_TURN,
    S_RED,S_YEL,S_GRN,S_TURN,
    W_RED,W_YEL,W_GRN,W_TURN
  };
  for(unsigned i=0;i<sizeof(pins)/sizeof(pins[0]);i++) digitalWrite(pins[i], LOW);
}
void trafficAllRedSolid(){
  trafficAllOff();
  digitalWrite(N_RED,HIGH); digitalWrite(E_RED,HIGH);
  digitalWrite(S_RED,HIGH); digitalWrite(W_RED,HIGH);
}
void trafficNSGreen(){
  trafficAllOff();
  digitalWrite(N_GRN,HIGH); digitalWrite(S_GRN,HIGH);
  digitalWrite(E_RED,HIGH); digitalWrite(W_RED,HIGH);
}
void trafficEWGreen(){
  trafficAllOff();
  digitalWrite(E_GRN,HIGH); digitalWrite(W_GRN,HIGH);
  digitalWrite(N_RED,HIGH); digitalWrite(S_RED,HIGH);
}
void trafficNSYellow(){
  trafficAllOff();
  digitalWrite(N_YEL,HIGH); digitalWrite(S_YEL,HIGH);
  digitalWrite(E_RED,HIGH); digitalWrite(W_RED,HIGH);
}
void trafficEWYellow(){
  trafficAllOff();
  digitalWrite(E_YEL,HIGH); digitalWrite(W_YEL,HIGH);
  digitalWrite(N_RED,HIGH); digitalWrite(S_RED,HIGH);
}
void pedAllStopSolid(){
  digitalWrite(PED_N_WALK, LOW); digitalWrite(PED_N_STOP, HIGH);
  digitalWrite(PED_E_WALK, LOW); digitalWrite(PED_E_STOP, HIGH);
  digitalWrite(PED_S_WALK, LOW); digitalWrite(PED_S_STOP, HIGH);
  digitalWrite(PED_W_WALK, LOW); digitalWrite(PED_W_STOP, HIGH);
}

/* ===================== Request LEDs ===================== */
void setReqLedPins(){
  digitalWrite(PED_REQ_LED_N, pedReqN ? HIGH : LOW);
  digitalWrite(PED_REQ_LED_E, pedReqE ? HIGH : LOW);
  digitalWrite(PED_REQ_LED_S, pedReqS ? HIGH : LOW);
  digitalWrite(PED_REQ_LED_W, pedReqW ? HIGH : LOW);
}

/* ===================== Popup helper ===================== */
void triggerPedMsg(const String& l1, const String& l2){
  pedMsgActive = true;
  pedMsgStart = millis();
  pedMsgLine1 = l1;
  pedMsgLine2 = l2;
}

/* ===================== Read buttons ===================== */
void readPedButtons(){
  static bool lastN=true, lastE=true, lastS=true, lastW=true;
  bool n = digitalRead(PED_BTN_N);
  bool e = digitalRead(PED_BTN_E);
  bool s = digitalRead(PED_BTN_S);
  bool w = digitalRead(PED_BTN_W);

  if(lastN==HIGH && n==LOW){ pedReqN=true; triggerPedMsg("N PED REQUEST ", "PLEASE WAIT"); }
  if(lastS==HIGH && s==LOW){ pedReqS=true; triggerPedMsg("S PED REQUEST ", "PLEASE WAIT"); }
  if(lastE==HIGH && e==LOW){ pedReqE=true; triggerPedMsg("E PED REQUEST ", "PLEASE WAIT"); }
  if(lastW==HIGH && w==LOW){ pedReqW=true; triggerPedMsg("W PED REQUEST ", "PLEASE WAIT"); }

  lastN=n; lastE=e; lastS=s; lastW=w;
}

/* ===================== Smart demand logic ===================== */
bool nsDemand(){
  bool veh = vehicleDetected(VS_N) || vehicleDetected(VS_S);
  bool ped = pedReqN || pedReqS;
  return veh || ped;
}
bool ewDemand(){
  bool veh = vehicleDetected(VS_E) || vehicleDetected(VS_W);
  bool ped = pedReqE || pedReqW;
  return veh || ped;
}

/* ===================== LCD strings ===================== */
String trafficCountdownLine(uint16_t sec){
  String s="REM: ";
  if(sec<10) s+="0";
  s += String(sec) + " sec";
  return s;
}
String pedTopLine(bool nsWalk, bool ewWalk){
  bool nsReq = (pedReqN || pedReqS);
  bool ewReq = (pedReqE || pedReqW);

  String ns = String("NS: ") + (nsWalk ? "Walk" : "Stop");
  ns += (nsReq ? "*" : " ");

  String ew = String("EW: ") + (ewWalk ? "Walk" : "Stop");
  ew += (ewReq ? "*" : " ");

  return ns + " " + ew;
}
String pedCountdownLine(const String& dir, uint16_t sec, bool show){
  if(!show) return "STOP";
  String s = dir + ": ";
  if(sec<10) s+="0";
  s += String(sec) + " sec";
  return s;
}
String vehicleLineMini(){
  char n = vehicleDetected(VS_N) ? 'N' : '-';
  char e = vehicleDetected(VS_E) ? 'E' : '-';
  char s = vehicleDetected(VS_S) ? 'S' : '-';
  char w = vehicleDetected(VS_W) ? 'W' : '-';
  String out = "V:";
  out += n; out += e; out += s; out += w;
  return out; // "V:NESW" style
}

/* ===================== Keypad ===================== */
void checkKeypad(){
  char k = keypad.getKey();
  if(!k) return;

  if(k=='*'){ codeBuffer=""; return; }

  codeBuffer += k;
  if(codeBuffer.length() > 8) codeBuffer.remove(0, codeBuffer.length()-8);

  if(codeBuffer.endsWith(MAINT_CODE)){
    maintenanceMode = !maintenanceMode;
    codeBuffer="";
  }
  if(codeBuffer.endsWith(EMERG_EXIT_CODE)){
    emergencyMode=false;
    emergencyDir=EM_NONE;
    codeBuffer="";
    pirArmed=false;
    phase=P_ALL_RED_1;
    phaseStart=millis();
  }
}

/* ===================== Emergency PIR ===================== */
void checkEmergencyPIR(){
  if(emergencyMode) return;

  if(!pirArmed){
    if(digitalRead(PIR_NS)==LOW && digitalRead(PIR_EW)==LOW) pirArmed=true;
    return;
  }
  if(digitalRead(PIR_NS)==HIGH){
    emergencyMode=true; emergencyDir=EM_NS; emergencyStart=millis(); pirArmed=false;
  } else if(digitalRead(PIR_EW)==HIGH){
    emergencyMode=true; emergencyDir=EM_EW; emergencyStart=millis(); pirArmed=false;
  }
}

void runEmergency(bool doLCD){
  rgbRed();
  pedAllStopSolid();
  stopBeep();

  unsigned long el = millis() - emergencyStart;
  if(el < EMERGENCY_CLEAR_MS){
    trafficAllRedSolid();
    if(doLCD){
      lcd1SetRows("** EMERGENCY **","ALL RED CLEAR ");
      lcd2SetRows("ALL PEDS STOP  ","EXIT: 9110#   ");
    }
    return;
  }

  if(emergencyDir==EM_NS){
    trafficNSGreen();
    if(doLCD){
      lcd1SetRows("** EMERGENCY **","NS GREEN HOLD ");
      lcd2SetRows("ALL PEDS STOP  ","EXIT: 9110#   ");
    }
  } else if(emergencyDir==EM_EW){
    trafficEWGreen();
    if(doLCD){
      lcd1SetRows("** EMERGENCY **","EW GREEN HOLD ");
      lcd2SetRows("ALL PEDS STOP  ","EXIT: 9110#   ");
    }
  } else {
    trafficAllRedSolid();
  }
}

void runMaintenance(bool doLCD){
  rgbPurple(); // ✅ PURPLE solid

  static bool blink=false;
  static unsigned long t=0;
  if(millis()-t>=350){ t=millis(); blink=!blink; }

  trafficAllOff();
  digitalWrite(N_RED,blink);
  digitalWrite(E_RED,blink);
  digitalWrite(S_RED,blink);
  digitalWrite(W_RED,blink);

  pedAllStopSolid();

  digitalWrite(PED_REQ_LED_N,LOW);
  digitalWrite(PED_REQ_LED_E,LOW);
  digitalWrite(PED_REQ_LED_S,LOW);
  digitalWrite(PED_REQ_LED_W,LOW);

  stopBeep();

  if(doLCD){
    lcd1SetRows("** MAINT MODE **","RED BLINK ONLY ");
    lcd2SetRows("ALL PEDS STOP  ","EXIT: 1235#   ");
  }
}

/* ===================== Setup ===================== */
void setup(){
  pinMode(SPK, OUTPUT);
  stopBeep();

  pinMode(RGB_R, OUTPUT);
  pinMode(RGB_G, OUTPUT);
  pinMode(RGB_B, OUTPUT);
  rgbOff();

  pinMode(PIR_NS, INPUT);
  pinMode(PIR_EW, INPUT);

  pinMode(VS_N, INPUT);
  pinMode(VS_E, INPUT);
  pinMode(VS_S, INPUT);
  pinMode(VS_W, INPUT);

  pinMode(PED_BTN_N, INPUT_PULLUP);
  pinMode(PED_BTN_E, INPUT_PULLUP);
  pinMode(PED_BTN_S, INPUT_PULLUP);
  pinMode(PED_BTN_W, INPUT_PULLUP);

  pinMode(PED_REQ_LED_N, OUTPUT);
  pinMode(PED_REQ_LED_E, OUTPUT);
  pinMode(PED_REQ_LED_S, OUTPUT);
  pinMode(PED_REQ_LED_W, OUTPUT);
  setReqLedPins();

  int outs[]={
    N_RED,N_YEL,N_GRN,N_TURN,E_RED,E_YEL,E_GRN,E_TURN,
    S_RED,S_YEL,S_GRN,S_TURN,W_RED,W_YEL,W_GRN,W_TURN,
    PED_N_WALK,PED_N_STOP,PED_E_WALK,PED_E_STOP,PED_S_WALK,PED_S_STOP,PED_W_WALK,PED_W_STOP
  };
  for(unsigned i=0;i<sizeof(outs)/sizeof(outs[0]);i++) pinMode(outs[i],OUTPUT);

  lcd1.begin(16,2);
  lcd2.begin(16,2);

  trafficAllRedSolid();
  pedAllStopSolid();

  lcd1SetRows("SMART 4-WAY SYS","Booting...     ");
  lcd2SetRows("NS: Stop  EW:Stop","STOP           ");

  phase=P_ALL_RED_1;
  phaseStart=millis();
}

/* ===================== Loop ===================== */
void loop(){
  checkKeypad();
  if(!maintenanceMode) checkEmergencyPIR();

  bool doLCD = (millis() - lcdLast) > 200;
  if(doLCD) lcdLast = millis();

  if(maintenanceMode){ runMaintenance(doLCD); return; }
  if(emergencyMode){ runEmergency(doLCD); return; }

  rgbOff();

  readPedButtons();
  setReqLedPins();

  // ✅ SMART SKIP at the all-red gates
  if(phase == P_ALL_RED_1){
    if(!nsDemand() && ewDemand()){
      phase = P_EW_TURN;
      phaseStart = millis();
    }
  }
  if(phase == P_ALL_RED_2){
    if(!ewDemand() && nsDemand()){
      phase = P_NS_TURN;
      phaseStart = millis();
    }
  }

  unsigned long dur = phaseDuration();
  unsigned long el  = millis() - phaseStart;
  bool done = (el >= dur);
  bool turnBlink = ((millis()/TURN_BLINK_MS)%2)==0;

  unsigned long leftMs = (dur > el) ? (dur - el) : 0;
  uint16_t trafficSec = ceilSecondsRemaining(leftMs);

  bool nsWalk=false, ewWalk=false;
  bool pedCounting=false;
  bool walkBlinking=false;
  bool walkSolid=false;
  bool redBlinking=false;

  String pedDir="";
  uint16_t pedSec=0;

  String trafficTop="";

  switch(phase){

    case P_ALL_RED_1:{
      trafficAllRedSolid();
      pedAllStopSolid();
      trafficTop="ALL RED " + vehicleLineMini();
      if(done){
        if(nsDemand() || !ewDemand()) phase=P_NS_TURN;
        else                         phase=P_EW_TURN;
        phaseStart=millis();
      }
    }break;

    case P_NS_TURN:{
      trafficAllRedSolid();
      digitalWrite(N_TURN, turnBlink);
      digitalWrite(S_TURN, turnBlink);

      unsigned long left = (TURN_TIME>el)?(TURN_TIME-el):0;

      if(left <= PED_WALK_BLINK_LAST_MS){
        nsWalk=true; ewWalk=false;
        pedCounting=true; pedDir="NS"; pedSec=ceilSecondsRemaining(left);
        walkBlinking=true;

        bool pb = ((millis()/PED_BLINK_MS)%2)==0;
        digitalWrite(PED_N_WALK, pb); digitalWrite(PED_N_STOP, LOW);
        digitalWrite(PED_S_WALK, pb); digitalWrite(PED_S_STOP, LOW);

        pedReqN=false; pedReqS=false;
        setReqLedPins();
      } else {
        pedAllStopSolid();
      }

      trafficTop="NS TURN " + vehicleLineMini();
      if(done){ phase=P_NS_GREEN; phaseStart=millis(); }
    }break;

    case P_NS_GREEN:{
      trafficNSGreen();

      nsWalk=true; ewWalk=false;
      pedCounting=true; pedDir="NS";
      pedSec=ceilSecondsRemaining((GREEN_TIME>el)?(GREEN_TIME-el):0);
      walkSolid=true;

      digitalWrite(PED_N_WALK, HIGH); digitalWrite(PED_N_STOP, LOW);
      digitalWrite(PED_S_WALK, HIGH); digitalWrite(PED_S_STOP, LOW);

      digitalWrite(PED_E_WALK, LOW);  digitalWrite(PED_E_STOP, HIGH);
      digitalWrite(PED_W_WALK, LOW);  digitalWrite(PED_W_STOP, HIGH);

      trafficTop="NS GREEN " + vehicleLineMini();
      if(done){ phase=P_NS_YELLOW; phaseStart=millis(); }
    }break;

    case P_NS_YELLOW:{
      trafficNSYellow();

      bool pb = ((millis()/PED_BLINK_MS)%2)==0;
      digitalWrite(PED_N_WALK, LOW); digitalWrite(PED_N_STOP, pb);
      digitalWrite(PED_S_WALK, LOW); digitalWrite(PED_S_STOP, pb);

      digitalWrite(PED_E_WALK, LOW); digitalWrite(PED_E_STOP, HIGH);
      digitalWrite(PED_W_WALK, LOW); digitalWrite(PED_W_STOP, HIGH);

      redBlinking=true;

      trafficTop="NS YEL  " + vehicleLineMini();
      if(done){ phase=P_ALL_RED_2; phaseStart=millis(); }
    }break;

    case P_ALL_RED_2:{
      trafficAllRedSolid();
      pedAllStopSolid();
      trafficTop="ALL RED " + vehicleLineMini();
      if(done){
        if(ewDemand() || !nsDemand()) phase=P_EW_TURN;
        else                         phase=P_NS_TURN;
        phaseStart=millis();
      }
    }break;

    case P_EW_TURN:{
      trafficAllRedSolid();
      digitalWrite(E_TURN, turnBlink);
      digitalWrite(W_TURN, turnBlink);

      unsigned long left = (TURN_TIME>el)?(TURN_TIME-el):0;

      if(left <= PED_WALK_BLINK_LAST_MS){
        nsWalk=false; ewWalk=true;
        pedCounting=true; pedDir="EW"; pedSec=ceilSecondsRemaining(left);
        walkBlinking=true;

        bool pb = ((millis()/PED_BLINK_MS)%2)==0;
        digitalWrite(PED_E_WALK, pb); digitalWrite(PED_E_STOP, LOW);
        digitalWrite(PED_W_WALK, pb); digitalWrite(PED_W_STOP, LOW);

        digitalWrite(PED_N_WALK, LOW); digitalWrite(PED_N_STOP, HIGH);
        digitalWrite(PED_S_WALK, LOW); digitalWrite(PED_S_STOP, HIGH);

        pedReqE=false; pedReqW=false;
        setReqLedPins();
      } else {
        pedAllStopSolid();
      }

      trafficTop="EW TURN " + vehicleLineMini();
      if(done){ phase=P_EW_GREEN; phaseStart=millis(); }
    }break;

    case P_EW_GREEN:{
      trafficEWGreen();

      nsWalk=false; ewWalk=true;
      pedCounting=true; pedDir="EW";
      pedSec=ceilSecondsRemaining((GREEN_TIME>el)?(GREEN_TIME-el):0);
      walkSolid=true;

      digitalWrite(PED_E_WALK, HIGH); digitalWrite(PED_E_STOP, LOW);
      digitalWrite(PED_W_WALK, HIGH); digitalWrite(PED_W_STOP, LOW);

      digitalWrite(PED_N_WALK, LOW);  digitalWrite(PED_N_STOP, HIGH);
      digitalWrite(PED_S_WALK, LOW);  digitalWrite(PED_S_STOP, HIGH);

      trafficTop="EW GREEN " + vehicleLineMini();
      if(done){ phase=P_EW_YELLOW; phaseStart=millis(); }
    }break;

    case P_EW_YELLOW:{
      trafficEWYellow();

      bool pb = ((millis()/PED_BLINK_MS)%2)==0;
      digitalWrite(PED_E_WALK, LOW); digitalWrite(PED_E_STOP, pb);
      digitalWrite(PED_W_WALK, LOW); digitalWrite(PED_W_STOP, pb);

      digitalWrite(PED_N_WALK, LOW); digitalWrite(PED_N_STOP, HIGH);
      digitalWrite(PED_S_WALK, LOW); digitalWrite(PED_S_STOP, HIGH);

      redBlinking=true;

      trafficTop="EW YEL  " + vehicleLineMini();
      if(done){ phase=P_ALL_RED_1; phaseStart=millis(); }
    }break;
  }

  // Sound
  if (walkBlinking) slowBeep();
  else if (walkSolid && pedCounting) fastBeep();
  else if (redBlinking) slowBeep();
  else stopBeep();

  // LCD
  if(doLCD){
    lcd1SetRows(trafficTop, trafficCountdownLine(trafficSec));

    if(pedMsgActive){
      lcd2SetRows(pedMsgLine1, pedMsgLine2);
      if(millis() - pedMsgStart > PED_MSG_TIME) pedMsgActive = false;
    } else {
      lcd2SetRows(
        pedTopLine(nsWalk, ewWalk),
        pedCountdownLine(pedDir, pedSec, pedCounting)
      );
    }
  }
}
