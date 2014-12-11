void askInput(char* tag)
{
  lcd.clear();
  setCursor(0,0);
  printString("Insert amout:");
  setCursor(0,1);
  STRINGSIZE = 0;
  while(LABEL != 10)
  {
    keypad();
    if(STRINGSIZE > 6)
    {
      lcd.clear();
      setCursor(0,0);
      printString("That is enough! You are not a   millionaire!");
      delay(2000);
      break;
    }
  }
  LABEL = 0;
  STRING[STRINGSIZE-1] = '\0';
  STRINGSIZE = 0;

  if(confirm())
  {
    lcd.clear();
    setCursor(0,0);
    printString("APPROVED!");
    setCursor(0,1);
    printString("Adding ");
    printString(STRING);
    setCursor(0,2);
    printString("to your tab...");
    delay(2000);
    startSD();
    File myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile)
    {
      Serial.print("Writing to test.txt...");
      myFile.println(tag);
      myFile.println(STRING);
      // close the file:
      myFile.close();
      Serial.println("done."); 
      setCursor(5,3);
      printString("DONE");
      delay(1000);
      lcd.clear();
      setCursor(0,0);
      printString("Pleasure to     make business   with you!");
      delay(3000);
    }
    else
    {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
      lcd.clear();
      setCursor(0,0);
      printString("Something went  wrong! Please   try again");
    }
  }
  else
  {
    lcd.clear();
    setCursor(0,0);
    printString("NOT APPROVED!");
    delay(1000);
    askInput(tag);
  }
}

boolean confirm()
{
  lcd.clear();
  setCursor(0,0);
  printString("Is ");
  printString(STRING);
  setCursor(0,1);
  printString("correct amount?");
  setCursor(0,3);
  printString("[YES]       [NO]");
  while(LABEL != 10)
  {
    keypad2();
    if (LABEL == 12)
    {
      LABEL = 0;
      return false;
    }
  }
  LABEL = 0;
  return true;
}
