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
  int x,y;
} Point;

typedef struct Node {
  struct Node *n,*e,*s,*w;      // Pointers to neighbors vertical/horizontal
  struct Node *nw,*ne,*se,*sw;  // Pointers to neighbors diagonal
  struct Node *parent;          // Pointer to parent node
  unsigned char walls;          // Hex value for the 8 walls
  int movecost;                 // Steps needed to get here
  struct Node *next;            // Next node in the list
} Nodes;

typedef struct {
  Point start;
  Point finish;
  Point size; // Size is amount of nodes in the map
  unsigned char **segments; // 2D array of the map data from text file (user input)
  Nodes **node; // 2D array of each node's 8 neighbours represented in a hex value
} Maps;

typedef struct {
  Point pos;
  Maps map;
  // IDEA We could setup other data we need such as:
  // struct Path
  // struct Motors
  // struct LEDs
} Robot;


// Function declarations
void go();
void node_map_load(Robot *robot);
int robot_finished(Robot *robot);
unsigned char scan();
void map_save(Robot *robot);
void map_check(Robot *robot);
void map_update(Robot *robot, char hex);
void test_node_array(Robot *robot);

void move_next(Robot *robot);


Robot *init_robot();
void robot_print(Robot *robot);


//don't want to be moved to their own .h or .c files
void map_load(Robot *robot);

