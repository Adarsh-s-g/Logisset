#include <ESP8266WiFi.h>
//#include <WiFiUdp.h>
#include <SPI.h>
#include <RF24.h>
//#include <NTPClient.h>

const char* ssid = "4g";
const char* password = "Ashwin*23";
const byte receiverAddress[32] = "Address02";// Pipe address for communication
const int interval = 10000; // 
const int channel = 115; // NRF24L01 channel number
const IPAddress receiverIP(192, 168, 29, 108);
const int receiverPort = 1234;
const int limitSwitchPin = D1;
RF24 radio(2, 4); 
void setup()
 {
   Serial.begin(9600);
   Serial.setTimeout(2e+6);
   pinMode(limitSwitchPin, INPUT_PULLUP);
   WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    { 
     delay(1000);
     Serial.println("Connecting to WiFi...");
    }
   Serial.println("Connected to WiFi");
   radio.begin();
   radio.setChannel(channel); // Set NRF24L01 channel
   radio.openWritingPipe(receiverAddress);
   radio.setPALevel(RF24_PA_MIN);
   radio.setDataRate(RF24_250KBPS);
   radio.stopListening();
 }
void loop() 
 
 { 
   int limitSwitchState = digitalRead(limitSwitchPin);// Check if the limit switch is pressed
   if (limitSwitchState == LOW)
   {
     String message = "Asset has been tampered!";
    // message.replace("%d", "1"); //Asset id 
     radio.write(message.c_str(), message.length() + 1);
     Serial.println(message);
     String messagee = "ASSETID";
     messagee.replace("ASSETID", " CRO 2"); // Replace with your asset ID
     radio.write(messagee.c_str(), messagee.length() + 1);
     Serial.println(messagee);     
    
          
   } 
   else
   {
     String message = "";
    // message.replace("%d", "1"); //Asset id 
     radio.write(message.c_str(), message.length() + 1);
     Serial.println(message);
      String messagee = "ASSETID";
     messagee.replace("ASSETID", " CRO 2"); // Replace with your asset ID
     radio.write(messagee.c_str(), messagee.length() + 1);
     Serial.println(messagee);
   }
    
    delay(interval);
  
  Serial.println("Going to sleep for 20 sec...");
   //ESP.deepSleep(20e6);
 
}
