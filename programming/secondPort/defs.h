/*******************
 defs.h
*******************/
#include <stdlib.h>     // Needed for malloc
#include <msp430.h>

#define TRUE 1
#define FALSE 0

#define North 0x01
#define East 0x02
#define South 0x04
#define West 0x08
#define NorthEast 0x10
#define SouthEast 0x20
#define SouthWest 0x40
#define NorthWest 0x80

#define Xsize 3
#define Ysize 3
#define numnodes 9

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
  //--Node based--//
  Point start;          // start position as node coordinates
  Point finish;         // finish position as node coordinates
  Point nSize;          // size of the nodemap
  Nodes node[Ysize][Xsize];// 2D array of nodes
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

/*--GLOBALS--
 *
 */
Robot robot;

char queue[numnodes];
int queue_count;

/*
Function declarations
*/

// Robot
void go(void);
void robot_init(void);

// Map
void map_load(void);
void map_save(void);
void map_check(void);
void map_update(unsigned char hex);
void node_map_load(void); // node/map?
int robot_finished(void);
void test_node_array(void);

// Scan
unsigned char scan(void);

// Move
void move_next(void);
void push_move_stack(MoveStack **head, unsigned char new_move);
unsigned char pop_move(MoveStack **head);

// Priority queue and stack
int push_queue(char coords);  // add element on the stack
void push_stack(Stack **head, Nodes *new_node);
char pop_queue(void); // removes element from top of queue

// Pathfinding
void path_test(void);
void path_set_neighbors(void);
void path_calculate(void);
void path_calculate_movement(void);
