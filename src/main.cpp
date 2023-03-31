#include <Arduino.h>

#include <GP2YDustSensor.h>

const uint8_t SHARP_LED_PIN = 18;   // Sharp Dust/particle sensor Led Pin
const uint8_t SHARP_VO_PIN = 34;    // Sharp Dust/particle analog out pin used for reading 

GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1010AU0F, SHARP_LED_PIN, SHARP_VO_PIN);
char logBuffer[255];
int dustAverage = 0;

void setup() {
  Serial.begin(9600);
  dustSensor.begin();
}

void loop() {
  for (int i; i <= 100; i++) {
      sprintf(logBuffer, "Dust density: %d ug/m3", dustSensor.getDustDensity());
      Serial.println(logBuffer);
      delay(580);
  }

  dustAverage = dustSensor.getRunningAverage();
  float newBaseline = dustSensor.getBaselineCandidate();
  
  sprintf(logBuffer, "1m Avg Dust Density: %d ug/m3; New baseline: %.4f", dustAverage, newBaseline);
  Serial.println(logBuffer);

  // compensates sensor drift after 1m
  dustSensor.setBaseline(newBaseline);

  delay(1000);
}