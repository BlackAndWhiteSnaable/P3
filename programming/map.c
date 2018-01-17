#include "defs.h"

// Scan surroundings at current position and compare with map segment
// If it differs, update map, then save map to file and recalculate path
void map_check(Robot *robot) {
  unsigned char scan_segment = scan();
  unsigned char map_segment = robot->map.node[robot->pos.x][robot->pos.y].walls;

  // If scan and map segments are NOT identical
  if(scan_segment != map_segment) {
    // Update the segment at current position in the map struct
    map_update(robot, scan_segment);

    // Save struct map data to file
    //map_save(robot);

    // Map has changed so calculate shortest path again
    //path_calculate(robot);
  }
}

// Write map data to text file
void map_save(Robot *robot) {

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


void map_load(Robot *robot) {
/*
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
      cols = 0;     // Reset character counter (only count on last line)
    } else {
      cols++;       // Count each character, except newlines
    }
  }

  // Set file pointer position back to beginning of file
  rewind(myfile);
*/

/* Change to map load starts here */

  // Manually set map size
  int rows = 11;       // Size of map (newlines)
  int cols = 11;       // Size of map (characters)

  // Map data
  char map[] =  "###########"
                "#A o o o o#"
                "## ###### #"
                "#o o o o o#"
                "######### #"
                "#o o o o o#"
                "# ####### #"
                "#o#o o#o o#"
                "# ## ###  #"
                "#o o#o B#o#"
                "###########";

  // Allocate memory for the 2D array with size of rows and cols
  // malloc() allocates single block of memory
  // calloc() allocates multiple blocks of memory each of same size and sets all bytes to zero
  // sizeof() returns size in bytes of the object representation of type
  unsigned char **array; // Pointer to array
  array = malloc(rows * sizeof(char*));
  for (int i = 0; i < rows; i++) array[i] = calloc(cols, sizeof(char));

  // Store the pointer to the 2D array in map struct
  robot->map.segments = array;

  // Save map size (rows and cols) in struct
  robot->map.size.x = cols;
  robot->map.size.y = rows;

  char c;              	// Holds each character as it is read
  int c_count = 0;		// Character counter

  // Fill map array with map data from file
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      //c = fgetc(myfile);            // Read next character from file (changed to array!)

	  c = map[c_count]; 			// Read map character
	  c_count++;					// Advance to next character

      robot->map.segments[i][j] = c;    // Store each character in map array

      if (c == 'A') {
        robot->map.start.x = (j-1)/2;
        robot->map.start.y = (i-1)/2;
        printf("[INFO]\tStart position:  [%2d][%2d]\n", robot->map.start.x, robot->map.start.y);
      }

      if (c == 'B') {
        robot->map.finish.x = (j-1)/2;
        robot->map.finish.y = (i-1)/2;
        printf("[INFO]\tFinish position: [%2d][%2d]\n", robot->map.finish.x, robot->map.finish.y);
      }
    }
    //fgetc(myfile); // Skip last character in each line (newline)
  }
  //fclose(myfile);

  for (int i = 0; i < rows; i++) {
    printf("[INFO]\t");
    for (int j = 0; j < cols; j++) {
      printf("%c", robot->map.segments[i][j]);
    }
  printf("\n");
  }

  // Set robot current position to map start position
  robot->pos.x = robot->map.start.x;
  robot->pos.y = robot->map.start.y;
}

// TODO change name to build_nodes?
void node_map_load(Robot *robot) {
  // From the map size the amount of nodes in the map can be calculated
  // TODO save in node struct
  robot->map.nSize.x = (robot->map.size.x-1)/2;
  robot->map.nSize.y = (robot->map.size.y-1)/2;

  // Declare node map of correct size
  Nodes **array;
  array = malloc(robot->map.nSize.x * sizeof(Nodes*));
  for(int i=0; i<robot->map.nSize.x; i++) {
    array[i] = malloc(robot->map.nSize.y * sizeof(Nodes));
  }

  // Store the pointer to the nodes in map struct
  // Data can now be written to the allocated array through the struct
  robot->map.node = array;

  // Build hex value that contains data about the walls surrounding each node
  unsigned char hex;

  // loop through all nodes positions in the map (avoid walls)
  for (int i=1; i<robot->map.size.y; i+=2) {
    for (int j=1; j<robot->map.size.x; j+=2) {
      // For each node check walls in the 8 directions and build 8-bit value
      // # means the direction is closed by a wall, if no wall it is open
      hex = 0;
      hex += (robot->map.segments[i-1][j+0] == '#') ? N : 0;
      hex += (robot->map.segments[i-0][j+1] == '#') ? E : 0;
      hex += (robot->map.segments[i+1][j-0] == '#') ? S : 0;
      hex += (robot->map.segments[i-0][j-1] == '#') ? W : 0;
      hex += (robot->map.segments[i-1][j+1] == '#') ? NE : 0;
      hex += (robot->map.segments[i+1][j+1] == '#') ? SE : 0;
      hex += (robot->map.segments[i+1][j-1] == '#') ? SW : 0;
      hex += (robot->map.segments[i-1][j-1] == '#') ? NW : 0;

      // Save final 8-bit wall value
      robot->map.node[(i-1)/2][(j-1)/2].walls = hex;

      // Save nodes own x,y position on node map
      // Nodes position is calculated based on the position in segment map
      // Example: First node top left will have position 0,0 and so on
      robot->map.node[(i-1)/2][(j-1)/2].position.x = (i-1)/2;
      robot->map.node[(i-1)/2][(j-1)/2].position.y = (j-1)/2;
    }
  }
}

// Input for walls is a hex value eg. FF means walls all around
// Check the 8 individual hex values and update the correct map array values
//
// should update the node at the current position, which is the same node on map or node.map
void map_update(Robot *robot, unsigned char hex) {

  // Convert node coordinate to map coordinate
  int i = robot->pos.y*2+1;
  int j = robot->pos.x*2+1;

  // Update all 8 neighbors according to the hex wall value
  // Done by comparing bitwise each neighbor of the node to the hex wall value
  // Equal values puts a wall in the given direction by storing a '#'
  // Not equal stores a ' ' (space)
  robot->map.segments[i-1][j+0] = (hex & N) ? '#' : ' ';
  robot->map.segments[i-0][j+1] = (hex & E) ? '#' : ' ';
  robot->map.segments[i+1][j-0] = (hex & S) ? '#' : ' ';
  robot->map.segments[i-0][j-1] = (hex & W) ? '#' : ' ';
  robot->map.segments[i-1][j+1] = (hex & NE) ? '#' : ' ';
  robot->map.segments[i+1][j+1] = (hex & SE) ? '#' : ' ';
  robot->map.segments[i+1][j-1] = (hex & SW) ? '#' : ' ';
  robot->map.segments[i-1][j-1] = (hex & NW) ? '#' : ' ';

  // Map is now up to date, so rebuild nodes based on the updated map
  free(robot->map.node); // Free current nodes
  node_map_load(robot); // Rebuild nodes
}

/*
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
*/

//[DEV] prints every element from a Node
void map_print_node(Nodes *node){
  int ownX, ownY;
  int parX, parY;
  char move=0;

  ownX = node->position.x; ownY = node->position.y;
  if (node->parent){
    parX = node->parent->position.x;
    parY = node->parent->position.y;
  }

  printf("[INFO]\tNode information [%2i][%2i]:\n",ownX, ownY);
  printf("[INFO]\tParent\t\tmovecost\tNeighbors\n");
  printf("[INFO]\t%p\t%i\t\t",node->parent,node->movecost);
  if (node->n) printf("N  0x%02x\n[INFO]\t\t\t\t\t",node->n->walls);
  if (node->e) printf("E  0x%02x\n[INFO]\t\t\t\t\t",node->e->walls);
  if (node->s) printf("S  0x%02x\n[INFO]\t\t\t\t\t",node->s->walls);
  if (node->w) printf("W  0x%02x\n[INFO]\t\t\t\t\t",node->w->walls);

  if (node->ne) printf("NE 0x%02x\n[INFO]\t\t\t\t\t",node->ne->walls);
  if (node->se) printf("SE 0x%02x\n[INFO]\t\t\t\t\t",node->se->walls);
  if (node->sw) printf("SW 0x%02x\n[INFO]\t\t\t\t\t",node->sw->walls);
  if (node->nw) printf("NW 0x%02x\n[INFO]\t\t\t\t\t",node->nw->walls);

  if (node->parent){
    printf("\n[INFO]\tParent is [%2i][%2i]\n",parX ,parY);
    printf("[INFO]\tMoving here from parent:\n");
    //adds all movements together
    if (ownX<parX) move+=N;       //Something north
    if (ownY>parY) move+=E;       //Something east
    if (ownX>parX) move+=S;       //Something south
    if (ownY<parY) move+=W;       //Something west

    //checks for two movements
    if (((move!=N)&&(move!=E)&&(move!=S)&&(move!=W))){
      if (move==N+E) move=NE;     //North and East
      else if (move==S+E) move=SE;//South and East
      else if (move==S+W) move=SW;//South and West
      else if (move==N+W) move=NW;//North and West
    }
    printf("[INFO]\t\t\t0x%02x\n\n",move);
  } else printf("\n[INFO]\tNode [%2i][%2i] has no parent\n\n",ownX ,ownY);
}

  // a 5x5 array must be used to hold the values

  // Count number of lines and number of characters per line (last line)
  // calloc() allocates multiple blocks of memory each of same size and sets all bytes to zero
  // sizeof() returns size in bytes of the object type
