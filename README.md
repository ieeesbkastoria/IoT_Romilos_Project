### Reason for the Project
The IoT_Romilos_Project was developed as a research project by the IEEE Student Branch of Western Macedonia, Kastoria, to explore the field of Internet of Things (IoT) and gain practical knowledge in this area. It serves as a hands-on learning experience for understanding the implementation of IoT applications and sensor integration for weather monitoring.

### Project Capabilities
The IoT_Romilos_Project is capable of collecting and transmitting various real-time weather measurements. The project includes sensors for the following measurements:
- Temperature
- Humidity
- Pressure
- Light Level
- Wind Speed

These measurements are continuously monitored and can be sent to an online platform for further analysis and visualization.

### Materials and Required Software
To run this project, you will need the following materials:
- Arduino Uno R3 board
- SparkFun sensors (MPL3115A2 for pressure and SparkFun Si7021 for humidity)
- Additional hardware components (wiring, resistors, etc.) as specified in the project documentation

The software required to run the project includes:
- Arduino IDE or Visual Studio Code with Arduino extension
- Libraries for the sensors used (SparkFunMPL3115A2 and SparkFun_Si7021_Breakout)

## Installation Instructions

Follow these step-by-step instructions to set up the IoT_Romilos_Project on your system:

### Prerequisites

- Arduino IDE or Visual Studio Code with Arduino extension installed on your computer.
- An Arduino Uno R3 board compatible with the Arduino IDE.

### Hardware Setup

1. Connect the required hardware components, including the Arduino board, SparkFun MPL3115A2 pressure sensor, and SparkFun Si7021 humidity sensor, as per the wiring diagram provided in the project documentation.

2. Ensure all connections are secure and properly aligned.



### Software Setup

1. Open the Arduino IDE or Visual Studio Code with Arduino extension.

2. Create a new Arduino project.

3. Install the necessary libraries for the project:
   - Open the Library Manager in the Arduino IDE by navigating to **Sketch** -> **Include Library** -> **Manage Libraries**.
   - Search for "SparkFunMPL3115A2" and click **Install** to install the MPL3115A2 library.
   - Search for "SparkFun_Si7021_Breakout" and click **Install** to install the Si7021 library.

4. Include the required libraries in your sketch:
   ```cpp
   #include <Wire.h>
   #include "SparkFunMPL3115A2.h"
   #include "SparkFun_Si7021_Breakout_Library.h"
   ```

5. Configure the Arduino board settings, such as the board type and port, in the Arduino IDE or Visual Studio Code.

6. Copy the code from the respective project part (Romilos_Only_Sparkfun or Romilos_With_Ubidots) and paste it into your Arduino sketch.

7. Upload the sketch to your Arduino board by clicking the **Upload** button in the Arduino IDE or using the corresponding command in Visual Studio Code.

8. Open the serial monitor in the Arduino IDE or Visual Studio Code to view the output and ensure proper communication with the sensors.

9. Congratulations! You have successfully set up the IoT_Romilos_Project on your system.

### Troubleshooting

If you encounter any issues during installation or while running the project, try the following troubleshooting steps:

- Check the wiring connections to ensure they are correct and secure.
- Verify that the required libraries are installed properly and up to date.
- Ensure that the Arduino board is selected correctly in the Arduino IDE or Visual Studio Code.
- Restart the Arduino IDE or Visual Studio Code and reconnect the Arduino board.
- Consult the project documentation or seek help from the community for further assistance.

## Contributing and License

We, the team of the IEEE Student Branch of Western Macedonia, Kastoria, are delighted to have created the IoT_Romilos_Project as a valuable resource for newcomers to the Internet of Things (IoT) field. Our goal is to foster learning and provide a platform for individuals interested in exploring the exciting world of IoT.

We invite you to use this project as a learning tool and gain practical experience in working with IoT technologies and sensor integration. Whether you are a student, hobbyist, or professional, we believe that this project can serve as a stepping stone for understanding and mastering IoT concepts.

Additionally, we encourage you to engage with our team and the wider community. If you have any questions, suggestions, or improvements regarding the IoT_Romilos_Project, please feel free to reach out to us. We are open to collaboration and look forward to working together to enhance this project further.

To contribute to the IoT_Romilos_Project, you can follow these steps:

1. Fork the repository on GitHub.
2. Make your desired changes or additions to the project.
3. Test your modifications thoroughly to ensure they work as intended.
4. Create a pull request, clearly documenting the changes you have made and their purpose.
5. Our team will review your contribution and provide feedback.
6. Once approved, your changes will be merged into the main project.

We appreciate your interest and support in making the IoT_Romilos_Project better. Together, let's explore the possibilities of IoT and create a collaborative learning environment.

Feel free to communicate with us through the project repository's issue tracker or by reaching out to the project maintainers directly.

Let's grow together in the exciting field of IoT!





### Αφορμή για την υλοποίηση του Project

Το IoT_Romilos_Project αναπτύχθηκε ως project έρευνας από το IEEE Student Branch Δυτικής Μακεδονίας, Καστοριά, με σκοπό την εξερεύνηση του χώρου του Internet of Things (IoT) και την απόκτηση πρακτικών γνώσεων στον τομέα αυτό. Χρησιμεύει ως μια πρακτική μαθησιακή εμπειρία για την κατανόηση της υλοποίησης εφαρμογών IoT και της ενσωμάτωσης αισθητήρων για την παρακολούθηση του καιρού.



### Δυνατότητες του έργου

Το IoT_Romilos_Project είναι ικανό να συλλέγει και να μεταδίδει διάφορες μετρήσεις καιρού σε πραγματικό χρόνο. Το project περιλαμβάνει αισθητήρες για τις ακόλουθες μετρήσεις:

- Θερμοκρασία

- Υγρασία

- Πίεση

- Επίπεδο φωτός

- Ταχύτητα ανέμου



Αυτές οι μετρήσεις παρακολουθούνται συνεχώς και μπορούν να αποστέλλονται σε μια διαδικτυακή πλατφόρμα για περαιτέρω ανάλυση και απεικόνιση.

### Απαιτούμενα υλικά και λογισμικό

Για να πραγματοποιήσετε αυτό το project, θα χρειαστείτε τα ακόλουθα:

- Πλακέτα Arduino

- αισθητήρες SparkFun (MPL3115A2 για την πίεση και SparkFun Si7021 για την υγρασία)

- Πρόσθετα εξαρτήματα υλικού (καλωδίωση, αντιστάσεις κ.λπ.) όπως ορίζεται στην τεκμηρίωση του έργου



Το λογισμικό που απαιτείται για την εκτέλεση του έργου περιλαμβάνει:

- Arduino IDE ή Visual Studio Code με επέκταση Arduino

- Βιβλιοθήκες για τους αισθητήρες που χρησιμοποιούνται (SparkFunMPL3115A2 και SparkFun_Si7021_Breakout)


## Οδηγίες τοποθέτησης



Ακολουθήστε αυτές τις οδηγίες βήμα προς βήμα για να ρυθμίσετε το IoT_Romilos_Project στο σύστημά σας:



### Προϋποθέσεις



- Εγκατεστημένο στον υπολογιστή σας το Arduino IDE ή το Visual Studio Code με την επέκταση Arduino.

- Μια πλακέτα Arduino συμβατή με το Arduino IDE.



### Εγκατάσταση υλικού



1. Συνδέστε τα απαιτούμενα εξαρτήματα υλικού, συμπεριλαμβανομένης της πλακέτας Arduino, του αισθητήρα πίεσης SparkFun MPL3115A2 και του αισθητήρα υγρασίας SparkFun Si7021, σύμφωνα με το διάγραμμα συνδεσμολογίας που παρέχεται στην τεκμηρίωση του έργου.



2. Βεβαιωθείτε ότι όλες οι συνδέσεις είναι ασφαλείς και σωστά ευθυγραμμισμένες.


### Εγκατάσταση λογισμικού



1. Ανοίξτε το Arduino IDE ή το Visual Studio Code με την επέκταση Arduino.



2. Δημιουργήστε ένα νέο έργο Arduino.



3. Εγκαταστήστε τις απαραίτητες βιβλιοθήκες για το έργο:

   - Ανοίξτε τη διαχείριση βιβλιοθηκών στο Arduino IDE, μεταβαίνοντας στην επιλογή **Sketch** -> **Include Library** -> **Manage Libraries**.

   - Αναζητήστε το "SparkFunMPL3115A2" και κάντε κλικ στο **Εγκατάσταση** για να εγκαταστήσετε τη βιβλιοθήκη MPL3115A2.

   - Αναζητήστε το "SparkFun_Si7021_Breakout" και κάντε κλικ στο **Εγκατάσταση** για να εγκαταστήσετε τη βιβλιοθήκη Si7021.
Για το Ubidots χρησιμοποιούμε τις βιβλιοθηκες :
-Ethernet.h
-SPI.h
-UbidotsEthernet.h
-Wire.h
Τις συγκεκριμενες βιβλιοθήκες μπορειτε να τις βρείτε με μια απλη αναζητηση στο google.


4. Συμπεριλάβετε τις απαιτούμενες βιβλιοθήκες στο σκίτσο σας:

   ```cpp

   #include <Wire.h>

   #include "SparkFunMPL3115A2.h"

   #include "SparkFun_Si7021_Breakout_Library.h"

   ```



5. Διαμορφώστε τις ρυθμίσεις της πλακέτας Arduino, όπως τον τύπο και τη θύρα της πλακέτας, στο Arduino IDE ή στο Visual Studio Code.



6. Αντιγράψτε τον κώδικα από το αντίστοιχο μέρος του έργου (Romilos_Only_Sparkfun ή Romilos_With_Ubidots) και επικολλήστε τον στο σκίτσο Arduino.



7. Ανεβάστε το σκίτσο στην πλακέτα Arduino κάνοντας κλικ στο κουμπί **Upload** στο Arduino IDE ή χρησιμοποιώντας την αντίστοιχη εντολή στο Visual Studio Code.



8. Ανοίξτε τη σειριακή οθόνη στο Arduino IDE ή στο Visual Studio Code για να δείτε την έξοδο και να διασφαλίσετε τη σωστή επικοινωνία με τους αισθητήρες.



9. Συγχαρητήρια! Έχετε ρυθμίσει με επιτυχία το IoT_Romilos_Project στο σύστημά σας.


## Συνεισφορά και άδεια χρήσης



Εμείς, η ομάδα του IEEE Student Branch Δυτικής Μακεδονίας, Καστοριά, είμαστε στην ευχάριστη θέση να έχουμε δημιουργήσει το IoT_Romilos_Project ως μια χρήσιμη πηγή για τους νεοεισερχόμενους στον τομέα του Διαδικτύου των Πραγμάτων (IoT). Στόχος μας είναι να προωθήσουμε τη μάθηση και να παρέχουμε μια πλατφόρμα για άτομα που ενδιαφέρονται να εξερευνήσουν τον συναρπαστικό κόσμο του IoT.



Σας προσκαλούμε να χρησιμοποιήσετε αυτό το έργο ως εργαλείο μάθησης και να αποκτήσετε πρακτική εμπειρία στην εργασία με τεχνολογίες IoT και την ενσωμάτωση αισθητήρων. Είτε είστε φοιτητής, ερασιτέχνης ή επαγγελματίας, πιστεύουμε ότι αυτό το έργο μπορεί να χρησιμεύσει ως εφαλτήριο για την κατανόηση και την κατάκτηση των εννοιών του IoT.



Επιπλέον, σας ενθαρρύνουμε να συνεργαστείτε με την ομάδα μας και την ευρύτερη κοινότητα. Αν έχετε οποιεσδήποτε ερωτήσεις, προτάσεις ή βελτιώσεις σχετικά με το IoT_Romilos_Project, μη διστάσετε να επικοινωνήσετε μαζί μας. Είμαστε ανοιχτοί στη συνεργασία και ανυπομονούμε να συνεργαστούμε για την περαιτέρω βελτίωση αυτού του έργου.



Για να συνεισφέρετε στο IoT_Romilos_Project, μπορείτε να ακολουθήσετε τα παρακάτω βήματα:



1. Διασυνδέστε το αποθετήριο στο GitHub.

2. Κάντε τις επιθυμητές αλλαγές ή προσθήκες στο έργο.

3. Δοκιμάστε διεξοδικά τις τροποποιήσεις σας για να βεβαιωθείτε ότι λειτουργούν όπως προβλέπεται.

4. Δημιουργήστε ένα pull request, τεκμηριώνοντας με σαφήνεια τις αλλαγές που κάνατε και τον σκοπό τους.

5. Η ομάδα μας θα επανεξετάσει τη συνεισφορά σας και θα παράσχει ανατροφοδότηση.

6. Μόλις εγκριθεί, οι αλλαγές σας θα συγχωνευθούν στο κύριο έργο.



Εκτιμούμε το ενδιαφέρον και την υποστήριξή σας για να κάνουμε το IoT_Romilos_Project καλύτερο








Romilos_Only_Sparkfun README

# Weather Monitoring with Arduino and Sensors - README

This README file provides a step-by-step explanation of the code provided. The code is designed to read data from various sensors, including a pressure sensor, a humidity sensor, and a light sensor, using an Arduino board. The data collected is then printed to the Serial Monitor. Additionally, the code includes instructions for setting up the hardware and installing the necessary libraries to make the project work.

## Hardware Setup

To use this code, you will need the following hardware components:

1. Arduino board (e.g., Arduino Uno, Arduino Mega, etc.)
2. Weather Shield (includes the MPL3115A2 Pressure Sensor and the Si7021 Humidity Sensor)
3. Light Sensor (connected to the Arduino analog pin A1)
4. Two LEDs (optional) for status indication (connected to Arduino digital pin 7)

Connect the hardware as follows:

1. Connect the Weather Shield to the Arduino board using the I2C interface.
2. Connect the Light Sensor to the analog pin A1 of the Arduino.
3. Optionally, connect two LEDs to the digital pin 7 of the Arduino for status indication.

## Library Installation

Before uploading the code to the Arduino board, you need to install the required libraries from the Arduino Library Manager. Follow these steps to install the libraries:

1. Search for "SparkFun MPL3115" in the Library Manager and install the "SparkFun MPL3115A2" library.
2. Search for "SparkFun Si7021" in the Library Manager and install the "SparkFun_Si7021_Breakout_Library."

## Code Explanation

Below is a step-by-step explanation of the code:

1. Import necessary libraries:

   ```c++
   #include <Wire.h> // I2C for sensors
   #include "SparkFunMPL3115A2.h" // Pressure Sensor
   #include "SparkFun_Si7021_Breakout_Library.h" // Humidity Sensor
   ```

2. Create instances for the pressure and humidity sensors:

   ```c++
   MPL3115A2 myPressure; // Create a pressure sensor instance
   Weather myHumidity; // Create a humidity sensor instance
   ```

3. Define hardware terminal pins:

   ```c++
   const byte STAT_BLUE = 7;
   const byte REFERENCE_3V3 = A3;
   const byte LIGHT = A1;
   ```

   These variables store the pin numbers for the status LED, 3.3V reference terminal, and light sensor.

4. Initialize global variables:

   ```c++
   long lastSecond; // The millis counter to see when a second rolls by
   ```

5. The `setup()` function:

   - Initialize Serial communication at 9600 baud rate.
   - Print a message to indicate the Weather Shield example is running.
   - Set the STAT_BLUE pin as an output for the status LED.
   - Set the REFERENCE_3V3 and LIGHT pins as inputs for the light sensor and reference voltage measurement, respectively.
   - Configure the pressure sensor (`myPressure`) by:
     - Calling `begin()` to start communication with the sensor.
     - Setting the measurement mode to barometric pressure using `setModeBarometer()`.
     - Adjusting the oversample rate for higher accuracy with `setOversampleRate()`.
     - Enabling event flags for pressure and temperature with `enableEventFlags()`.
   - Configure the humidity sensor (`myHumidity`) by calling `begin()`.

6. The `loop()` function:

   - The main loop runs continuously.
   - The `if` statement checks if a second has elapsed by comparing the current `millis()` value with `lastSecond`. If a second has passed, it enters the loop to read sensor data and print it to the Serial Monitor.

7. Reading Humidity Sensor:

   - The code reads humidity data from the Si7021 humidity sensor using `myHumidity.getRH()`.
   - If the humidity reading is `998`, it indicates a failure in the I2C communication with the sensors. The code prints an error message and attempts to reinitialize I2C communication and the sensors.
   - If the humidity reading is valid, it is printed to the Serial Monitor.

8. Reading Temperature:

   - The code reads temperature data from the Si7021 humidity sensor using `myHumidity.getTempF()`.
   - The temperature is then converted from Fahrenheit to Celsius and printed to the Serial Monitor.

9. Reading Pressure:

   - The code reads pressure data from the MPL3115A2 pressure sensor using `myPressure.readPressure()`.
   - The pressure reading is printed to the Serial Monitor in Pascal units.

10. Reading Light Sensor:

    - The code calls the `get_light_level()` function to read the light sensor data.
    - The function reads the analog value from the light sensor and calculates the light level percentage based on the 3.3V reference voltage.
    - The light level percentage is printed to the Serial Monitor.

11. Status LED Indication:

    - The STAT_BLUE LED is briefly turned on and then off to indicate that the sensor readings have been taken for that second.

12. Delay:

    - The code introduces a delay of 5 seconds (`delay(5000)`) to provide a small gap between consecutive readings.

## Additional Notes

- This code assumes that you have correctly connected the hardware components and installed the required libraries.
- Make sure the Arduino board is connected to your computer and the correct port is selected in the Arduino IDE before uploading the code.
- The code is designed to read sensor data every second. You can adjust the timing in the `if (millis() - lastSecond >= 1000)` statement to change the frequency of readings.
- The sensor readings are printed to the Serial Monitor. If you want to send this data to a remote server or platform, additional code needs to be added to handle data transmission, such as using Wi-Fi or other communication modules.

Remember to double-check your hardware connections, as incorrect wiring could lead to unexpected behavior or sensor failures.



# Έλεγχος του καιρικών συνθηκών με τον Arduino και τους αισθητήρες - README



Αυτό το αρχείο README παρέχει μια βήμα προς βήμα εξήγηση του παρεχόμενου κώδικα. Ο κώδικας έχει σχεδιαστεί για να διαβάζει δεδομένα από διάφορους αισθητήρες, συμπεριλαμβανομένου ενός αισθητήρα πίεσης, ενός αισθητήρα υγρασίας και ενός αισθητήρα φωτός, χρησιμοποιώντας μια πλακέτα Arduino. Τα δεδομένα που συλλέγονται εκτυπώνονται στη συνέχεια στη σειριακή οθόνη. Επιπλέον, ο κώδικας περιλαμβάνει οδηγίες για τη ρύθμιση του υλικού και την εγκατάσταση των απαραίτητων βιβλιοθηκών για να λειτουργήσει το έργο.



## Ρύθμιση υλικού



Για να χρησιμοποιήσετε αυτόν τον κώδικα, θα χρειαστείτε τον ακόλουθο εξοπλισμό:



1. Πλακέτα Arduino (π.χ. Arduino Uno, Arduino Mega κ.λπ.)

2. Weather Shield (περιλαμβάνει τον αισθητήρα πίεσης MPL3115A2 και τον αισθητήρα υγρασίας Si7021).

3. Αισθητήρας φωτός (συνδεδεμένος στον αναλογικό ακροδέκτη A1 του Arduino)

4. Δύο λυχνίες LED (προαιρετικά) για την ένδειξη της κατάστασης (συνδεδεμένες στον ψηφιακό ακροδέκτη 7 του Arduino)



Συνδέστε το υλικό ως εξής:



1. Συνδέστε το Weather Shield στην πλακέτα Arduino χρησιμοποιώντας τη διεπαφή I2C.

2. Συνδέστε τον αισθητήρα φωτός στον αναλογικό ακροδέκτη A1 του Arduino.

3. Προαιρετικά, συνδέστε δύο λυχνίες LED στον ψηφιακό ακροδέκτη 7 του Arduino για την ένδειξη της κατάστασης.



## Εγκατάσταση βιβλιοθήκης



Πριν ανεβάσετε τον κώδικα στην πλακέτα Arduino, πρέπει να εγκαταστήσετε τις απαιτούμενες βιβλιοθήκες από το Arduino Library Manager. Ακολουθήστε τα παρακάτω βήματα για να εγκαταστήσετε τις βιβλιοθήκες:



1. Αναζητήστε τη βιβλιοθήκη "SparkFun MPL3115" στο Library Manager και εγκαταστήστε τη βιβλιοθήκη "SparkFun MPL3115A2".

2. Αναζητήστε το "SparkFun Si7021" στο Library Manager και εγκαταστήστε τη βιβλιοθήκη "SparkFun_Si7021_Breakout_Library".



## Επεξήγηση κώδικα



Ακολουθεί μια βήμα προς βήμα επεξήγηση του κώδικα:



1. Εισάγετε τις απαραίτητες βιβλιοθήκες:



   ```c++

   #include <Wire.h> // I2C για αισθητήρες

   #include "SparkFunMPL3115A2.h" // Αισθητήρας πίεσης

   #include "SparkFun_Si7021_Breakout_Library.h" // Αισθητήρας υγρασίας

   ```



2. Δημιουργήστε στιγμιότυπα για τους αισθητήρες πίεσης και υγρασίας:



   ```c++

   MPL3115A2 myPressure; // Δημιουργία μιας περίπτωσης αισθητήρα πίεσης

   Weather myHumidity; // Δημιουργία μιας περίπτωσης αισθητήρα υγρασίας

   ```



3. Καθορίστε ακροδέκτες υλικού:



   ```c++

   const byte STAT_BLUE = 7,

   const byte REFERENCE_3V3 = A3,

   const byte LIGHT = A1,

   ```



   Αυτές οι μεταβλητές αποθηκεύουν τους αριθμούς ακροδεκτών για το LED κατάστασης, τον ακροδέκτη αναφοράς 3,3V και τον αισθητήρα φωτός.



4. Αρχικοποιήστε τις παγκόσμιες μεταβλητές:



   ```c++

   long lastSecond; // Ο μετρητής millis για να βλέπουμε πότε περνάει ένα δευτερόλεπτο

   ```



5. Η συνάρτηση `setup()`:



   - Αρχικοποίηση της σειριακής επικοινωνίας με ρυθμό 9600 baud.

   - Εκτύπωση ενός μηνύματος για να δείξει ότι το παράδειγμα Weather Shield εκτελείται.

   - Ορίστε την ακίδα STAT_BLUE ως έξοδο για το LED κατάστασης.

   - Ορίστε τις ακίδες REFERENCE_3V3 και LIGHT ως εισόδους για τον αισθητήρα φωτός και τη μέτρηση τάσης αναφοράς, αντίστοιχα.

   - Ρυθμίστε τον αισθητήρα πίεσης (`myPressure`) ως εξής:

     - Καλώντας την εντολή `begin()` για να ξεκινήσει η επικοινωνία με τον αισθητήρα.

     - Ορίζοντας τον τρόπο μέτρησης σε βαρομετρική πίεση χρησιμοποιώντας την `setModeBarometer()`.

     - Ρύθμιση του ρυθμού υπερδειγματοληψίας για μεγαλύτερη ακρίβεια με την `setOversampleRate()`.

     - Ενεργοποίηση των σημαιών συμβάντων για την πίεση και τη θερμοκρασία με την `enableEventFlags()`.

   - Διαμόρφωση του αισθητήρα υγρασίας (`myHumidity`) με την κλήση της διαδικασίας `begin()`.



6. Η συνάρτηση `loop()`:



   - Ο κύριος βρόχος εκτελείται συνεχώς.

   - Η εντολή `if` ελέγχει αν έχει περάσει ένα δευτερόλεπτο συγκρίνοντας την τρέχουσα τιμή `millis()` με την τιμή `lastSecond`. Εάν έχει περάσει ένα δευτερόλεπτο, εισέρχεται στο βρόχο για να διαβάσει τα δεδομένα του αισθητήρα και να τα εκτυπώσει στην σειριακή οθόνη.



7. Ανάγνωση του αισθητήρα υγρασίας:



   - Ο κώδικας διαβάζει δεδομένα υγρασίας από τον αισθητήρα υγρασίας Si7021 χρησιμοποιώντας την `myHumidity.getRH()`.

   - Εάν η ένδειξη υγρασίας είναι `998`, υποδεικνύει αποτυχία στην επικοινωνία I2C με τους αισθητήρες. Ο κώδικας εκτυπώνει ένα μήνυμα σφάλματος και προσπαθεί να επανεκκινήσει την επικοινωνία I2C και τους αισθητήρες.

   - Εάν η ένδειξη υγρασίας είναι έγκυρη, εκτυπώνεται στη σειριακή οθόνη.



8. Ανάγνωση θερμοκρασίας:



   - Ο κώδικας διαβάζει δεδομένα θερμοκρασίας από τον αισθητήρα υγρασίας Si7021 χρησιμοποιώντας την `myHumidity.getTempF()`.

   - Στη συνέχεια, η θερμοκρασία μετατρέπεται από Fahrenheit σε Κελσίου και εκτυπώνεται στη σειριακή οθόνη.



9. Ανάγνωση της πίεσης:



   - Ο κώδικας διαβάζει δεδομένα πίεσης από τον αισθητήρα πίεσης MPL3115A2 χρησιμοποιώντας την `myPressure.readPressure()`.

   - Η ένδειξη της πίεσης εκτυπώνεται στη σειριακή οθόνη σε μονάδες Pascal.



10. Ανάγνωση αισθητήρα φωτός:



    - Ο κώδικας καλεί τη συνάρτηση `get_light_level()` για να διαβάσει τα δεδομένα του αισθητήρα φωτός.

    - Η συνάρτηση διαβάζει την αναλογική τιμή από τον αισθητήρα φωτός και υπολογίζει το ποσοστό στάθμης φωτός με βάση την τάση αναφοράς 3,3V.

    - Το ποσοστό στάθμης φωτός εκτυπώνεται στην σειριακή οθόνη.



11. Ένδειξη LED κατάστασης:



    - Η λυχνία LED STAT_BLUE ανάβει για λίγο και στη συνέχεια σβήνει για να υποδείξει ότι οι μετρήσεις του αισθητήρα έχουν ληφθεί για το συγκεκριμένο δευτερόλεπτο.



12. Καθυστέρηση:



    - Ο κώδικας εισάγει μια καθυστέρηση 5 δευτερολέπτων (`delay(5000)`) για να παρέχει ένα μικρό κενό μεταξύ των διαδοχικών μετρήσεων.



## Πρόσθετες σημειώσεις



## Πρόσθετες σημειώσεις



- Αυτός ο κώδικας προϋποθέτει ότι έχετε συνδέσει σωστά τα εξαρτήματα υλικού και έχετε εγκαταστήσει τις απαιτούμενες βιβλιοθήκες.

- Βεβαιωθείτε ότι η πλακέτα Arduino είναι συνδεδεμένη με τον υπολογιστή σας και ότι η σωστή θύρα είναι επιλεγμένη στο Arduino IDE πριν ανεβάσετε τον κώδικα.

- Ο κώδικας έχει σχεδιαστεί για να διαβάζει τα δεδομένα του αισθητήρα κάθε δευτερόλεπτο. Μπορείτε να προσαρμόσετε το χρονισμό στην εντολή `if (millis() - lastSecond >= 1000)` για να αλλάξετε τη συχνότητα των αναγνώσεων.

- Οι μετρήσεις του αισθητήρα εκτυπώνονται στην σειριακή οθόνη. Εάν θέλετε να στείλετε αυτά τα δεδομένα σε έναν απομακρυσμένο διακομιστή ή πλατφόρμα, πρέπει να προστεθεί πρόσθετος κώδικας για να χειριστείτε τη μετάδοση δεδομένων, όπως η χρήση Wi-Fi ή άλλων μονάδων επικοινωνίας.



Θυμηθείτε να ελέγχετε διπλά τις συνδέσεις υλικού, καθώς η λανθασμένη καλωδίωση μπορεί να οδηγήσει σε απροσδόκητη συμπεριφορά ή αποτυχία του αισθητήρα.









