#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Consants
const unsigned char ONE_WIRE_BUS = 4;
DeviceAddress temperature_sensor = {0x28, 0x73, 0xF6, 0x45, 0xD4, 0xC7, 0x6B, 0x9C};

// variables
unsigned long previousTime = millis();

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);



void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  if (millis() - previousTime >= 5000){
    previousTime = millis();
    
    Serial.print("Requesting Temperatures...");
    sensors.requestTemperatures();
    Serial.print("done :)\n");

    Serial.println(sensors.getTempC(temperature_sensor));
  }
}


