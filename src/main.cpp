// I Aileen Velasco, 000805966 certify that this material is my original work. 
//No other person's work has been used without due acknowledgement. 
//I have not made my work available to anyone else.
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

DeviceAddress deviceAdd;
 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  Serial.println("\nTemperature Application");

  //Check if a device is connected
  if (!DS18B20.getAddress(deviceAdd, 0)){
    Serial.println("No DS18B20 temperature sensors are installed");
  } else {
    String deviceAddress = "";
    for (uint8_t i = 0; i < 8; i++)
    {
      deviceAddress += String(deviceAdd[i], HEX);
    }

    Serial.println("Found DS18B20 sensor with address: " + deviceAddress);    
  }
} 
 
void loop() { 
  if (DS18B20.getAddress(deviceAdd, 0)){
  float fTemp; 
  String judgement = "";
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 
 
  // Check temp to store the judgement
  if(fTemp < 10) judgement = "Cold!";
  else if (fTemp >= 10 && fTemp < 15) judgement = "Cool";
  else if (fTemp >= 15 && fTemp < 25) judgement = "Perfect";
  else if (fTemp >= 25 && fTemp < 30) judgement = "Warm";
  else if (fTemp >= 30 && fTemp < 35) judgement = "Hot";
  else judgement = "Too Hot!";

  // print the temp & judgement to the USB serial monitor 
  Serial.println("Current temperature is: " + String(fTemp) + " C or " + judgement); 
 
  // wait 2s (2000ms) before doing this again 
  delay(2000); 
  }
} 