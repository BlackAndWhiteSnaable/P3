#include "defs.h"

// For each map node
// Declaring as 2D array keeps track of the elements [i][j]
//
// By using a 2D array we do not have a list with closed nodes, which means extra cycles?
// Unless pathfinding knows which nodes to ask for?
struct Nodes {
  unsigned char hex;
  unsigned int status:1; // 1 bit unsigned int (bool) 0/1 indicates open or closed
  unsigned int move1_cost;
  // parent
};


// Function declarations
void go();
void node_map_load(struct Robot *robot);
int finished(struct Robot *robot);
unsigned char scan();
void map_save(struct Robot *robot);
void map_check(struct Robot *robot);
void map_update(struct Robot *robot, char hex);
void test_node_array(struct Robot *robot);

//don't want to be moved to their own .h or .c files
void map_load(struct Robot *robot);

/*******************
 main.c
*******************/
int main() {
  go(); // Calls all other functions

  return 0;
}

/*******************
 functions.c
*******************/
// Executes robot behavior instructions
void go() {
  struct Robot *robot;    // Declare empty pointer to a struct of type Robot
  robot = init_robot();   // Allocate structs and return the address to pointer

  map_load(robot);        // Load map data from file into structs and set current pos to map start pos
  node_map_load(robot);
  //path_calculate(robot);  // Calculate shortest path from msp start to finish

  // While robot has not reached the finish position
  while (!finished(robot)) {
    robot_print(robot);

    // Scan surroundings at current position and compare with map segment
    // if scan and map differs update map segment save file and recalculate path
    map_check(robot);

    // Move to next position
    // path_next_move(robot);

    // Simulate move south east until finish is reached
    robot->pos.x++;
    robot->pos.y++;

  }

  // While loop has ended so robot must be at finish coordinates
  printf("\nRobot current pos: %d.%d\n", robot->pos.x, robot->pos.y);
  printf("### Finishline reached ###\n\n");

  printf("Map array size: %dx%d\n", robot->map.size.x, robot->map.size.y);
  printf("Node array size: %dx%d\n\n", (robot->map.size.x-1)/2, (robot->map.size.y-1)/2);

  for (int i = 0; i < (robot->map.size.y-1)/2; ++i) { // loop rows
    for (int j = 0; j < (robot->map.size.x-1)/2; ++j) { // loop cols
      printf("Node %d.%d in map.nodes = 0x%02X\n", i, j, robot->map.nodes[i][j]);
    }
  }

  test_node_array(robot);
  printf("\nrobot->node[0][0]: hex=0x%02X, status=%d, move cost=%d\n", robot->node[0][0].hex, robot->node[0][0].status, robot->node[0][0].move1_cost);
  printf("robot->node[1][0]: hex=0x%02X, status=%d, move cost=%d\n", robot->node[1][0].hex, robot->node[1][0].status, robot->node[1][0].move1_cost);
  printf("robot->node[2][0]: hex=0x%02X, status=%d, move cost=%d\n", robot->node[2][0].hex, robot->node[2][0].status, robot->node[2][0].move1_cost);
}

// Initialize default settings for robot on startup
struct Robot *init_robot() {
  // Dynamically allocate robot struct in memory and return pointer
  struct Robot *robot = malloc(sizeof(struct Robot));
  // Return pointer to the data allocated in memory
  return robot;
}

void test_node_array(struct Robot *robot) {
  // Allocating 2D array of Node structs
  // This can be done, once we know the size of the array (runtime)
  // The size will be known from map size
  struct Nodes **node; // Pointer to an array of Nodes structs

  // Example allocating 2D array with size 3x1
  node = (struct Nodes **)malloc(sizeof(struct Nodes *) * 3);
  for (int i = 0; i < 3; i++) {
    node[i] = (struct Nodes *)malloc(sizeof(struct Nodes) * 1);
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

  robot->node[0][0].move1_cost = 5;
  robot->node[1][0].move1_cost = 10;
  robot->node[2][0].move1_cost = 20;
}

void robot_print(struct Robot *robot) {
  printf("\n");
  printf("Robot current pos: %d,%d\n", robot->pos.x, robot->pos.y);
  printf("Check map segments[%d][%d] - Map says: 0x%02X scan() says: 0x%02X (hardcoded)\n", robot->pos.x, robot->pos.y, robot->map.nodes[robot->pos.x][robot->pos.y], scan());
}

// Returns TRUE if robot current position is identical to map finish position
int finished(struct Robot *robot) {
  // Compares robot current position with map finish position
  if(robot->pos.x == robot->map.finish.x &&
    robot->pos.y == robot->map.finish.y) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// TODO Sensor scan
unsigned char scan() {
  return 0xFF; // Return scan result - in this case just a hardcoded value
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

// Reads map data from file and saves it in the map struct
  // Start and finish positions are read from file and saved in robot struct
  //
  // In C an array and its size must be declared before we can store data in it
  // Since we do not know the needed array size at compile time we wait and
  // calculate the needed size at runtime instead
  //
  // The array size depends on the map size (rows and cols)
  // The maps rows and cols can be calculated by counting the lines in the file
  // and by counting characters in each line
  //
  // For 5 lines of map segments (5 rows) and 5 characters in each line (5 cols)
  // a 5x5 array must be used to hold the values

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

  // printf
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%c", robot->map.segments[i][j]);
    }
  printf("\n");
  }

  // Set robot current position to map start position
  robot->pos.x = robot->map.start.x;
  robot->pos.y = robot->map.start.y;
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







// Read map into an array for processing to nodes, and for
// updating/displaying/saving to file
// For changes the map only need ONE node updated, node map also needs the
// correct of 8 neighbors updatedm and checking for map borders is painfull
//
// For creating nodes, circle around each node to get the neighbours
//
// For saving map from node (after a change to a node - sucks more nodes need update)
// if line < 3 and FIRST node print all neighbours
// if line < 3 and NOT first node print above/below and right side
// if line > 3 and FIRST node print all sides but the above
// if line > 3 and NOT first node print right and below
//
// line 3 could also be identified as first node line: node[i][j] where i = 0

/*

// <<<<<<<<<<<<<<<<<<<<<<

// 1. save map data in an array
// 2. >for each node in array<, lookup the 8 neighbours and if its a wall add the hex value to the node
// how to figure out each node pos (had that ealier)
// If there's a change, update map and regenerate node map


char hex[20][20];

// The 8 binary byte values in hex according to direction of neighbour wall
// Values for binary byte (0000 0000) where each bit represents a neighbour
// that is either moveable (0) or a wall (1)
char values[3][3] = {
  {0x10, 0x01, 0x20}, // NW, N, NE
  {0x08, 0x00, 0x02}, // W, Node, E
  {0x80, 0x04, 0x40}  // SW, S, SE
};


// Calculate which node the neighbour (character) that gets read belongs to
node_x = cols/3; // divide chars into groups of 3 -> 012=1 345=2 678=3
node_y = rows/3; // divide rows into groups of 3 -> 012=1 345=2 678=3

  //hex[rows/3][cols/3] += values[rows%3][cols%3];



//
// using lists (containers) for the open and closed nodes rather than a grid of nodes,
// and returning paths as self-contained objects (you can write a class or struct for that.
// https://www.gamedev.net/forums/topic/521928-a-star-a-pathfinding-in-c/
//
// Nodes are only necessary to indicate what tiles you've checked or still need to check,
// and how costly they are, as well as what their parent is
// (hint: the final node already contains your path: just follow it's chain of parents).
//
// instead of keeping x and y coordinates, you can use pointers to nodes instead.
// The same can be done for storing parents.
//
//
// *** Todos
// how will new map work? empty file? all 0's? filename?
// change filename to file with empty map, but still start and finish. Will that work?
// change char hex values to uint8_t or unsigned char
//
//
// *** Notes
// We do it differently because we can expect changes to the map
// All other examples of diekstra/A* don't expect to recalculate
// But why do it differently? Makes no sense
//
// The correct way would be to have Map_nodes to store all data for a node
// in a list, instead of having different node data multiple times (arrays)

IDEA for data structure:

Why is this better than iterating through a list?
We have the possibillity of being able to address any random element
In a list you typically want to add and remove elements.
We have a fixed amount of elements (a map size) unless we reroute which means
we delete (all?) node data and start over -> is it possible to update a node
neighbord instead, and the actual map (and save) instead of updating map, save, reload

-------------------------

The idea is to store all data about each node in a node struct.
This way we don't have node neighbours in one 2D array, node costs
node parents and open/closed in different 2D arrays. We just store it all in ONE place.
This also requires less data to be read into memory. (node map is only sligthly bigger than user map)

Like a linked list (structs) can hold different data types, so I just want to create an 2D array of node structs.
Each node (struct) should be accessable through map_node[i][j] instead of having a head and next pointers in linked list.

To access it we could write map_nodes[i][j]->somevar.
But by storing the adress of the 2D array in the Maps struct, we can still access all the node structs as
robot->node[i][i].neighbors (which would be a hex)
robot->node[i][i].cost (which would be a hex)

In theory this should work (at least in my head).

-------------------------


struct Maps {
  Struct Map_nodes **nodes; <-- add this to Map
};

// any data that
Struct Map_nodes {

}


A thing to test
having a pointer point to the 2D array pointer to get to a 2D array is that smart
why not just directly store the adress of a 2D array in a pointer

go from
**[pointer] -> *[pointer for 2d array adress]
to this
*[pointer] -> &[pointer for 2d array adress]

tested, it did not work hehe



Dashboard diodes (light for 1 sek?):
- Map change found
- Calculating path
- Show walls detected or possible directions to move
- Steps to goal?
*/
