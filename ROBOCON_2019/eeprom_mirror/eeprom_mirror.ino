#include<Servo.h>
#include <EEPROM.h>
#include "head.h"
#include "sd_head.h"
#include "array.h"

void setup() {
  Serial.begin(9600);
  //  count = 0;
  //  pinMode(led,OUTPUT);
  //load from EEPROM and store in m1 object
  for (int eeAddress =  0 * sizeof(m1); eeAddress < 251  * sizeof(m1); eeAddress += sizeof(m1))
  {
    EEPROM.get(eeAddress, m1);
    trace[count] = m1;
    count++;
  }

  Serial.println("done initilization");
  sd_init();

  join();  //join all servos
  straight();  //align legs to initial position

  File dataFile = SD.open("c1_363.txt", FILE_READ);  //read forward motion from sd card
  read_sd(dataFile, 363);

  set_initial();  //set the servo to starting position

}

void loop() {

    File dataFile = SD.open("b1_558.txt", FILE_READ);
    read_sd(dataFile, 558);
    print_sd(558);
    forward();
    turn_left();
    climb_sand();
    rope();
}

void diag_left(angle m1)
{
  //rotate the diagonal legs of left side simultaneously at given angle
  front_lu.writeMicroseconds(val(59.20 - val_t(m1.top_1), 1));
  front_lb.writeMicroseconds(val(13.40 + val_b(m1.bot_1)));

  back_ru.writeMicroseconds(val(54.20 + val_t(m1.top_1)));
  back_rb.writeMicroseconds(val(93.20 - val_b(m1.bot_1)));
  delay(0);
}


void diag_right(angle m1)
{
  //rotate the diagonal legs of right side simultaneously at given angle
  front_ru.writeMicroseconds(val(77.60 + val_t(m1.top_1), 2));
  front_rb.writeMicroseconds(val(93.20 - val_b(m1.bot_1)));

  back_lu.writeMicroseconds(val(58.80 - val_t(m1.top_1)));
  back_lb.writeMicroseconds(val(11.20 + val_b(m1.bot_1)));
  delay(0);
}


void front_left(angle m1)
{
  //rotate the front left servo pair at desired angle
  front_lu.writeMicroseconds(val(59.20 - val_t(m1.top_1), 1));
  front_lb.writeMicroseconds(val(13.40 + val_b(m1.bot_1)));
}
void back_left(angle m1)
{
  //rotate the back left servo pair at desired angle
  back_lu.writeMicroseconds(val(58.80 - val_t(m1.top_1)));
  back_lb.writeMicroseconds(val(11.20 + val_b(m1.bot_1)));
}
void front_right(angle m1)
{
  //rotate the front right servo pair at desired angle
  front_ru.writeMicroseconds(val(77.60 + val_t(m1.top_1), 2));
  front_rb.writeMicroseconds(val(93.20 - val_b(m1.bot_1)));
}
void back_right(angle m1)
{
  //rotate the back right servo pair at desired angle
  back_ru.writeMicroseconds(val(54.20 + val_t(m1.top_1)));
  back_rb.writeMicroseconds(val(93.20 - val_b(m1.bot_1)));
}

void rope(void)
{
  int mid = 180;
  for (int i = 0; i < mid; i++) //total ==363 pot val =433
  {
    front_right(trace[i]);
    delay(5);
  }
  for (int i = 0; i < mid; i++) //total ==363 pot val =433
  {
    back_left(trace[i]);
    delay(5);
  }
  for (int i = 0; i < mid; i++) //total ==363 pot val =433
  {
    front_left(trace[i]);
    delay(5);
  }
  for (int i = 0; i < mid; i++) //total ==363 pot val =433
  {
    back_right(trace[i]);
    delay(5);
  }
  for (int i = mid; i < 251; i++) //total ==363 pot val =433
  {
    diag_right(trace[i]);
    diag_left(trace[i]);
    delay(10);
  }
}
void turn_right(void)
{

  for (int i = 0; i <= centre; i++) //total
  {
    front_left(trace[i]);
    back_right(trace[centre - i]);
    delay(20);
  }
  for (int i = 0; i <= centre; i++) //total
  { 
    back_left(trace[i]);
    front_right(trace[centre - i]);
    delay(20);
  }
  for (int i = 0; i <= centre; i++) //total
  {
    front_left(trace[centre + i]);
    back_right(trace[total - i]);

    back_left(trace[centre + i]);
    front_right(trace[total - i]);
    delay(20 );
  }


}

void turn_left(void)
{
  int centre = 172;
  for (int i = 0; i <= centre; i++) //total
  {
    front_left(trace[centre - i]);
    back_right(trace[ i]);
    delay(3);
  }
  for (int i = 0; i <= centre; i++) //total
  {
    front_left(trace[centre + i]);
    back_right(trace[total - i]);
    delay(3);
  }

}


void move_forward(void)
{
    if (!flag) {
    File dataFile = SD.open("for_369.txt", FILE_READ);
    read_sd(dataFile, 369);
      flag=1;
    }
  int centre = 184;
  for (int i = 0; i <= centre; i++) //124
  {
    diag_left(trace[i]);
    diag_right(trace[i + centre]); //i max+ num =total
    delay(2.8);
  }

  for (int i = 0; i <= centre; i++) //124
  {
    diag_left(trace[i + centre]);  //i max+ num =total
    diag_right(trace[i]);
    delay(2.8);

  }

}

void climb_sand()
{

  File dataFile = SD.open("a1_458.txt", FILE_READ);
  read_sd(dataFile, 458);
  //front leg steps while going up on sand dune
  for (int i = 0; i < 458; i++) //124
  {
    front_left(trace[i]);
    delay(3);
  }
  for (int i = 0; i < 458; i++) //124
  {
    front_right(trace[i]);
    delay(3);
  }
  int  foot_fall = 0;
  dataFile = SD.open("b1_558.txt", FILE_READ);
  read_sd(dataFile, 558);
  while (foot_fall < 2)
  {
    //back leg small steps while pushing bot forward
    for (int i = 0; i < 557; i++) //124
    {
      back_right(trace[i]);
      delay(3);

    }

    for (int i = 0; i < 557; i++) //124
    {
      back_left(trace[i]);
      delay(3);
    }
    foot_fall++;
  }
  delay(100);

   straight();
  //.........................................................roll
  delay(100);
  front_lu.writeMicroseconds(val(59.20, 1));
  front_lb.writeMicroseconds(val(13.40));

  front_ru.writeMicroseconds(val(77.60, 2));
  front_rb.writeMicroseconds(val(93));


  back_left(trace[556]);
  back_right(trace[556]);
  delay(100);
  straight();

  dataFile = SD.open("c1_363.txt", FILE_READ);
  read_sd(dataFile, 363);
  for (int i = 28; i < 363; i++) //total ==363 pot val =433
  {
    back_left(trace[i]);
    delay(5);
  }
  for (int i = 28; i < 363; i++) //124
  {
    back_right(trace[i]);
    delay(5);
  }
  delay(200);
  stepb.top_1 = 289 - 433; 
  stepb.bot_1 = 1023 - 713;

  
  File dataFile = SD.open("c1_363.txt", FILE_READ);
  read_sd(dataFile, 363);
  back_left(trace[300]);
  back_right(trace[300]);
  delay(300);
  front_lu.writeMicroseconds(val(59.20, 1));
  front_lb.writeMicroseconds(val(13.40));

  front_ru.writeMicroseconds(val(77.60, 2));
  front_rb.writeMicroseconds(val(93));
  delay(2000);

  int foot_fall = 0;
  while (foot_fall < 2)
  {
    delay(100);
    setv.top_1 = 324 - 433;  //position of back leg when forward legs are stepping dune
    setv.bot_1 = 1023 - 759;
    back_left(setv);
    back_right(setv);
    delay(200);
    for (int i = 0; i < 197; i++) //124
    {
      stepf.top_1 = top_val1[i];
      stepf.bot_1 = bot_val1[i];
      front_left(stepf);
      delay(5);

    }
    for (int i = 0; i < 197; i++) //124
    {
      stepf.top_1 = top_val1[i];
      stepf.bot_1 = bot_val1[i];
      front_right(stepf);
      delay(5);

    }
    delay(300);
    setv.top_1 = 352 - 433;
    setv.bot_1 = 1023 - 864;
    back_left(setv);
    back_right(setv);
    delay(300);
    for (int i = 0; i < 305; i++) //124
    {
      stepb.top_1 = top_val4[i];
      stepb.bot_1 = bot_val4[i];
      back_right(stepb);
      delay(3);
    }

    for (int i = 0; i < 305; i++) //124
    {
      stepb.top_1 = top_val4[i];
      stepb.bot_1 = bot_val4[i];
      back_left(stepb);
      delay(3);
    }

    for (int i = 305, j = 197; i < 535 , j < 427; i++, j++) //124
    {

      stepb.top_1 = top_val4[i];
      stepb.bot_1 = bot_val4[i];
      back_left(stepb);
      back_right(stepb);
      stepf.top_1 = top_val1[j];
      stepf.bot_1 = bot_val1[j];
      front_right(stepf);
      front_left(stepf);
      delay(3);

    }
    foot_fall++;
  }
  delay(300);
  straight();
  delay(100);
  stepb.top_1 = 289 - 433;
  stepb.bot_1 = 1023 - 713;
  back_left(stepb);
  back_right(stepb);
  delay(300);
  straight();
  set_initial();

}
