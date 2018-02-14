/*******************
 defs.h
*******************/
#include <stdio.h>      // Needed for printf
#include <stdlib.h>     // Needed for malloc
#include <string.h>
#include <msp430.h>

#define TRUE 1
#define FALSE 0
#define ROBOT_NAME "MazeRunner"
#define MAP_FILENAME "testmap.txt"

#define North 0x01
#define East 0x02
#define South 0x04
#define West 0x08
#define NorthEast 0x10
#define SouthEast 0x20
#define SouthWest 0x40
#define NorthWest 0x80

typedef struct {
  unsigned int x,y;
} Point;

typedef struct Node {
  Point position;               // Nodes own x,y position on node map
  struct Node *n,*e,*s,*w;      // Pointers to neighbors vertical/horizontal
  struct Node *ne,*se,*sw,*nw;  // Pointers to neighbors diagonal
  struct Node *parent;          // Pointer to parent node
  unsigned char walls;          // Hex value for the 8 walls
  int movecost;                 // Steps needed to get here
} Nodes;

typedef struct {
  Point start;
  Point finish;
  Point size;     // Size is amount of characters in the textfile
  Point nSize;    //size of the nodemap
  char segments[11][11]; // 2D array of the map data from text file (user input)
  Nodes **node; // 2D array of each node's 8 neighbours represented in a hex value
} Maps;

typedef struct element {
  Nodes *node;      // Pointer to the map node
  struct element *next; // next element in queue
} Queue, Stack;

typedef struct move_element {
    unsigned char movement;
    struct move_element *next; // next element in queue
} MoveStack;

typedef struct {
  Point pos;
  Maps map;
  Queue *unchecked;    // Head of queue for unchecked nodes
  Stack *checked;      // Head of stack for checked nodes
  MoveStack *movement; // first element in movement stack
} Robot;



/*
Function declarations
*/

// Robot
void go();
Robot *robot_init();

// Map
void map_load(Robot *robot);
void map_save(Robot *robot);
void map_check(Robot *robot);
void map_update(Robot *robot, unsigned char hex);
void node_map_load(Robot *robot); // node/map?
int robot_finished(Robot *robot);
void test_node_array(Robot *robot);

// Scan
unsigned char scan();

// Move
void move_next(Robot *robot);
void push_move_stack(MoveStack **head, unsigned char new_move);
unsigned char pop_move(MoveStack **head);

// Priority queue and stack
void push_queue(Queue **head, Nodes *new_node);  // add element on the stack
void push_stack(Stack **head, Nodes *new_node);
Nodes *pop(Queue **head); // removes element from top of queue or stack

// Pathfinding
void path_test(Robot *robot);
void path_set_neighbors(Robot *robot);
void path_calculate(Robot *robot);
void path_calculate_movement(Robot *robot);
