#include <Wire.h> // I2C for sensors
#include "SparkFunMPL3115A2.h" // Pressure Sensor - Search "SparkFun MPL3115" and install from Library Manager
#include "SparkFun_Si7021_Breakout_Library.h" // Humidity sensor - Search "SparkFun Si7021" and install from Library Manager

MPL3115A2 myPressure; // Create a pressure sensor instance
Weather myHumidity; // Create a humidity sensor instance

// Hardware terminal definitions
// ----------------------------------
const byte STAT_BLUE = 7;

const byte REFERENCE_3V3 = A3;
const byte LIGHT = A1;
// This section defines the hardware pins used in the code. STAT_BLUE and STAT_GREEN are the terminals for the status LEDs, REFERENCE_3V3 is the terminal used for the 3.3V rail reference, and LIGHT is the terminal for the light sensor.

// Global variables
// ----------------------------------
long lastSecond; // The millis counter to see when a second rolls by

void setup()
{
  Serial.begin(9600);
  Serial.println("Weather Shield Example");

  pinMode(STAT_BLUE, OUTPUT); // Blue status LED

  pinMode(REFERENCE_3V3, INPUT);
  pinMode(LIGHT, INPUT);

  // Configure the pressure sensor
  myPressure.begin(); // Get the pressure sensor online
  myPressure.setModeBarometer(); // Measure pressure in Pascal from 20 to 110 kPa
  myPressure.setOversampleRate(7); // Set oversample rate to recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temperature event flags

  // Configure the humidity sensor
  myHumidity.begin();

  lastSecond = millis();

  Serial.println("Weather Shield online!");
}

void loop()
{
  // Print readings every second
  if (millis() - lastSecond >= 1000)
  {
    digitalWrite(STAT_BLUE, HIGH); // Blink the stat LED

    lastSecond += 1000;

    // Check the humidity sensor
    float humidity = myHumidity.getRH(); // This value needs to be sent to ubidots

    if (humidity == 998) // Humidity sensor failed to respond
    {
      Serial.println("I2C communication to sensors is not working. Check solder connections.");

      // Try reinitializing I2C communication and the sensors
      myPressure.begin();
      myPressure.setModeBarometer();
      myPressure.setOversampleRate(7);
      myPressure.enableEventFlags();
      myHumidity.begin();
    }
    else
    {
      Serial.print("Humidity = ");
      Serial.print(humidity);
      Serial.print("%, ");
      float temp_h = myHumidity.getTempF(); // This value needs to be sent to ubidots
      temp_h = (temp_h - 32) / 1.8000;
      Serial.print("Temperature = ");
      Serial.print(temp_h, 2);
      Serial.print("°C, ");

      // Check the pressure sensor
      float pressure = myPressure.readPressure(); // This value needs to be sent to ubidots
      Serial.print("Pressure = ");
      Serial.print(pressure);
      Serial.print(" Pa, ");

      // Check the light sensor
      float light_lvl = get_light_level() * 100; // This value needs to be sent to ubidots
      Serial.print("Light Level = ");
      Serial.print(light_lvl);
      Serial.print("%");

      Serial.println();
    }

    digitalWrite(STAT_BLUE, LOW); // Turn off the stat LED
  }

  delay(5000);
}

// Returns the voltage of the light sensor based on the 3.3V rail
// This allows us to ignore variations in VCC (an Arduino connected to USB has VCC ranging from 4.5V to 5.2V)
float get_light_level()
{
  float operatingVoltage = analogRead(REFERENCE_3V3);
  float lightSensor = analogRead(LIGHT);
  operatingVoltage = 3.3 / operatingVoltage; // The reference voltage is 3.3V
  lightSensor = operatingVoltage * lightSensor;
  return lightSensor;
}
