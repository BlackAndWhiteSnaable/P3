#include "defs.h"

void path_next_move(RobotType *robot){
    // Simulate move south east until finish is reached
    robot->pos.x++;
    robot->pos.y++;
}

