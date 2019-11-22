#include <SPI.h>
#include <SD.h>  //library to access sd card data
#include <EEPROM.h>
//'''sd card'''......................
const int chipSelect = 53;  //sd-card connected at pin 53
//.....................................

void sd_init() {
  //check if sd card is connected
  if (!SD.begin(chipSelect)) {
    while (1);  //loop until not connected
  }
}
void read_sd(File dataFile, int space)
{
  /*read from the sd card filename <datafile> and save in an array "trace"*/
  int  index = 0;
  if (dataFile) { //check if file if ready to be read
    while (dataFile.available() && index < 2 * space)  //read until data is available 
    {
 
      if (index < space) {
        trace[index].top_1 = dataFile.parseInt();  //store <space> no. of values in the "top_1" array and next <space> values in "bot_1"
      }
      else {
        trace[index-space].bot_1 = dataFile.parseInt(); //convert values in sd card file to integer
       
      }
      index++;
    }

    dataFile.close();  //close the file after reading
  }
}
void print_sd(int space)
{
  /*print the data stored in the arrays*/
  for (int i = 0; i < space; i++)
  {
    Serial.print(trace[i].top_1);
    Serial.print(" ,");
    Serial.print(trace[i].bot_1);
    Serial.print(", ");
    Serial.println(i);
  }
}
