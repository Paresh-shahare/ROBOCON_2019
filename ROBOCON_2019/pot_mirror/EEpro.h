void diag_left(int a, int b);
void diag_right(int a, int b);
void front_left(int a, int b);
void front_right(int a, int b);
void back_left(int a, int b);
void back_right(int a, int b);


void pot_write()   //do not call in loop
{
  //read the value from potentiometers and store them in EEPROM while also simulating the motion of legs
  Serial.println("writing");
  int eeAddress = 0;
  while (flag)
  {
    a = analogRead(top);
    b = analogRead(bot);
    m1.top_1 = a - pot_val;
    m1.bot_1 = 1023 - b;
    EEPROM.put(eeAddress, m1);
    eeAddress += sizeof(m1);
    count++;
    //uncomment the leg that needs to be simulated
    //back_right(a,b);
    //back_left(a, b);
    //front_right(a, b);
    //front_left(a, b);
    if (digitalRead(ir) == 1)  //stop recording when IR is triggered again
      flag = 0;
  }
  //  address = eeAddress + sizeof(m1);
}


//...............................................................................
void E_read(void)
{
  for (int eeAddress = 0; eeAddress < EEPROM.length() * sizeof(m1); eeAddress += sizeof(m1))
  {
    EEPROM.get(eeAddress, m1);
    Serial.print(m1.top_1);
    Serial.print("     ");
    Serial.print(m1.bot_1);
    Serial.print("     ");
    Serial.println(count);
    count++;
  }
  while (1);
}
//...............................................................................
void E_clean(void)
{
  for (int i = 0 ; i < EEPROM.length() ; i++)
    EEPROM.write(i, 0);
  Serial.print("done");
  while (1);
}
