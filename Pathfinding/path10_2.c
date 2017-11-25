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

//a simple point, consisting of two integers
struct Point {
  int x,y;
};

//a map, consisting of start, finish and size
//and two char arrays (segments & nodes)
struct Maps {
  struct Point start;
  struct Point finish;
  struct Point size; // Size is amount of nodes in the map
  unsigned char **segments; // 2D array of the map data from text file (user input)
  unsigned char **nodes; // 2D array of each node's 8 neighbours represented as a hex value
};

//TODO initialize
struct Path {
  struct Node *HoP;  //Head of Path
  //use char hex as movement instruction
  //use Point parent as nextInList
};

//the master struct, containing:
//  current position, map struct, node array
struct Robot {
  struct Point pos;   //current position?
  struct Maps map;
  //TODO next line seems redundant
  struct Node **node; // testing node structs in 2D array
  // IDEA We could setup other data we need such as:
  struct Path path;
  // struct Motors
};

// For each map node
// Declaring as 2D array keeps track of the elements [i][j]
struct Node {
  unsigned char hex;
  unsigned int status:1; // 1 bit unsigned int (bool) 0/1 indicates open or closed
  unsigned int move_cost; //how much does it cost to move here
  struct Point parent;  //saving the parent as a point (x & y)
  struct Point self;    //own coordinates (needed in pathfinding)
  struct Node *next;    //next in linked list   should default to NULL
};


// Function declarations
void go();
struct Robot *init_robot();
void map_load(struct Robot *robot);
void map_save(struct Robot *robot);
void map_check(struct Robot *robot);
void map_update(struct Robot *robot, char hex);

void node_map_load(struct Robot *robot);
void robot_print(struct Robot *robot);
int finished(struct Robot *robot);
unsigned char scan();

void path_calculate(struct Robot *robot);

void test_node_array(struct Robot *robot);

void move_next(struct Robot *robot);

/*******************
 main.c
*******************/
int main() {
  //really ugly, you can't see what's happening --Daniel
  go(); // Calls all other functions

  return 0;
}

/*******************
 functions.c
*******************/
// Executes robot behavior instructions
void go() {
  //1. this could be moved into a function --Daniel
  struct Robot *robot;    // Declare empty pointer to a struct of type Robot
  robot = init_robot();   // Allocate structs and return the address to pointer
  //1.

  map_load(robot);        // Load map data from file into structs and set current pos to map start pos

  //path_calculate(robot);  // Calculate shortest path from msp start to finish

  // While robot has not reached the finish position
  while (!finished(robot)) {
    //robot_print(robot);

    // Scan surroundings at current position and compare with map segment
    // if scan and map differs update map segment save file and recalculate path
    map_check(robot);

    // Move to next position
    move_next(robot);
  }

  // While loop has ended so robot must be at finish coordinates
  printf("\nRobot current pos: %d.%d\n", robot->pos.x, robot->pos.y);
  printf("### Finishline reached ###\n\n");

  //why is this in hex though? --Daniel
  printf("Map array size: %dx%d\n", robot->map.size.x, robot->map.size.y);
  printf("Node array size: %dx%d\n\n", (robot->map.size.x-1)/2, (robot->map.size.y-1)/2);

  /* This is only debug, and was annoying me --Daniel
  for (int i = 0; i < (robot->map.size.y-1)/2; ++i) { // loop rows
    for (int j = 0; j < (robot->map.size.x-1)/2; ++j) { // loop cols
      printf("Node %d.%d in map.nodes = 0x%02X\n", i, j, robot->map.nodes[i][j]);
    }
  }
  */


//  printf("\nThis is a test: %i\n", /*robot->map.nodes[0][0]); */node(0,0)); // testing interesting declaration

  test_node_array(robot);
//  printf("\nrobot->node[0][0]: hex=0x%02X, status=%d, move cost=%d\n", robot->node[0][0].hex, robot->node[0][0].status, robot->node[0][0].move_cost);
//  printf("robot->node[1][0]: hex=0x%02X, status=%d, move cost=%d\n", robot->node[1][0].hex, robot->node[1][0].status, robot->node[1][0].move_cost);
//  printf("robot->node[2][0]: hex=0x%02X, status=%d, move cost=%d\n", robot->node[2][0].hex, robot->node[2][0].status, robot->node[2][0].move_cost);
}

//should fetch the next movement from the movement stack
//TODO implement
void move_next(struct Robot *robot) {
  // Simulate move south east until finish is reached
  robot->pos.x++;
  robot->pos.y++;
}

// Initialize default settings for robot on startup
//a whole function for one line?
struct Robot *init_robot() {
  // Dynamically allocate robot struct in memory and return pointer
  struct Robot *robot = malloc(sizeof(struct Robot));

  //actually initialize the struct with values
  robot->map.finish.x=0;
  robot->map.finish.y=0;

  //2D array
  struct Node **nodes;
  nodes = (struct Node **)malloc(sizeof(struct Node *) * 5);
  for (int i = 0; i < 5; i++) {
      nodes[i] = (struct Node **)malloc(sizeof(struct Node) *5);
  }
  robot->map.nodes = nodes;

  //2D array
  //robot->map.segments

  robot->map.size.x=0;
  robot->map.size.y=0;

  robot->map.start.x=0;
  robot->map.start.y=0;

  //2D array
  //robot->node

  //TODO implement
  //robot->path.HoP = init_list();
  robot->pos.x=0;
  robot->pos.y=0;
  // Return pointer to the data allocated in memory
  return robot;
}


void test_node_array(struct Robot *robot) {
  // Allocating 2D array of Node structs
  // This can be done, once we know the size of the array (runtime)
  // The size will be known from map size
  struct Node **node; // Pointer to an array of Node structs


  // Example allocating 2D array with size 3x1
  node = (struct Node **)malloc(sizeof(struct Node *) * 3);
  for (int i = 0; i < 3; i++) {
    node[i] = (struct Node *)malloc(sizeof(struct Node) * 1);
  }

  // Store array adress in robot struct
  robot->node = node;

  // Setting some test values
  // access as nodes[x][y] - remember size is 3x1
  robot->node[0][0].hex = 10;
  robot->node[1][0].hex = 16;
  robot->node[2][0].hex = 128;

  robot->node[0][0].status = 0;
  robot->node[1][0].status = 1;
  robot->node[2][0].status = 0;

  robot->node[0][0].move_cost = 5;
  robot->node[1][0].move_cost = 10;
  robot->node[2][0].move_cost = 20;
}

//prints information about the current position
void robot_print(struct Robot *robot) {
  printf("\n");
  printf("Robot current pos: %d,%d\n", robot->pos.x, robot->pos.y);
  printf("Check map segments[%d][%d] - Map says: 0x%02X scan() says: 0x%02X (hardcoded)\n", robot->pos.x, robot->pos.y, robot->map.nodes[robot->pos.x][robot->pos.y], scan());
}

// Returns TRUE if robot current position is identical to map finish position
int finished(struct Robot *robot) {
  // Compares robot current position with map finish position
  if(!(robot->pos.x == robot->map.finish.x &&
    robot->pos.y == robot->map.finish.y)) {
    return FALSE;
  }
  return TRUE;
}

// TODO Sensor scan
unsigned char scan() {
  return 0x5F; // Return scan result - in this case just a hardcoded value
}

// Scan surroundings at current position and compare with map segment
// If it differs, update map, then save map to file and recalculate path
void map_check(struct Robot *robot) {
  char scan_segment = scan();
  char map_segment = robot->map.segments[robot->pos.x][robot->pos.y];

  // If scan and map segments are NOT identical
  if(scan_segment != map_segment) {
    // Update the segment at current position in the map struct
    map_update(robot, scan_segment);

    // Save struct map data to file
    map_save(robot);

    // Map has changed so calculate shortest path again
    //path_calculate(robot);
  }
}

// Write map data to text file
void map_save(struct Robot *robot) {

  // Open the file in write mode
  FILE *myfile = fopen(MAP_FILENAME, "w");
  if (!myfile) {
    //return -1; // Error - compiler does not like -1 here
  }

  // Write map segments to text file
  for (int i = 0; i < robot->map.size.y; ++i) { // loop rows
    for (int j = 0; j < robot->map.size.x; ++j) { // loop cols
      // Write map segment value to file
      fprintf(myfile, "%c", robot->map.segments[i][j]);
    }
    // Add a linebreak after each line, except the last line
    if(i < robot->map.size.y - 1) {
      fprintf(myfile, "\n");
    }
  }
  fclose(myfile); // Close
}

// Load map fata from a text file
void map_load(struct Robot *robot) {
  // for first 2 lines all characters into an array = string (skip for now)
  //
  // for map segments read character by character into array (forget size and malloc to begin with?)
  // where 1st character is stored in [0][0] next in [0][1] and so on
  // first character on next line in [1][0]
  //
  // when that is stored then we can always print out that map again
  // first node/position will be at 1,1 next at 1,4

  // Open file
  // *myfile is a pointer to a FILE object
  FILE *myfile = fopen(MAP_FILENAME, "r");

  // Count number of lines and number of characters per line (last line)
  //
  // Reading the file twice is seems like a good method for now,
  // it is quick for small files and does not take up unnescesarry memory.
  //
  // Other options could be to call malloc/realloc for each character
  // or to have a buffer large enough to hold map data of any size.
  int rows = 1;       // Counts newlines, 1 because last line has no \n
                      //except it should --Daniel
  int cols = 0;       // Counts characters in each line
  int c;              // Holds each character as it is read from file

  while ((c = fgetc(myfile)) != EOF) { // Read file character by character
    if (c == '\n') {
      rows++;       // Count the line
      cols = 0;     // Reset character counter
    } else {
      cols++;       // Count each character, except newlines
    }
  }

  // Set file pointer position back to beginning of file
  rewind(myfile);

  // Allocate memory for the 2D array with size of rows and cols
  // malloc() allocates single block of memory
  // calloc() allocates multiple blocks of memory each of same size and sets all bytes to zero
  // sizeof() returns size in bytes of the object representation of type
  unsigned char **array; // Pointer to array
  array = malloc(rows * sizeof(char*));
  for (int i = 0; i < rows; i++) array[i] = calloc(cols, sizeof(char));

  // Store the pointer to the 2D array in map struct
  // Data can now be written to the allocated array through the struct
  robot->map.segments = array;

  // Save map size (rows and cols) in struct
  robot->map.size.x = cols;
  robot->map.size.y = rows;

  // Fill map struct with map data from file
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      c = fgetc(myfile);                // Read next character from file

      robot->map.segments[i][j] = c;    // Store each character in map array

      if (c == 'A') {
        robot->map.start.x = (j-1)/2;
        robot->map.start.y = (i-1)/2;
        printf("Start position: %d.%d\n", robot->map.start.x, robot->map.start.y);
      }

      if (c == 'B') {
        robot->map.finish.x = (j-1)/2;
        robot->map.finish.y = (i-1)/2;
        printf("Finish position: %d.%d\n", robot->map.finish.x, robot->map.finish.y);
      }
    }
    fgetc(myfile); // Skip last character in the line (newline)
  }
  fclose(myfile);

  // print the whole map from memory
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%c", robot->map.segments[i][j]);
    }
  printf("\n");
  }

  // Set robot current position to map start position
  robot->pos.x = robot->map.start.x;
  robot->pos.y = robot->map.start.y;

  node_map_load(robot);
}

void node_map_load(struct Robot *robot) {
  // For creating nodes, circle around each node to get the neighbours

  // From the map size the amount of nodes in the map can be calculated
  // TODO save in node struct
  int rows = (robot->map.size.y-1)/2;
  int cols = (robot->map.size.x-1)/2;

  // declare node map of correct size
  unsigned char **array;
  array = malloc(rows * sizeof(char*));
  for(int i=0; i<rows; i++) array[i] = malloc(cols * sizeof(char));

  // Store the pointer to the 2D array in map struct
  // Data can now be written to the allocated array through the struct
  robot->map.nodes = array;

  unsigned char hex;

  // loop through all nodes in map
  for (int i=1; i<robot->map.size.y; i+=2) {
    for (int j=1; j<robot->map.size.x; j+=2) {

      // For each node check the 8 neighbours and generate the total hex value
      hex = 0;
      hex += (robot->map.segments[i-1][j+0] == '#') ? N : 0;
      hex += (robot->map.segments[i-0][j+1] == '#') ? E : 0;
      hex += (robot->map.segments[i+1][j-0] == '#') ? S : 0;
      hex += (robot->map.segments[i-0][j-1] == '#') ? W : 0;
      hex += (robot->map.segments[i-1][j+1] == '#') ? NE : 0;
      hex += (robot->map.segments[i+1][j+1] == '#') ? SE : 0;
      hex += (robot->map.segments[i+1][j-1] == '#') ? SW : 0;
      hex += (robot->map.segments[i-1][j-1] == '#') ? NW : 0;

      robot->map.nodes[(i-1)/2][(j-1)/2] = hex;
    }
  }
}

// TODO TODO update a map segment (then call generate_node_map)
// input is a hex ie FF (walls all around)
// split it into the 8 individual hex values and update the correct map array values
//
// should update the node at the current position, which is the same node on map or node.map

void map_update(struct Robot *robot, char hex) {

  // Get robot current node position
  // Math converts node coordinate to map coordinate
  int i = robot->pos.y*2+1;
  int j = robot->pos.x*2+1;

  // Update all 8 neighbours corresponding to the hex value
  // Bitwise comparison for each neighbour in the hex value, 1 puts a wall in the given direction
  // store a '#' if not store a ' ' (space)
  robot->map.segments[i-1][j+0] = (hex & N) ? '#' : ' ';
  robot->map.segments[i-0][j+1] = (hex & E) ? '#' : ' ';
  robot->map.segments[i+1][j-0] = (hex & S) ? '#' : ' ';
  robot->map.segments[i-0][j-1] = (hex & W) ? '#' : ' ';
  robot->map.segments[i-1][j+1] = (hex & NE) ? '#' : ' ';
  robot->map.segments[i+1][j+1] = (hex & SE) ? '#' : ' ';
  robot->map.segments[i+1][j-1] = (hex & SW) ? '#' : ' ';
  robot->map.segments[i-1][j-1] = (hex & NW) ? '#' : ' ';

  // Map has changed so update the node map
  free(robot->map.nodes); // TODO more free stuff all around
  node_map_load(robot);
}

void path_calculate(struct Robot *robot) {
  //TODO check if current node is finishline
  if (robot->path.HoP->self.x == robot->map.finish.x &&
      robot->path.HoP->self.y == robot->map.finish.y) return;
  printf("calculate more");
  //look at current node
  //evaluate neighbours
  //save costs
  //mark as finished
  //re-order nodes
}
