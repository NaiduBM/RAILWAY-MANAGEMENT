#include <LiquidCrystal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SoftwareSerial.h>

const int rs = 13, en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial ZigSerial(6, 7);/* (Rx, Tx) */ 



int IN1=14;
int IN2=15;

int IN3=16;
int IN4=17;


#define trigPin 4
#define echoPin 5


long duration;
int distance;

int Left_IR=2;
int Right_IR=3;
int Fire=18;
int Relay=19;

int T=1;
char ch;
void setup(void) 
{
  Serial.begin(9600);
  ZigSerial.begin(9600);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(Relay, OUTPUT);

      pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  
  pinMode(Relay, OUTPUT);
  
  pinMode(Left_IR,INPUT);
  pinMode(Right_IR,INPUT);
  pinMode(Fire,INPUT);

  

  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
   digitalWrite(Relay,LOW);
  
   lcd.begin(16,2);                      // Initialize the LCD
  lcd.clear();   
  lcd.print("Railway Management  ");
  lcd.setCursor(0,1);
  lcd.print("   System  "); 
  delay(1000);
  Serial.println("Railway Management System..");
  delay(1000);
}
void loop() 
{
  RECEIVE_DATA();
 // CRACK_CHECK();
 // FORWARD();
  
}
void DITACH()
{
  digitalWrite(Relay,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(4000);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(Relay,LOW);
}
void FIRE_CHECK()
{
  if(digitalRead(Fire)==HIGH)
  {
    lcd.clear();
    lcd.print("Fire Detected");
    Serial.println("$Fire Detected#");
    
    delay(1000);
    STOP();
    DITACH();
    delay(1000);
    
  }
  
}
void CRACK_CHECK()
{
  
  if(digitalRead(Left_IR)==HIGH)
  {
    lcd.clear();
    lcd.print("Left Side Crack");
    lcd.setCursor(0,1);
    lcd.print("  Detected");
      Serial.println("$Left Side Crack Detected#");
      STOP();

      delay(5000); 
      while(digitalRead(Left_IR)==HIGH);
  }
  if(digitalRead(Right_IR)==HIGH)
  {
    lcd.clear();
    lcd.print("Right Side Crack");
    lcd.setCursor(0,1);
    lcd.print("  Detected");
    Serial.println("$Right Side Crack Detected#");
    STOP();
   delay(5000);
 while(digitalRead(Right_IR)==HIGH);
  }
  
 // delay(5000);
  //FORWARD();
}

void CRACK_CHECK_IP()
{
  if(ZigSerial.available()>0)
  {
    ch=ZigSerial.read();
    Serial.println("Received Data:"+String(ch));
    if(ch=='X')
    {
      lcd.clear();
      lcd.print("Left Side Crack");
      lcd.setCursor(0,1);
      lcd.print("  Detected");
        Serial.println("$Left Side Crack Detected#");
        STOP();
  
        delay(5000); 
    }
    if(ch=='Y')
    {
      lcd.clear();
      lcd.print("Right Side Crack");
      lcd.setCursor(0,1);
      lcd.print("  Detected");
      Serial.println("$Right Side Crack Detected#");
      STOP();
     delay(5000);
   
    }
   // delay(5000);
    //FORWARD();
  }

}
void FORWARD()
{
  lcd.clear();
  lcd.print("Moving..");
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   delay(1000);
   while(1)
   {
     CRACK_CHECK();
    // CRACK_CHECK_IP();
     FIRE_CHECK();
      Ultra_Check();
     RECEIVE_DATA();
   }
   
}
void Ultra_Check()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance = duration * 0.034 / 2;

  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
//  Serial.print("Distance = ");
//  Serial.print(distance);
//  Serial.println(" cm");
  lcd.clear();
  lcd.print("Distance= ");
  lcd.print(distance);
  lcd.print("cm");

  delay(1000);
  if(distance<50)
  {
   // Serial.println("$Vehicle Detected Distance of 50cm#");
    lcd.clear();
    lcd.print("Object Detected ");
    lcd.setCursor(0,1);
    lcd.print("Distance of 50cm..");
    STOP();
    delay(2000);
    
  }
} 
void RECEIVE_DATA()
{
  if(ZigSerial.available()>0)
  {
    ch=ZigSerial.read();
    Serial.println("Received Data:"+String(ch));
    if(ch=='A')
    {
      lcd.clear();
      lcd.print("Platform 1");
      lcd.setCursor(0,1);
      lcd.print("Available");
      Serial.println("Platform 1 Available");
      delay(1000);
      FORWARD();
      
    }
    if(ch=='B')
    {
      lcd.clear();
      lcd.print("Platform 2");
      lcd.setCursor(0,1);
      lcd.print("Available");
      Serial.println("Platform 2 Available");
      delay(1000);
      FORWARD();
    }
    if(ch=='C')
    {
      lcd.clear();
      lcd.print("Platform 3");
      lcd.setCursor(0,1);
      lcd.print("Available");
      Serial.println("Platform 3 Available");
      delay(1000);
      FORWARD();
    }
    if(ch=='Z')
    {
      lcd.clear();
      lcd.print("All Platforms");
      lcd.setCursor(0,1);
      lcd.print("Are Busy...");
      Serial.println("All Platforms Are Busy...");
      delay(1000);
      
    }
  }

}

void STOP()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);

}
