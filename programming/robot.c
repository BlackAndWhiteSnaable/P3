#include "defs.h"

void robot_print(RobotType *robot) {
  printf("\n");
  printf("Robot current pos: %d,%d\n", robot->pos.x, robot->pos.y);
  printf("Check map segments[%d][%d] - Map says: 0x%02X scan() says: 0x%02X (hardcoded)\n", robot->pos.x, robot->pos.y, robot->map.nodes[robot->pos.x][robot->pos.y], scan());
}

// Returns TRUE if robot current position is identical to map finish position
int robot_finished(RobotType *robot) {
  // Compares robot current position with map finish position
  if(robot->pos.x == robot->map.finish.x &&
    robot->pos.y == robot->map.finish.y) {
    return TRUE;
  }
  return FALSE;
}
