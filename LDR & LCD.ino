#include <LiquidCrystal.h>
#include <Servo.h>
//Define the LDR sensor pins
#define LDR1 A0
#define LDR2 A1
//Define the error value. You can change it as you like
#define error 10
//Starting point of the servo motor
int Spoint =  90;
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//Create an object for the servo motor
Servo servo;

void setup() {
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
  
  lcd.print("*AVISHKAR-2022*");  // Print a text to the LCD.
//Include servo motor PWM pin
  servo.attach(8);
//Set the starting point of the servo
  servo.write(Spoint);
  delay(1000);

}

void loop() {
//Get the LDR sensor value
  int ldr1 = analogRead(LDR1);
//Get the LDR sensor value
  int ldr2 = analogRead(LDR2);

//Get the difference of these values
  int value1 = abs(ldr1 - ldr2);
  int value2 = abs(ldr2 - ldr1);

//Check these values using a IF condition
  if ((value1 <= error) || (value2 <= error)) {

  } else {
    if (ldr1 > ldr2) {
      Spoint = --Spoint;
    }
    if (ldr1 < ldr2) {
      Spoint = ++Spoint;
    }
  }

//Write values on the servo motor
  servo.write(Spoint);
  delay(80);
  lcd.setCursor(0, 1);
  
}