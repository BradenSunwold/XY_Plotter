#ifndef XY_Plotter_h
#define XY_Plotter_h

#include "Arduino.h"
//extern bool dir = true;     // Make direction variable external

#define sw_x      2 //Define pin for switch 1 (x switch)
#define sw_y      3 //Define pin for switch 2 (y switch)

// Define stepper motor x pins
#define pul_x      10  //define Pulse pin for x axis
#define dir_x      9  //define Direction pin for x axis
#define en_x       8  //define Enable Pin for x axis

// Define stepper motor y pins
#define pul_y      6  //define Pulse pin for y axis
#define dir_y      5  //define Direction pin for y axis
#define en_y       4  //define Enable Pin for y axis

// Define XY_plotter class
class XY_Plotter {
private:
public:
  XY_Plotter();
  void init();
  void step(int xy, int steps, int rpm);
  void sendHome();
};

#endif
