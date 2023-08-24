/********************************
 * Βιβλιοθήκες που περιλαμβάνονται
 *******************************/
#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>
#include <Wire.h> // I2C απαραίτητο για τους αισθητήρες
#include "SparkFunMPL3115A2.h" // Αισθητήρας πίεσης - Αναζήτηση "SparkFun MPL3115" και εγκατάσταση από τον Προγραμματιστικό Πίνακα
#include "SparkFun_Si7021_Breakout_Library.h" // Αισθητήρας υγρασίας - Αναζήτηση "SparkFun Si7021" και εγκατάσταση από τον Προγραμματιστικό Πίνακα

MPL3115A2 myPressure; // Δημιουργία ενός αντικειμένου για τον αισθητήρα πίεσης
Weather myHumidity; // Δημιουργία ενός αντικειμένου για τον αισθητήρα υγρασίας

// Ορισμοί υποδομής για την ορισμένη αριθμητική και ψηφιακή αντιστοίχιση των ακροδεκτών
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Ψηφιακοί ακροδέκτες Ε/Σ
const byte WSPEED = 3;
const byte RAIN = 2;
const byte STAT1 = 7;
const byte STAT2 = 8;

// Αναλογικοί ακροδέκτες Ε/Σ
const byte REFERENCE_3V3 = A3;
const byte LIGHT = A1;
const byte BATT = A2;
const byte WDIR = A0;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Παγκόσμιες Μεταβλητές
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long lastSecond; // Ο μετρητής millis για τον έλεγχο πότε περνάει ένα δευτερόλεπτο
byte seconds; // Όταν φτάσει το 60, αυξάνεται η τρέχουσα λεπτά
byte minutes; // Κρατάει το πού βρισκόμαστε σε διάφορα σύνολα δεδομένων

long lastWindCheck = 0;
volatile long lastWindIRQ = 0;
volatile byte windClicks = 0;
byte windspdavg[120]; // 120 bytes για να κρατάμε τη μέση τιμή 2 λεπτών

#define WIND_DIR_AVG_SIZE 120
int winddiravg[WIND_DIR_AVG_SIZE]; // 120 ints για να κρατάμε τη μέση τιμή 2 λεπτών
float windgust_10m[10]; // 10 floats για να κρατάμε το μέγιστο 10 λεπτών
int windgustdirection_10m[10]; // 10 ints για να κρατάμε την κατεύθυνση του μέγιστου 10 λεπτών
volatile float rainHour[60]; // 60 αριθμοί με κινητή υποδιαστολή για να κρατάμε τα 60 λεπτά βροχής

// Αυτές είναι όλες οι αξίες καιρού που αναμένει το Wunderground:
int winddir = 0; // [0-360 άμεση κατεύθυνση ανέμου]
float windspeedmph = 0; // [mph άμεση ταχύτητα ανέμου]
float windgustmph = 0; // [mph τρέχουσα ταχύτητα ανέμου, χρησιμοποιώντας προκαθορισμένη χρονική περίοδο λογισμικού]
int windgustdir = 0; // [0-360 χρησιμοποιώντας προκαθορισμένη χρονική περίοδο λογισμικού]
float windspdmph_avg2m = 0; // [mph 2-λεπτη μέση ταχύτητα ανέμου mph]
int winddir_avg2m = 0; // [0-360 2-λεπτη μέση κατεύθυνση ανέμου]
float windgustmph_10m = 0; // [mph ταχύτητα ανέμου των τελευταίων 10 λεπτών]
int windgustdir_10m = 0; // [0-360 κατεύθυνση ταχύτητας ανέμου των τελευταίων 10 λεπτών]
float humidity = 0; // [%]
float tempf = 0; // [θερμοκρασία F]
float rainin = 0; // [ιντσών βροχή τις τελευταίες ώρες)] - η συσσωρευμένη βροχή της τελευταίας ώρας
volatile float dailyrainin = 0; // [ιντσών βροχή μέχρι τώρα σήμερα στην τοπική ώρα]
float pressure = 0;
float light_lvl = 455; // [αναλογική τιμή από 0 έως 1023]

// Οι volatiles μπορούν να τροποποιηθούν από τις IRQs
volatile unsigned long raintime, rainlast, raininterval, rain;

//Συναρτήσεις διακοπτών (αυτές καλούνται από τις υλικού παρακάμψεις, όχι από τον κύριο κώδικα)
void rainIRQ()
// Μετράει τα κουταλάκια της βροχομετρητής καθώς συμβαίνουν
// Ενεργοποιείται από το μαγνήτη και το ρελέ που είναι συνδεδεμένα στον βροχομετρητή, που είναι συνδεδεμένα στην είσοδο D2
{
    raintime = millis(); // πάρε την τρέχουσα ώρα
    raininterval = raintime - rainlast; // υπολόγισε το διάστημα ανάμεσα σε αυτό και το προηγούμενο γεγονός

    if (raininterval > 10) // αγνόησε τα προβλήματα αναπήδησης του διακόπτη λιγότερο από 10ms μετά την αρχική άκρη
    {
        dailyrainin += 0.011; // Κάθε αντλία είναι 0,011" νερό
        rainHour[minutes] += 0.011; // Αυξάνει την ποσότητα της βροχής αυτού του λεπτού

        rainlast = raintime; // ρύθμιση για το επόμενο γεγονός
    }
}

void wspeedIRQ()
// Ενεργοποιείται από τον μαγνήτη στο ανεμόμετρο (2 κλικ ανά περιστροφή), που είναι συνδεδεμένο στην είσοδο D3
{
    if (millis() - lastWindIRQ > 10) // Αγνόησε τα προβλήματα αναπήδησης του διακόπτη λιγότερο από 10ms (μέγιστη ανάγνωση 142MPH) μετά το κλείσιμο του διακόπτη Reed
    {
        lastWindIRQ = millis(); // Καταγράψτε την τρέχουσα ώρα
        windClicks++; // Υπάρχουν 1,492MPH για κάθε κλικ ανά δευτερόλεπτο.
    }
}

/********************************
 * Σταθερές και αντικείμενα
 *******************************/
/* Ορίζει τις παραμέτρους του Ubidots */
char const * TOKEN = "BBFF-ILkRfrbiyQZpdd0HERbzL33R6FKaZu"; // Αναθέστε το TOKEN Ubidots
char const * VARIABLE_LABEL_1 = "temperature"; // Αναθέστε μια μοναδική ετικέτα μεταβλητής για την αποστολή των δεδομένων
char const * VARIABLE_LABEL_2 = "humidity"; // Αναθέστε μια μοναδική ετικέτα μεταβλητής για την αποστολή των δεδομένων
char const * VARIABLE_LABEL_3 = "pressure"; // Αναθέστε μια μοναδική ετικέτα μεταβλητής για την αποστολή των δεδομένων
char const * VARIABLE_LABEL_4 = "light"; // Αναθέστε μια μοναδική ετικέτα μεταβλητής για την αποστολή των δεδομένων
char const * VARIABLE_LABEL_5 = "rainin"; // Αναθέστε μια μοναδική ετικέτα μεταβλητής για την αποστολή των δεδομένων
char const * VARIABLE_LABEL_6 = "winddir"; // Αναθέστε μια μοναδική ετικέτα μεταβλητής για την αποστολή των δεδομένων
char const * VARIABLE_LABEL_7 = "speed"; // Αναθέστε μια μοναδική ετικέτα μεταβλητής για την αποστολή των δεδομένων

/* Καθορίζει μια διεύθυνση MAC για τον ελεγκτή σας παρακάτω */
/* Οι νεότερες Ethernet shields έχουν μια διεύθυνση MAC που είναι εκτυπωμένη σε αυτοκόλλητο στο shield */
byte mac[] = { 0xDE, 0x69, 0xBE, 0xEF, 0x69, 0xED };

/* αρχικοποιεί το αντικείμενο */
Ubidots client(TOKEN);

/********************************
 * Κύριες Συναρτήσεις
 *******************************/
void setup()
{
    Serial.begin(9600);
    Serial.println("Weather Shield Example");

    pinMode(STAT1, OUTPUT); // Ορισμός ως έξοδος για το LED κατάστασης Μπλε
    pinMode(STAT2, OUTPUT); // Ορισμός ως έξοδος για το LED κατάστασης Πράσινο

    pinMode(WSPEED, INPUT_PULLUP); // είσοδος από αισθητήρες ταχύτητας ανέμου
    pinMode(RAIN, INPUT_PULLUP); // είσοδος από αισθητήρες μετρητή βροχής

    pinMode(REFERENCE_3V3, INPUT);
    pinMode(LIGHT, INPUT);

    // Ρύθμιση του αισθητήρα πίεσης
    myPressure.begin(); // Ενεργοποίηση του αισθητήρα
    myPressure.setModeBarometer(); // Μέτρηση της πίεσης σε Pascals από 20 έως 110 kPa
    myPressure.setOversampleRate(7); // Ορισμός του Μεγέθους Δείγματος στη συνιστώμενη τιμή 128
    myPressure.enableEventFlags(); // Ενεργοποίηση όλων των σημαιών γεγονότων πίεσης και θερμοκρασίας

    // Ρύθμιση του αισθητήρα υγρασίας
    myHumidity.begin();

    seconds = 0;
    lastSecond = millis();

    // Σύνδεση εξωτερικών διακοπτών με τις συναρτήσεις IRQ
    attachInterrupt(0, rainIRQ, FALLING);
    attachInterrupt(1, wspeedIRQ, FALLING);

    // Ενεργοποίηση διακοπτών
    interrupts();

    Serial.println("Weather Shield online!");
    /* ξεκινήστε τη σύνδεση Ethernet */
    Serial.print(F("Έναρξη Ethernet..."));
    if (!Ethernet.begin(mac)) {
        Serial.println(F("απέτυχε"));
    } else {
        Serial.println(Ethernet.localIP());
    }
    /* Περιμένετε ένα δευτερόλεπτο για να αρχικοποιηθεί το Ethernet shield */
    delay(2000);
    Serial.println(F("Έτοιμο το Ethernet"));
}

void loop()
{
    Ethernet.maintain();
    // Κρατήστε τον έλεγχο του τρέχοντος λεπτού
    if (millis() - lastSecond >= 1000)
    {
        digitalWrite(STAT1, HIGH); // Αναβοσβήνει το LED κατάστασης

        lastSecond += 1000;
        float currentSpeed = get_wind_speed();
        windspeedmph = currentSpeed; // Ενημέρωση της παγκόσμιας μεταβλητής για την ταχύτητα ανέμου όταν χρησιμοποιείται η συνάρτηση printWeather()
        int currentDirection = get_wind_direction();

        // Αναφορά όλων των δεδομένων που λαμβάνονται από τους αισθητήρες
        temperature();
        humidityValue();
        pressureValue();
        lightValue();
        raininValue();
        windirValue();
        speedValue();

        digitalWrite(STAT1, LOW); // Σβήσιμο του LED κατάστασης
    }
}

// Συνάρτηση για τη μέτρηση της θερμοκρασίας
void temperature()
{
    tempf = myHumidity.getTempF(); // Ανάκτηση θερμοκρασίας σε βαθμούς Fahrenheit
    Serial.print("Temperature: ");
    Serial.print(tempf);
    Serial.println(" F");
    client.add(VARIABLE_LABEL_1, tempf); // Προσθέστε τη θερμοκρασία στη λίστα αποστολής του Ubidots
}

// Συνάρτηση για τη μέτρηση της υγρασίας
void humidityValue()
{
    humidity = myHumidity.getRH(); // Ανάκτηση υγρασίας σε επίπεδο 0-100%
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    client.add(VARIABLE_LABEL_2, humidity); // Προσθήκη της υγρασίας στη λίστα αποστολής του Ubidots
}

// Συνάρτηση για τη μέτρηση της πίεσης
void pressureValue()
{
    pressure = myPressure.readPressure(); // Ανάκτηση της πίεσης σε Pascals
    pressure = pressure / 100; // Μετατροπή της πίεσης σε hPa
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" hPa");
    client.add(VARIABLE_LABEL_3, pressure); // Προσθέστε την πίεση στη λίστα αποστολής του Ubidots
}

// Συνάρτηση για τη μέτρηση της φωτεινότητας
void lightValue()
{
    light_lvl = analogRead(LIGHT); // Ανάκτηση της αναλογικής τιμής της φωτεινότητας
    Serial.print("Light Level: ");
    Serial.println(light_lvl);
    client.add(VARIABLE_LABEL_4, light_lvl); // Προσθήκη της φωτεινότητας στη λίστα αποστολής του Ubidots
}

// Συνάρτηση για τη μέτρηση της βροχής
void raininValue()
{
    rainin = dailyrainin; // Ανάκτηση της συσσωρευμένης βροχής της τελευταίας ώρας
    Serial.print("Rain in last hour: ");
    Serial.print(rainin);
    Serial.println(" in");
    client.add(VARIABLE_LABEL_5, rainin); // Προσθήκη της βροχής στη λίστα αποστολής του Ubidots
}

// Συνάρτηση για τη μέτρηση της κατεύθυνσης του ανέμου
void windirValue()
{
    winddir = get_wind_direction(); // Ανάκτηση της κατεύθυνσης του ανέμου
    Serial.print("Wind Direction: ");
    Serial.print(winddir);
    Serial.println(" degrees");
    client.add(VARIABLE_LABEL_6, winddir); // Προσθήκη της κατεύθυνσης του ανέμου στη λίστα αποστολής του Ubidots
}

// Συνάρτηση για τη μέτρηση της ταχύτητας του ανέμου
void speedValue()
{
    windspeedmph = get_wind_speed(); // Ανάκτηση της ταχύτητας του ανέμου
    Serial.print("Windspeed: ");
    Serial.print(windspeedmph);
    Serial.println(" mph");
    client.add(VARIABLE_LABEL_7, windspeedmph); // Προσθήκη της ταχύτητας του ανέμου στη λίστα αποστολής του Ubidots
}

// Συνάρτηση για τον υπολογισμό της ταχύτητας του ανέμου
float get_wind_speed()
{
    float deltaTime = millis() - lastWindCheck; // Χρονική διάρκεια από τον τελευταίο έλεγχο της ταχύτητας ανέμου
    deltaTime /= 1000.0; // Μετατροπή σε δευτερόλεπτα

    float windSpeed = (float)windClicks / deltaTime; // Υπολογισμός της ταχύτητας ανέμου σε κλικ ανά δευτερόλεπτο

    windClicks = 0; // Επαναφορά του μετρητή των κλικ ανέμου

    lastWindCheck = millis(); // Ενημέρωση της τελευταίας χρονικής σήμανσης του ελέγχου της ταχύτητας ανέμου

    return windSpeed;
}

// Συνάρτηση για τον υπολογισμό της κατεύθυνσης του ανέμου
int get_wind_direction()
{
    unsigned int adc;

    adc = analogRead(WDIR); // Ανάκτηση της αναλογικής τιμής της κατεύθυνσης του ανέμου

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

    return (-1); // Μη έγκυρη τιμή, αν δεν βρέθηκε καμία αντιστοιχία
}
