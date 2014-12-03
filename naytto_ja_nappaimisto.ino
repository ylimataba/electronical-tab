#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//2-dimensional array for asigning the buttons and there high and low values
/* freakduino
int Button[12][3] = {{1, 800, 845},      // button 1
                     {2, 440, 470},      // button 2
                     {3, 90, 145},       // button 3
                     {4, 720, 750},      // button 4
                     {5, 280, 320},      // button 5
                     {6, 50, 89},        // button 6
                     {7, 670, 710},      // button 7
                     {8, 175, 220},      // button 8
                     {9, 5, 49},         // button 9
                     {10, 580, 630},     // enter
                     {11, 146, 174},     // button 0
                     {12, 1000, 1023}};  // cancel
*/
int Button[12][3] = {{1, 770, 845},      // button 1
                     {2, 440, 470},      // button 2
                     {3, 101, 145},       // button 3
                     {4, 690, 750},      // button 4
                     {5, 280, 320},      // button 5
                     {6, 61, 100},        // button 6
                     {7, 650, 689},      // button 7
                     {8, 191, 220},      // button 8
                     {9, 10, 60},         // button 9
                     {10, 550, 630},     // enter
                     {11, 146, 190},     // button 0
                     {12, 900, 1023}};  // cancel
int analogpin = A5; // analog pin to read the buttons
int label = 0;  // for reporting the button label
int counter = 0; // how many times we have seen new value
long time = 0;  // the last time the output pin was sampled
int debounce_count = 150; // number of millis/samples to consider before declaring a debounced input
int current_state = 0;  // the debounced input value
int ButtonVal;
int col = 0;
int row = 0;

boolean dot = false;
long timer = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  analogWrite(8,90); //contrast
  lcd.begin(16,4);

}

void loop()
{
   // If we have gone on to the next millisecond
  if (millis() != time)
  {
    // check analog pin for the button value and save it to ButtonVal
    ButtonVal = analogRead(analogpin);
    
    // for calibration
    //Serial.println(ButtonVal);
    //delay(1000);
    
    if(ButtonVal == current_state && counter >0)
    { 
      counter--;
    }
    if(ButtonVal != current_state)
    {
      counter++;
    }
    // If ButtonVal has shown the same value for long enough let's switch it
    if (counter >= debounce_count)
    {
      counter = 0;
      current_state = ButtonVal;
      //Checks which button or button combo has been pressed
      if (ButtonVal > 0)
      {
        ButtonCheck();
      }
    }
    time = millis();
  }
}
void ButtonCheck()
{
  // loop for scanning the button array.
  for(int i = 0; i <= 12; i++)
  {
    // checks the ButtonVal against the high and low vales in the array
    if(ButtonVal >= Button[i][1] && ButtonVal <= Button[i][2])
    {
      // stores the button number to a variable
      label = Button[i][0];
      
      if (time > timer + 500 || label != 1)
        dot = false;
      if (dot)
        label = 13;

      Action();

      Serial.println(col);
      Serial.println(row);
      Serial.println();
    }
  }
}

void Action()
{
  if (label == 1)
  {
    timer = time;
    Serial.println("1");
    lcd.print("1");
    dot = true;
    moveCursorForward();
  }
  if(label == 2)
  {
    Serial.println("2");
    lcd.print("2");
    moveCursorForward();
  }
  if(label == 3)
  { 
    Serial.println("3");
    lcd.print("3");
    moveCursorForward();
  }
  if(label == 4)
  {
    Serial.println("4");
    lcd.print("4");
    moveCursorForward();
  }
  if(label == 5)
  {
    Serial.println("5");
    lcd.print("5");
    moveCursorForward();
  }
  if(label == 6)
  {
    Serial.println("6");
    lcd.print("6");
    moveCursorForward();
  }
  if(label == 7)
  {
    Serial.println("7");
    lcd.print("7");
    moveCursorForward();
  }
  if(label == 8)
  {
    Serial.println("8");
    lcd.print("8");
    moveCursorForward();
  }
  if(label == 9)
  {
    Serial.println("9");
    lcd.print("9");
    moveCursorForward();
  }
  if(label == 10)
  {
    Serial.println("ENTER");
    char enter[] = "ENTER";
    for (int i = 0; i++; i<5)
    {
        lcd.print(enter[i]);
        moveCursorForward();
    }
  }
  if(label == 11)
  {
    Serial.println("0");
    lcd.print("0");
    moveCursorForward();
  }    
  if(label == 12)
  {
    Serial.println("CANCEL");
    moveCursorBackward();
    lcd.print(" ");
    moveCursorBackward();
  }
  if(label == 13)
  {
    Serial.println(",");
    moveCursorBackward();
    lcd.print(",");
    dot = false;
  }
}

void moveCursorForward()
{
  col++;
  if (col > 15 && row == 0)
  {
    row++;
    col = 0;
  }
  if ((col > 15 && row == 1) || (col > 11 && row == 2))
  {
    row++;
    col = -4;
  }
  if (col > 11 && row == 3)
  {
    row = 0;
    col = 0;
  }
  lcd.setCursor(col,row);
}

void moveCursorBackward()
{
  col--;
  if (col < 0 && row == 3)
  {
    row--;
    col = 11;
  }
  if ((col < -4 && row == 2) && (col < 0 && row == 1))
  {
    row--;
    col = 15;
  }
  if (col < 0 && row == 0)
  {
    row = 0;
    col = 0;
  }
  lcd.setCursor(col,row);
}
