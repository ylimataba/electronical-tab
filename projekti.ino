#include <SD.h>
#include <SPI.h>
#include <PN532_SPI.h>
#include "PN532.h"
#include <NfcAdapter.h>
#include <LiquidCrystal.h>

Sd2Card card;
SdVolume volume;
SdFile root;
File myFile;

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int COL = 0;
int ROW = 0;

char* STRING = (char*)malloc(sizeof(char)*32);
int STRINGSIZE = 0;
int BUTTON[12][3] = {{1, 770, 845},      // button 1
                     {2, 440, 470},      // button 2
                     {3, 101, 145},      // button 3
                     {4, 690, 750},      // button 4
                     {5, 280, 320},      // button 5
                     {6, 61, 100},       // button 6
                     {7, 650, 689},      // button 7
                     {8, 191, 220},      // button 8
                     {9, 10, 60},        // button 9
                     {10, 550, 630},     // enter
                     {11, 146, 190},     // button 0
                     {12, 900, 1023}};   // cancel
int ANALOGPIN = A5;       // analog pin to read the buttons
int LABEL = 0;            // for reporting the button label
int COUNTER = 0;          // how many times we have seen new value
long TIME = 0;            // the last time the output pin was sampled
int DEBOUNCE_COUNT = 30; // number of millis/samples to consider before declaring a debounced input
int CURRENT_STATE = 0;    // the debounced input value
int BUTTONVAL;
boolean dot = false;
long TIMER = 0;

void setup(void)
{
  Serial.begin(9600);

  pinMode(10,OUTPUT);  // NFC-module
  pinMode(A1,OUTPUT);  // SD-module
  pinMode(7,OUTPUT);   // LCD display
  
  // setup for LCD display
  digitalWrite(7,HIGH);
  analogWrite(8,90);   // Contrast
  lcd.begin(16,4);
}

void loop(void)
{
  lcd.clear();
  setCursor(0,0);
  printString("Hello!");
  setCursor(0,1);
  printString("Please identify yourself with   a tag");
  
  startNFC();
  char* tag = getTag();    
  
  if(tag[0] != '\0')
  {
    lcd.clear();
    setCursor(0,0);
    printString(tag);
    setCursor(0,2);
    printString("Tag accepted!");
    //startSD();
    //testWrite(tag);
    delay(1000);
    
    lcd.clear();
    setCursor(0,0);
    printString("Insert amout:");
    setCursor(0,1);
    while(LABEL != 10)
    {
      keypad();
    }
    LABEL = 0;
    STRING[STRINGSIZE-1] = '\0';
    STRINGSIZE = 0;
    lcd.clear();
    setCursor(0,3);
    printString(STRING);
    
    setCursor(0,0);
    printString("Pleasure to     make business   with you!");
    delay(5000);
  }
}

void startSD()
{
  digitalWrite(10,HIGH);
  digitalWrite(A1,LOW);
  SD.begin(A1);
}

void testWrite(char* tag)
{
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile)
  {
    myFile.println(tag);
    lcd.clear();
    setCursor(0,0);
    printString("Insert amout:");
    setCursor(0,1);
    while(LABEL != 10)
    {
      keypad();
    }
    myFile.println(STRING);
    myFile.close();
    lcd.clear();
    setCursor(0,0);
    printString("Pleasure to     make business   with you!");
  }
  else
    printString("Sorry I fucked up!");
}

