# Romilos Project 

*A hands-on learning experience for understanding the implementation of IoT applications and sensor integration for weather monitoring.*

Other Languages: *[Greek](https://github.com/ieeesbkastoria/IoT_Romilos_Project/blob/main/README_GR.md)*

-------------------------------------------------------
- [Romilos Project](#romilos-project)
  - [Project Motivation](#project-motivation)
  - [Project Capabilities](#project-capabilities)
  - [Materials \& Required Software](#materials--required-software)
  - [Installation Instructions](#installation-instructions)
    - [Hardware Setup](#hardware-setup)
    - [Software Setup](#software-setup)
  - [Troubleshooting](#troubleshooting)
  - [Contributing and License](#contributing-and-license)
  - [Project Implementation Team](#project-implementation-team)

## Project Motivation

The IoT_Romilos_Project was developed as a research project by the IEEE Student Branch of University of Western Macedonia - Kastoria as a way to explore the field of Internet of Things (IoT) and gain practical knowledge in this area. It serves as a hands-on learning experience for understanding the implementation of IoT applications and sensor integration for weather monitoring.

## Project Capabilities

The IoT_Romilos_Project is capable of collecting and transmitting various real-time weather measurements. The project includes sensors for the following measurements:
- Temperature
- Humidity
- Pressure
- Light Level
- Wind Speed

These measurements are continuously monitored and can be sent to an online platform for further analysis and visualization.

## Materials & Required Software

To run this project, you will need the following materials:
- Arduino Uno R3 board
- SparkFun sensors (MPL3115A2 for pressure and SparkFun Si7021 for humidity)
- Additional hardware components (wiring, resistors, etc.) as specified in the project documentation

The software required to run the project includes:
- Arduino IDE or Visual Studio Code with Arduino extension
- Libraries for the sensors used (SparkFunMPL3115A2 and SparkFun_Si7021_Breakout)

## Installation Instructions

Follow these step-by-step instructions to set up the IoT_Romilos_Project on your system:

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

## Troubleshooting

If you encounter any issues during installation or while running the project, try the following troubleshooting steps:

- Check the wiring connections to ensure they are correct and secure.
- Verify that the required libraries are installed properly and up to date.
- Ensure that the Arduino board is selected correctly in the Arduino IDE or Visual Studio Code.
- Restart the Arduino IDE or Visual Studio Code and reconnect the Arduino board.
- Seek help from the community for further assistance.

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

## Project Implementation Team

[Anastasiou Christos](https://github.com/Christos-16) - 4th Year Student of the University of Western Macedonia, Department of Informatics  
[Polychronis Kotsiopoulos](https://github.com/pjkots01) - 3rd Year Student of the University of Western Macedonia, Department of Computer Science  
[Christos Hitiris](https://github.com/Tilemaxos46) - PhD Candidate of the University of Western Macedonia in the Department of Electrical & Computer Engineering  
