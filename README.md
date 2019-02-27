# Keep Talking and Nobody Explodes - Arduino
Our Arduino project for the Robotics course at our faculty: the bomb from Keep Talking And Nobody Explodes.  
The game can be played with a minumum of 2 players, with one player as the "Defuser" and the remaining players as the "Experts" reading the provided bomb defusal manual.    

As designed, the Defuser cannot look at the manual and must rely on the Experts to instruct him or her; likewise, the Experts cannot see the bomb and must rely on the Defuser to describe the bomb to them. Communicating with each other occurs directly from across a table.
  
The bomb consists of 4 modules: Simon Says, Who's on First, Memory and The Button. The modules are independent of each other and can be disarmed in any order. The modules require disarming, with the bomb successfully difused when all the modules are successfully disarmed.  

The bomb also has a countdown timer that, if it hits zero, will cause the bomb to go off. It also has a maximum number of strikes resulting from errors made during defusing, and if that maximum is reached, the bomb will also go off.  

The modules use complex instruction sets and puzzle-like elements to be solved; one module uses words that may be homophones of other similar words ("sees" to "seas") or be verbal tics ("uhhh" or "uh huh") that could easily be confused during communication between the Defuser and the Experts. Another module has multiple stages that require the Experts to keep track of past actions as they work through each stage. There's also a module that depends on the state of the bomb such as how many strikes it presently has, or other data on the bomb, like the serial number.  

You can find the bomb defusal manual here: [link](https://ema1ih.github.io/ArduinoKTANE-Manual/)

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
- LiquidCrystal_I2C - [link](https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c?fbclid=IwAR016eH4yHLd4HKqA-OcUghdO19ukQlUcGXE2mY0AUaA8aWecJZJvaQrt5E)
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

* Thanks to [bremme](https://github.com/bremme) and [wayoda](https://github.com/wayoda) for creating the open-source libraries we used
* Definetly check the game that inspired us, official website [here](https://keeptalkinggame.com/)
