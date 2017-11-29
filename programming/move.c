#include "defs.h"

void move_next(Robot *robot){
    // Simulate move south east until finish is reached
    robot->pos.x++;
    robot->pos.y++;
}

