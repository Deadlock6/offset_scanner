#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <GravityTDS.h>
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>


// Consants
const unsigned char ONE_WIRE_BUS = 4;
const unsigned char TRIGGER_PIN = 5;
const unsigned char ECHO_PIN = 18; 
const uint16_t MAX_DISTANCE = 400;
const DeviceAddress temperature_sensor = {0x28, 0x73, 0xF6, 0x45, 0xD4, 0xC7, 0x6B, 0x9C};

const unsigned char TDS_PIN = 15; 

// variables
unsigned long previousTime = millis();
double current_temp;
uint16_t distance;
double ec;

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
}

void loop() {
  if (millis() - previousTime >= 5000){
    previousTime = millis();

// температура

    Serial.print("Requesting Temperatures...");
    sensors.requestTemperatures();
    Serial.print("done :)\n");
    current_temp = sensors.getTempC(temperature_sensor);
    Serial.println(current_temp);

// электропроводность

    tds.setTemperature(current_temp);
    ec = tds.getTdsValue() / 0.5;
    Serial.print("EC: ");
    Serial.print(ec);

// расстояние

    distance = sonar.ping_cm();
    Serial.print(distance);
    Serial.println(" cm");
    
  }
}


