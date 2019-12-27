#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>

const int chipSelect = 53;
int a[458];
int k[458];
int i=0;
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
  File dataFile = SD.open("a1_458.txt");
  if (dataFile) {
    int g=0;
    while (dataFile.available())
    {
      int h = dataFile.parseInt();
      a[g]= h;
      g++;    
    }

for(int i=0;i<458;i++)
{
  k[i]=a[i];
  } 
    dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt");
  }
}

void loop() {

Serial.println("kjg------------------------------------");
  for(int i=0;i<458;i++)
{
  Serial.println(k[i]);
  }
  while(1);
}
