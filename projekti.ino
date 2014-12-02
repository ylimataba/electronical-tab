#include <LiquidCrystal.h>
#include <SD.h>
#include <SPI.h>
#include <PN532_SPI.h>
#include "PN532.h"

// For NFC-module to work:
PN532_SPI pn532spi(SPI, 10);
PN532 nfc(pn532spi);

// For SD-module to work:
Sd2Card card;
SdVolume volume;
SdFile root;

// For LDC-display to work:
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int col = 0;
int row = 0;

// For keypad to work:
//2-dimensional array for asigning the buttons and there high and low values
int Button[12][3] = {{1, 770, 845},      // button 1
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
int analogpin = A5;       // analog pin to read the buttons
int label = 0;            // for reporting the button label
int counter = 0;          // how many times we have seen new value
long time = 0;            // the last time the output pin was sampled
int debounce_count = 150; // number of millis/samples to consider before declaring a debounced input
int current_state = 0;    // the debounced input value
int ButtonVal;

  
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
  
  // NFC listens MASTER
  digitalWrite(10,LOW);
  digitalWrite(A1,HIGH);
  
  // setup for NFC-module
  nfc.begin();
  nfc.setPassiveActivationRetries(0xFF); // Set the max number of retry attempts to read from a card
  nfc.SAMConfig();                       // configure board to read RFID tags
  
  // SD listens MASTER
  digitalWrite(10,HIGH);
  digitalWrite(A1,LOW);
  
  // setup for SD-module
  SD.begin(A1);
}

void loop(void)
{
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;  // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  lcd.setCursor(0,0);
  lcd.print("Hello!");
  lcd.setCursor(0,1);
  lcd.print("Read card!");  
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  
  if (success) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("UID Value: ");
    lcd.setCursor(0,1);
    for (uint8_t i=0; i < uidLength; i++) 
    {
      lcd.print(uid[i]); 
    }
    // Wait 1 second before continuing
    delay(1000);
    lcd.clear();
  }
}
