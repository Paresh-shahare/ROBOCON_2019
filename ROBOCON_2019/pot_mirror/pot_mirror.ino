#include<Servo.h>
#include <EEPROM.h>
#include "head.h"
#include "EEpro.h"
void setup() {
  Serial.begin(9600);

  join();

  //uncomment as per position of bot
  //  set_initial();  //normal standing position
  //  straight();     //position when bot needs to move straight
  //  forward();      //position when bot is near sand dune
  //  set_climb();    //sand dune climbing position
  //  set_rope();     //rope crossing position


  delay(1000);
  // E_read();
  // E_clean();

}

void loop() {

  a = analogRead(top);
  b = analogRead(bot);
  Serial.print(a);
  Serial.print("     ");
  Serial.println(b);
  //  diag_right(a, b);
  //  diag_left(a, b);
  front_right(a, b);
  //  front_left(a, b);
  //  back_right(a, b);
  back_left(a, b);


  //.....................................................
  //if IR receives signal start rcording the motion using values obtained from potentiometer
  if (digitalRead(ir) == 1) {
    delay(200);
    Serial.println("going in");
    flag = 1;
    pot_write();  //write the values of pot in EEPROM
    E_read();    //print the written values
  }
  //.....................................................

  /*Code to simulate the motion of legs by moving the demo leg consisting of potentiometers
    s decides which leg is simulated
    uncomment accordingly
    everytime IR is triggered the motion will switch to next block
  */
  if ( (s == 0)) {
    delay(800);
    while (!digitalRead(ir)) {
      a = analogRead(top);
      b = analogRead(bot);
      front_right(a, b);
      back_left(a, b);
      s = 1;
    }
  }

  else if ( (s == 1)) {
    delay(800);
    while (!digitalRead(ir)) {
      a = analogRead(top);
      b = analogRead(bot);
      front_left(a, b);
      //back_left(a,b);
      back_right(a, b);
      //back_right(a, b);
      s = 2;
    }
    //
  }
  else if ( (s == 2)) {
    delay(800);
    while (!digitalRead(ir)) {
      a = analogRead(top);
      b = analogRead(bot);
      back_left(a, b);
      //back_right(a, b);
      s = 3;
    }

  }
  else if ( (s == 3)) {
    delay(800);
    while (!digitalRead(ir)) {
      a = analogRead(top);
      b = analogRead(bot);
      back_right(a, b);
      //front_right(a, b);
      s = 0;  //go back to first motion
      //s can be made 4 in order to simulate more motions
    }
  }

  else if ( (s == 4)) {
    delay(1000);
    while (!digitalRead(ir)) {
      a = analogRead(top);
      b = analogRead(bot);
      //back_right(a, b);
      front_left(a, b);
      s = 0;
    }

  }
}
void diag_left(int a, int b)
{
  front_lu.writeMicroseconds(val(59.20 - val_t(a), 1));
  front_lb.writeMicroseconds(val(13.40 + val_b(b)));

  back_ru.writeMicroseconds(val(54.20 + val_t(a)));
  back_rb.writeMicroseconds(val(93.20 - val_b(b)));
}
void diag_right(int a, int b)
{
  front_ru.writeMicroseconds(val(77.60 + val_t(a)));
  front_rb.writeMicroseconds(val(93.20 - val_b(b)));

  back_lu.writeMicroseconds(val(58.80 - val_t(a)));
  back_lb.writeMicroseconds(val( 11.20 + val_b(b)));
}

void front_left(int a, int b)
{
  front_lu.writeMicroseconds(val(59.20 - val_t(a), 1));
  front_lb.writeMicroseconds(val(13.40 + val_b(b)));
}
void back_left(int a, int b)
{
  back_lu.writeMicroseconds(val(58.80 - val_t(a)));
  back_lb.writeMicroseconds(val( 11.20 + val_b(b)));
}
void front_right(int a, int b)
{
  front_ru.writeMicroseconds(val(77.60 + val_t(a), 2));
  //  front_rb.writeMicroseconds(val(93.20 - val_b(b)));
}
void back_right(int a, int b)
{
  back_ru.writeMicroseconds(val(54.20 + val_t(a)));
  back_rb.writeMicroseconds(val(93.20 - val_b(b)));
}
