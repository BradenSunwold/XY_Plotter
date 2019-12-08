#include "XY_Plotter.h"
#include <Arduino.h>
#include <stdint.h>

XY_Plotter::XY_Plotter() {}

void XY_Plotter::init() {
  pinMode(sw_x, INPUT);
  pinMode(sw_y, INPUT);

  pinMode(pul_x, OUTPUT);
  pinMode(dir_x, OUTPUT);
  pinMode(en_x, OUTPUT);

  pinMode(pul_y, OUTPUT);
  pinMode(dir_y, OUTPUT);
  pinMode(en_y, OUTPUT);
}

// Steps either x stepper or y stepper
// if xy = 1 then x stepper will move, if xy = 2 then y stepper will move
void XY_Plotter::step(int xy, int steps, int rpm) {

  // delay calculation assuming controller set to 1/32 microstep
  // 1/32 microstep = 6400 steps per revolution
  int rpm_delay = rpm * 64;       // Steps per min calculation (multiplied by 64 instead 6400 to avoid overflow)
  rpm_delay = rpm_delay / 60;     // steps per second = delays per second
  rpm_delay = rpm_delay * 100;    // multiply by 100 (overflow handling)
  rpm_delay = 1 / rpm_delay;      // 1 second / X delays = delay
  rpm_delay = rpm_delay / 1000;   // convert to milli seconds
  rpm_delay = rpm_delay / 2;      // There are two delays per step

  // define variables to track if we want to move x or y
  int dir;
  int en;
  int pul;

  if (xy == 1) {
    dir = dir_x;
    en = en_x;
    pul = pul_x;
  } else {
    dir = dir_y;
    en = en_y;
    pul = pul_y;
  }

  if(steps > 0) {
    for (int i=0; i <= steps; i++) {
      digitalWrite(dir,LOW);
      digitalWrite(en,HIGH);
      digitalWrite(pul,HIGH);
      delay(rpm_delay);
      digitalWrite(pul,LOW);
      delay(rpm_delay);
    }
  } else {
    for (int i=0; i <= abs(steps); i++) {
      digitalWrite(dir,HIGH);
      digitalWrite(en,HIGH);
      digitalWrite(pul,HIGH);
      delay(rpm_delay);
      digitalWrite(pul,LOW);
      delay(rpm_delay);
    }
  }
}

// Send printer to home or (0, 0)
void XY_Plotter::sendHome() {
  while (digitalRead(sw_x) != 1 && digitalRead(sw_y) != 1) {
    while(digitalRead(sw_y) != 1) {
      step(2, -5, 1);   // step x until it is at 0
    }
    while(digitalRead(sw_x) != 1) {
      step(1, -5, 1);   // step y until it is at 0
    }
  }
}
