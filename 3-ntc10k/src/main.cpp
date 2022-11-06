#include <Arduino.h>

const double VCC = 3.3;             // NodeMCU na płytce 3.3V
const double R2 = 10000;            // 10k ohm rezystor
const double adc_resolution = 4095.0; // 12-bit adc

const double A = 0.001129148;   // parametry równania termistora
const double B = 0.000234125;
const double C = 0.0000000876741; 

void setup() {
  Serial.begin(9600);  
}

void loop() {
  double Vout, Rth, temperature, adc_value; 

  adc_value = analogRead(34);
  Vout = (adc_value * VCC) / adc_resolution;
  Rth = (VCC * R2 / Vout) - R2;

/*  Równanie termistora Steinharta-Harta:
 *  Temperatura w Kelwinach = 1 / (A + B[ln(R)] + C[ln(R)]^3)
 *  gdzie A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));   // Temperatura w Kelwinach

  temperature = temperature - 273.15;  // Termperatura w stopniach Celcjusza
  Serial.print("Temperatura = ");
  Serial.print(temperature);
  Serial.println(" °C");
  delay(1000);
}