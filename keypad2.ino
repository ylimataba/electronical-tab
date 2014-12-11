void keypad2() //karu toteutus vain enterin ja cancelin lukemiseen
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
        ButtonCheck2();
      }
    }
    //Serial.println(BUTTONVAL);
  }
}

void ButtonCheck2()
{
  // loop for scanning the button array.
  for(int i = 0; i <= 12; i++)
  {
    // checks the BUTTONVAL against the high and low vales in the array
    if(BUTTONVAL >= BUTTON[i][1] && BUTTONVAL <= BUTTON[i][2])
    {
      // stores the BUTTON number to a variable
      LABEL = BUTTON[i][0];
      Action2();
      break; // poistuu for silmukasta luettuaan näppäimen!
    }
  }
}

void Action2()
{
  if(LABEL == 10)
  {
    Serial.println("ENTER");
    setCursor(0,3);
    printString("ENTER           ");
    delay(200);
  }   
  if(LABEL == 12)
  {
    Serial.println("CANCEL");
    setCursor(0,3);
    lcd.print("          CANCEL");
    delay(200);
  }
}
