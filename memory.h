// Memory Module

#define PIN_MEMORY_BUTTON_1 A6
#define PIN_MEMORY_BUTTON_2 A7
#define PIN_MEMORY_BUTTON_3 A8
#define PIN_MEMORY_BUTTON_4 A9

#define PIN_MEMORY_LED_1 31
#define PIN_MEMORY_LED_2 33
#define PIN_MEMORY_LED_3 35
#define PIN_MEMORY_LED_4 37
#define PIN_MEMORY_LED_GREEN 39

LedControl lc = LedControl(18, 16, 17, 1); //DIN, CLK, LOAD, No. DRIVER

int previousButton, button; //the previos and the current button
int rightPoz; //the answer to the current stage
int val[6], pos[6]; // the right values and positions of every stage
int stageNumber = 1;
int digits[5]; // the values of the current stage

bool printAnswer = true;

void turnOffLeds()
{
  digitalWrite(PIN_MEMORY_LED_1, LOW);
  digitalWrite(PIN_MEMORY_LED_2, LOW);
  digitalWrite(PIN_MEMORY_LED_3, LOW);
  digitalWrite(PIN_MEMORY_LED_4, LOW);
  digitalWrite(PIN_MEMORY_LED_GREEN, LOW);
}

// function that generate a random digit from 1 to 4
int randomNumber() 
{
  return (random(20, 100)) / 20;
}

// generates the digits of the current stage
void generateNumbers() 
{
  digits[0] = randomNumber();
  digits[1] = randomNumber();
  digits[2] = randomNumber();
  digits[3] = randomNumber();

  // if the digits repeat:
  while (digits[2] == digits[1]) digits[2] = randomNumber();
  while (digits[3] == digits[1] || digits[3] == digits[2]) digits[3] = randomNumber();

  digits[4] = 10 - digits[3] - digits[2] - digits[1]; // the last digit is the last number from 1-4
}

// display the current digits
void displayNumbers() 
{
  lc.setDigit(0, 5, digits[0], false);
  lc.setDigit(0, 0, digits[1], false);
  lc.setDigit(0, 1, digits[2], false);
  lc.setDigit(0, 2, digits[3], false);
  lc.setDigit(0, 3, digits[4], false);
}

// function that returns the postion of a digit
int positionOf(int nr)
{
  for (int i = 1; i < 5; i++)
    if (digits[i] == nr) return i;
}

// function that calculates the answer for the current stage
void stage(int nr) 
{
  if (nr == 1)
  {
    if (digits[0] == 1) rightPoz = 2;
    else if (digits[0] == 2) rightPoz = 2;
    else if (digits[0] == 3) rightPoz = 3;
    else if (digits[0] == 4) rightPoz = 4;
  }
  else if (nr == 2)
  {
    if (digits[0] == 1) rightPoz = positionOf(4);
    else if (digits[0] == 2) rightPoz = pos[1];
    else if (digits[0] == 3) rightPoz = 1;
    else if (digits[0] == 4) rightPoz = pos[1];
  }
  else if (nr == 3)
  {
    if (digits[0] == 1) rightPoz = positionOf(val[2]);
    else if (digits[0] == 2) rightPoz = positionOf(val[1]);
    else if (digits[0] == 3) rightPoz = 3;
    else if (digits[0] == 4) rightPoz = positionOf(4);
  }
  else if (nr == 4)
  {
    if (digits[0] == 1) rightPoz = pos[1];
    else if (digits[0] == 2) rightPoz = 1;
    else if (digits[0] == 3) rightPoz = pos[2];
    else if (digits[0] == 4) rightPoz = pos[2];
  }
  else if (nr == 5)
  {
    if (digits[0] == 1) rightPoz = positionOf(val[1]);
    else if (digits[0] == 2) rightPoz = positionOf(val[2]);
    else if (digits[0] == 3) rightPoz = positionOf(val[4]); //3
    else if (digits[0] == 4) rightPoz = positionOf(val[3]); //4
  }

  pos[nr] = rightPoz;
  val[nr] = digits[rightPoz];
}

void memorySetup()
{
  lc.shutdown(0, false); // turn off power saving, enables display

  lc.setIntensity(0, 4); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen

  randomSeed(analogRead(0));

  pinMode(PIN_MEMORY_LED_1, OUTPUT);
  pinMode(PIN_MEMORY_LED_2, OUTPUT);
  pinMode(PIN_MEMORY_LED_3, OUTPUT);
  pinMode(PIN_MEMORY_LED_4, OUTPUT);
  pinMode(PIN_MEMORY_LED_GREEN, OUTPUT);

  turnOffLeds();

  // stage 1
  generateNumbers();
  displayNumbers();
  stageNumber = 1;
}

void changeStage() // the next stage
{
  if (stageNumber == 1) digitalWrite(PIN_MEMORY_LED_1, HIGH);
  else if (stageNumber == 2) digitalWrite(PIN_MEMORY_LED_2, HIGH);
  else if (stageNumber == 3) digitalWrite(PIN_MEMORY_LED_3, HIGH);
  else if (stageNumber == 4) digitalWrite(PIN_MEMORY_LED_4, HIGH);

  generateNumbers();
  stageNumber++;
  displayNumbers();
  printAnswer = true;
}

// function that resets the module
void memoryReset() 
{
  addStrike();
  if (nrStrikes < 3)
  {
    stageNumber = 0;
    changeStage();
    turnOffLeds();
  }
}

// function that returns the pressed button
int memoryPressedButton() 
{
  previousButton = button;
  if (digitalRead(PIN_MEMORY_BUTTON_1) == 1) return 1;
  if (digitalRead(PIN_MEMORY_BUTTON_2) == 1) return 2;
  if (digitalRead(PIN_MEMORY_BUTTON_3) == 1) return 3;
  if (digitalRead(PIN_MEMORY_BUTTON_4) == 1) return 4;
  return 0;
}

// function that checks if a button is pressed
void memoryCheckButton() 
{
  button = memoryPressedButton();
  stage(stageNumber);
  if (printAnswer) // print the answer to the current stage
  {
    Serial.print("Memory Stage ");
    Serial.print(stageNumber);
    Serial.print(" : ");
    Serial.println(rightPoz);
    printAnswer = false;
  }

  if (button != 0 && previousButton != button)
  {
    if (button == rightPoz) // if the right button was pressed
    {
      if (stageNumber == 5) // if it's the last stage, the module is defused
      {
        turnOffLeds();
        digitalWrite(PIN_MEMORY_LED_GREEN, HIGH);
        lc.clearDisplay(0);
        memoryModuleDefused = true;
        defusedModuleBuzzer();
        stageNumber++;

        if (whoModuleDefused && simonModuleDefused && memoryModuleDefused && buttonModuleDefused)
        {
          victoryBuzzer();
          defused = true;
        }

      }
      else
        changeStage(); // else go to the next stage

    }
    else
      memoryReset(); // else reset the module
  }
}

// function that turns off everything but the green led
void memoryModuleBoom() 
{
  digitalWrite(PIN_MEMORY_LED_1, LOW);
  digitalWrite(PIN_MEMORY_LED_2, LOW);
  digitalWrite(PIN_MEMORY_LED_3, LOW);
  digitalWrite(PIN_MEMORY_LED_4, LOW);
  lc.clearDisplay(0);
}

void memoryLoop()
{
  if (!memoryModuleDefused)
    memoryCheckButton();

}
