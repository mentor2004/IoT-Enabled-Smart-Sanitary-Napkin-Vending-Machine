#define BLYNK_TEMPLATE_ID "TMPL3wlwzVkkm"
#define BLYNK_TEMPLATE_NAME "IOT Sanitary napkin vending machine"
#define BLYNK_AUTH_TOKEN "hwHdfbt57YFsFOF14BPerNJUZjvfYwW1"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <EEPROM.h>
#define EEPROM_SIZE 4

//blynk authentication// 
char auth[] = BLYNK_AUTH_TOKEN;
const char* ssid = "Galaxy S10+772b"; 
const char* pass = "RAYANSALIM"; 

#define rst 18
int rstval=0,storage=0,myInteger=5;
const uint8_t InterruptPin1 = 16;
bool Request1=0;

void IRAM_ATTR isr1() {
  
 Request1 = 1;
}
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 pinMode(InterruptPin1, INPUT);
 attachInterrupt(InterruptPin1, isr1, RISING);
 EEPROM.begin(EEPROM_SIZE);
 pinMode(rst,INPUT);
 pinMode(23,OUTPUT);
 digitalWrite(23,HIGH);
 storage= EEPROM.read(0);
}

void loop() {
  // put your main code here, to run repeatedly:
 Blynk.run();
 Serial.println(Request1);
 if(storage>0){
  Serial.println("storage is available");
  Serial.println(storage);
  if(Request1==1){
    digitalWrite(23,LOW);
    delay(5000);
    digitalWrite(23,HIGH);
    storage=storage-1;
    EEPROM.write(0,storage);
    EEPROM.commit(); 
    Serial.println(storage);
    Request1=0;
  }}
  else{
    Serial.println("storage finished");
    Blynk.logEvent("message","Storage finished,Please press reset button");
    rstval=digitalRead(rst);
    if(rstval==1){
    EEPROM.write(0,myInteger);
    EEPROM.commit(); 
    storage=EEPROM.read(0);
    Serial.println(storage);
    }
  }
delay(500);
}
