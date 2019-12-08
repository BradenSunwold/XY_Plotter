#include "XY_Plotter.h"

XY_Plotter plotter;   // Define instance of XY_Plotter class with printing area of 8.5 inch by 11 inch

void setup() {
  // put your setup code here, to run once:
  plotter.init();

  plotter.sendHome();
}

void loop() {
  // put your main code here, to run repeatedly:
}
