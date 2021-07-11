
#include "print_val.h"
#include <Arduino.h>

void printValues(double temperature, double pressure, double humidity, double height) 
{
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Pressure = ");
  Serial.print(calc_sea_level_pressure(height, pressure/100.0F, temperature ));
  Serial.println(" hPa");
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println();
  Serial.println( std::string(100, '*').c_str() );
}

double calc_sea_level_pressure(double height_above_sea_level, double atmospheric_pressure, double temperature_celcius)
{
  double term1 = (1-(0.0065*height_above_sea_level/(temperature_celcius+0.0065*height_above_sea_level+273.15)));
  double term2 = pow(term1, -5.257);
  return atmospheric_pressure * term2;
}