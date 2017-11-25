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

// For each map node
// Declaring as 2D array keeps track of the elements [i][j]
//
// By using a 2D array we do not have a list with closed nodes, which means extra cycles?
// Unless pathfinding knows which nodes to ask for?
typedef struct {
  unsigned char hex;
  unsigned int status:1; // 1 bit unsigned int (bool) 0/1 indicates open or closed
  unsigned int move1_cost;
  // parent
} NodesType;

typedef struct  {
  int x,y;
} PointType;

typedef struct{
  PointType start;
  PointType finish;
  PointType size; // Size is amount of nodes in the map
  unsigned char **segments; // 2D array of the map data from text file (user input)
  unsigned char **nodes; // 2D array of each node's 8 neighbours represented in a hex value
} MapsType;

typedef struct{
  PointType pos;
  MapsType map;
  NodesType **node; // testing node struts in 2D array
  // IDEA We could setup other data we need such as:
  // struct Path
  // struct Motors
  // struct LEDs
} RobotType;


// Function declarations
void go();
void node_map_load(RobotType *robot);
int robot_finished(RobotType *robot);
unsigned char scan();
void map_save(RobotType *robot);
void map_check(RobotType *robot);
void map_update(RobotType *robot, char hex);
void test_node_array(RobotType *robot);

void path_next_move(RobotType *robot);


RobotType *init_robot();
void robot_print(RobotType *robot);


//don't want to be moved to their own .h or .c files
void map_load(RobotType *robot);

