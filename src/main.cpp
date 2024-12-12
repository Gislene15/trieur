#include <Arduino.h>
#include "rgb_lcd.h"
#define RED 1

rgb_lcd lcd;
int BP1 = 2, BP2 = 12, BP0 = 0;
int val_BP1, val_BP2, val_BP0;

int pot = 33;
int lecture_pot;

// PWM
int pwm1 = 27;
int frequence = 25000;
int canal0 = 0;
int resolution = 11;
int non_horraire = 26;

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
  pinMode(non_horraire, OUTPUT);

  // configuration de la PWM
  ledcSetup(canal0, frequence, resolution);
  // liison des canux des PWM avec les broches de l'ESP32
  ledcAttachPin(pwm1, canal0);

  Serial.begin(9600);
}

void loop()
{
  val_BP0 = digitalRead(BP0);
  val_BP1 = digitalRead(BP1);
  val_BP2 = digitalRead(BP2);

  // non_horraire = digitalRead(non_horraire);

  /*if (val_BP0==LOW)
  {
  digitalWrite(non_horraire,LOW);
  ledcWrite(canal0, 511 );
  lcd.setCursor(0, 0);
  lcd.printf(" sens horaire ");
  }
  else if(val_BP1==LOW)
  {
  digitalWrite(non_horraire,HIGH);
  ledcWrite(canal0, 511 );
  lcd.setCursor(0, 1);
  lcd.printf("sens non horaire");
  }
  else{
  lcd.setCursor(0, 1);
  lcd.printf("stop");
  }
  */

  digitalWrite(non_horraire, LOW);
  ledcWrite(canal0, 511);

  lcd.setCursor(0, 0);
  // lcd.printf("VAL BP2%D\n",val_BP2);
  lcd.printf("BP0%d BP1%d BP2%d", val_BP0, val_BP1, val_BP2);

  lecture_pot = analogRead(pot);

  lcd.setCursor(0, 1);
  lcd.printf("pot=%d", lecture_pot);
}
