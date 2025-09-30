#define BLYNK_TEMPLATE_ID "TMPL6jfYERH8m"
#define BLYNK_TEMPLATE_NAME "mainHub1"

#define BLYNK_PRINT Serial
#define APP_DEBUG

#include "BlynkEdgent.h"
#include <Keypad.h>
#include <string.h>
#include <LiquidCrystal_I2C.h>
#include <Preferences.h>

Preferences preferences;

const byte ROWS = 4;
const byte COLS = 4;

//////////////////// PIN CONFIG ////////////////////
const int flm_sensIn = 13;   // Flame
const int gas_sensIn = 14;   // Gas
const int clk1 = 34;         // MSB
const int clk0 = 35;         // LSB
byte rowPins[ROWS] = {18, 19, 23, 25};
byte colPins[COLS] = {26, 27, 32, 33};
static int brd_to_cam = 17;
static int dr_lock = 16;

//////////////////// VARIABLES ////////////////////
int smk[]={0,0,0,0};
int gas[]={0,0,0,0};
int gas_state = 0;
int filtr_thres = 3;

int clk_1 =0;
int clk_0=0;
int flm_sens_val=0;
int gas_sens_val=0;

static int pass_size = 6;
char pass_ent[] = {'0','0','0','0','0','0'};
char pass[] = {'0','0','0','0','0','0'};
int idx = 0;
char key='\0';
int mod_stat = 0;
int pass_entered = 0;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

LiquidCrystal_I2C lcd_i2c(0x27, 16, 2);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
BlynkTimer timer;

//////////////////// FUNCTIONS ////////////////////
void shiftLeft(char array[], int size) {
  for (int i = 0; i < size - 1; i++) {
    array[i] = array[i + 1];
  }
  idx++;
}

void myTimer() {
  Blynk.virtualWrite(V4, gas_state);
  if(gas_state == 1) Blynk.logEvent("Gas_Leakage_Alert","Possible Gas leakage in Room 1 !");
  if(gas_state == 2) Blynk.logEvent("Gas_Leakage_Alert","Possible Gas leakage in Room 2 !");
  if(gas_state == 3) Blynk.logEvent("Gas_Leakage_Alert","Possible Gas leakage in Room 3 !");
  if(gas_state == 4) Blynk.logEvent("Gas_Leakage_Alert","Possible Gas leakage in Room 4 !");

  Blynk.virtualWrite(V0, smk[0]);
  Blynk.virtualWrite(V1, smk[1]);
  Blynk.virtualWrite(V2, smk[2]);
  Blynk.virtualWrite(V3, smk[3]);
}

//////////////////// SETUP ////////////////////
void setup() {
  timer.setInterval(1000L, myTimer);
  Serial.begin(115200);
  delay(100);

  pinMode(flm_sensIn, INPUT);
  pinMode(gas_sensIn, INPUT);
  pinMode(brd_to_cam, OUTPUT);
  pinMode(dr_lock, OUTPUT);
  pinMode(clk1, INPUT);
  pinMode(clk0, INPUT);

  lcd_i2c.init();
  lcd_i2c.backlight();
  lcd_i2c.clear();
  lcd_i2c.setCursor(0, 0);
  lcd_i2c.print("Enter Password:");
  lcd_i2c.setCursor(4, 1);
  lcd_i2c.print("> <");

  preferences.begin("PASSWORD", false);
  for(int i=0;i<6;i++) {
    String key = "pass" + String(i);
    pass[i] = preferences.getChar(key.c_str(),'0');
  }
  preferences.end();

  Serial.printf("Current value: %c %c %c %c %c %c\n\n", pass[0],pass[1],pass[2],pass[3],pass[4],pass[5]);
  BlynkEdgent.begin();
}

//////////////////// LOOP ////////////////////
void loop() {
  BlynkEdgent.run();
  timer.run();

  clk_1 = digitalRead(clk1);
  clk_0 = digitalRead(clk0);
  flm_sens_val = digitalRead(flm_sensIn);
  gas_sens_val = digitalRead(gas_sensIn);

  if(clk_1 == 0 && clk_0 == 0){ smk[0] = !flm_sens_val; gas[0] = !gas_sens_val; gas_state = gas[0]? 1:0;}
  if(clk_1 == 0 && clk_0 == 1){ smk[1] = !flm_sens_val; gas[1] = !gas_sens_val; gas_state = gas[1]? 2:0;}
  if(clk_1 == 1 && clk_0 == 0){ smk[2] = !flm_sens_val; gas[2] = !gas_sens_val; gas_state = gas[2]? 3:0;}
  if(clk_1 == 1 && clk_0 == 1){ smk[3] = !flm_sens_val; gas[3] = !gas_sens_val; gas_state = gas[3]? 4:0;}

  key = keypad.getKey();
  if (key) {
    if(!mod_stat) {
      lcd_i2c.setCursor(0, 0);
      lcd_i2c.print("Enter Password:");
    }
    if(key != '*' && key != '#') {
      shiftLeft(pass_ent, pass_size);
      pass_ent[pass_size-1] = key;
      lcd_i2c.setCursor(idx+4, 1);
      lcd_i2c.print(key);
    }
  }

  if((key =='#') && !strncmp(pass, pass_ent, pass_size) && pass_entered) {
    lcd_i2c.clear();
    lcd_i2c.setCursor(0, 1);
    lcd_i2c.print("Welcome Home");
    digitalWrite(dr_lock,1);
    delay(1000);
    digitalWrite(dr_lock,0);
    pass_entered = 0; idx = 0;
  } 
  else if((key =='#') && strncmp(pass, pass_ent, pass_size) && pass_entered) {
    lcd_i2c.clear();
    lcd_i2c.setCursor(0, 1);
    lcd_i2c.print("Wrong Password !");
    digitalWrite(brd_to_cam, 1);
    delay(500);
    digitalWrite(brd_to_cam, 0);
    pass_entered = 0; idx = 0;
  }

  if(mod_stat && pass_entered) {
    for(int i=0;i<6;i++) pass[i] = pass_ent[i];
    preferences.begin("PASSWORD", false);
    for(int i=0;i<6;i++) {
      String key = "pass" + String(i);
      preferences.putChar(key.c_str(), pass[i]);
    }
    preferences.end();
    lcd_i2c.clear();
    lcd_i2c.setCursor(0, 1);
    lcd_i2c.print("Pass Modified ");
    mod_stat = 0; pass_entered = 0;
  }

  if(idx==6) { pass_entered = 1; idx = 0; }
  delay(10);
}
