#include <Servo.h>
#include <RedBot.h>
RedBotSensor left_sen = RedBotSensor(A1); //Chân S1
//RedBotSensor left_sen1 = RedBotSensor(A2); //Chân S2
RedBotSensor center_sen = RedBotSensor(A3); //Chân S3
RedBotSensor right_sen = RedBotSensor(A5);//Chân S4
//RedBotSensor right_sen1 = RedBotSensor(A4);//Chân S5

int lineStandard = 100;
// mach cau H ( tu trai qua phai: day trang so 5, day xam so 10, day tim so 9, day xanh duong so 8 , day xanh la so  7, day vang dam so 6,)
//tren trai mach cau H gom: enA-in4-in3      con ben phai gom:enB-in2-in1    mach cau H hoat dong tu phai sang trai
byte in1 =7; 
byte in2 =8;
byte in3 =9;
byte in4 =10;
int enA = 5;
int enB = 6;
int i,j;
int k,t;
int n,x;
#define trig 11  // khai bao chan 11 la chan trig cua sieu am
#define echo 12  // khai bao chan 12 la chan echo cua sieu am
int  spd=78;// giá trị băm xung=50% cong suat(191/255)
Servo servo1;
void setup() {
pinMode (trig, OUTPUT);
pinMode (echo, INPUT);
Serial.begin(9600);
servo1.attach(3);// Khai báo chân servo
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);

}
void  line_follow(){
 
 if(left_sen.read()>lineStandard && center_sen.read()<lineStandard && right_sen.read()>lineStandard){
   motor_forw();
 }else if(left_sen.read()<lineStandard ){
   motor_right();
 }
 else if( right_sen.read()<lineStandard){
   motor_left();
 }
 else if( right_sen.read()<lineStandard && center_sen.read()<lineStandard){
   Stop();
   delay(1000);
   motor_left();
   delay(1000);
 
 }else if(left_sen.read()<lineStandard && center_sen.read()<lineStandard){
   Stop();
   delay(1000);
   motor_right();
   delay(1000);
 }
 
 else if(left_sen.read()<lineStandard && center_sen.read()<lineStandard && right_sen.read()<lineStandard){
   Stop;
  // delay(1000);
 }
 
 
}

// moto:  di lui la HIGH-LOW, di thuan la LOW-HIGH, di thang la LOW-LOW 
void motor_forw() // chương trình con cho xe chay tới
{
analogWrite(enA,spd);
analogWrite(enB,spd);
digitalWrite(in1,HIGH);//motor bên trái chạy tới
digitalWrite(in3,HIGH);// motor bên phải chạy tới
//delay(1000);
digitalWrite(in2,LOW);
digitalWrite(in4,LOW);
//delay(1000);
}
void motor_back()// chương trình con robot chạy lùi
{
analogWrite(enA,65);
analogWrite(enB,65);
digitalWrite(in2,HIGH);
digitalWrite(in4,HIGH);
//delay(1000);
digitalWrite(in1,LOW);
digitalWrite(in3,LOW);
//delay(1000);
}
void motor_left()
{
analogWrite(enA,70);
analogWrite(enB,80);
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
//delay(5000);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
//delay(5000);
}
void motor_right()
{
analogWrite(enA,spd);
analogWrite(enB,spd);
digitalWrite(in3,HIGH);
digitalWrite(in1,LOW);
//delay(5000);
digitalWrite(in2,LOW);
digitalWrite(in4,LOW);
//delay(5000);
}
void motor_tack()
{
analogWrite(enA,spd);
analogWrite(enB,spd);
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
//delay(1000);
}
void Stop()
{
analogWrite(enA,0);
analogWrite(enB,0);
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
//delay(1000);
}

int distance() // do khoang cach vat can,khong hieu hoi thay
{  
   int dir;
   int time;
   digitalWrite(trig,LOW);
   delayMicroseconds(2);
   digitalWrite(trig,HIGH);
   delayMicroseconds(5);
   digitalWrite(trig,LOW);
   time =pulseIn(echo,HIGH); 
   dir =0.029*(time/2);
   dir = dir;
   if(dir < 255)
   {
   Serial.print(dir);
   Serial.println("cm");
   return dir;
   }
}
void servo_trai()
{
   for (t=90; t<=135; t=t+3) 
    {      
 
        servo1.write(t);    
        delay(10); // đợi 3 mili dây
    
    }  
    Serial.println("servo quay trai");
  
}
 
void servo_vetrai()
{
  for (i=135; i>=90; i=i-3) 
    {      

        servo1.write(i);     
        delay(10); // đợi 3 mili dây
    }
Serial.println("servo ve tu trai");

}
 void servo_phai()
 {
    for (k=90; k>=45; k=k-3)
    {
      
        servo1.write(k);
        delay(10); 
      
    }     
     Serial.println("servo qua phai"); 

 }
void servo_vephai()
{
for (j=45; j<=90; j=j+3)
    {
      
        servo1.write(j);
        delay(10);  
    }
Serial.println("servo ve tu phai");
}

void motor_robotic()
{
  while(distance() >= 15)// khoang cach lon hon 15cm
  {
  for (x=49; x<=132; x=x+3)//goc servo quay
   {
      Serial.println("servo ra ben trai");
        servo1.write(x);
        delay(5);
        if (distance() < 15)  break;
  while (distance() >= 15)
  {
    motor_forw();
    break;
   }
  }
  for (x=132; x>=49; x=x-3)// Nếu ta cố điều khiển servo vượt quá những giới hạn cơ học của nó , trục ra của động cơ sẽ đụng vật cản bên trong, dẫn đến các bánh răng bị mài mòn hay bị rơ. 
                           // Hiện tượng này kéo dài hơn vài giây sẽ làm bánh răng của động cơ bị phá hủy
  {
      Serial.println("servo ra ben phai");
        servo1.write(x);
        delay(5);
        if (distance() < 15)  break;
        while (distance() >= 15)
  {
      motor_forw();
    break;
   }
    }
  }
}
void motor_robot()
{
 while   (distance() < 15)
  {
    
  //motor_tack();
  motor_back();
 // delay(5);
 // motor_tack();
  servo_trai();
  delay(200);
  Serial.println("luu vao ROM 2 thong so nay:");
  float b = (distance());// lay gia tri khoang cach vat ben trai gan vao b
  delay(20);
  servo_vetrai();
  servo_phai();
   delay(200);
  Serial.println("luu vao ROM 3 thong so nay:");
  int c = (distance());  //lay gia tri khoang cach vat can ben phai gan vao c
  delay(20);
  servo_vephai();
  
    if (b > 15 &&  c > 15 ) 
    {
   
    motor_back();
    //delay(5);
    //motor_right();
    motor_forw();
    //delay(100);
    
    }
    else if (b > 15 && c < 15)
    {
     
    motor_back();
    //delay(5);
    motor_left();
    //delay(500);
    }
    else if (b < 15 && c > 15 )
    {
   
    motor_back();
    //delay(5);
    motor_right();
    delay(500);
    }
    else if (b < 15 && c < 15  )
    {
    
    motor_back();
    //delay(5);
    //motor_tack();
    //motor_forw();
    //delay(500);
    motor_right();
    delay(500);
  }
 

break;
  }
}

void loop() {
 if((left_sen.read()<lineStandard||right_sen.read()<lineStandard||center_sen.read()<lineStandard)&& distance()> 15 ){
     line_follow();
 }
 
 if((left_sen.read()>lineStandard&&right_sen.read()>lineStandard&&center_sen.read()>lineStandard)&&(distance()<=15)){
         Stop();
         delay(2000);
         motor_robotic();
         motor_robot();
 }
 if(left_sen.read()>lineStandard && center_sen.read()>lineStandard && right_sen.read()>lineStandard){
   motor_forw();
   if(left_sen.read()<lineStandard||right_sen.read()<lineStandard||center_sen.read()<lineStandard ){
     Stop();
     delay(1000);
     line_follow();
 }
   
  // delay(1000);
 } 
}
