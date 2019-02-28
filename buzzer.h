// The sounds for the buzzer

#define BUZZER 24

void victoryBuzzer() // the sound of the buzzer when the team wins
{
  delay(700);
  tone(BUZZER, 1000);
  delay(250);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 600);
  delay(250);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1000);
  delay(1000);
  noTone(BUZZER);
}

void boomBuzzer() // the sound of the buzzer when the team loses
{
  delay(700);
  for (int i = 0; i < 4; i++) {
    tone(BUZZER, 800);
    delay(300);
    noTone(BUZZER);
    delay(100);

    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);

    tone(BUZZER, 300);
    delay(1000);
    noTone(BUZZER);
  }
}

void defusedModuleBuzzer() // the sound of the buzzer when a module is defused
{
  tone(BUZZER, 500);
  delay(300);
  noTone(BUZZER);
  delay(100);

  tone(BUZZER, 1000);
  delay(300);
  noTone(BUZZER);
}

void strikeBuzzer() // the sound of the buzzer when the team makes a mistake
{
  tone(BUZZER, 800);
  delay(300);
  noTone(BUZZER);
  delay(100);

  tone(BUZZER, 300);
  delay(300);
  noTone(BUZZER);

}
