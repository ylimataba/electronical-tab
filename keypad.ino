int keypad(int from, int to)
{
  // check analog pin for the BUTTON value and save it to BUTTONVAL
  int buttonval = analogRead(A5);
  
  if(buttonval == CURRENT_STATE && COUNTER >0)
  { 
    COUNTER--;
  }
  if(buttonval != CURRENT_STATE)
  {
    COUNTER++;
  }
  // If buttonval has shown the same value for long enough let's switch it
  if (COUNTER >= DEBOUNCE_COUNT)
  {
    COUNTER = 0;
    CURRENT_STATE = buttonval;
    //Checks which button or button combo has been pressed
    if (buttonval > 0)
    {
      return ButtonCheck(buttonval, from, to);
    }
  }
  //Serial.println(buttonval);
  return 0;
}

int ButtonCheck(int buttonval, int from, int to)
{
  // loop for scanning the button array.
  for(int i = from; i <= to; i++)
  {
    // checks the buttonval against the high and low vales in the array
    if(buttonval >= BUTTON[i][1] && buttonval <= BUTTON[i][2])
    {
      // stores the BUTTON number to a variable
      int label = BUTTON[i][0];
      if(from > 0 && label == 12)
        Action(13);
      if(from > 0 && label == 10)
        Action(14);
      else
        Action(label);
      return label;
      //break; // poistuu for silmukasta luettuaan näppäimen!
    }
  }
  return 0;
}

void Action(int label)
{
  Serial.print("label: ");
  Serial.println(label);
  if(label == 1)
  {
    Serial.println("1");
    printString("1");
    STRING[STRINGSIZE] = '1';
  }
  if(label == 2)
  {
    Serial.println("2");
    printString("2");
    STRING[STRINGSIZE] = '2';
  }
  if(label == 3)
  { 
    Serial.println("3");
    printString("3");
    STRING[STRINGSIZE] = '3';
  }
  if(label == 4)
  {
    Serial.println("4");
    printString("4");
    STRING[STRINGSIZE] ='4';
  }
  if(label == 5)
  {
    Serial.println("5");
    printString("5");
    STRING[STRINGSIZE] = '5';
  }
  if(label == 6)
  {
    Serial.println("6");
    printString("6");
    STRING[STRINGSIZE] = '6';
  }
  if(label == 7)
  {
    Serial.println("7");
    printString("7");
    STRING[STRINGSIZE] = '7';
  }
  if(label == 8)
  {
    Serial.println("8");
    printString("8");
    STRING[STRINGSIZE] = '8';
  }
  if(label == 9)
  {
    Serial.println("9");
    printString("9");
    STRING[STRINGSIZE] = '9';
  }
  if(label == 10)
  {
    Serial.println("0");
    printString("0");
    STRING[STRINGSIZE] = '0';
  }   
  if(label == 11)
  {
    Serial.println("ENTER");
    setCursor(0,3);
    printString("ENTER           ");
    delay(200);
  } 
  if(label == 12)
  {
    deleteChar();
    if (ROW==1 && COL < 7)
      setCursor(7, 1);
    STRINGSIZE--;
    if (STRINGSIZE < 0)
      STRINGSIZE = 0;
    STRING[STRINGSIZE] = '\0';
  }
  if(label == 13)
  {
    Serial.println("CANCEL");
    setCursor(0,3);
    lcd.print("          CANCEL");
    delay(200);
  }
  if(label == 14)
  {
    Serial.println("EXIT");
    setCursor(0,3);
    lcd.print("      EXIT      ");
    delay(200);
  }
  if(label < 11)
    STRINGSIZE++;
}
