int eeAddress = 0;  //starting address of EEPROM
int count = 0; //counter for incrementing address of EEPROM

//structure to store the angles of top and bottom servo motors
struct angle {
  int top_1;  //angles of top servo
  int bot_1;  //angles bottom servo
} m1;  //created a struct m1

//...............................................................................

//Write in Arduinos EEPRom memory starting from 0th address
void E_write(void)   
{
  count=0;
  for (int eeAddress = 0; eeAddress < 558 * sizeof(m1); eeAddress += sizeof(m1))
  {
    m1.top_1 = top_val[count];  //read from array stored in header "array.h"
    m1.bot_1 = bot_val[count];
    EEPROM.put(eeAddress, m1);
    count++;
  }
}
//Read and print the data stored in the EEPROM of arduino starting from 0th address
void E_read(void)   
{
  count=0;
  for (int eeAddress = 0; eeAddress < 558 * sizeof(m1); eeAddress += sizeof(m1))
  {
    EEPROM.get(eeAddress, m1);
    Serial.print(m1.top_1);
    Serial.print("     ");
    Serial.print(m1.bot_1);
    Serial.print("     ");
    Serial.println(count);
    count++;
  }
}
//clear the EEPROM memory of arduino before writing new data
void E_clean(void)
{
  for (int i = 0 ; i < EEPROM.length() ; i++)
    EEPROM.write(i, 0);  //write 0 at all addressess for clearing memory
}
