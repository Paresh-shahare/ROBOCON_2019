int bot = A13;
int top = A12;
int tp = A12;
int ir = 23;
//int address=0;
int k = 0, s = 0;
int a, b, c, count = 0, flag = 0, pot_val = 433;
struct angle {
  int top_1;
  int bot_1;
} m1;

//...............................................................................

uint8_t f_ru = 4;
uint8_t f_rb = 5;
uint8_t f_lu = 2;
uint8_t f_lb = 3;
uint8_t b_ru = 8;
uint8_t b_rb = 9;
uint8_t b_lu = 6;
uint8_t b_lb = 7;


uint8_t f_lu_s = 60;   //+angle forward  60
uint8_t f_lb_s = 80;   //+angle backward  80
uint8_t f_ru_s = 55;   //+angle backward //call map 0 to 45  50
uint8_t f_rb_s = 55;  //+angle forward  //180 degree  45
uint8_t b_lu_s = 77;   //+angle forward  80
uint8_t b_lb_s = 80;   //+angle backward  75
uint8_t b_ru_s = 53;  //+angle backward 45
uint8_t b_rb_s = 50;  //+angle forward  55
//...............................................................................

Servo front_lu, front_lb, front_ru, front_rb, back_lu, back_lb, back_ru, back_rb;


// code to convert analog value of potentiometer into angle in degrees
//1 unit change in the value of potentiometer is equivalent to 0.2 degrees
float val_t(int a) //angle for top potentiometer
{
  return (a - pot_val) * 0.2;
}

//angle for bottom potentiometer
float val_b(int a)
{
  return (1023 - a) * 0.2;
}

/*convert angle in degrees to pulse per minute for providing signal to servo
  servos can rotate from 0 to 120 degrees
  ppm of a servo ranges from ~900 to ~2100
  2 of our servos malfunctioned hence had different ppm values for same angles*/
int val(float x, int a = 0)
{
  //a is used due to malfunctioning of few servos
  if (a == 1)
  {
    if (x > 120)
      return 1008;
    else if (x < 0)
      return 544;
    else
      return 544 + 3.8666 * x;
  }
  if (a == 2)
  {
    if (x > 120)
      return 2090;
    else if (x < 0)
      return 853;
    else
      return 853 + 10.316 * x;
  }
  else
  {
    if (x > 120)
      return 2100;
    else if (x < 0)
      return 900;
    else
      return 900 + 10 * x;  //scaled and calculated
  }
}


void join() {
  front_lu.attach(f_lu);
  front_lb.attach(f_lb);
  //
  front_ru.attach(f_ru);
  front_rb.attach(f_rb);

  back_lu.attach(b_lu);
  back_lb.attach(b_lb);

  back_ru.attach(b_ru);
  back_rb.attach(b_rb);
}

void set_initial()
{

  front_lu.writeMicroseconds(788);
  front_lb.writeMicroseconds(1166);
  front_ru.writeMicroseconds(1593);
  front_rb.writeMicroseconds(1700);
  back_lu.writeMicroseconds(1528);
  back_lb.writeMicroseconds(1144);
  back_ru.writeMicroseconds(1402);
  back_rb.writeMicroseconds(1700);
}

void set_climb()
{

  front_lu.writeMicroseconds(1612);  //1738
  front_lb.writeMicroseconds(1186);  //1770
  front_ru.writeMicroseconds(749);   //683  //732
  front_rb.writeMicroseconds(1938);  //1250  //1834
  back_lu.writeMicroseconds(1746);
  back_lb.writeMicroseconds(1738);
  back_ru.writeMicroseconds(1354);
  back_rb.writeMicroseconds(1262);
}

void set_rope()
{

  front_lu.writeMicroseconds(1738);  //1738
  front_lb.writeMicroseconds(1770);  //1770
  front_ru.writeMicroseconds(683);   //683  //732
  front_rb.writeMicroseconds(1250);  //1250  //1834
  back_lu.writeMicroseconds(1746);
  back_lb.writeMicroseconds(1738);
  back_ru.writeMicroseconds(1354);
  back_rb.writeMicroseconds(1262);
}

//...............................................................


void straight(void)
{
  front_lu.writeMicroseconds(val(59.20, 1));
  front_lb.writeMicroseconds(val(13.40));

  back_ru.writeMicroseconds(val(54.20 ));
  back_rb.writeMicroseconds(val(93.20));

  front_ru.writeMicroseconds(val(77.60, 2));
  front_rb.writeMicroseconds(val(93));

  back_lu.writeMicroseconds(val(58.80 ));
  back_lb.writeMicroseconds(val(11.20));
}

void print_vals(void)
{
  int top_init = a;
  int bot_init = b;
  Serial.print(val(59.20 - val_t(top_init), 1)); //flu
  Serial.print("    ");
  Serial.print(val(13.40 + val_b(bot_init))); //flb
  Serial.print("    ");
  Serial.print(val(59.40 + val_t(top_init), 2)); //fru
  Serial.print("    ");
  Serial.print(val(93.20 - val_b(bot_init)));  //frb
  Serial.print("    ");
  Serial.print(val(58.80 - val_t(top_init))); //blu
  Serial.print("    ");
  Serial.print(val(11.20 + val_b(bot_init))); //blb
  Serial.print("    ");
  Serial.print(val(54.20 + val_t(top_init)));  //bru
  Serial.print("    ");
  Serial.println(val(93.20 - val_b(bot_init))); //brb
}
