void askinput(char* tag)
{
  lcd.clear();
  setCursor(0, 3);
  printString("ENTER        DEL");
  setCursor(0, 0);
  printString("Insert amount incents: ");
  STRINGSIZE = 0;
  int label = 0;
  long tiima = 0;
  while (1)
  {
    if(millis() != tiima)
    {
      label = keypad(0, 12);
      if (label == 11)
        break;
      if (STRINGSIZE > 7)
      {
        lcd.clear();
        setCursor(0, 0);
        printString("That is enough! You are not a   millionaire!");
        delay(2000);
        break;
      }
    }
    tiima = millis();
  }
  STRING[STRINGSIZE] = '\0';
  STRINGSIZE = 0;
  int button = confirm();
  if (button == 1)
  {
    lcd.clear();
    setCursor(0, 0);
    printString("APPROVED!");
    setCursor(0, 1);
    printString("Adding ");
    printStringE(STRING);
    setCursor(0, 2);
    printString("to your tab...");
    delay(2000);
    writeToSD(tag);
  }
  else if (button == 0)
  {
    lcd.clear();
    setCursor(0, 0);
    printString("NOT APPROVED!");
    delay(1000);
    askinput(tag);
  }
  else if (button == 100)
  {
    lcd.clear();
    setCursor(0, 0);
    printString("Quitting...");
    delay(1000);
    lcd.clear();
    setCursor(0, 0);
    loop();
  }
}

int confirm()
{
  lcd.clear();
  setCursor(0, 0);
  printString("Is ");
  printStringE(STRING); // print in euros
  printString(" Euro");
  setCursor(0, 1);
  printString("correct amount?");
  setCursor(0, 3);
  printString("YES   EXIT   NO");
  delay(2000);

  int label = 0;
  long tiima = 0;
  while (1)
  {
    if(millis()!=tiima)
    {
      label = keypad(9, 12);
      if (label == 10)
        return 100;
      if (label == 11)
        return 1;
      if (label == 12)
        return 0;
    }
    tiima = millis();
  }
}
