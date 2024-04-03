#include <HX711_ADC.h>
#if defined(ESP8266) || defined(ESP32)
#include <EEPROM.h>
#define LED_PIN 13
#endif

const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5;  //mcu > HX711 sck pin
// const int LED_BUILTIN = 12;

HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long startTime = 0;
const unsigned long tareDuration = 5000; // 5 seconds taring duration
const unsigned long additionalDelay = 3000;
const unsigned long measurementDuration = 15000; // 10 seconds measurement duration

void setup() {
  Serial.begin(57600);
  LoadCell.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Check if data is available to read from serial port
  if (Serial.available() > 0) {
    // Start the weight measurement loop
    float calibrationValue = -101.93; // calibration value (see example file "Calibration.ino")
    boolean _tare = true;

    LoadCell.start(tareDuration, _tare);
    LoadCell.setCalFactor(calibrationValue);

    // Record the start time for tare
    startTime = millis();

    // Turn on the LED
    digitalWrite(LED_BUILTIN, HIGH);

    // Wait for tare duration
    while (millis() - startTime < tareDuration + additionalDelay ) {
      // You can perform other operations within the loop if needed
    }

    // Turn off the LED after tare duration
    digitalWrite(LED_BUILTIN, LOW);

    // Start the measurement loop after tare
    startTime = millis();

    // Weight measurement loop
    while (millis() - startTime < measurementDuration) {
      LoadCell.update();
      // You can also perform other operations within the loop if needed
    }

    // Print the final weight after measurement
    Serial.println(LoadCell.getData());
    delay(15000);
    
  }
}