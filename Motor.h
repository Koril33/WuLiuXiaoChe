#ifndef _Motor_h_
#define _Motor_h_

#include "Arduino.h"

class Motor {
    public:
        Motor(int input1, int input2, int input3, int input4, int pwm1, int pwm2);
        void motorRun(int command);
    private:
        int _input1;
        int _input2;
        int _input3;
        int _input4;
        int _pwm1;
        int _pwm2;
};

#endif
