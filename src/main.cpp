#include <Arduino.h>
#include <GP2YDustSensor.h>
#include <fastLED.h>

const uint8_t SHARP_LED_PIN = 18;   // Sharp Dust/particle sensor Led Pin
const uint8_t SHARP_VO_PIN = 34;    // Sharp Dust/particle analog out pin used for reading 

GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1010AU0F, SHARP_LED_PIN, SHARP_VO_PIN);
char logBuffer[255];
int dustAverage = 0;

bool green_flag = false;
bool light_green_flag =  false;
bool yellow_flag = false;
bool orange_flag = false;
bool red_flag = false;
bool maroon_flag = false; 

void setup() {
  Serial.begin(9600);
  dustSensor.begin();
}

void loop() {
  for (int i = 0; i < 10; i++) {
    sprintf(logBuffer, "Dust density: %d ug/m3", dustSensor.getDustDensity());
    Serial.println(logBuffer);
    delay(500);
  }

  dustAverage = dustSensor.getRunningAverage();
  float newBaseline = dustSensor.getBaselineCandidate();
  
  Serial.printf("Dust Average = %d\t",dustAverage);

  // Check air quality based on dust density
  if (dustAverage <= 50) {
    Serial.println("\t\tAir quality is good");
    green_flag = true;
  }
  else {
    green_flag = false;
  }
  
  if (dustAverage > 50 && dustAverage <= 100) {
    Serial.println("\t\tAir quality is moderate");
    light_green_flag = true;
  }
  else {
    light_green_flag = false;
  }
  
  if (dustAverage >100 && dustAverage <= 150) {
    Serial.println("\t\tAir quality is unhealthy for sensitive groups");
    yellow_flag =true;
  }
  else {
    yellow_flag = false;
  }
  
  if (dustAverage > 150 && dustAverage <= 200) {
    Serial.println("\t\tAir quality is unhealthy");
    orange_flag = true;
  }
  else {
    orange_flag = false;
  } 
  
  if (dustAverage > 200 && dustAverage <= 300) {
    Serial.println("\t\tAir quality is very unhealthy");
    red_flag = true;
  }
  else {
    red_flag = false;
  }

  if(dustAverage > 300)
  {
    Serial.println("\t\tAir quality is hazardous");
    maroon_flag = true;
  }
  else {
    maroon_flag = false;
  }
  delay(1000);
}