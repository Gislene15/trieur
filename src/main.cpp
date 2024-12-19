#include <Arduino.h>
#include <SPI.h>
#include "rgb_lcd.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t r, g, b, c, colorTemp, lux;
rgb_lcd lcd;
int BP1 = 2, BP2 = 12, BP0 = 0;
int val_BP1, val_BP2, val_BP0;

// pot init
int pot = 33;
int lecture_pot;

//  PWM
int pwm1 = 27;
int frequence = 25000;
int canal0 = 0;
int resolution = 11;
int non_horraire = 26;

int servo = 13;
int canal2 = 2;
int frequence1= 50;
int resolution1 =10;
void setup()
{
  Serial.begin(115200);
  Serial.println("Color View Test!");

  // Initialise l'écran LCD
  Wire1.setPins(15, 5);
  lcd.begin(16, 2, LCD_5x8DOTS, Wire1);
   lcd.printf("Gigi la GOAT");
  // changer couleur sur le LCD
  lcd.setColor(2);

  // configuration des boutons
  pinMode(BP0, INPUT_PULLUP);
  pinMode(BP1, INPUT_PULLUP);
  pinMode(BP2, INPUT_PULLUP);                     

  // configuration en sortie de la pin sgn qui permet de la mettre en non horaire
  pinMode(non_horraire, OUTPUT);
  pinMode(pwm1, OUTPUT);
  // configuration de la PWM
  ledcSetup(canal0, frequence, resolution);
  // liaison des canux des PWM avec les broches de l'ESP32
  ledcAttachPin(pwm1, canal0);

  pinMode(servo, OUTPUT);
  // configuration du servo
  ledcSetup(canal2, frequence1, resolution);
  // liaison des canux des servo avec les broches de l'ESP32
  ledcAttachPin(servo, canal2);

  if (tcs.begin())
  {
    Serial.println("Found sensor");
  }
  else
  {
    Serial.println("No TCS34725 found ... check your connections");
    while (1)
      ; // halt!
  }
}

void loop()
{
  // boutons
  val_BP0 = digitalRead(BP0);
  val_BP1 = digitalRead(BP1);
  val_BP2 = digitalRead(BP2);
  // pot
  lecture_pot = analogRead(pot);
  lcd.setCursor(0, 1);
  lcd.printf("pot=%d", lecture_pot);

  /*lcd.setCursor(0, 0);
  // lcd.printf("VAL BP2%D\n",val_BP2);
  lcd.printf("BP0%d BP1%d BP2%d", val_BP0, val_BP1, val_BP2);


  // pwm
  if (lecture_pot > 100)
  {
    lecture_pot = 100;
    }*/
/*if (val_BP0 == LOW)
{
  digitalWrite(non_horraire, LOW);
  ledcWrite(canal0, lecture_pot);
  lcd.setCursor(0, 0);
  lcd.printf(" sens horaire ");
}
else if (val_BP1 == LOW)
{
  digitalWrite(non_horraire, HIGH);
  ledcWrite(canal0, lecture_pot);
  lcd.setCursor(0, 0);
  lcd.printf("sens non horaire");
}
else if (val_BP2 == LOW)
{
  ledcWrite(canal0, 0);
  lcd.setCursor(0, 1);
  lcd.printf("stop");
}*/

// couleur
/*tcs.getRawData(&r, &g, &b, &c);
lux = tcs.calculateLux(r, g, b);
// colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);

Serial.print("Color Temp: ");
Serial.print(colorTemp, DEC);
Serial.print(" K - ");
Serial.print("Lux: ");
Serial.print(lux, DEC);
Serial.print(" - ");
Serial.print("R: ");
Serial.print(r, DEC);
Serial.print(" ");
Serial.print("G: ");
Serial.print(g, DEC);
Serial.print(" ");
Serial.print("B: ");
Serial.print(b, DEC);
Serial.print(" ");
Serial.print("C: ");
Serial.print(c, DEC);
Serial.print("  \n");
delay(100);*/

// servo
if (val_BP0 == LOW)
{
  ledcWrite(canal2, 0);
}
/*else if( val_BP1==LOW)
 {
  ledcWrite(canal2,0);
 }
 else if( val_BP2==LOW)
 {
  ledcWrite(canal2,0);
 }
 */

}
