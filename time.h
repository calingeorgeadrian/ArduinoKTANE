// The Timer

#define PIN_CLK 14
#define PIN_DIO 15

SevenSegmentExtended timer(PIN_CLK, PIN_DIO);
unsigned long seconds = 0;
int mins = TIMER_MINUTES, sec = TIMER_SECONDS + 1;

void timeSetup() {
  timer.begin();            // initializes the display
  timer.setBacklight(100);  // set the brightness to 100%
};

// function that displays the time on the clock
void displayTime() 
{
  if (seconds < millis())
  {
    seconds += 1000;
    sec--;
    if (sec == -1)
    {
      mins--;
      if (mins == -1)  bombExploded(); // if the time hits zero, the bomb will go off
      else sec = 59;
    }

    if (mins == -1) timer.printTime(0, 0, true);
    else timer.printTime(mins, sec, true);
  }
}

void timeLoop() {

  // defused : time left
  // exploded from time : 00:00
  // exploded from strikes : exploded

  if (exploded && explodedFromStrikes)
    timer.print("    BOMB EXPLODED    ");
  else if (!defused && !(exploded && !explodedFromStrikes))
    displayTime();

}
