void keypad()
{
  TIME = millis();
  // If we have gone on to the next millisecond
  if (millis() != TIME)
  {
    // check analog pin for the BUTTON value and save it to BUTTONVAL
    BUTTONVAL = analogRead(ANALOGPIN);
    
    if(BUTTONVAL == CURRENT_STATE && COUNTER >0)
    { 
      COUNTER--;
    }
    if(BUTTONVAL != CURRENT_STATE)
    {
      COUNTER++;
    }
    // If BUTTONVAL has shown the same value for long enough let's switch it
    if (COUNTER >= DEBOUNCE_COUNT)
    {
      COUNTER = 0;
      CURRENT_STATE = BUTTONVAL;
      //Checks which button or button combo has been pressed
      if (BUTTONVAL > 0)
      {
        ButtonCheck();
      }
    }
    //Serial.println(BUTTONVAL);
  }
}

void ButtonCheck()
{
  // loop for scanning the button array.
  for(int i = 0; i <= 12; i++)
  {
    // checks the BUTTONVAL against the high and low vales in the array
    if(BUTTONVAL >= BUTTON[i][1] && BUTTONVAL <= BUTTON[i][2])
    {
      // stores the BUTTON number to a variable
      LABEL = BUTTON[i][0];
      if (TIME > TIMER + 500 || LABEL != 1)
        dot = false;
      if (dot)
        LABEL = 13;
      Action();
      break; // poistuu for silmukasta luettuaan näppäimen!
    }
  }
}

void Action()
{
  Serial.print("label: ");
  Serial.println(LABEL);
  if(LABEL == 1)
  {
    TIMER = TIME;
    Serial.println("1");
    printString("1");
    STRING[STRINGSIZE] = '1';
    dot = true;
  }
  if(LABEL == 2)
  {
    Serial.println("2");
    printString("2");
    STRING[STRINGSIZE] = '2';
  }
  if(LABEL == 3)
  { 
    Serial.println("3");
    printString("3");
    STRING[STRINGSIZE] = '3';
  }
  if(LABEL == 4)
  {
    Serial.println("4");
    printString("4");
    STRING[STRINGSIZE] ='4';
  }
  if(LABEL == 5)
  {
    Serial.println("5");
    printString("5");
    STRING[STRINGSIZE] = '5';
  }
  if(LABEL == 6)
  {
    Serial.println("6");
    printString("6");
    STRING[STRINGSIZE] = '6';
  }
  if(LABEL == 7)
  {
    Serial.println("7");
    printString("7");
    STRING[STRINGSIZE] = '7';
  }
  if(LABEL == 8)
  {
    Serial.println("8");
    printString("8");
    STRING[STRINGSIZE] = '8';
  }
  if(LABEL == 9)
  {
    Serial.println("9");
    printString("9");
    STRING[STRINGSIZE] = '9';
  }
  if(LABEL == 10)
  {
    Serial.println("ENTER");
    setCursor(0,3);
    printString("ENTER");
    delay(200);
  }
  if(LABEL == 11)
  {
    Serial.println("0");
    printString("0");
    STRING[STRINGSIZE] = '0';
  }    
  if(LABEL == 12)
  {
    Serial.println("CANCEL");
    lcd.setCursor(5,3);
    lcd.print("CANCEL");
    delay(200);
    lcd.setCursor(5,3);
    lcd.print("      ");
    deleteChar();
    if (ROW==0)
      setCursor(0, 1);
    STRINGSIZE--;
    if (STRINGSIZE < 0)
      STRINGSIZE = 0;
    STRING[STRINGSIZE] = '\0';
  }
  if(LABEL == 13)
  {
    Serial.println(",");
    deleteChar();
    printString(",");
    STRING[STRINGSIZE - 1] = ',';
    dot = false;
  }
  if(LABEL < 12)
    STRINGSIZE++;
}
