#include <Arduino.h>
#include <array>
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include "FreeFonts.h" // Include the header file attached to this sketch
#include <SPI.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "print_val.h"


// caclulation of the air pressure: https://keisan.casio.com/exec/system/1224575267

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;
 MbedI2C theWire(4, 5);
TFT_eSPI tft = TFT_eSPI();  // Invoke library
unsigned long previousMillis = 0;        
const long interval = 1000;           //  (milliseconds)

void setup() {
    
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_RED);
    tft.setCursor(0, 0, 2);
  // Set the font colour to be white with a black background, set text size multiplier to 1
    tft.setTextColor(TFT_CYAN,TFT_BLACK); 

    tft.println("V 0.1");
    tft.println("Initialize Serial...!");
    //tft.setFreeFont(FF1);

    Serial.begin(9600);
    //while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    
    // default settings
    status = bme.begin(0x76, &theWire);  

    
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }

    Serial.print("Sensor ID= ");
    Serial.println(bme.sensorID());
    
    Serial.println("-- Default Test --");
    Serial.println();
    tft.fillScreen(TFT_BLACK);
}

int test = 0;



void print_display(float temperature, float pressure, float humidity, double height)
{
    tft.setCursor(0, 0);
    tft.setTextSize(3);
    tft.setTextColor(TFT_CYAN,TFT_BLACK); 
    tft.print(temperature, 1); tft.println(" `C");
    tft.print(humidity, 1); tft.println(" %");
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE,TFT_BLACK); 
    tft.print(calc_sea_level_pressure(height, pressure/100.0F, temperature ), 1); tft.println(" hPa");
}


void loop() {
    test++; 

    unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= interval) 
     {
         auto current_temp = bme.readTemperature();
         auto current_pressure = bme.readPressure();
         auto current_humidity = bme.readHumidity();
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        printValues(current_temp, current_pressure, current_humidity, 110);
        print_display(current_temp, current_pressure, current_humidity, 110);
     }

}
