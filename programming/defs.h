/*******************
 defs.h
*******************/
#include <stdio.h>      // Needed for printf
#include <stdlib.h>     // Needed for malloc

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

typedef struct {
  int x,y;
} Point;

typedef struct Node {
  Point position;               // Nodes own x,y position on node map
  struct Node *n,*e,*s,*w;      // Pointers to neighbors vertical/horizontal
  struct Node *nw,*ne,*se,*sw;  // Pointers to neighbors diagonal
  struct Node *parent;          // Pointer to parent node
  unsigned char walls;          // Hex value for the 8 walls
  int movecost;                 // Steps needed to get here
} Nodes;

typedef struct {
  Point start;
  Point finish;
  Point size; // Size is amount of segments in the map
  //Point num_nodes; // number of nodes in the map
  unsigned char **segments; // 2D array of the map data from text file (user input)
  Nodes **node; // 2D array of each node's 8 neighbours represented in a hex value
} Maps;

typedef struct element {
    Nodes *node;      // Pointer to the map node
	struct element *next; // next element in queue
} Queue, Stack;
/*
typedef struct {
	int num;        // Number of elements in stack
	Queue *head;   // Queue start
} TopQueue;
*/
typedef struct {
  Point pos;
  Maps map;
  Queue *unchecked; // Head of queue for unchecked nodes
  Queue *checked; // Head of stack for checked nodes
} Robot;




/*
Function declarations
*/

// Robot
void go();
Robot *init_robot();

// Map
void map_load(Robot *robot);
void map_save(Robot *robot);
void map_check(Robot *robot);
void map_update(Robot *robot, char hex);
void node_map_load(Robot *robot); // node/map?
int robot_finished(Robot *robot);
void test_node_array(Robot *robot);

// Scan
unsigned char scan();

// Move
void move_next(Robot *robot);

// Priority queue
void pushQ(Queue **HoQ, Nodes *new_node);  // add element on the stack
void pop(Queue *tq); // removes element from top of stack
void printQueue(Queue *tq); //prints the elements in the stack
void emptyQueue(Queue *tq); // empties the stack using the pop operation
//void push(int queue, Nodes *node); // temp

// Pathfinding
void path_test(Robot *robot);
void path_set_neighbors(Robot *robot);
void path_calculate(Robot *robot);

// Debugging and print to screen
void robot_print(Robot *robot);


