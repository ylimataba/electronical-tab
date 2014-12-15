#include <SD.h>
#include <SPI.h>
#include <PN532_SPI.h>
#include "PN532.h"
#include <NfcAdapter.h>
#include <LiquidCrystal.h>

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int COL = 0;
int ROW = 0;

char* STRING = (char*)malloc(sizeof(char)*9);
int STRINGSIZE = 0;

char* tag = (char*)malloc(sizeof(char)*15);

int BUTTON[12][3] = {{1, 740, 770},      // button 1
                     {2, 120, 140},      // button 2
                     {3, 440, 460},      // button 3
                     {4, 20, 40},      // button 4
                     {5, 145, 165},      // button 5
                     {6, 500, 530},       // button 6
                     {7, 55, 75},      // button 7
                     {8, 220, 250},      // button 8
                     {9, 530, 560},        // button 9
                     {10, 330, 360},     // button 0
                     {11, 80, 110},     // enter
                     {12, 600, 640}};  // cancel
int COUNTER = 0;          // how many times we have seen new value
int DEBOUNCE_COUNT = 30;  // number of millis/samples to consider before declaring a debounced input
int CURRENT_STATE = 0;    // the debounced input value


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
  lcd.clear();
  setCursor(0,0);
}

void loop(void)
{ 
  if(COL == 0 && ROW == 0)
  {
    printString("Hello!");
    setCursor(0,1);
    printString("Please identify yourself with   a tag!");
  }

  tag = getTag();
  
  if (tag[0] != '\0')
  {
    lcd.clear();
    setCursor(0,0);
    printString("1: ADD");
    setCursor(0,1);
    printString("2: REDUCE");
    setCursor(0,2);
    printString("3: SHOW TAB INFO");
    setCursor(0,3);
    printString("4: QUIT");
    int label = 0;
    long tiima = 0;
    while(1)
    {
      if(millis() != tiima)
      {
        label = keypad(0,4);
        if(label == 1)
        {
          askinput(tag);
          break;
        }
        if(label == 2)
        {
          lcd.clear();
          setCursor(0,0);
          printString("TODO");
          delay(1000);
          break;
        }
        if(label == 3)
        {
          lcd.clear();
          setCursor(0,0);
          printString("TODO");
          delay(1000);
          break;
        }
        if(label == 4)
        {
          break;
        }
      }
      tiima = millis();
    }
    lcd.clear();
    setCursor(0,0);
  }
}
