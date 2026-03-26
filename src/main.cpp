#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <GravityTDS.h>

// Consants
const unsigned char ONE_WIRE_BUS = 4;
DeviceAddress temperature_sensor = {0x28, 0x73, 0xF6, 0x45, 0xD4, 0xC7, 0x6B, 0x9C};

const unsigned char TDS_PIN = 16; 

// variables
unsigned long previousTime = millis();
double current_temp;

double ec;

// objects
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
GravityTDS tds;




void setup() {
  Serial.begin(9600);
  sensors.begin();

// tds meter initialization
  tds.setPin(TDS_PIN);
  tds.setAref(3.3);     
  tds.setAdcRange(4095); 
  tds.begin();


}

void loop() {
  if (millis() - previousTime >= 5000){
    previousTime = millis();
    
    Serial.print("Requesting Temperatures...");
    sensors.requestTemperatures();
    Serial.print("done :)\n");
    current_temp = sensors.getTempC(temperature_sensor);
    Serial.println(current_temp);

    tds.setTemperature(current_temp);
    ec = tds.getTdsValue() / 0.5;

    Serial.print("EC: ");
    Serial.print(ec);
  }
}


