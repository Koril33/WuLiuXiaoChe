#include "Arduino.h"
#include "Motor.h"

#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define TURNRIGHT 3
#define TURNLEFT 4
#define TURNRIGHTLITTLE 5
#define TURNLEFTLITTLE 6

Motor::Motor(int input1, int input2, int input3, int input4, int pwm1, int pwm2) {
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
    pinMode(input3, OUTPUT);
    pinMode(input4, OUTPUT);
    pinMode(pwm1, OUTPUT);
    pinMode(pwm2, OUTPUT);

    _input1 = input1;
    _input2 = input2;
    _input3 = input3;
    _input4 = input4;
    _pwm1 = pwm1;
    _pwm2 = pwm2;
}

void Motor::motorRun(int command) {
    switch(command) {
        case STOP:
        analogWrite(_pwm1, 0);
        analogWrite(_pwm2, 0);
        digitalWrite(_input1, LOW);
        digitalWrite(_input2, LOW);
        digitalWrite(_input3, LOW);
        digitalWrite(_input4, LOW);
        break;
        
        case TURNLEFT:
        analogWrite(_pwm1, 120);
        analogWrite(_pwm2, 120);
        digitalWrite(_input1, HIGH);
        digitalWrite(_input2, LOW);
        digitalWrite(_input3, LOW);
        digitalWrite(_input4, HIGH);
        break;
        
        case TURNLEFTLITTLE:
        analogWrite(_pwm1, 0);
        analogWrite(_pwm2, 120);
        digitalWrite(_input1, HIGH);
        digitalWrite(_input2, LOW);
        digitalWrite(_input3, LOW);
        digitalWrite(_input4, HIGH);
        break;

        case TURNRIGHT:
        analogWrite(_pwm1, 120);
        analogWrite(_pwm2, 120);
        digitalWrite(_input1, LOW);
        digitalWrite(_input2, HIGH);
        digitalWrite(_input3, HIGH);
        digitalWrite(_input4, LOW);
        break;

        case TURNRIGHTLITTLE:
        analogWrite(_pwm1, 120);
        analogWrite(_pwm2, 0);
        digitalWrite(_input1, LOW);
        digitalWrite(_input2, HIGH);
        digitalWrite(_input3, HIGH);
        digitalWrite(_input4, LOW);
        break;
        
        
        case FORWARD:
        analogWrite(_pwm1, 43);
        analogWrite(_pwm2, 51);
        digitalWrite(_input1, LOW);
        digitalWrite(_input2, HIGH);
        digitalWrite(_input3, LOW);
        digitalWrite(_input4, HIGH);
        break;

        case BACKWARD:
        analogWrite(_pwm1, 100);
        analogWrite(_pwm2, 100);
        digitalWrite(_input1, LOW);
        digitalWrite(_input2, HIGH);
        digitalWrite(_input3, HIGH);
        digitalWrite(_input4, LOW);
        break;            
    }
}
