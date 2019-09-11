#include "Motor.h"

#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define TURNRIGHT 3
#define TURNLEFT 4
#define TURNRIGHTLITTLE 5
#define TURNLEFTLITTLE 6

int i;
const int HeadTrace[8] = {29, 28, 27, 26, 25, 24, 23, 22}; //8路循迹
int HD[8];  //将循迹的数据存储到数组中                                            
Motor MyMotor(5, 6, 10, 11, 3, 9);  


void headTracing() {

  for(i = 0; i < 8; i++) {
    HD[i] = digitalRead(HeadTrace[i]);
  }

  /*前进的情况 */
  //1111 1111
  if(HD[0] && HD[1] && HD[2] && HD[3] && HD[4] && HD[5] && HD[6] && HD[7]) {
    MyMotor.motorRun(FORWARD);
  }
  
  //0000 0000
  else if(!HD[0] && !HD[1] && !HD[2] && !HD[3] && !HD[4] && !HD[5] && !HD[6] && !HD[7]) {
    MyMotor.motorRun(STOP);
  }

  //0001 1000
  else if(!HD[0] && !HD[1] && !HD[2] && HD[3] && HD[4] && !HD[5] && !HD[6] && !HD[7])
    MyMotor.motorRun(FORWARD);

  //0000 1000
  else if(!HD[0] && !HD[1] && !HD[2] && !HD[3] && HD[4] && !HD[5] && !HD[6] && !HD[7]) {
    MyMotor.motorRun(FORWARD);
  }

  //0001 0000
  else if(!HD[0] && !HD[1] && !HD[2] && HD[3] && !HD[4] && !HD[5] && !HD[6] && !HD[7]) {
    MyMotor.motorRun(FORWARD);
  }
    
  /*左转小弯的情况 */  
  //0011 1000
  else if(!HD[0] && !HD[1] && HD[2] && HD[3] && HD[4] && !HD[5] && !HD[6] && !HD[7]) 
    MyMotor.motorRun(TURNLEFTLITTLE);

  //0011 0000
  else if(!HD[0] && !HD[1] && HD[2] && HD[3] && !HD[4] && !HD[5] && !HD[6] && !HD[7]) 
    MyMotor.motorRun(TURNLEFTLITTLE);

  /*左转大弯的情况 */
  //0110 0000
  else if(!HD[0] && HD[1] && HD[2] && !HD[3] && !HD[4] && !HD[5] && !HD[6] && !HD[7]) {
    MyMotor.motorRun(TURNLEFT);
    delay(100);
  }

  //1100 0000
  else if(HD[0] && HD[1] && !HD[2] && !HD[3] && !HD[4] && !HD[5] && !HD[6] && !HD[7]) {
    MyMotor.motorRun(TURNLEFT);
    delay(150);
  }

  //0111 0000
  else if(!HD[0] && HD[1] && HD[2] && HD[3] && !HD[4] && !HD[5] && !HD[6] && !HD[7]) 
    MyMotor.motorRun(TURNLEFT);
  
  //1110 0000
  else if(!HD[0] && HD[1] && HD[2] && HD[3] && !HD[4] && !HD[5] && !HD[6] && !HD[7]) {
    MyMotor.motorRun(TURNLEFT);
    delay(150);
  }
  
  //1111 0000
  else if(!HD[0] && HD[1] && HD[2] && HD[3] && !HD[4] && !HD[5] && !HD[6] && !HD[7]) 
    MyMotor.motorRun(TURNLEFT);

  /*右转小弯的情况 */
  //0001 1100
    else if(!HD[0] && !HD[1] && !HD[2] && HD[3] && HD[4] && HD[5] && !HD[6] && !HD[7]) {
    MyMotor.motorRun(TURNRIGHTLITTLE);
  }

  //0000 1100
  else if(!HD[0] && !HD[1] && !HD[2] && !HD[3] && HD[4] && HD[5] && !HD[6] && !HD[7])
    MyMotor.motorRun(TURNRIGHTLITTLE);

  /*右转大弯的情况 */
  //0000 0110
  else if(!HD[0] && !HD[1] && !HD[2] && !HD[3] && !HD[4] && HD[5] && HD[6] && !HD[7])
    MyMotor.motorRun(TURNRIGHT);

  //0000 0011
  else if(!HD[0] && !HD[1] && !HD[2] && !HD[3] && !HD[4] && !HD[5] && HD[6] && HD[7])
    MyMotor.motorRun(TURNRIGHT);
  
  //0000 1110
  else if(!HD[0] && !HD[1] && !HD[2] && !HD[3] && HD[4] && HD[5] && HD[6] && !HD[7]) {
    MyMotor.motorRun(TURNRIGHT);
    delay(100);
  }

  //0000 0111
  else if(!HD[0] && !HD[1] && !HD[2] && !HD[3] && !HD[4] && HD[5] && HD[6] && HD[7]) {
    MyMotor.motorRun(TURNRIGHT);
    delay(100);
  }

  //0000 1111
  else if(!HD[0] && !HD[1] && !HD[2] && !HD[3] && HD[4] && HD[5] && HD[6] && HD[7]) {
    MyMotor.motorRun(TURNRIGHT);
    delay(200);
  } else {
    MyMotor.motorRun(FORWARD);
  }

}
