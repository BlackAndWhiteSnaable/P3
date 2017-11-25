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



struct Point {
  int x,y;
};

struct Maps {
  struct Point start;
  struct Point finish;
  struct Point size; // Size is amount of nodes in the map
  unsigned char **segments; // 2D array of the map data from text file (user input)
  unsigned char **nodes; // 2D array of each node's 8 neighbours represented in a hex value
};

typedef struct Robot {
  struct Point pos;
  struct Maps map;
  struct Nodes **node; // testing node struts in 2D array
  // IDEA We could setup other data we need such as:
  // struct Path
  // struct Motors
  // struct LEDs
} RobotType;

