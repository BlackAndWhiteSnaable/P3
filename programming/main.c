#include "defs.h"


/*******************
 main.c
*******************/
int main() {
  go(); // Calls all other functions
        /*TODO This is not what Daniel meant with "make it tidy", we just moved
        all the crap somewhere else   --Daniel*/
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
  //--------------------------------------------------------------------------//

  robot_print(robot);     //print the status of the robot

  //---------------------------------RUNNING ---------------------------------//
  path_calculate(robot);  //calculate path

  print_move_stack(robot->movement);

  /*
  // While robot has not reached the finish position
  while (!robot_finished(robot)) {
    robot_print(robot);

    // Scan surroundings at current position and compare with map segment
    // if scan and map differs update map segment save file and recalculate path
    map_check(robot);

    // Move to next position
    move_next(robot);

  }

  // While loop has ended so robot must be at finish coordinates
  printf("\nRobot current pos: %d.%d\n", robot->pos.x, robot->pos.y);
  printf("### Finishline reached ###\n\n");

  printf("Map array size: %dx%d\n", robot->map.size.x, robot->map.size.y);
  printf("Node array size: %dx%d\n\n", (robot->map.size.x-1)/2, (robot->map.size.y-1)/2);

  for (int i = 0; i < (robot->map.size.y-1)/2; ++i) { // loop rows
    for (int j = 0; j < (robot->map.size.x-1)/2; ++j) { // loop cols
      printf("Node in robot->map.node[%d][%d].walls = 0x%02X\n", i, j, robot->map.node[i][j].walls);
    }
  }
  */
}
