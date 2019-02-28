#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LedControl.h>
#include <SevenSegmentExtended.h>

#define TIMER_MINUTES 7
#define TIMER_SECONDS 0

#define PIN_STRIKE_1 50 // strike 1
#define PIN_STRIKE_2 48 // strike 2
#define PIN_STRIKE_3 46  // strike 3

bool defused = false, exploded = false;
bool memoryModuleDefused = false, buttonModuleDefused = false, simonModuleDefused = false, whoModuleDefused = false;
bool explodedFromStrikes = false;
int nrStrikes = 0;

char serialCode[10];

void bombExploded();
void addStrike();

// function that generates the serial number for Simon Says
void generateSerialCode() 
{
  char alphanumeric[50] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  for ( int i = 0; i < 7; i++)
    serialCode[i] = alphanumeric[random(0, 35)];
}

#include "time.h"
#include "buzzer.h"
#include "who.h"
#include "memory.h"
#include "button.h"
#include "simon.h"

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(PIN_STRIKE_1, OUTPUT);
  pinMode(PIN_STRIKE_2, OUTPUT);
  pinMode(PIN_STRIKE_3, OUTPUT);

  digitalWrite(PIN_STRIKE_1, LOW);
  digitalWrite(PIN_STRIKE_2, LOW);
  digitalWrite(PIN_STRIKE_3, LOW);

  generateSerialCode();

  timeSetup();
  whoSetup();
  memorySetup();
  buttonSetup();
  defusedSimonSetup();
}

void bombExploded()
{
  exploded = true;
  whoModuleBoom();
  memoryModuleBoom();
  buttonModuleBoom();
  boomBuzzer();
}

// function that adds a strike
void addStrike() 
{
  nrStrikes++;
  strikeBuzzer();

  if (nrStrikes == 1) digitalWrite(PIN_STRIKE_1, HIGH);
  else if (nrStrikes == 2) digitalWrite(PIN_STRIKE_2, HIGH);
  else if (nrStrikes == 3) // the maximum number of strikes is reached
  {
    digitalWrite(PIN_STRIKE_3, HIGH);
    explodedFromStrikes = true;
    bombExploded();
  }
}

void loop()
{

  timeLoop();

  if (!defused && !exploded)
  {
    whoLoop();
    memoryLoop();
    buttonLoop();
  }


}
