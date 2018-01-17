#include "defs.h"
#include <msp430.h>

/*******************
 main.c
*******************/
int main() {
  go(); // Calls all other functions
  return 0;
}

/*******************
 functions.c
*******************/
// Executes robot behavior instructions
void go() {
  //----------------------------------SETUP ----------------------------------//
  Robot *robot;           // Declare empty pointer to a struct of type Robot
  robot = robot_init();   // Allocate structs and return the address to pointer

  map_load(robot);        // Load map data from file
  node_map_load(robot);   // load map into node array

  //---------------------------------RUNNING ---------------------------------//
  path_calculate(robot);  //calculate path

  unsigned char stackmove;
  stackmove = pop_move(&robot->movement);

}
