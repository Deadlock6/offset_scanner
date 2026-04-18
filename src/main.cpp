#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <GravityTDS.h>
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define TDS_PIN 35

// Consants
const unsigned char ONE_WIRE_BUS = 4;
const unsigned char TRIGGER_PIN = 5;
const unsigned char ECHO_PIN = 18; 
const uint16_t MAX_DISTANCE = 400;
const DeviceAddress temperature_sensor = {0x28, 0x73, 0xF6, 0x45, 0xD4, 0xC7, 0x6B, 0x9C};



// variables
unsigned long previousTime = millis();
double current_temp;
uint16_t distance;
float ec = 0;

// objects
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
GravityTDS tds;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  sensors.begin();

// tds meter initialization
  tds.setPin(TDS_PIN);
  tds.setAref(3.3);     
  tds.setAdcRange(4095); 
  tds.begin();
  Serial.println("enter\r\n");
  Serial.println("cal:320\r\n");
}

void loop() {
  if (millis() - previousTime >= 1000){
    previousTime = millis();

// температура

    
    sensors.requestTemperatures();
    
    current_temp = sensors.getTempC(temperature_sensor);
    Serial.print(current_temp);
    Serial.println(" C");

// электропроводность

    tds.setTemperature(25.0);
    tds.update();
    
    ec = tds.getTdsValue();
    Serial.print("EC: ");
    Serial.print(ec, 0);
    Serial.print("\n");

// расстояние

    distance = sonar.ping_cm();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
  }
}


