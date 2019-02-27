// The Button Module


#define LCD_BUTTON_CONTRAST 40

#define PIN_THE_BUTTON_LED_GREEN 19 //green led buton

#define BTN_PIN 26 // buton mare

#define BUZZER_PIN 6
#define BTN_RED_PIN 7
#define BTN_GREEN_PIN 8
#define BTN_BLUE_PIN 9
#define STRIP_RED_PIN 10
#define STRIP_GREEN_PIN 11
#define STRIP_BLUE_PIN 12
 
#define lcdButton_V0_PIN 13
LiquidCrystal lcdButton(29, 27, 41, 43, 45, 47);

int btnState = LOW;
int lastBtnState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelayButton = 50;
int moduleFinished = 0;
int btnColor;
int stripColor;
int btnWordGen;
//int loops = 19920; //60 secunde a cate 166 loop-uri fiecare
//int secondsButton = loops/166;



void setColor (int redPin, int redValue, int greenPin, int greenValue, int bluePin, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void buttonModuleDefusedPrint()
{ 
   setColor(BTN_RED_PIN,0,BTN_GREEN_PIN,0,BTN_BLUE_PIN,0);
   setColor(STRIP_RED_PIN,0,STRIP_GREEN_PIN,0,STRIP_BLUE_PIN,0);
   buttonModuleDefused = true;
   if(whoModuleDefused && simonModuleDefused && memoryModuleDefused && buttonModuleDefused) 
    {
      victoryBuzzer();
      defused = true;
    }
}

void buttonModuleBoom()
{ 
  setColor(BTN_RED_PIN,0,BTN_GREEN_PIN,0,BTN_BLUE_PIN,0);
  setColor(STRIP_RED_PIN,0,STRIP_GREEN_PIN,0,STRIP_BLUE_PIN,0);
  lcdButton.clear();
  lcdButton.setCursor(6,0);
  lcdButton.print("BOMB");
  lcdButton.setCursor(4,1);
  lcdButton.print("EXPLODED"); 
}


bool checkClock(int value){
  //seconds = loops/166;
  int timer = sec;
  while(timer >0)
  {
    if(timer%10 == value)
    return 1;
    timer = timer/10;
  }

  timer = mins;
  while(timer >0)
  {
    if(timer%10 == value)
    return 1;
    timer = timer/10;
  }
  
  return 0;
}

void printWord() {
  switch(btnWordGen){
    case 1: { //HOLD
      lcdButton.setCursor(5,0);
      lcdButton.print("HOLD");
    }
    break;
    case 2: { //DETONATE
      lcdButton.setCursor(4,0);
      lcdButton.print("DETONATE");
    }
    break;
    case 3: { //ABORT
      lcdButton.setCursor(5,0);
      lcdButton.print("ABORT");
    }
    break;
  }
}

void printModuleDefused() {
  buttonModuleDefusedPrint();
  lcdButton.clear();
  lcdButton.setCursor(1,0);
  lcdButton.print("MODULE DEFUSED");
  lcdButton.setCursor(0,1);
  lcdButton.print("Serial: ");
  lcdButton.print(serialCode);
}

void buttonSetup()
{
  //Serial.begin(9600);
  pinMode(BTN_RED_PIN, OUTPUT);
  pinMode(BTN_GREEN_PIN, OUTPUT);
  pinMode(BTN_BLUE_PIN, OUTPUT);
  pinMode(STRIP_RED_PIN, OUTPUT);
  pinMode(STRIP_GREEN_PIN, OUTPUT);
  pinMode(STRIP_BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_PIN,INPUT);
  pinMode(PIN_THE_BUTTON_LED_GREEN,OUTPUT);
  pinMode(lcdButton_V0_PIN, OUTPUT);

  analogWrite(lcdButton_V0_PIN, LCD_BUTTON_CONTRAST);
  lcdButton.begin(16,2);

  //generez un seed pentru a alege doua numere random cu ajutorul acestuia
  randomSeed(analogRead(0));

  //generam culorile pentru buton si pentru strip
  btnColor = random(1,5);
  stripColor = random(1,5);
  btnWordGen = random(1,4);
  switch(btnColor){
    case 1: {
      setColor(BTN_RED_PIN,0,BTN_GREEN_PIN,0,BTN_BLUE_PIN,255);
    }
    break;
    case 2: {
      setColor(BTN_RED_PIN,255,BTN_GREEN_PIN,0,BTN_BLUE_PIN,0);
    }
    break;
    case 3: {
      setColor(BTN_RED_PIN,0,BTN_GREEN_PIN,255,BTN_BLUE_PIN,0);
    }
    break;
    case 4: {
      setColor(BTN_RED_PIN,255,BTN_GREEN_PIN,255,BTN_BLUE_PIN,255);
    }
    break;
  }
  switch(stripColor){
    case 1: {
      setColor(STRIP_RED_PIN,0,STRIP_GREEN_PIN,0,STRIP_BLUE_PIN,255);
    }
    break;
    case 2: {
      setColor(STRIP_RED_PIN,255,STRIP_GREEN_PIN,0,STRIP_BLUE_PIN,0);
    }
    break;
    case 3: {
      setColor(STRIP_RED_PIN,0,STRIP_GREEN_PIN,255,STRIP_BLUE_PIN,0);
    }
    break;
    case 4: {
      setColor(STRIP_RED_PIN,255,STRIP_GREEN_PIN,255,STRIP_BLUE_PIN,255);
    }
    break;
  }

  printWord();
  lcdButton.setCursor(0,1);
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
    
/*  loops--;
  seconds = loops/166;
  Serial.println(seconds);
  */
  
  /*if(seconds>=100 && !moduleFinished)
  {
    lcdButton.setCursor(5,1);
    lcdButton.print(seconds);
  }
  else if(seconds>=10 && !moduleFinished)
  {
    lcdButton.setCursor(5,1);
    lcdButton.print(seconds);
    lcdButton.print(" ");
  }
  else if(seconds>0 && !moduleFinished)
  {
    lcdButton.setCursor(5,1);
    lcdButton.print(seconds);
    lcdButton.print("  ");
  }
  else if(!moduleFinished)
  {
    lcdButton.setCursor(2,1);
    lcdButton.print("TIME IS OVER");
  }
  */
  int reading = digitalRead(BTN_PIN);
  
  if(reading != lastBtnState)
  lastDebounceTime = millis();
  
  switch(btnColor){
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
        switch(stripColor){
          case 1: {// strip-ul are culoarea albastra
            //release when timer has a 4 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(4)){
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
          case 2: {// strip-ul are culoarea rosie
            //release when timer has a 3 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(3)){
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
          case 3: {// strip-ul are culoarea verde
            //release when timer has a 5 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(5)){
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
          case 4: {// strip-ul are culoarea alba
            //release when timer has a 1 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(1)){
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
    case 2:{// butonul are culoarea rosie
      if(btnWordGen == 1 && seconds > 0 && !moduleFinished){ //scrie Hold pe buton
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
        switch(stripColor){
          case 1: {// strip-ul are culoarea albastra
            //release when timer has a 4 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(4)){
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
          case 2: {// strip-ul are culoarea rosie
            //release when timer has a 3 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(3)){
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
          case 3: {// strip-ul are culoarea verde
            //release when timer has a 5 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(5)){
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
          case 4: {// strip-ul are culoarea alba
            //release when timer has a 1 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(1)){
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
    case 3:{// butonul are culoarea verde
      if(btnWordGen == 2 && seconds > 0 && !moduleFinished){ //scrie Detonate pe buton
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
        switch(stripColor){
          case 1: {// strip-ul are culoarea albastra
            //release when timer has a 4 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(4)){
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
          case 2: {// strip-ul are culoarea rosie
            //release when timer has a 3 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(3)){
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
          case 3: {// strip-ul are culoarea verde
            //release when timer has a 5 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(5)){
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
          case 4: {// strip-ul are culoarea alba
            //release when timer has a 1 in any position
            if(millis() - lastDebounceTime > debounceDelayButton)
            {
                if(reading != btnState)
                {
                  btnState = reading;
                  if(btnState == LOW && checkClock(1)){
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
    case 4:{// butonul are culoarea alba
        if(seconds > 0 && !moduleFinished)
          switch(stripColor){
            case 1: {// strip-ul are culoarea albastra
              //release when timer has a 4 in any position
              if(millis() - lastDebounceTime > debounceDelayButton)
              {
                  if(reading != btnState)
                  {
                    btnState = reading;
                    if(btnState == LOW && checkClock(4)){
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
            case 2: {// strip-ul are culoarea rosie
              //release when timer has a 3 in any position
              if(millis() - lastDebounceTime > debounceDelayButton)
              {
                  if(reading != btnState)
                  {
                    btnState = reading;
                    if(btnState == LOW && checkClock(3)){
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
            case 3: {// strip-ul are culoarea verde
              //release when timer has a 5 in any position
              if(millis() - lastDebounceTime > debounceDelayButton)
              {
                  if(reading != btnState)
                  {
                    btnState = reading;
                    if(btnState == LOW && checkClock(5)){
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
            case 4: {// strip-ul are culoarea alba
              //release when timer has a 1 in any position
              if(millis() - lastDebounceTime > debounceDelayButton)
              {
                  if(reading != btnState)
                  {
                    btnState = reading;
                    if(btnState == LOW && checkClock(1)){
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
