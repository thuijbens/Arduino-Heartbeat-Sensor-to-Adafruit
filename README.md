# Arduino-Heartbeat-Sensor-to-Adafruit
How to use a heartbeat sensor and log the data to Adafruit using Arduino?
### About
This tutorial explains how one can use a heartbeat sensor with Arduino and how this data is send to an Adafruit feed, abling you to connect it to even more devices like a mobile phone. We created this in order to track the heartbeat of a cat and log that data to a mobile phone. Since this is a prototype, we decided to connect in to Adafruit instead, abling me to test the code without needing any additional codes.
### First things first
Before we begin you'll need a few things to make this installation work properly.
* An Arduino Device
* A heartbeat sensor, compatible with Arduino
* An Adafruit account with access to your feeds.

We also need to install two libraries in Arduino. You can find these by going to Tools -> Library Manager and type the names in the search bar. (You can also use the links below)
* [CC3000 Library](https://github.com/adafruit/Adafruit_CC3000_Library/)
* [MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library/tree/master/examples/)

### Let's get to it - Coding
The sketch starts by including the required libraries and calling the Adafruit client:
```
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

Adafruit_CC3000_Client client = Adafruit_CC3000_Client();
mqttclient("io.adafruit.com", 1883, callback, client);
```
Then we need to define the path to the Adafruit feed:
```
#define HEARTBEAT_PUBLISH_PATH "api/feeds/heartbeat/data/send.json"
```
After this we create a few variables which we need later.
```
int i=0,k=0,rate=0;

unsigned long time2,time1;
unsigned long time;
```
Now we arrive at the Void_Setup, in which we only name one variable, variable t equals the variable rate
```
void setup() {
  // put your setup code here, to run once:
int t = rate
}
```
Things get interesting in the Void_loop. There are several methods for calculating heart rate, but here we have read only five pulses. Then we have calculated total heart beat in a minute by applying the below formula: (this is not the code you use in Arduino, this is just for your understanding.)
```
Five_pusle_time=time2-time1;
Single_pulse_time= Five_pusle_time /5;
rate=60000/ Single_pulse_time;
```
Where time1 is first pulse counter value. 
Time2 is list pulse counter value. 
Rate is final heart rate.

In the Void_loop this code looks like this:
```
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
```
Last but not least we need to publish the found heart rate to Adafruit and reset the heartrate to 0. After the calculating function we need to loop the code so it will run again, indefinitely.
```
mqttclient.publish(HEARTBEAT_PUBLISH_PATH, (char *) String(t).c_str());
delay(2000);
rate=0;
mqttclient.loop();
}
```
*Config.h
this installation needs two seperate Arduino files, the main file and the Conig.h file. This file makes sure Arduino has a working connection to the internet and thus the Adafruit feeds. You just need to replace the IO-Username with your Adafruit username and the IO-Key with the AIO-Key you can recieve on your Adafruit page. You might also need to change the SSID and PASS's of your internet connecting, depending on what type of connection you want to use, wifi or wlan. Here you can see the complete config.h file:
```
/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "ApexPredatorTH"
#define IO_KEY         "cc91718bd396437d98addb9fef8945f1"

/******************************* WIFI **************************************/

// the AdafruitIO_WiFi client will work with the following boards:
//   - HUZZAH ESP8266 Breakout -> https://www.adafruit.com/products/2471
//   - Feather HUZZAH ESP8266 -> https://www.adafruit.com/products/2821
//   - Feather HUZZAH ESP32 -> https://www.adafruit.com/product/3405
//   - Feather M0 WiFi -> https://www.adafruit.com/products/3010
//   - Feather WICED -> https://www.adafruit.com/products/3056

#define WIFI_SSID       "IOT"
#define WIFI_PASS       "!HVAIOT!"
#define WLAN_SSID       "IOT"
#define WLAN_PASS       "!HVAIOT!"
#define WLAN_SECURITY   WLAN_SEC_WPA2

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/**************************** ETHERNET ************************************/

// the AdafruitIO_Ethernet client will work with the following boards:
//   - Ethernet FeatherWing -> https://www.adafruit.com/products/3201

// uncomment the following two lines for ethernet,
// and comment out the AdafruitIO_WiFi client in the WIFI section
// #include "AdafruitIO_Ethernet.h"
// AdafruitIO_Ethernet io(IO_USERNAME, IO_KEY);
```

### Congratulations, you made your own heartbeat logger!
for more information on this code you might want to look [here](https://learn.adafruit.com/create-an-internet-of-things-dashboard-with-adafruit-dot-io/build-the-arduino-sketch) and [here](https://circuitdigest.com/microcontroller-projects/heartbeat-monitor-project-using-arduino). Thanks for reading!
