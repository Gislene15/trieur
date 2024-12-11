#include <Arduino.h>
#include "rgb_lcd.h"
#define RED 1

rgb_lcd lcd;
int BP1 = 2, BP2 = 12, BP0 = 0;
int val_BP1, val_BP2, val_BP0;
int pot = 33;
int lecture_pot;

//PWM
int pwm1 = 27;
int frequence = 500;
int canal0 = 0;
int canal1 = 2;
int resolution = 10;

void setup()
{
  // Initialise la liaison avec le terminal
  Serial.begin(115200);

  // Initialise l'écran LCD
  Wire1.setPins(15, 5);
  lcd.begin(16, 2, LCD_5x8DOTS, Wire1);
  // lcd.printf("Gigi la GOAT");
  // changer couleur sur le LCD
  lcd.setColor(2);
// configuration des boutons
  pinMode(BP0, INPUT_PULLUP);
  pinMode(BP1, INPUT_PULLUP);
  pinMode(BP2, INPUT_PULLUP);


  Serial.begin(9600);
}

void loop()
{
  val_BP0 = digitalRead(BP0);
  val_BP1 = digitalRead(BP1);
  val_BP2 = digitalRead(BP2);
  lcd.setCursor(0, 0);
  // lcd.printf("VAL BP2%D\n",val_BP2);
  lcd.printf("BP0%d BP1%d BP2%d",val_BP0,val_BP1, val_BP2);

  lecture_pot=analogRead(pot);
  lcd.setCursor(0, 1);
  lcd.printf("pot=%d",lecture_pot);

}
