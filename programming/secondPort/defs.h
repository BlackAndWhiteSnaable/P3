/*******************
 defs.h
*******************/
#include <stdlib.h>     // Needed for malloc
#include <msp430.h>

#define TRUE 1
#define FALSE 0

#define North 0x01
#define East  0x02
#define South 0x04
#define West  0x08

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

char stack[numnodes];
int stack_count;

char move_stack[numnodes];
int move_stack_count;

// hardcoded 3x3 map
char orig[3][3];
char map[3][3];
unsigned int mapc[3][3];
char mapp[3][3];
//positions in hex
char start;
char end;
char pos;
/*
Function declarations
*/
// Robot
void go(void);
char xy2hex(char x,char y);
char hex2x(char hex);
char hex2y(char hex);
void robot_init(void);

// Map
void map_hardcode(void);
void map_load(void);
void map_check(void);
void map_update(unsigned char hex);
void map_reset_parents(void);
void map_reset_cost(void);

// Scan
unsigned char scan(void);

// Move
void move_next(void);
void push_move_stack(char move);
char pop_move_stack(void);

// Priority queue and stack
void push_queue(char coords);  // add element on the stack
void push_stack(char coords);
char pop_queue(void); // removes element from top of queue
char pop_stack(void);   // pops element from stack

// Pathfinding
void path_test(void);
void path_set_neighbors(void); //TODO ?
void path_calculate(void);
void path_calculate_movement(void);
