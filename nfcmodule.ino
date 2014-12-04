void startNFC()
{
  digitalWrite(10,LOW);
  digitalWrite(A1,HIGH);
  nfc.begin();
}

char* getTag()
{
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    String str = tag.getUidString();
    char* tmp = (char*)malloc(sizeof(char)*(str.length()+1));
    str.toCharArray(tmp, str.length()+1);
    tmp = deblank(tmp); // remove spaces
    Serial.println(str);
    
    return tmp;
  }
  return "";
}
char* deblank(char* input)                                         
{
    int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)          
    {
        if (input[i]!=' ')                           
            output[j]=input[i];                     
        else
            j--;                                     
    }
    output[j]=0;
    return output;
}
