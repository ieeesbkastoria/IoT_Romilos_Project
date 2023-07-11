/********************************
 * Libraries included
 *******************************/
#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>
#include <Wire.h> //I2C needed for sensors
#include "SparkFunMPL3115A2.h" //Pressure sensor - Search "SparkFun MPL3115" and install from Library Manager
#include "SparkFun_Si7021_Breakout_Library.h" //Humidity sensor - Search "SparkFun Si7021" and install from Library Manager

MPL3115A2 myPressure; //Create an instance of the pressure sensor
Weather myHumidity; //Create an instance of the humidity sensor

// Hardware pin definitions
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// digital I/O pins
const byte WSPEED = 3;
const byte RAIN = 2;
const byte STAT1 = 7;
const byte STAT2 = 8;

// analog I/O pins
const byte REFERENCE_3V3 = A3;
const byte LIGHT = A1;
const byte BATT = A2;
const byte WDIR = A0;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Global Variables
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long lastSecond; // The millis counter to see when a second rolls by
byte seconds; // When it hits 60, increase the current minute
byte minutes; // Keeps track of where we are in various arrays of data

long lastWindCheck = 0;
volatile long lastWindIRQ = 0;
volatile byte windClicks = 0;
byte windspdavg[120]; // 120 bytes to keep track of 2-minute average

#define WIND_DIR_AVG_SIZE 120
int winddiravg[WIND_DIR_AVG_SIZE]; // 120 ints to keep track of 2-minute average
float windgust_10m[10]; // 10 floats to keep track of 10-minute max
int windgustdirection_10m[10]; // 10 ints to keep track of 10-minute max
volatile float rainHour[60]; // 60 floating numbers to keep track of 60 minutes of rain

// These are all the weather values that Wunderground expects:
int winddir = 0; // [0-360 instantaneous wind direction]
float windspeedmph = 0; // [mph instantaneous wind speed]
float windgustmph = 0; // [mph current wind gust, using software specific time period]
int windgustdir = 0; // [0-360 using software specific time period]
float windspdmph_avg2m = 0; // [mph 2-minute average wind speed mph]
int winddir_avg2m = 0; // [0-360 2-minute average wind direction]
float windgustmph_10m = 0; // [mph past 10 minutes wind gust mph ]
int windgustdir_10m = 0; // [0-360 past 10 minutes wind gust direction]
float humidity = 0; // [%]
float tempf = 0; // [temperature F]
float rainin = 0; // [rain inches over the past hour)] -- the accumulated rainfall in the past 60 min
volatile float dailyrainin = 0; // [rain inches so far today in local time]
float pressure = 0;
float light_lvl = 455; // [analog value from 0 to 1023]

// volatiles are subject to modification by IRQs
volatile unsigned long raintime, rainlast, raininterval, rain;

//Interrupt routines (these are called by the hardware interrupts, not by the main code)
void rainIRQ()
// Count rain gauge bucket tips as they occur
// Activated by the magnet and reed switch in the rain gauge, attached to input D2
{
    raintime = millis(); // grab current time
    raininterval = raintime - rainlast; // calculate interval between this and last event

    if (raininterval > 10) // ignore switch-bounce glitches less than 10ms after the initial edge
    {
        dailyrainin += 0.011; // Each dump is 0.011" of water
        rainHour[minutes] += 0.011; // Increase this minute's amount of rain

        rainlast = raintime; // set up for the next event
    }
}

void wspeedIRQ()
// Activated by the magnet in the anemometer (2 ticks per rotation), attached to input D3
{
    if (millis() - lastWindIRQ > 10) // Ignore switch-bounce glitches less than 10ms (142MPH max reading) after the reed switch closes
    {
        lastWindIRQ = millis(); // Grab the current time
        windClicks++; // There is 1.492MPH for each click per second.
    }
}

/********************************
 * Constants and objects
 *******************************/
/* Assigns the Ubidots parameters */
char const * TOKEN = "BBFF-ILkRfrbiyQZpdd0HERbzL33R6FKaZu"; // Assign your Ubidots TOKEN
char const * VARIABLE_LABEL_1 = "temperature"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_2 = "humidity"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_3 = "pressure"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_4 = "light"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_5 = "rainin"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_6 = "winddir"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_7 = "speed"; // Assign the unique variable label to send the data

/* Enter a MAC address for your controller below */
/* Newer Ethernet shields have a MAC address printed on a sticker on the shield */
byte mac[] = { 0xDE, 0x69, 0xBE, 0xEF, 0x69, 0xED };

/* initialize the instance */
Ubidots client(TOKEN);

/********************************
 * Main Functions
 *******************************/
void setup()
{
    Serial.begin(9600);
    Serial.println("Weather Shield Example");

    pinMode(STAT1, OUTPUT); // Status LED Blue
    pinMode(STAT2, OUTPUT); // Status LED Green

    pinMode(WSPEED, INPUT_PULLUP); // input from wind meters windspeed sensor
    pinMode(RAIN, INPUT_PULLUP); // input from wind meters rain gauge sensor

    pinMode(REFERENCE_3V3, INPUT);
    pinMode(LIGHT, INPUT);

    // Configure the pressure sensor
    myPressure.begin(); // Get sensor online
    myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
    myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
    myPressure.enableEventFlags(); // Enable all three pressure and temp event flags

    // Configure the humidity sensor
    myHumidity.begin();

    seconds = 0;
    lastSecond = millis();

    // Attach external interrupt pins to IRQ functions
    attachInterrupt(0, rainIRQ, FALLING);
    attachInterrupt(1, wspeedIRQ, FALLING);

    // Turn on interrupts
    interrupts();

    Serial.println("Weather Shield online!");
    /* start the Ethernet connection */
    Serial.print(F("Starting Ethernet..."));
    if (!Ethernet.begin(mac)) {
        Serial.println(F("failed"));
    } else {
        Serial.println(Ethernet.localIP());
    }
    /* Give the Ethernet shield a second to initialize */
    delay(2000);
    Serial.println(F("Ethernet Ready"));
}

void loop()
{
    Ethernet.maintain();
    // Keep track of which minute it is
    if (millis() - lastSecond >= 1000)
    {
        digitalWrite(STAT1, HIGH); // Blink stat LED

        lastSecond += 1000;
        float currentSpeed = get_wind_speed();
        windspeedmph = currentSpeed; // Update global variable for windspeed when using the printWeather() function
        int currentDirection = get_wind_direction();

        // Report all readings every second
        // printWeather();
        calcWeather(); // Go calculate all the various sensors
        client.add(VARIABLE_LABEL_1, tempf);
        client.add(VARIABLE_LABEL_2, humidity);
        client.add(VARIABLE_LABEL_3, pressure);
        client.add(VARIABLE_LABEL_4, light_lvl);
        client.add(VARIABLE_LABEL_5, rainin);
        client.sendAll();
        client.add(VARIABLE_LABEL_6, winddir);
        client.add(VARIABLE_LABEL_7, windspeedmph);
        client.sendAll();
        digitalWrite(STAT1, LOW); // Turn off stat LED
    }
    delay(5000);
}

// Calculates each of the variables that Wunderground is expecting
void calcWeather()
{
    // Calc winddir
    winddir = get_wind_direction();

    // Calc windspeed
    // windspeedmph = get_wind_speed(); // This is calculated in the main loop on line 185

    // Calc windgustmph
    // Calc windgustdir
    // These are calculated in the main loop

    // Calc windspdmph_avg2m
    float temp = 0;
    for (int i = 0; i < 120; i++)
        temp += windspdavg[i];
    temp /= 120.0;
    windspdmph_avg2m = temp;
    long sum = winddiravg[0];
    int D = winddiravg[0];
    for (int i = 1; i < WIND_DIR_AVG_SIZE; i++)
    {
        int delta = winddiravg[i] - D;

        if (delta < -180)
            D += delta + 360;
        else if (delta > 180)
            D += delta - 360;
        else
            D += delta;

        sum += D;
    }
    winddir_avg2m = sum / WIND_DIR_AVG_SIZE;
    if (winddir_avg2m >= 360)
        winddir_avg2m -= 360;
    if (winddir_avg2m < 0)
        winddir_avg2m += 360;

    // Calc windgustmph_10m
    // Calc windgustdir_10m
    // Find the largest windgust in the last 10 minutes
    windgustmph_10m = 0;
    windgustdir_10m = 0;
    // Step through the 10 minutes
    for (int i = 0; i < 10; i++)
    {
        if (windgust_10m[i] > windgustmph_10m)
        {
            windgustmph_10m = windgust_10m[i];
            windgustdir_10m = windgustdirection_10m[i];
        }
    }

    // Calc humidity
    humidity = myHumidity.getRH();

    // Calc tempf from pressure sensor
    tempf = myHumidity.getTempF();
    tempf = (tempf - 32) / 1.8000;

    // Total rainfall for the day is calculated within the interrupt
    // Calculate the amount of rainfall for the last 60 minutes
    rainin = 0;
    for (int i = 0; i < 60; i++)
        rainin += rainHour[i];

    // Calc pressure
    pressure = myPressure.readPressure();

    // Calc light level
    light_lvl = get_light_level();
}

// Returns the voltage of the light sensor based on the 3.3V rail
// This allows us to ignore what VCC might be (an Arduino plugged into USB has VCC of 4.5 to 5.2V)
float get_light_level()
{
    float operatingVoltage = analogRead(REFERENCE_3V3);
    float lightSensor = analogRead(LIGHT);
    operatingVoltage = 3.3 / operatingVoltage; // The reference voltage is 3.3V
    lightSensor = operatingVoltage * lightSensor;
    return (lightSensor);
}

// Returns the voltage of the raw pin based on the 3.3V rail
// This allows us to ignore what VCC might be (an Arduino plugged into USB has VCC of 4.5 to 5.2V)
// Battery level is connected to the RAW pin on Arduino and is fed through two 5% resistors:
// 3.9K on the high side (R1), and 1K on the low side (R2)
float get_battery_level()
{
    float operatingVoltage = analogRead(REFERENCE_3V3);
    float rawVoltage = analogRead(BATT);
    operatingVoltage = 3.30 / operatingVoltage; // The reference voltage is 3.3V
    rawVoltage = operatingVoltage * rawVoltage; // Convert the 0 to 1023 int to the actual voltage on the BATT pin
    rawVoltage *= 4.90; // (3.9k+1k)/1k - multiple BATT voltage by the voltage divider to get the actual system voltage
    return (rawVoltage);
}

// Returns the instantaneous wind speed
float get_wind_speed()
{
    float deltaTime = millis() - lastWindCheck; // 750ms
    deltaTime /= 1000.0; // Convert to seconds
    float windSpeed = (float)windClicks / deltaTime; // 3 / 0.750s = 4
    windClicks = 0; // Reset and start watching for new wind
    lastWindCheck = millis();
    windSpeed *= 1.492; // 4 * 1.492 = 5.968MPH
    return (windSpeed);
}

// Read the wind direction sensor, return heading in degrees
int get_wind_direction()
{
    unsigned int adc;
    adc = analogRead(WDIR); // Get the current reading from the sensor

    // The following table is ADC readings for the wind direction sensor output, sorted from low to high.
    // Each threshold is the midpoint between adjacent headings. The output is degrees for that ADC reading.
    // Note that these are not in compass degree order! See Weather Meters datasheet for more information.

    if (adc < 380)
        return (113);
    if (adc < 393)
        return (68);
    if (adc < 414)
        return (90);
    if (adc < 456)
        return (158);
    if (adc < 508)
        return (135);
    if (adc < 551)
        return (203);
    if (adc < 615)
        return (180);
    if (adc < 680)
        return (23);
    if (adc < 746)
        return (45);
    if (adc < 801)
        return (248);
    if (adc < 833)
        return (225);
    if (adc < 878)
        return (338);
    if (adc < 913)
        return (0);
    if (adc < 940)
        return (293);
    if (adc < 967)
        return (315);
    if (adc < 990)
        return (270);
    return (-1); // error, disconnected?
}
