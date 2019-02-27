// The Button Module
/* 
I know there is a lot of repetitive code inside this but when I tried to
refactor it, everything stopped working so I decided to keep it like this
*/

#define LCD_BUTTON_CONTRAST 40
#define PIN_THE_BUTTON_LED_GREEN 19
#define BTN_PIN 26
#define BUZZER_PIN 6
#define LEFT_LED_RED_PIN 7
#define LEFT_LED_GREEN_PIN 8
#define LEFT_LED_BLUE_PIN 9
#define RIGHT_LED_RED_PIN 10
#define RIGHT_LED_GREEN_PIN 11
#define RIGHT_LED_BLUE_PIN 12
#define V0_PIN 13

LiquidCrystal lcdButton(29, 27, 41, 43, 45, 47);

int btnState = LOW;
int lastBtnState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelayButton = 50;
int moduleFinished = 0;
int leftLedColor;
int rightLedColor;
int btnWordGen;

void setColor (int redPin, int redValue, int greenPin, int greenValue, int bluePin, int blueValue) 
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void buttonModuleDefusedPrint()
{ 
   setColor(LEFT_LED_RED_PIN, 0, LEFT_LED_GREEN_PIN, 0, LEFT_LED_BLUE_PIN, 0);
   setColor(RIGHT_LED_RED_PIN, 0, RIGHT_LED_GREEN_PIN, 0, RIGHT_LED_BLUE_PIN, 0);
   buttonModuleDefused = true;
   if(whoModuleDefused && simonModuleDefused && memoryModuleDefused && buttonModuleDefused) 
    {
      victoryBuzzer();
      defused = true;
    }
}

void buttonModuleBoom()
{ 
  setColor(LEFT_LED_RED_PIN, 0, LEFT_LED_GREEN_PIN, 0, LEFT_LED_BLUE_PIN, 0);
  setColor(RIGHT_LED_RED_PIN, 0, RIGHT_LED_GREEN_PIN, 0, RIGHT_LED_BLUE_PIN, 0);
  lcdButton.clear();
  lcdButton.setCursor(6, 0);
  lcdButton.print("BOMB");
  lcdButton.setCursor(4, 1);
  lcdButton.print("EXPLODED"); 
}

bool checkClock(int value)
{
  int timer = sec;
  while(timer >0)
  {
    if(timer % 10 == value)
    return 1;
    timer = timer / 10;
  }

  timer = mins;
  while(timer >0)
  {
    if(timer % 10 == value)
    return 1;
    timer = timer / 10;
  }
  
  return 0;
}

void printWord() {
  switch(btnWordGen)
  {
    case 1: 
    { //HOLD
      lcdButton.setCursor(5, 0);
      lcdButton.print("HOLD");
    }
    break;
    case 2: 
    { //DETONATE
      lcdButton.setCursor(4, 0);
      lcdButton.print("DETONATE");
    }
    break;
    case 3: 
    { //ABORT
      lcdButton.setCursor(5, 0);
      lcdButton.print("ABORT");
    }
    break;
  }
}

void printModuleDefused() 
{
  buttonModuleDefusedPrint();
  lcdButton.clear();
  lcdButton.setCursor(1, 0);
  lcdButton.print("MODULE DEFUSED");
  lcdButton.setCursor(0, 1);
  lcdButton.print("Serial: ");
  lcdButton.print(serialCode);
}

void buttonSetup()
{
  pinMode(LEFT_LED_RED_PIN, OUTPUT);
  pinMode(LEFT_LED_GREEN_PIN, OUTPUT);
  pinMode(LEFT_LED_BLUE_PIN, OUTPUT);
  pinMode(RIGHT_LED_RED_PIN, OUTPUT);
  pinMode(RIGHT_LED_GREEN_PIN, OUTPUT);
  pinMode(RIGHT_LED_BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  pinMode(PIN_THE_BUTTON_LED_GREEN, OUTPUT);
  pinMode(V0_PIN, OUTPUT);

  analogWrite(V0_PIN, LCD_BUTTON_CONTRAST);
  lcdButton.begin(16, 2);

  //generez un seed pentru a alege doua numere random cu ajutorul acestuia
  randomSeed(analogRead(0));

  //generam culorile pentru buton si pentru strip
  leftLedColor = random(1, 5);
  rightLedColor = random(1, 5);
  btnWordGen = random(1, 4);
 
  switch(leftLedColor)
  {
    case 1: {
      setColor(LEFT_LED_RED_PIN, 0, LEFT_LED_GREEN_PIN, 0, LEFT_LED_BLUE_PIN, 255);
    }
    break;
    case 2: {
      setColor(LEFT_LED_RED_PIN, 255, LEFT_LED_GREEN_PIN, 0, LEFT_LED_BLUE_PIN, 0);
    }
    break;
    case 3: {
      setColor(LEFT_LED_RED_PIN, 0, LEFT_LED_GREEN_PIN, 255,LEFT_LED_BLUE_PIN, 0);
    }
    break;
    case 4: {
      setColor(LEFT_LED_RED_PIN, 255, LEFT_LED_GREEN_PIN, 255, LEFT_LED_BLUE_PIN, 255);
    }
    break;
  }
  switch(rightLedColor){
    case 1: {
      setColor(STRIP_RED_PIN, 0, STRIP_GREEN_PIN, 0, STRIP_BLUE_PIN, 255);
    }
    break;
    case 2: {
      setColor(STRIP_RED_PIN, 255, STRIP_GREEN_PIN, 0, STRIP_BLUE_PIN, 0);
    }
    break;
    case 3: {
      setColor(STRIP_RED_PIN, 0, STRIP_GREEN_PIN, 255, STRIP_BLUE_PIN, 0);
    }
    break;
    case 4: {
      setColor(STRIP_RED_PIN, 255, STRIP_GREEN_PIN, 255, STRIP_BLUE_PIN, 255);
    }
    break;
  }

  printWord();
  lcdButton.setCursor(0, 1);
  lcdButton.print("Serial: ");
  lcdButton.print(serialCode);
  
  Serial.println("Culoarea butonului: ");
  Serial.println(btnColor);
  Serial.println("Culoarea liniei: ");
  Serial.println(stripColor);
  Serial.println("Valoarea cuv de pe buton: ");
  Serial.println(btnWordGen);
}


void buttonLoop()
{ 
  if(!buttonModuleDefused) 
  {
  int reading = digitalRead(BTN_PIN);
  
  if(reading != lastBtnState)
  lastDebounceTime = millis();
  
  switch(leftLedColor)
  {
    case 1: {// butonul are culoarea albastra
      if(btnWordGen == 3 && seconds > 0 && !moduleFinished){ //scrie Abort pe buton
        // press and imediately release
        if(millis() - lastDebounceTime > debounceDelayButton)
          {
            if(reading != btnState)
            {
              btnState = reading;
              if(btnState == HIGH)
              {
                moduleFinished = 1;
                digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                Serial.println("VALIDAT: Buton albastru + Abort");
                defusedModuleBuzzer();
                printModuleDefused();
              }
            }
          }
      }
      else if (seconds > 0 && !moduleFinished) //hold button
        switch(rightLedColor)
        {
          case 1: 
          {// strip-ul are culoarea albastra
            //release when timer has a 4 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(4))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton albastru + Strip albastru");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                  else if(btnState == LOW && !checkClock(4))
                  {
                    addStrike();
                  }
                }
            }
          }
          break;
          case 2: 
          {// strip-ul are culoarea rosie
            //release when timer has a 3 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(3))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton albastru + Strip rosu");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(3))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
          case 3: 
          {// strip-ul are culoarea verde
            //release when timer has a 5 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(5))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton albastru + Strip verde");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(5))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
          case 4: 
          {// strip-ul are culoarea alba
            //release when timer has a 1 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(1))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton albastru + Strip alb");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(1))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
        }
    }
    break;
    case 2:
    {// butonul are culoarea rosie
      if(btnWordGen == 1 && seconds > 0 && !moduleFinished)
      { //scrie Hold pe buton
        // press and imediately release
        if(millis() - lastDebounceTime > debounceDelayButton)
          {
            if(reading != btnState)
            {
              btnState = reading;
              if(btnState == HIGH)
              {
                moduleFinished = 1;
                digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                Serial.println("VALIDAT: Buton rosu + Hold");
                defusedModuleBuzzer();
                printModuleDefused();
              }
            }
          }
      }
      else if(seconds > 0 && !moduleFinished) //hold button
        switch(rightLedColor)
        {
          case 1: 
          {// strip-ul are culoarea albastra
            //release when timer has a 4 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(4))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton rosu + Strip albastru");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(4))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
          case 2: 
          {// strip-ul are culoarea rosie
            //release when timer has a 3 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(3))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton rosu + Strip rosu");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(3))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
          case 3: 
          {// strip-ul are culoarea verde
            //release when timer has a 5 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(5))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton rosu + Strip verde");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(5))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
          case 4: 
          {// strip-ul are culoarea alba
            //release when timer has a 1 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(1))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton rosu + Strip alb");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(1))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
        }
    }
    break;
    case 3:
    {// butonul are culoarea verde
      if(btnWordGen == 2 && seconds > 0 && !moduleFinished)
      { //scrie Detonate pe buton
        // press and imediately release
        if(millis() - lastDebounceTime > debounceDelayButton)
          {
            if(reading != btnState)
            {
              btnState = reading;
              if(btnState == HIGH)
              {
                moduleFinished = 1;
                digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                Serial.println("VALIDAT: Buton verde + Detonate");
                defusedModuleBuzzer();
                printModuleDefused();
              }
            }
          }
      }
      else if(seconds > 0 && !moduleFinished) //hold button
        switch(rightLedColor)
        {
          case 1: 
          {// strip-ul are culoarea albastra
            //release when timer has a 4 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(4))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton verde + Strip albastru");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(4))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
          case 2: 
          {// strip-ul are culoarea rosie
            //release when timer has a 3 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(3))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton verde + Strip rosu");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(3))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
          case 3: 
          {// strip-ul are culoarea verde
            //release when timer has a 5 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(5))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton verde + Strip verde");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(5))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
          case 4: 
          {// strip-ul are culoarea alba
            //release when timer has a 1 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(1))
                  {
                      moduleFinished = 1;
                      digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                      Serial.println("VALIDAT: Buton verde + Strip alb");
                      defusedModuleBuzzer();
                      printModuleDefused();
                  }
                    else if(btnState == LOW && !checkClock(1))
                    {
                      addStrike();
                    }
                }
            }
          }
          break;
        }
    }
    break;
    case 4:
    {// butonul are culoarea alba
        if(seconds > 0 && !moduleFinished)
          switch(rightLedColor)
          {
            case 1: 
            {// strip-ul are culoarea albastra
              //release when timer has a 4 in any position
              if(millis() - lastDebounceTime > debounceDelayButton)
              {
                  if(reading != btnState)
                  {
                    btnState = reading;
                    if(btnState == LOW && checkClock(4))
                    {
                        moduleFinished = 1;
                        digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                        Serial.println("VALIDAT: Buton alb + Strip albastru");
                        defusedModuleBuzzer();
                        printModuleDefused();
                    }
                    else if(btnState == LOW && !checkClock(4))
                    {
                      addStrike();
                    }
                  }
              }
            }
            break;
            case 2: 
            {// strip-ul are culoarea rosie
              //release when timer has a 3 in any position
              if(millis() - lastDebounceTime > debounceDelayButton)
              {
                  if(reading != btnState)
                  {
                    btnState = reading;
                    if(btnState == LOW && checkClock(3))
                    {
                        moduleFinished = 1;
                        digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                        Serial.println("VALIDAT: Buton alb + Strip rosu");
                        defusedModuleBuzzer();
                        printModuleDefused();
                    }
                    else if(btnState == LOW && !checkClock(3))
                    {
                      addStrike();
                    }
                  }
              }
            }
            break;
            case 3: 
            {// strip-ul are culoarea verde
              //release when timer has a 5 in any position
              if(millis() - lastDebounceTime > debounceDelayButton)
              {
                  if(reading != btnState)
                  {
                    btnState = reading;
                    if(btnState == LOW && checkClock(5))
                    {
                        moduleFinished = 1;
                        digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                        Serial.println("VALIDAT: Buton alb + Strip verde");
                        defusedModuleBuzzer();
                        printModuleDefused();
                    }
                    else if(btnState == LOW && !checkClock(5))
                    {
                      addStrike();
                    }
                  }
              }
            }
            break;
            case 4: 
            {// strip-ul are culoarea alba
              //release when timer has a 1 in any position
              if(millis() - lastDebounceTime > debounceDelayButton)
              {
                  if(reading != btnState)
                  {
                    btnState = reading;
                    if(btnState == LOW && checkClock(1))
                    {
                        moduleFinished = 1;
                        digitalWrite(PIN_THE_BUTTON_LED_GREEN, HIGH);
                        Serial.println("VALIDAT: Buton alb + Strip alb");
                        defusedModuleBuzzer();
                        printModuleDefused();
                    }
                    else if(btnState == LOW && !checkClock(1))
                    {
                      addStrike();
                    }
                  }
              }
            }
            break;
          }
    }
    break;
  }
  
  lastBtnState = reading;
  }
}
