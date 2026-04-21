#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <GravityTDS.h>
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>
#include <Keys.h>

#define I2C_SDA 21
#define I2C_SCL 22

// Consants
const unsigned char ONE_WIRE_BUS = 4;
const unsigned char TRIGGER_PIN = 5;
const unsigned char ECHO_PIN = 18; 
const uint16_t MAX_DISTANCE = 400;
const DeviceAddress temperature_sensor = {0x28, 0x73, 0xF6, 0x45, 0xD4, 0xC7, 0x6B, 0x9C};
const unsigned char TDS_PIN = 15; 
const char* SSID = ssid;
const char* PASSWORD = password;

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
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  sensors.begin();

// tds meter initialization
  tds.setPin(TDS_PIN);
  tds.setAref(3.3);     
  tds.setAdcRange(4095); 
  tds.begin();

  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("ESP32 + LCD");
  
  lcd.setCursor(0, 1);
  lcd.print("Hello, World!");
}  

void loop() {
  if (millis() - previousTime >= 5000){
    previousTime = millis();

// температура

    
    sensors.requestTemperatures();
    current_temp = sensors.getTempC(temperature_sensor);
    Serial.print("T: ");
    Serial.print(current_temp);

// электропроводность
    lcd.clear();    

    tds.setTemperature(current_temp); 
    tds.update();
    Serial.print(" Tds: ");
    Serial.print(tds.getTdsValue());
    Serial.print(" EC: ");
    ec = tds.getEcValue();
    Serial.print(ec);

// расстояние
    Serial.print(" Distance: ");
    distance = sonar.ping_cm();
    Serial.print(distance);
    Serial.println(" cm");
    
    lcd.setCursor(0, 0);
    lcd.print("EC:");
    lcd.setCursor(3, 0);
    lcd.print(ec);

    lcd.setCursor(9, 0);
    lcd.print("D:");
    lcd.setCursor(11, 0);
    lcd.print(distance);
    lcd.setCursor(14, 0);
    lcd.print("cm");

    lcd.setCursor(0, 1);
    lcd.print("T=");
    lcd.setCursor(2,1);
    lcd.print(current_temp);
  }
}


