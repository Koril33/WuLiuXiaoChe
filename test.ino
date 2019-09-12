#include <Servo.h>
#include "Motor.h"
#include "headTracing.h"
#include <Adafruit_ssd1306syp.h>

/*******************
 * OLED的SDA和SCL引脚
*******************/
#define SDA_PIN 20
#define SCL_PIN 21


/*******************
 * 电机运行动作
*******************/
#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define TURNRIGHT 3
#define TURNLEFT 4
#define TURNRIGHTLITTLE 5
#define TURNLEFTLITTLE 6

/*******************
 * 机械臂储存在size为3的数组
 * Myservo[0]--大臂舵机
 * Myservo[1]--小臂舵机
 * Myservo[2]--底部转盘舵机
*******************/
#define bigServo 0
#define smallServo 1
#define buttomServo 2

Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);


const int SideTrace[2] = {35, 36};                            //侧边循迹，从前到后
const int RearTrace = 37;

//const int E18Pin = ;  避障

/*******************
 * 气泵吸盘由两部分组成
 * bigMotor--大马达
 * smallMotor--小马达
*******************/
const int bigMotor = 7;
const int smallMotor = 8;

/*******************
 * 机械臂舵机数组
*******************/
Servo MyServo[3];                                               
Servo platform;
int SideD[2];                                                  //车身侧边传感器数据
int RearD;

void setup() {

  Serial.begin(9600);

  display.initialize();
  
//  pinMode(E18Pin, INPUT);

/*******************
 * 初始化气泵的两个马达
*******************/
  pinMode(bigMotor, OUTPUT);
  pinMode(smallMotor, OUTPUT);

/*******************
 * 初始化红外传感器
*******************/
  for(i = 0; i < 8; i++) {
    pinMode(HeadTrace[i], INPUT);
  }

pinMode(RearTrace, INPUT);

  for(i = 0; i < 2; i++) {
    pinMode(SideTrace[i], INPUT);
  }

/*******************
 * 连接四个舵机和引脚
*******************/
  MyServo[bigServo].attach(50);
  MyServo[smallServo].attach(51);
  MyServo[buttomServo].attach(52);
  platform.attach(53);
  
/*******************
 * 初始化四个舵机角度
*******************/  
  MyServo[bigServo].write(80);
  MyServo[smallServo].write(180);
  MyServo[buttomServo].write(50);
  platform.write(110);
  
  oledShow();
  delay(3000);
  platform.write(170);
}

/*******************
 * OLED显示"Hello, world!"
*******************/
void oledShow()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello, world!");
  display.update();
}

/*******************
 * 吸气
*******************/
void inhale(){
  analogWrite(bigMotor, 250);
  analogWrite(smallMotor, 40);
}

/*******************
 * 放气
*******************/
void deflate() {
  analogWrite(bigMotor, 40);
  analogWrite(smallMotor, 250);  
}

/*******************
 * 机械臂抓取动作
*******************/
void armCatch() {
  servoMove(bigServo, 80, 120, 20);
  servoMove(smallServo, 180, 150, 20);
  inhale();
  delay(2000);
  servoMove(bigServo, 120, 80, 20);
  servoMove(smallServo, 150, 180, 20);

  servoMove(buttomServo, 50, 0, 20);
  delay(1000);
  deflate();
  servoMove(buttomServo, 0, 50, 20);
  
}

/*******************
 * 舵机函数
*******************/
void servoMove(int _which, int _start, int _finish, long _time) {
  static int Direct;
  static int Diff;
  static long DeltaTime;
  if (_start <= _finish)
    Direct = 1;
  else
    Direct = -1;
  Diff = abs(_finish - _start);
  
  DeltaTime = _time;
  for (int i = 0; i < Diff; i++)
  {
    MyServo[_which].write(_start + i * Direct);
    delay(DeltaTime);
  }
}

void loop() {

  headTracing();
  
  
  for(i = 0; i < 2; i++) {
    SideD[i] = digitalRead(SideTrace[i]);
  }
  RearD = digitalRead(RearTrace);
  
  if(SideD[0] && SideD[1]) {
      MyMotor.motorRun(STOP);
      delay(3000);
      armCatch();
      MyMotor.motorRun(FORWARD);
      delay(500);
   }
  /*
   if(SideD[0] && RearD) {
      MyMotor.motorRun(STOP);
      delay(3000);
      
      MyMotor.motorRun(FORWARD);
      delay(500);

      MyMotor.motorRun(STOP);
      delay(3000);
      
   }
  */ 

} 
