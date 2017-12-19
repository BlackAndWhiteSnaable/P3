#include "defs.h"

/// Returns TRUE if robot current position is identical to map finish position
int robot_finished(Robot *robot) {
  // Compares robot current position with map finish position
  if(robot->pos.x == robot->map.finish.x &&
    robot->pos.y == robot->map.finish.y) {
    return TRUE;
  }
  return FALSE;
}

/// Allocate robot struct in memory using malloc, store address in *robot pointer and return it
Robot *robot_init() {
  // Dynamically allocate robot struct in memory and return pointer
  Robot *robot = malloc(sizeof(Robot));

  // First queue and stack element must be initialized to NULL
  robot->unchecked = NULL;
  robot->checked = NULL;
  robot->movement = NULL;

  return robot;
}
