#include <DHT.h>  // Including library for dht
#include "MQ135.h"
#include <ESP8266WiFi.h>
 
String apiKey = "IQJ20146ITX7WSEN";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "wifi";     // replace with your wifi ssid and wpa2 key
const char *pass =  "wifipass";
const char* server = "api.thingspeak.com";
float voltage =0.0;
float temp=0.0;
float r1=100000.0;    
float r2=100000.0;      

#define DHTPIN D1         //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);
 
WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{

      MQ135 gasSensor = MQ135(A0);
    
      float air_quality = gasSensor.getPPM();
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      int sensorValue = analogRead(A0);
      temp = (sensorValue * 3.3) / 1024.0;       
      voltage = temp / (r2/(r1+r2));
   
              if (isnan(h) || isnan(t))
                 {
                     Serial.println("Failed to read from sensor!");
                      return;
                 }
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
                             postStr += "&field3=";
                             postStr += String(air_quality);
                             postStr += "r\n";
                             postStr += "&field4=";
                             postStr += String(voltage);
                             postStr += "r\n";
                             
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("\tTemperature: ");
                             Serial.print(t);

                             Serial.print(" \t Humidity : ");
                             Serial.print(h);
                            
                              Serial.print("\tAir Quality: ");  
                              Serial.print(air_quality);
                              Serial.println("  PPM"); 

                              Serial.print("\tVoltage = ");
                              Serial.print(voltage);
                              
                             Serial.println( "\nSend to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
