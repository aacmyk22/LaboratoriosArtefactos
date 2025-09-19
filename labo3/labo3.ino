#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int pinLM35 = A0;     // Vout del LM35 a A0
const float Vref = 5.0;     // REFERENCIA ADC (ajusta si usas 3.3V)

void setup() {
  Serial.begin(9600);

  delay(250);
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.display();
}

void loop() {
  int lectura = analogRead(pinLM35);            // 0..1023
  float voltaje = lectura * (Vref / 1023.0);    // V
  float tempC   = voltaje * 100.0;              // °C (10 mV/°C)

  Serial.print("Temperatura: ");
  Serial.print(tempC, 2);
  Serial.println(" °C");

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(0, 28);
  display.println("Temperatura:");

  display.setTextSize(2);           // valor grande
  display.setCursor(0, 42);
  display.print(tempC, 1);
  display.println(" C");

  display.display();     // guarda cambios
  display.clearDisplay();// limpia para el siguiente ciclo

  delay(1000); // actualización cada 1 s (simple, sin optimizar)
}