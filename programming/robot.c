#include "defs.h"

void robot_print(Robot *robot) {
  printf("\n");
  printf("[INFO]\tRobot current pos: [%2d][%2d]\n", robot->pos.x, robot->pos.y);
  //printf("Check map segments[%d][%d] - Map says: 0x%02X scan() says: 0x%02X (hardcoded)\n",robot->pos.x, robot->pos.y, robot->map.node[robot->pos.x][robot->pos.y].walls, scan());
}

// Returns TRUE if robot current position is identical to map finish position
int robot_finished(Robot *robot) {
  // Compares robot current position with map finish position
  if(robot->pos.x == robot->map.finish.x &&
    robot->pos.y == robot->map.finish.y) {
    return TRUE;
  }
  return FALSE;
}

Robot *robot_init() {
  // Dynamically allocate robot struct in memory and return pointer
  Robot *robot = malloc(sizeof(Robot));

  // First queue and stack element must be initialized to NULL
  robot->unchecked = NULL;
  robot->checked = NULL;
  robot->movement = NULL;

  //TODO give values to everything, even if they are only 0   --Daniel
  return robot;
}
