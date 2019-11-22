int bot = A15;
int top = A14;
int eeAddress = 0;
int count = 0;
int ir = 23, pot_val = 600,flag=0,ir2=22,led=13;
const int total = 600, centre =172 ;     // 363 tha thodi der pehle  //558

struct angle {
  int top_1;
  int bot_1;
} m1, trace[total], stepf, stepb, setv, stepd;

//define the pin of each servo

uint8_t f_ru = 4;
uint8_t f_rb = 5;
uint8_t f_lu = 2;
uint8_t f_lb = 3;
uint8_t b_ru = 8;
uint8_t b_rb = 9;
uint8_t b_lu = 6;
uint8_t b_lb = 7;

//make 8 servo objects for 8 joints of quadruped

Servo front_lu, front_lb, front_ru, front_rb, back_lu, back_lb, back_ru, back_rb;


//...............................................................................

float val_t(int a)
{
//    return (719-a) * 0.2;  //for forward
  //return (a-583) * 0.2;   //for forward dune
//  return (a-549) * 0.2;
  //return (a-pot_val) * 0.2;
  return a * 0.2;
}

//...............................................................................

float val_b(int a)
{
  return a * 0.2;
//    return (1023 - a) * 0.2;
}

//...............................................................................

int val(float x, int a = 0)
{
  if (a==1)
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
      return 900 + 10 * x;
  }
}

//...............................................................................


void join() {
  /*attach all the servo motors to their defined pins*/
  
  front_lu.attach(f_lu);
  front_lb.attach(f_lb);
  
  front_ru.attach(f_ru);
  front_rb.attach(f_rb);

  back_lu.attach(b_lu);
  back_lb.attach(b_lb);

  back_ru.attach(b_ru);
  back_rb.attach(b_rb);
}

void set_initial()
{
  /*initial standing position of the quadruped*/
  front_lu.writeMicroseconds(788);
  front_lb.writeMicroseconds(1166);
  front_ru.writeMicroseconds(1593);
  front_rb.writeMicroseconds(1700);
  back_lu.writeMicroseconds(1528);
  back_lb.writeMicroseconds(1144);
  back_ru.writeMicroseconds(1402);
  back_rb.writeMicroseconds(1700);
}

void straight(void)
{
  front_lu.writeMicroseconds(val(59.20, 1));
  front_lb.writeMicroseconds(val(13.40));

  back_ru.writeMicroseconds(val(54.20 ));
  back_rb.writeMicroseconds(val(93.20));

  front_ru.writeMicroseconds(val(77.60,2));
  front_rb.writeMicroseconds(val(93));

  back_lu.writeMicroseconds(val(58.80 ));
  back_lb.writeMicroseconds(val(11.20));
}
void forward()
{
  front_ru.writeMicroseconds(803); 

  front_rb.writeMicroseconds(1494);    


  back_ru.writeMicroseconds(1632); 
  
  back_rb.writeMicroseconds(1560);  
}
void set_climb()
{

  front_lu.writeMicroseconds(1738);
  front_lb.writeMicroseconds(1770);
  front_ru.writeMicroseconds(683);
  front_rb.writeMicroseconds(1250);
  back_lu.writeMicroseconds(1746);
  back_lb.writeMicroseconds(1738);
  back_ru.writeMicroseconds(1354);
  back_rb.writeMicroseconds(1262);
}

void set_walk()
{

  front_lu.writeMicroseconds(1368);
  front_lb.writeMicroseconds(1528);
  front_ru.writeMicroseconds(827);
  front_rb.writeMicroseconds(1492);
  back_lu.writeMicroseconds(1398);
  back_lb.writeMicroseconds(1458);
  back_ru.writeMicroseconds(1702);
  back_rb.writeMicroseconds(1542);
}
void print_vals(void)
{
  /*print the angles of each motor at given pulse*/
  int top_init = 920;
  int bot_init = 920;
  Serial.print(val(59.20 - val_t(top_init), 1)); //front left up
  Serial.print("    ");
  Serial.print(val(13.40 + val_b(bot_init))); //front left bottom
  Serial.print("    ");
  Serial.print(val(59.40 + val_t(top_init),2)); //front right up
  Serial.print("    ");
  Serial.print(val(93.20 - val_b(bot_init)));  //front right bottom
  Serial.print("    ");
  Serial.print(val(58.80 - val_t(top_init))); //back left up
  Serial.print("    ");
  Serial.print(val(11.20 + val_b(bot_init))); //back left bottom
  Serial.print("    ");
  Serial.print(val(54.20 + val_t(top_init)));  //back right up
  Serial.print("    ");
  Serial.println(val(93.20 - val_b(bot_init))); //back right bottom
}
