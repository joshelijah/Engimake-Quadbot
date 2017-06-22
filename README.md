# Engimake-Quadbot
The design and software files for the Engimake QuadBot. An open source, four-legged, 3D Printed robot. Included here are all the files you'll need to create QuadBot.

1) The Arduino code
2) The Mechanical design files
3) The PCB layout

These files are presented as-is, and are not in a finished state. You'll need to apply initiative to fill in any gaps, this is not a step by step guide! That said these files are the basis of what you'll need to build a working QuadBot.

## Getting Started

These instructions will tell you what software you'll need for accessing these design and software files. 

### Prerequisites

What things you need to install the software and how to install them

```
Software: Arduino IDE, found here (www.arduino.cc/en/Main/Software)
Mechanical Design: Any 3D CAD package. We used Autodesk Fusion 360, found here (www.autodesk.com/products/fusion-360/free-trial)
Electronics Design: Any electronics CAD package. We recommend DesignSpark PCB or Eagle (www.rs-online.com/designspark/pcb-software) or (https://www.autodesk.com/products/eagle/free-download)

```

### Installing Arduino

Installing the CAD packages is straight forward. To program QuadBot from Arduino you will need to install Arduino and the following Arduino libraries...

```
1) The Servo library
2) The Adafruit Neopixel library, found here (https://github.com/adafruit/Adafruit_NeoPixel)
3) The QuadBot library, found in these files.
```
The Servo library comes preinstalled with Arduino, and allows us to control the servos. The Adafruit Neopixel library needs to be downloaded and installed to Arduino. Follow the link below for a guide on installing Arduino libraries.

https://www.arduino.cc/en/Guide/Libraries

The QuadBot library was written by us to allow easy programming of QuadBot. It's relatively straight forward and well documented. Credit to Daniel Elijah for writing this fantastic library. d.elijah@gmail.com

```
1) Install the Arduino IDE. 
2) Download the Adafruit Neopixel library and install it.
3) Download the QuadBot library and install it.
```

## Built With

* [Autodesk Fusion 360](www.autodesk.com/products/fusion-360/free-trial) - CAD software
* [DesignSpark PCB](www.rs-online.com/designspark/pcb-software) - Electronics Cad software
* [Arduino](www.arduino.cc/en/Main/Software) - Arduino

## Contributing

Feel free as you wish to contribute your designs. This repository is not maintained.

## Authors

Engimake Ltd.

## License

This project is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License (CC BY-SA 4.0). Refer to http://creativecommons.org/licenses/by-sa/4.0/ for more information.
