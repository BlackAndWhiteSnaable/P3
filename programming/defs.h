/*******************
 defs.h
*******************/
#include <stdio.h>  // Needed for printf
#include <stdlib.h> // Needed for malloc

#define TRUE 1
#define FALSE 0
#define ROBOT_NAME "MazeRunner"
#define MAP_FILENAME "testmap.txt"

#define N 0x01
#define E 0x02
#define S 0x04
#define W 0x08
#define NE 0x10
#define SE 0x20
#define SW 0x40
#define NW 0x80

#include "map.h"
#include "framework.h"
#include "path.h"
//#include "move.h"
//#include "scan.h"
