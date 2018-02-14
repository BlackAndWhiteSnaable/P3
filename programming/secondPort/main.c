#include "defs.h"

/*******************
 main.c
*******************/
int main() {
  WDTCTL = WDTPW + WDTHOLD;
  go(); // Calls all other functions
  return 0;
}

/*******************
 functions.c
*******************/
// Executes robot behavior instructions
void go() {
  P1DIR = 0x01;
  P1OUT = 0x00;
  //----------------------------------SETUP ----------------------------------//
  Robot *robot;           // Declare empty pointer to a struct of type Robot
  robot = robot_init();   // Allocate structs and return the address to pointer

  map_load(robot);        // Load map data from file
  node_map_load(robot);   // load map into node array

  //---------------------------------RUNNING ---------------------------------//
  //path_calculate(robot);  //calculate path

  P1OUT = 0x01;
}
