


#include <LiquidCrystal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SoftwareSerial.h>

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial ZigSerial(6, 7);/* (Rx, Tx) */ 

int IR1=2;
int IR2=3;
int IR3=4;

int RED=8;
int GREEN=9;

void setup(void) 
{
  Serial.begin(9600); 
  ZigSerial.begin(9600);

  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
 

  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  
  lcd.begin(16,2);                      // Initialize the LCD
  lcd.clear();   
  lcd.print(" Platform  ");
  lcd.setCursor(0,1);
  lcd.print("  Module  "); 
  delay(1000);

}
void loop() 
{
  CHECK_PLATFORM();
  
}
void CHECK_PLATFORM()
{
  lcd.clear();
      lcd.print("Platforms");
      lcd.setCursor(0,1);
      lcd.print("Checking...");
  if((digitalRead(IR1)==LOW)&&(digitalRead(IR2)==LOW)&&(digitalRead(IR3)==LOW))
  {
      lcd.clear();
      lcd.print("All Platforms");
      lcd.setCursor(0,1);
      lcd.print("Are Busy...");
      Serial.println("All Platforms Are Busy...");
      ZigSerial.begin(9600);
      ZigSerial.println('Z');
      digitalWrite(RED,HIGH);
      delay(1000);  
  }
  if((digitalRead(IR1)==HIGH)&&(digitalRead(IR2)==LOW)&&(digitalRead(IR3)==LOW))
  {
      lcd.clear();
      lcd.print("Platform 1");
      lcd.setCursor(0,1);
      lcd.print("Available");
      Serial.println("Platform 1 Available");
      ZigSerial.begin(9600);
      ZigSerial.println('A');
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,HIGH);
      delay(1000);  
  }
   if((digitalRead(IR1)==LOW)&&(digitalRead(IR2)==HIGH)&&(digitalRead(IR3)==LOW))
  {
      lcd.clear();
      lcd.print("Platform 2");
      lcd.setCursor(0,1);
      lcd.print("Available");
      Serial.println("Platform 2 Available");
      ZigSerial.begin(9600);
      ZigSerial.println('B');
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,HIGH);
      delay(1000);  
  }
   if((digitalRead(IR1)==LOW)&&(digitalRead(IR2)==LOW)&&(digitalRead(IR3)==HIGH))
  {
      lcd.clear();
      lcd.print("Platform 3");
      lcd.setCursor(0,1);
      lcd.print("Available");
      Serial.println("Platform 3 Available");
      ZigSerial.begin(9600);
      ZigSerial.println('C');
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,HIGH);
      delay(1000);  
  }
  
}
