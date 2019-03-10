#include <EEPROM.h>
int cnt = 0;
unsigned char process = 0;
double time_now = 0;
double time_old = 0;
double time_rev;
double delay_1 ;
double deg_per_sec;
unsigned char pointer = 0;
int flag = 0;
double speed_insec = 0; //(rev_per_sec)
double speed_ = 20.0;//multiple of 3
const char S[] = "A B C D";
unsigned char arr[200];
int text_len = strlen(S);
int count_1 = 0;
double rpm_val;
boolean p = 0;
boolean q = 0;
int w1 = 330.0;
int w2 = 30.0;

double angle_per_line = 2.82;
//int frame_1,frame_2; //frame position multile of 3
double th1 =  50.0;
double th2 = th1 + text_len * 5 * angle_per_line; //defined by user multiple of 3//degrees
//double angle_to_delay = rev_time*theta1/360.0;

long int LED[140] = {
  0b01111100, 0b00001010, 0b00001001, 0b00001010, 0b01111100,//a
  0b01111111, 0b01001001, 0b01001001, 0b00110110, 0b00000000,//b
  0b00011100, 0b00100010, 0b01000001, 0b01000001, 0b01000001,//c
  0b01111111, 0b01000001, 0b00100010, 0b00011100, 0b00000000,//d
  0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b00000000,//e
  0b01111111, 0100100101, 0b00100100, 0b00100100, 0b00000000,//f
  0b00011100, 0b00100010, 0b01000001, 0b01001001, 0b00111001,//g
  0b01111111, 0b00001000, 0b00001000, 0b01111111, 0b00000000,//h
  0b01000001, 0b01000001, 0b01111111, 0b01000001, 0b01000001,//i
  0b00010001, 0b00100001, 0b01111111, 0b00000001, 0b00000001,//j
  0b01111111, 0b00001000, 0b00010100, 0b00100010, 0b01000001,//k
  0b01111111, 0b01000000, 0b01000000, 0b01000000, 0b01000000,//l
  0b01111111, 0b00000100, 0b00001000, 0b00000100, 0b01111111,//m
  0b01111110, 0b00000100, 0b00001000, 0b00010000, 0b00111111,//n
  0b00111110, 0b01000001, 0b01000001, 0b01000001, 0b00111110,//o
  0b01111111, 0b00001001, 0b00001001, 0b00001001, 0b00001111,//p
  0b00111110, 0b01000001, 0b01010001, 0b01100001, 0b01111110,//q
  0b01111111, 0b00001001, 0b00011001, 0b00101001, 0b01001001,//r
  0b01001111, 0b01001001, 0b01001001, 0b01001001, 0b01111001,//s
  0b00000001, 0b00000001, 0b01111111, 0b00000001, 0b00000001,//t
  0b01111111, 0b01000000, 0b01000000, 0b01000000, 0b01111111,//u
  0b00011111, 0b00100000, 0b01000000, 0b00100000, 0b00011111,//v
  0b00111111, 0b01000000, 0b00110000, 0b01000000, 0b00111111,//w
  0b00100010, 0b00010100, 0b00001000, 0b00010100, 0b00100010,//x
  0b00000001, 0b00000010, 0b01111100, 0b00000010, 0b00000001,//y
  0b00100010, 0b00110010, 0b00101010, 0b00100110, 0b00100010,//z
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, //' '
  0b00000000, 0b00000000, 0b01111111, 0b00000000, 0b00000000 //01

};





void print_char(unsigned char a)
{
  
  unsigned char p1 = (a >> 6) & 1;
  //Serial.print(p1,BIN);
  unsigned char p2 = (a >> 5) & 1;
  //Serial.print(p2,,,,BIN);
  unsigned char p3 = (a >> 4) & 1;
  //Serial.print(p3,BIN);
  unsigned char p4 = (a >> 3) & 1;
  //Serial.print(p4,BIN);
  unsigned char p5 = (a >> 2) & 1;
  //Serial.print(p5,BIN);
  unsigned char p6 = (a >> 1) & 1;
  //Serial.print(p6,BIN);
  unsigned char p7 = a & 1;
  //Serial.print(p7,BIN);
  //Serial.println();
  //delay(10000);
  //Serial.println();
  Serial.begin(9600);
  digitalWrite(2, p1);
  digitalWrite(4, p2);
  digitalWrite(6, p3);
  digitalWrite(8, p4);
  digitalWrite(10, p5);
  digitalWrite(11, p6);
  digitalWrite(13, p7);
  delayMicroseconds(100);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(13, LOW);
}


void print_line(int i, int j )
{
  
  //count_1++;
 // Serial.println("inside");
  double timeRevDiv = (time_rev/256.0);
  //Serial.println(i);
  //Serial.println(j);
  //Serial.print("hello")
  for (int k = i; k < j; k++)
  {
    
    
    
    print_char(LED[arr[k]]);
    delayMicroseconds(timeRevDiv);
  }

  
   
}
void setup() {
  //rpm();
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(3,INPUT);
  //Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), rpm, FALLING);
  text_len = strlen(S);
  if (text_len > 24)
  {
    text_len = 24;
  }

  for (int j = 0; j < text_len; j++)
  {

    //if(int(S[j])>65 && int(S[j])<90)
    if (S[j] >= 'A' && S[j] <= 'Z')
    {
      pointer = S[j] - 'A';
    }
    else if ((S[j] == 32))
    {
      pointer = 26;
    }
    else if (S[j] == '1')
    {
      pointer = 27;
    }
    // Serial.println(pointer,BIN);
    for (int m = 0; m < 5; m++)
    {
      arr[j * 5 + m]  =  pointer * 5 + m;
    }
  
  }

}




void increment()
{

  //cnt++;
  th1 += speed_ * time_rev / (1000.0 * 1000.0);
  th2 = th1 + 5.0 * text_len * angle_per_line;
  
  if (th1<w2+10)
  {
    speed_ = -speed_;
  }
  if (th2 >w1-10)
  {
    speed_ = -speed_;
  }
  
 // th1+=360;
 // th2+=360;

}

void loop()
{
  // rpm();
  if (flag == 1)
  {
    
    increment();
    flag = 0;
  
   /* if (th1 < 30)
    {
      th1 += 360.0;
      p = 1;
    }
    if (th2 < 30)
    {
      th2 += 360.0;
      q = 1;
    }
    if (th1 > 30 && th1 < 330)
    {
      if (th2 > 30 && th2 < 330)
      {
        if (th2 > th1)
        {

          *///Serial.println("true 1");// print_line(th1,th2); //normal printing condition

         if(th1>30 && th2<330)
         {
          for (int k = 0; k < 10; k++)
          {
            delayMicroseconds((th1 / 3600.0)*time_rev);
          }
          int i = 0;
          int j = 5 * text_len;
          print_line(i, j);
         }
   
        /*}
        else
        {
          //Serial.println("true 2");
          int i = (w1 - th1) / angle_per_line;
          int j = 5 * text_len - (th2 - w2) / angle_per_line;
          for(int k = 0;k<10;k++)
          {
            delayMicroseconds((w2/3600.0)*time_rev);
          }
          print_line(j, 5 * text_len);
          for (int k = 0; k < 10; k++)
          {
            delayMicroseconds(((th1 - th2) / 3600.0)*time_rev);
          }
          print_line(0,i); //print in case of full overlap
          //delay(th1-th2);
          //print_line(th1,w1);
        }
      }
      else
      {
        // Serial.println("true 3");
        int i = (w1-th1)/angle_per_line;
        for (int k = 0; k < 10; k++)
        {
          delayMicroseconds((th1/ 3600.0)*time_rev);
        }
        print_line(0,i);
  
       


        //print_line(th1,w1); //print in case of partial overlap,th2 belongs to dark zone
      }
    }
    else
    {
      if (th2 > 30 && th2 < 330) //print in case of th1 in dark zone
      {

        int i = (w2 - th1 + 360) / angle_per_line;
        int j = 5 * text_len;
        for (int k = 0; k < 10; k++)
        {
          delayMicroseconds((w2 / 3600.0)*time_rev);
        }
        print_line(i, j);
        //Serial.println(i);
        // Serial.println(j);

        //Serial.println("true 4");
        //Serial.print(th2);
        //print_line(w2,th2); //th2 not in dark zone
      }
      else if (th2 > 330 && th2 < th1) //both in dark zone print only light zone completely
      {
        //.println("true 5");
        for (int k = 0; k < 10; k++)
        {
          delayMicroseconds((w2 / 360.0)*time_rev);
        }
        int i = (w1 + 360 - th1) / angle_per_line;
        int j = 5 * text_len - (th2 - w2) / angle_per_line;
        print_line(i, j);
      }
      else
      {
        //Serial.println("true 6");
        //don't print
      }
     */


   /* }
    if (p == 1)
    {
      th1 = th1 - 360;
      p=0;
    }
    if (q == 1)
    {
      th2 = th2 - 360;
      q = 0;
    }
    cnt++;

   // EEPROM.put(cnt, th1);
   */




  }
  }






void rpm()
{
  Serial.println("true");
 
  time_old = time_now;
  time_now = micros();
  flag  = 1;
  time_rev = (time_now - time_old);
  rpm_val =  (60.0 * 1000.0 * 1000.0) / (time_now - time_old);
  
  
}


