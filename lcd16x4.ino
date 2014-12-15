void setCursor(int col, int row)
{
  if (row > 1)
    col -= 4;
  COL = col;
  ROW = row;
  lcd.setCursor(COL,ROW);
}

void printString(const char *string)
{
  for (int i = 0; string[i] != '\0'; i++)
  {
    lcd.print(string[i]);
    nextCol();
  }
}

void printStringE(const char *string)
{
  int tmp = 0;
  while(string[tmp] != '\0')
    tmp++;
  for (int i = 0; string[i] != '\0'; i++)
  {
    if(i == tmp - 2)
    {
      lcd.print(",");
      nextCol();
    }
    lcd.print(string[i]);
    nextCol();
  }
}

void deleteChar()
{
  COL--;
  if (COL < -4 && ROW == 3)
  {
    ROW--;
    COL = 11;
  }
  if ((COL < -4 && ROW == 2) || (COL < 0 && ROW == 1))
  {
    ROW--;
    COL = 15;
  }
  if (COL < 0 && ROW == 0)
  {
    ROW = 0;
    COL = 0;
  }
  lcd.setCursor(COL,ROW);
  lcd.print(" ");
  lcd.setCursor(COL,ROW);
}

void deleteRow(int row)
{
  while (row == ROW)
    deleteChar();
}

void nextCol()
{
  COL++;
  if (COL > 15 && ROW == 0)
  {
    ROW++;
    COL = 0;
  }
  if ((COL > 15 && ROW == 1) || (COL > 11 && ROW == 2))
  {
    ROW++;
    COL = -4;
  }
  if (COL > 11 && ROW == 3)
  {
    ROW = 0;
    COL = 0;
  }
  lcd.setCursor(COL,ROW);
}
