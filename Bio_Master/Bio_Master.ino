#include <GyverEncoder.h>
#define CLK 6
#define DT 7
#define SW 5
Encoder enc1(CLK, DT, SW);  // для работы c 
#define LINES 2   // количество строк дисплея
#define SETTINGS_AMOUNT 12  // количество настроек
#define SETTINGS_AMOUNT1 7
int vals1[SETTINGS_AMOUNT1];
int vals[SETTINGS_AMOUNT];  // массив параметров
int8_t arrowPos = 0;
int8_t screenPos = 0; // номер "экрана"
int8_t arrowPos1 = 0;
int8_t screenPos1 = 0;
// названия параметров
const char *settingsNames[]  = {
  "Pamidor",
  "Sabzi",
  "Kartoshka",
  "Piyoz",
  "Baqlajon",
  "Karam",
  "Qovoq",
  "Tarvuz",
  "Qovun",
  "Bodring",
  "Boshqalar",
  "Chiqish"
};
  const char *settingsNames1[]  = {
  "Past Temp",
  "Baland Temp",
  "Past Havo",
  "Baland Havo",
  "Tuproq N",
  "Saqlab Chiqish",
  "Chiqish"
};
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
DHT dht (8, DHT11);
SoftwareSerial arduinoSerial(3, 4); 
LiquidCrystal_I2C lcd (0x27, 16, 2);
int rele = 13;
int rele1 = 2;
int rele2 = 12;
int rele3 = 11;
int buzzer = 9;

float dhtTemperature;
float dhtHumidity;

float T1;float T2;
float H1; float H2;
int S = 50;
int val3;

unsigned long lastActionTime = 0;
bool saveSettings = false;
bool scheduledSave = false;
bool val6 = false;
bool val5 = false;
bool val4 = false;
bool val2 = false;
bool val1 = false;
bool val = false;
unsigned long timer;
unsigned long timer1;
unsigned long timer2;
unsigned long timer3;
unsigned long timer4;
int dataldr;
int ldr;
int ldrpin = A1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
arduinoSerial.begin(9600);
dht.begin();
lcd.init();
lcd.backlight();
lcd.setCursor(1, 0);
lcd.print("Bio Master By");
lcd.setCursor(0, 1);
lcd.print("Samurai Product!");
pinMode(ldrpin, INPUT);
pinMode(buzzer, OUTPUT);
pinMode(rele, OUTPUT);
pinMode(rele1, OUTPUT);
pinMode(rele2, OUTPUT);
pinMode(rele3, OUTPUT);
enc1.setType(TYPE2);
delay(3000);
}

void loop() {
  if (val5 == true) {
    boshqalar();
  }
  
  else if (val == true) {
    encoder();
  }
  else {
 if (millis() - timer > 3000) {
 dhtTemperature = dht.readTemperature();
 char Temp = 'T';
 arduinoSerial.write(Temp);
 arduinoSerial.print(dhtTemperature);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Harorat:");
 lcd.setCursor(10, 0);
 lcd.print(dhtTemperature);
 lcd.setCursor(14, 0);
 lcd.print(char(223));
 lcd.setCursor(15, 0);
 lcd.print("C");
 dhtHumidity = dht.readHumidity();
 char Humd = 'H';
arduinoSerial.write(Humd);
arduinoSerial.print(dhtHumidity);
 lcd.setCursor(0, 1);
 lcd.print("Havo Namligi:");
 lcd.setCursor(13, 1);
 lcd.print(dhtHumidity);
 lcd.setCursor(15, 1);
 lcd.print("%");
 timer = millis();
 }
 
 int soilMoisture = analogRead(A0); 
 soilMoisture = map(soilMoisture, 0, 1023, 100, 0);
 if (millis() - timer1 > 6000) {
 char dataSoil = 'S';
 arduinoSerial.write(dataSoil);
 arduinoSerial.print(soilMoisture);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Yer Namligi:"); 
 lcd.setCursor(12, 0);
 lcd.print(soilMoisture);
 lcd.print("%");
 if (soilMoisture < S) {
 digitalWrite(rele, HIGH);
 lcd.setCursor(0, 1);
 lcd.print("Suv qo'yilmoqda!");
 }
 else {
 if (val2 == false) {
 digitalWrite(rele, LOW);
 lcd.setCursor(0, 1);
 lcd.print("Namlik a'lo");
 }
  }
 timer = millis();
 timer1 = millis();
  }
if (millis () - timer3 > 500) {
    ldr = analogRead(ldrpin);
 ldr = map(ldr, 1023, 0, 100, 0);
 char dataLDR = 'I';
 arduinoSerial.write(dataLDR);
 arduinoSerial.print(dataldr);
     if (arduinoSerial.available() > 0) {
    char data1 = arduinoSerial.read();
    val3 = arduinoSerial.parseFloat();
    switch (data1) {
      case 'R': datarele();
      case 'L': dataphoto();
    }
     } 
     if (ldr < 30) {
    digitalWrite(rele1, HIGH);
    dataldr = 1;
  }
  else {
    if (val4 == false) {
    digitalWrite(rele1, LOW);
    dataldr = 0;
  }
  }
  timer3 = millis ();
}
    if (val1 == true) {
    harorat();
  }
  handleEncoder ();
}
}
void handleEncoder() {
  if (millis() - timer2 > 200000){
    timer2 = millis();
    lcd.noBacklight();
  }
  enc1.tick();
  if (enc1.isClick()) {
    lcd.backlight();
    val = true;
    printgui();
  }
  if (enc1.isLeft() || enc1.isRight()) {
    timer2 = millis();
    lcd.backlight();
  }
}
