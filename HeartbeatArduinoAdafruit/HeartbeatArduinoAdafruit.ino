#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_MQTT_FONA.h>

#include<LiquidCrystal.h>

#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <PubSubClient.h>
#include "DHT.h"

#define HEARTBEAT_PUBLISH_PATH "api/feeds/heartbeat/data/send.json"

Adafruit_CC3000_Client client = Adafruit_CC3000_Client();
mqttclient("io.adafruit.com", 1883, callback, client);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int in = 8;
int Reset=6;
int start=7;
int count=0,i=0,k=0,rate=0;

unsigned long time2,time1;
unsigned long time;

byte heart[8] = 
{
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void setup() {
  // put your setup code here, to run once:
int t = rate
}

void loop() {
  // put your main code here, to run repeatedly:
    k=0;
    Serial.println("Please wait.......");
    while(k<5)
    {
      if(k==0)
      time1=millis();
      k++;
     }
      time2=millis();
      rate=time2-time1;
      rate=rate/5;
      rate=60000/rate;
      Serial.println("Heart Beat Rate:");
      Serial.println(rate);     
      k=0;
}
  
mqttclient.publish(HEARTBEAT_PUBLISH_PATH, (char *) String(t).c_str());
delay(2000);
rate=0;
mqttclient.loop();
}
