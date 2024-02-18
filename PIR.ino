const int pirPin = 2; // PIR sensor connected to digital pin 2
const int alarmPin = 4;
const int buzzer = 11;
const int light = A0;
  // Motor A
int motorA1 = 5; 
int motorA2 = 6;

// Motor B
int motorB1 = 7;
int motorB2 = 8; // Connect Motor B's Direction control to digital pin 6

//Correction factor
float correctionFactor = 1; 

#include <stdbool.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <TimeLib.h>
#include "pitches.h"

rgb_lcd lcd;

int melody[] = {

  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {

  4, 8, 8, 4, 4, 4, 4, 4
};

int colorR = 255;
int colorG = 1;
int colorB = 1;
bool motionDetectedFlag = false; // Flag to indicate motion detection

void setup() {
  pinMode(pirPin, INPUT); // Set PIR pin as input
  pinMode(light, INPUT);
  Serial.begin(9600); // Initialize serial communication
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB); 

    pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
}

void loop() {
  if (!motionDetectedFlag) { // Check if motion hasn't been detected yet
    int motionDetected = digitalRead(pirPin); // Read PIR sensor value
    int timer_input;
  
    if (motionDetected == HIGH) {
      Serial.println("Motion detected!\n");

      lcd.setCursor(0, 1);
      lcd.print("Motion detected");
      motionDetectedFlag = true; // Set the flag to indicate motion is detected

      colorR = 0; 
      colorG = 255; 
      colorB = 0;

      lcd.setRGB(colorR, colorG, colorB);

    } else {
      Serial.println("No motion detected.\n");

      lcd.print("No motion detected");
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.clear();

      colorR = 255; 
      colorG = 1; 
      colorB = 1;

      lcd.setRGB(colorR, colorG, colorB);
    }
  } else {

    int alarmTime = Serial.read();

    if(alarmTime == 'W'){
      moveForward(200);
      stopMotion();
    }
    if(alarmTime == 'A'){
      turnLeft(150);
      stopMotion();
    }
    if(alarmTime == 'D'){
      turnRight(150);
      stopMotion();
    }
    if(alarmTime == 'S'){
      moveBackward(200);
      stopMotion();
    }


      lcd.setCursor(0,0);
      lcd.print("Ready to use !");
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.clear();

      colorR = 1; 
      colorG = 255; 
      colorB = 1;

      time_t t = now();

      lcd.setRGB(colorR, colorG, colorB);
      lcd.setCursor(0,2);
      lcd.print(hour(t));
      lcd.print(":");
      lcd.print(minute(t));
      lcd.print(":");
      lcd.print(second(t));
      // Serial.print(t);
    
      int lightValue = analogRead(light);
      Serial.print(lightValue);
      Serial.print("\n");

      while (analogRead(light) > 650){
        // int lightValue = analogRead(light);
        lcd.setCursor(0,0);
        lcd.print("You should open");
        lcd.setCursor(0,1);
        lcd.print("the light!");
        colorR = 255; 
        colorG = 1; 
        colorB = 1;

        lcd.setRGB(colorR, colorG, colorB);
        delay(2000);
        lcd.clear();
      }
      while ( analogRead(light) < 150){
        // int lightValue = analogRead(light);
        lcd.setCursor(0,0);
        lcd.print("You should close the light");
        lcd.print("You should open");
        lcd.setCursor(0,1);
        lcd.print("the light!");
        colorR = 255; 
        colorG = 1; 
        colorB = 1;

        lcd.setRGB(colorR, colorG, colorB);
        delay(2000);
        lcd.clear();
      }

    if (alarmTime == 'A'){
    unsigned long startTime = now();
    unsigned long endTime = startTime + 30;
    while (now() < endTime) {
      lcd.setCursor(0, 1);
      lcd.print("Timer: ");
      lcd.print(endTime - now());
      lcd.print(" seconds");
      delay(1000); 
    }
    lcd.clear();
    lcd.print("Turn off alarm");
    while (true){
      int stopAlarm = digitalRead(alarmPin);
      if (stopAlarm == HIGH){
        break;
      } else {
        for (int thisNote = 0; thisNote < 8; thisNote++) {
          int noteDuration = 1000 / noteDurations[thisNote];

          tone(11, melody[thisNote], noteDuration);

          int pauseBetweenNotes = noteDuration * 1.30;

          delay(pauseBetweenNotes);

          noTone(11);
          
      }
      delay(1000);
    }
    }
    }

    else if (alarmTime == 'B'){
    unsigned long startTime = now();
    unsigned long endTime = startTime + 10;
    while (now() < endTime) {
      lcd.setCursor(0, 1);
      lcd.print("Timer: ");
      lcd.print(endTime - now());
      lcd.print(" seconds");
      delay(1000); 
    }
    lcd.clear();
    lcd.print("Turn off alarm");
    while (true){
      int stopAlarm = digitalRead(alarmPin);
      if (stopAlarm == HIGH){
        break;
      } else {
        for (int thisNote = 0; thisNote < 8; thisNote++) {
          int noteDuration = 1000 / noteDurations[thisNote];

          tone(11, melody[thisNote], noteDuration);

          int pauseBetweenNotes = noteDuration * 1.30;

          delay(pauseBetweenNotes);

          noTone(11);
          
      }
      delay(1000);
    }

    }
  }



  }}


void moveForward(int a) {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  delay(a);
}

void moveBackward(int a) {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  delay(a);
}

void turnLeft(int a) {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  delay(a);
}

void turnRight(int a) {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  delay(a);
}

void stopMotion() {
  digitalWrite(motorA1, LOW); 
  digitalWrite(motorA2, LOW); 
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}




