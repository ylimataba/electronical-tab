void startNFC()
{
  digitalWrite(10,LOW);
  digitalWrite(A1,HIGH);
  nfc.begin();
  nfc.setPassiveActivationRetries(0xFF); // Set the max number of retry attempts to read from a card
  nfc.SAMConfig();                       // configure board to read RFID tags
}

char* getTag()
{
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;  // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  if(success)
  {
    char* tag = (char*)malloc(sizeof(char) * uidLength);
    for (uint8_t i=0; i < uidLength; i++) 
    {
      tag[i] = uid[i];
    }
    tag[uidLength] = '\0';
    return tag;
  }
  return '\0';
}
