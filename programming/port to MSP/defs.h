/*******************
 defs.h
*******************/
#include <stdio.h>      // Needed for printf
#include <stdlib.h>     // Needed for malloc
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
  volatile unsigned int x,y;
} Point;

typedef struct Node {
  volatile Point position;               // Nodes own x,y position on node map
  volatile struct Node *n,*e,*s,*w;      // Pointers to neighbors vertical/horizontal
  volatile struct Node *ne,*se,*sw,*nw;  // Pointers to neighbors diagonal
  volatile struct Node *parent;          // Pointer to parent node
  volatile unsigned char walls;          // Hex value for the 8 walls
  volatile int movecost;                 // Steps needed to get here
} Nodes;

typedef struct {
  volatile Point start;
  volatile Point finish;
  volatile Point size;     // Size is amount of characters in the textfile
  volatile Point nSize;    //size of the nodemap
  volatile unsigned char **segments; // 2D array of the map data from text file (user input)
  volatile Nodes **node; // 2D array of each node's 8 neighbours represented in a hex value
} Maps;

typedef struct element {
  volatile Nodes *node;      // Pointer to the map node
  volatile struct element *next; // next element in queue
} Queue, Stack;

typedef struct move_element {
    volatile char movement;
    volatile struct move_element *next; // next element in queue
} MoveStack;

typedef struct {
  volatile Point pos;
  volatile Maps map;
  Queue *unchecked;    // Head of queue for unchecked nodes
  Stack *checked;      // Head of stack for checked nodes
  MoveStack *movement; //Head of stack for movement
} Robot;



/*
Function declarations
*/

// Robot
void go();
Robot *robot_init();

// Map
void map_load(volatile Robot *robot);
void map_save(volatile Robot *robot);
void map_check(volatile Robot *robot);
void map_update(volatile Robot *robot, volatile unsigned char hex);
void node_map_load(volatile Robot *robot); // node/map?
int robot_finished(volatile Robot *robot);
void test_node_array(volatile Robot *robot);

// Scan
unsigned char scan();

// Move
void move_next(volatile Robot *robot);
void push_move_stack(MoveStack **head, volatile unsigned char new_move);
unsigned char pop_move(volatile MoveStack **head);

// Priority queue and stack
void push_queue(Queue **head, volatile Nodes *new_node);  // add element on the stack
void push_stack(volatile Stack **head, volatile Nodes *new_node);
volatile Nodes *pop(volatile Queue **head); // removes element from top of queue or stack

// Pathfinding
void path_test(volatile Robot *robot);
void path_set_neighbors(volatile Robot *robot);
void path_calculate(volatile Robot *robot);
void path_calculate_movement(volatile Robot *robot);
