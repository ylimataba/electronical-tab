void writeToSD(char* tag)
{
  digitalWrite(10,HIGH);
  digitalWrite(A1,LOW);
  SD.begin(A1);
  File myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile)
  {
    Serial.print("Writing to test.txt...");
    //myFile.print("Card ID: ");
    myFile.println(tag);
    //myFile.print("Amount: ");
    myFile.println(STRING);
    myFile.println();
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
    delay(2000);
  }
}
