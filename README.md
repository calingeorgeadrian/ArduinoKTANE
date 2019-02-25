# Keep Talking and Nobody Explodes - Arduino
Our Arduino project for the Robotics course at our faculty: the bomb from Keep Talking And Nobody Explodes.  
It is a 2-players game that requires good communication skills and a lot of patience.  
  
The bomb has 4 different modules: Simon Says, Who's on First, Memory and The Button. Each one of these needs to be defused before the timer reaches zero in order for the bomb not to explode.  
Also, the bomb explodes if the team does 3 mistakes. 
  
One person will be holding the bomb and the other one will be going through the manual in order to help the first one defuse the modules.

## Table of Contents
**[1. Getting Started](#getting-started)**  
    - [1.1. Prerequisites](#prerequisites)  
    - [1.2. Installation](#installation)  
**[2. Components](#components)**  
**[3. Built With](#built-with)**  
**[4. Authors](#authors)**  
**[5. Credits](#credits)**  


## Getting Started
These instructions will get you a copy of the project up and running.

### Prerequisites
In order for the code to work, you will need the following libraries:  
- SevenSegmentTM1637 - [link](https://github.com/bremme/arduino-tm1637)  
- LedControl - [link](https://github.com/wayoda/LedControl)  
- LiquidCrystal - [link](https://www.arduinolibraries.info/libraries/liquid-crystal)  
- LiquidCrystal_I2C - [link](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)
- The files in this repository

### Installation
1. Download the .zip files from the links provided
2. Open Arduino IDE
3. Click Sketch -> Include Library -> Add .ZIP Library...
4. Select the library
5. Repeat steps 3 and 4 for each library
6. Download the files in this repository and put all of them in the same folder
7. Follow the Fritzing scheme in this repository in order to build the circuit

After following these steps, connect the Arduino board to your computer and upload the program, it should work just fine.

## Components
 - Arduino Mega
 - 1 Buzzer
 - 1 MAX7219 Driver
 - 1 16x2 LCD
 - 1 20x4 LCD
 - 1 I2C Module
 - 10 Push Buttons
 - 1 Illuminated Red Push Button
 - 1 Illuminated Green Push Button
 - 1 Illuminated Yellow Push Button
 - 1 Illuminated Blue Push Button
 - 3 Red LEDs
 - 4 Green LEDs
 - 7 Yellow LEDs
 - 2 RGB LEDs
 - 16 Led Supports
 - 1 7 Segment Digit
 - 1 4 Digits 7 Segment
 - 1 TM1637 LCD Clock
 - 1 Red Push Button
 - Many Resistances, Capacitors and Jumpers

## Built With

* [Arduino](https://www.arduino.cc/en/main/software) - The IDE we used to code into
* [Fritzing](http://fritzing.org/home/) - The program we used to create the components layout

## Authors

* **Calin George-Adrian** - [calingeorgeadrian](https://github.com/calingeorgeadrian)
* **Hirhui Ema** - [ema1ih](https://github.com/ema1ih)

## Credits

* Thanks to [bremme](https://github.com/bremme), [wayoda](https://github.com/wayoda), and [fdebrabander](https://github.com/fdebrabander) for creating the open-source libraries we used
* Definetly check the game that inspired us, official website [here](https://keeptalkinggame.com/)
