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
  RobotType *robot;    // Declare empty pointer to a struct of type Robot
  robot = init_robot();   // Allocate structs and return the address to pointer

  map_load(robot);        // Load map data from file into structs and set current pos to map start pos
  node_map_load(robot);
  //path_calculate(robot);  // Calculate shortest path from msp start to finish

  // While robot has not reached the finish position
  while (!robot_finished(robot)) {
    robot_print(robot);

    // Scan surroundings at current position and compare with map segment
    // if scan and map differs update map segment save file and recalculate path
    map_check(robot);

    // Move to next position
    path_next_move(robot);

  }

  // While loop has ended so robot must be at finish coordinates
  printf("\nRobot current pos: %d.%d\n", robot->pos.x, robot->pos.y);
  printf("### Finishline reached ###\n\n");

  printf("Map array size: %dx%d\n", robot->map.size.x, robot->map.size.y);
  printf("Node array size: %dx%d\n\n", (robot->map.size.x-1)/2, (robot->map.size.y-1)/2);

  for (int i = 0; i < (robot->map.size.y-1)/2; ++i) { // loop rows
    for (int j = 0; j < (robot->map.size.x-1)/2; ++j) { // loop cols
      printf("Node %d.%d in map.nodes = 0x%02X\n", i, j, robot->map.nodes[i][j]);
    }
  }

/*  test_node_array(robot);
  printf("\nrobot->node[0][0]: hex=0x%02X, status=%d, move cost=%d\n", robot->node[0][0].hex, robot->node[0][0].status, robot->node[0][0].move1_cost);
  printf("robot->node[1][0]: hex=0x%02X, status=%d, move cost=%d\n", robot->node[1][0].hex, robot->node[1][0].status, robot->node[1][0].move1_cost);
  printf("robot->node[2][0]: hex=0x%02X, status=%d, move cost=%d\n", robot->node[2][0].hex, robot->node[2][0].status, robot->node[2][0].move1_cost);
  */
}

//TODO Initialize default settings for robot on startup
RobotType *init_robot() {
  // Dynamically allocate robot struct in memory and return pointer
  RobotType *robot = malloc(sizeof(RobotType));
  //TODO give values to everything, even if they are only 0   --Daniel
  return robot;   // Return pointer to the data allocated in memory
}
