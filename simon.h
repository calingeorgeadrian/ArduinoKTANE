// Simon Says Module

#define RED_LED_PIN 42 // simon 1
#define GREEN_LED_PIN 40 // simon 2
#define YELLOW_LED_PIN 38 // simon 3
#define BLUE_LED_PIN 36 // simon 4
#define PIN_SIMON_LED_GREEN 44 //simon green led

#define RED_BTN_PIN A1 // 34 // simon 1
#define GREEN_BTN_PIN A2 //32 // simon 2
#define YELLOW_BTN_PIN A3 //30 // simon 3
#define BLUE_BTN_PIN A4 //28 // simon 4

unsigned long lastDebounceTimeRed = 0;
unsigned long lastDebounceTimeGreen = 0;
unsigned long lastDebounceTimeYellow = 0;
unsigned long lastDebounceTimeBlue = 0;
unsigned long debounceDelay = 50;

unsigned long currentMillisRed = 0;
unsigned long currentMillisGreen = 0;
unsigned long currentMillisYellow = 0;
unsigned long currentMillisBlue = 0;

int redLedState = 0;
int greenLedState = 0;
int yellowLedState = 0;
int blueLedState = 0;

int ledPins[4] = {42, 40, 38, 36};
int ledStates[4] = {0, 0, 0, 0};

int ledsNumber = 1;
int blinkingTime = 500;
unsigned long previousMillis = 0;
int ledSequence[4];

int answersWithVowel[3][4] = {{4, 3, 2, 1},
  {3, 4, 1, 2},
  {2, 3, 4, 1}
};

int answersWithoutVowel[3][4] = {{4, 2, 1, 3},
  {1, 3, 2, 4},
  {3, 4, 1, 2}
};


int currentLed=0, animationDelay = 5000;
unsigned long animationMillis = 0, beforeAnimationMillis;
int buttonsPressed = 0; 


int beforeAnimationDelay = 1000;


void simonModuleBoom()
{ 
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
}

void simonModuleDefusedPrint()
{ 
   defusedModuleBuzzer();
   simonModuleDefused = true;
   if(whoModuleDefused && simonModuleDefused && memoryModuleDefused && buttonModuleDefused) 
    {
      victoryBuzzer();
      defused = true;
    }
}


bool checkForVowel() {
  for (int i = 0; i < 7; i++)
    if (serialCode[i] == 'A' || serialCode[i] == 'E' || serialCode[i] == 'I' || serialCode[i] == 'O' || serialCode[i] == 'U')
      return 1;
  return 0;
}

void pressButton(int ledNr, int btnPin, int led, unsigned long &debounceTime, unsigned long &currentMillis, int &ledState) {
  int reading = digitalRead(btnPin);

  if (reading == HIGH)
  {
    debounceTime = millis();
    ledState = 1;
        
    
  }

  if (millis() - debounceTime > debounceDelay)
  {
    if (ledState == 1)
    {
      //nr++;
      
    currentLed = ledsNumber;
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    buttonsPressed++;
    if(checkForVowel()){
      Serial.println(answersWithVowel[nrStrikes][ledSequence[buttonsPressed-1]-1]);
      if(answersWithVowel[nrStrikes][ledSequence[buttonsPressed-1]-1] == ledNr){
        Serial.println("Corect");
        if(buttonsPressed == ledsNumber)
          {
            buttonsPressed = 0;
            ledsNumber++;
            beforeAnimationMillis = millis();
            currentLed = -1;
            if(ledsNumber > 4)
              {
                Serial.println("GATA");
                simonModuleDefusedPrint();
                digitalWrite(PIN_SIMON_LED_GREEN, HIGH);
                currentLed = ledsNumber+2;
              }
          }
      }
        else {
            addStrike();
            if(nrStrikes < 3)
            { 
              currentLed = -1;
              beforeAnimationMillis = millis(); 
              buttonsPressed = 0;
              Serial.println("Gresit");
              Serial.print(nrStrikes);
              Serial.println(buttonsPressed);
            }
        }
    }
    else {
      Serial.println(answersWithoutVowel[nrStrikes][ledSequence[buttonsPressed-1]-1]);
      if(answersWithoutVowel[nrStrikes][ledSequence[buttonsPressed-1]-1] == ledNr){
        Serial.println("Corect");
        if(buttonsPressed == ledsNumber)
          {
            buttonsPressed = 0;
            ledsNumber++;
            currentLed = -1;
            beforeAnimationMillis = millis();
            if(ledsNumber > 4)
              {
                Serial.println("GATA");
                simonModuleDefusedPrint();
                digitalWrite(PIN_SIMON_LED_GREEN, HIGH);
                currentLed = ledsNumber+2;
              }
          }
      }
        else {
          addStrike();
          if( nrStrikes < 3)
          { 
            currentLed = -1;
            beforeAnimationMillis = millis(); 
            buttonsPressed = 0;
            Serial.println("Gresit");
            Serial.print(nrStrikes);
            Serial.println(buttonsPressed);
          }
        }
    }
        
      digitalWrite(led, HIGH);
      currentMillis = millis();
      ledState = 2;
    }

    if (millis() - currentMillis >= blinkingTime && ledState == 2) {
      digitalWrite(led, LOW);
      ledState = 0;
    }
  }

}

void generateLedSequence() {
  /*for(int i=0; i<100; i++)
    int x = random(1,5);
  */
  for (int i = 0; i < 4; i++)
  {
    int x = random(1, 5);
    ledSequence[i] = x;
  }

  for(int i=0; i<4; i++)
    Serial.print(ledSequence[i]);
    Serial.println();
}

 


void blinkLed(int led,int &ledState) {
  unsigned long currentMillis = millis();
    
  if (currentMillis - previousMillis >= blinkingTime) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
      currentLed++;
    }
    
    digitalWrite(led, ledState);
  }
}

void ledAnimation() {

  if(currentLed == -1 && millis() - beforeAnimationMillis > beforeAnimationDelay) currentLed=0;
  
  if(currentLed == 0) 
          buttonsPressed = 0;
          
  if(currentLed < ledsNumber)
    blinkLed(ledPins[ledSequence[currentLed]-1], ledStates[ledSequence[currentLed]-1]);
  
  else
  {
    if(currentLed == ledsNumber) 
    {
      animationMillis = millis();
      currentLed++;
    }
    if(currentLed == ledsNumber+1 && millis() - animationMillis > animationDelay) currentLed=0;
  }
      
}

void simonSetup() {
  
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(PIN_SIMON_LED_GREEN, OUTPUT);
  pinMode(RED_BTN_PIN, INPUT);
  pinMode(GREEN_BTN_PIN, INPUT);
  pinMode(YELLOW_BTN_PIN, INPUT);
  pinMode(BLUE_BTN_PIN, INPUT);

  generateLedSequence();
  

  Serial.print("Vocala: ");
    Serial.print(checkForVowel());
    Serial.println();
}

void simonLoop() {
  
  if(!simonModuleDefused)
  {
      ledAnimation(); 
      pressButton(1, RED_BTN_PIN, RED_LED_PIN, lastDebounceTimeRed, currentMillisRed, redLedState);
      pressButton(2, GREEN_BTN_PIN, GREEN_LED_PIN, lastDebounceTimeGreen, currentMillisGreen, greenLedState);
      pressButton(3, YELLOW_BTN_PIN, YELLOW_LED_PIN, lastDebounceTimeYellow, currentMillisYellow, yellowLedState);
      pressButton(4, BLUE_BTN_PIN, BLUE_LED_PIN, lastDebounceTimeBlue, currentMillisBlue, blueLedState);  
    
  }
  
}
 
 
 
