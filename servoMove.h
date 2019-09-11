#include <Servo.h>

void servoMove(Servo _which, int _start, int _finish, long _time) {
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
    _which.write(_start + i * Direct);
    delay(DeltaTime);
  }
}