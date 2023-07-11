#include <Wire.h> // I2C για τους αισθητήρες
#include "SparkFunMPL3115A2.h" // Αισθητήρας πίεσης - Αναζήτηση "SparkFun MPL3115" και εγκατάσταση από τον διαχειριστή βιβλιοθηκών
#include "SparkFun_Si7021_Breakout_Library.h" // Αισθητήρας υγρασίας - Αναζήτηση "SparkFun Si7021" και εγκατάσταση από τον διαχειριστή βιβλιοθηκών

MPL3115A2 myPressure; // Δημιουργία αντικειμένου για τον αισθητήρα πίεσης
Weather myHumidity; // Δημιουργία αντικειμένου για τον αισθητήρα υγρασίας

// Ορισμοί ακροδεκτών υλικού
// ----------------------------------
const byte STAT_BLUE = 7;

const byte REFERENCE_3V3 = A3;
const byte LIGHT = A1;
// Αυτή η ενότητα καθορίζει τους ακροδέκτες του υλικού που χρησιμοποιούνται στον κώδικα. Οι STAT_BLUE και STAT_GREEN είναι οι ακροδέκτες για τα LED κατάστασης, ο REFERENCE_3V3 είναι ο ακροδέκτης που χρησιμοποιείται για την αναφορά της γραμμής 3,3V και ο LIGHT είναι ο ακροδέκτης για τον αισθητήρα φωτός.

// Παγκόσμιες μεταβλητές
// ----------------------------------
long lastSecond; // Ο μετρητής millis για να ελέγχει πότε περνάει ένα δευτερόλεπτο

void setup()
{
  Serial.begin(9600);
  Serial.println("Weather Shield Example");

  pinMode(STAT_BLUE, OUTPUT); // Μπλε LED κατάστασης

  pinMode(REFERENCE_3V3, INPUT);
  pinMode(LIGHT, INPUT);

  // Ρύθμιση του αισθητήρα πίεσης
  myPressure.begin(); // Εκκίνηση του αισθητήρα πίεσης
  myPressure.setModeBarometer(); // Μέτρηση πίεσης σε Pascal από 20 έως 110 kPa
  myPressure.setOversampleRate(7); // Ορισμός υπερδειγματοληψίας στο συνιστώμενο 128
  myPressure.enableEventFlags(); // Ενεργοποίηση των τριών σημαιών γεγονότων πίεσης και θερμοκρασίας

  // Ρύθμιση του αισθητήρα υγρασίας
  myHumidity.begin();

  lastSecond = millis();

  Serial.println("Weather Shield online!");
}

void loop()
{
  // Εκτύπωση των μετρήσεων κάθε δευτερόλεπτο
  if (millis() - lastSecond >= 1000)
  {
    digitalWrite(STAT_BLUE, HIGH); // Αναμόχλευση του LED κατάστασης

    lastSecond += 1000;

    // Έλεγχος του αισθητήρα υγρασίας
    float humidity = myHumidity.getRH(); // Αυτή η τιμή πρέπει να σταλεί στο ubidots

    if (humidity == 998) // Ο αισθητήρας υγρασίας απέτυχε να ανταποκριθεί
    {
      Serial.println("Η επικοινωνία I2C με τους αισθητήρες δεν λειτουργεί. Ελέγξτε τις συνδέσεις της κόλλησης.");

      // Προσπαθήστε να αρχικοποιήσετε ξανά την επικοινωνία I2C και τους αισθητήρες
      myPressure.begin();
      myPressure.setModeBarometer();
      myPressure.setOversampleRate(7);
      myPressure.enableEventFlags();
      myHumidity.begin();
    }
    else
    {
      Serial.print("Υγρασία = ");
      Serial.print(humidity);
      Serial.print("%, ");
      float temp_h = myHumidity.getTempF(); // Αυτή η τιμή πρέπει να σταλεί στο ubidots
      temp_h = (temp_h - 32) / 1.8000;
      Serial.print("Θερμοκρασία = ");
      Serial.print(temp_h, 2);
      Serial.print("°C, ");

      // Έλεγχος του αισθητήρα πίεσης
      float pressure = myPressure.readPressure(); // Αυτή η τιμή πρέπει να σταλεί στο ubidots
      Serial.print("Πίεση = ");
      Serial.print(pressure);
      Serial.print(" Pa, ");

      // Έλεγχος του αισθητήρα φωτός
      float light_lvl = get_light_level() * 100; // Αυτή η τιμή πρέπει να σταλεί στο ubidots
      Serial.print("Επίπεδο Φωτός = ");
      Serial.print(light_lvl);
      Serial.print("%");

      Serial.println();
    }

    digitalWrite(STAT_BLUE, LOW); // Απενεργοποίηση του LED κατάστασης
  }

  delay(5000);
}

// Επιστρέφει την τάση του αισθητήρα φωτός με βάση τη γραμμή 3,3V
// Αυτό μας επιτρέπει να αγνοήσουμε τις ποικίλες τάσεις VCC (ένα Arduino που είναι συνδεδεμένο στο USB έχει VCC που κυμαίνεται από 4,5V έως 5,2V)
float get_light_level()
{
  float operatingVoltage = analogRead(REFERENCE_3V3);
  float lightSensor = analogRead(LIGHT);
  operatingVoltage = 3.3 / operatingVoltage; // Η τάση αναφοράς είναι 3,3V
  lightSensor = operatingVoltage * lightSensor;
  return lightSensor;
}
