#include "defs.h"

// Scan surroundings at current position and compare with map segment
// If it differs, update map, then save map to file and recalculate path
void map_check(volatile Robot *robot) {
  volatile unsigned char scan_segment = scan();
  volatile unsigned char map_segment = robot->map.node[robot->pos.x][robot->pos.y].walls;

  // If scan and map segments are NOT identical
  if(scan_segment != map_segment) {
    // Update the segment at current position in the map struct
    map_update(robot, scan_segment);

  }
}


void map_load(volatile Robot *robot) {
/* Change to map load starts here */

  // Manually set map size
  volatile int rows = 11;       // Size of map (newlines)
  volatile int cols = 11;       // Size of map (characters)

  // Map data
  volatile char map[] = "###########"
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
  volatile unsigned char **array; // Pointer to array
  array = malloc(rows * sizeof(char*));
  volatile int i,j;
  for (i = 0; i < rows; i++) array[i] = calloc(cols, sizeof(char));

  // Store the pointer to the 2D array in map struct
  robot->map.segments = array;

  // Save map size (rows and cols) in struct
  robot->map.size.x = cols;
  robot->map.size.y = rows;

  volatile char c;              	// Holds each character as it is read
  volatile int c_count = 0;		// Character counter

  // Fill map array with map data from file
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      //c = fgetc(myfile);            // Read next character from file (changed to array!)

	  c = map[c_count]; 			// Read map character
	  c_count++;					// Advance to next character

      robot->map.segments[i][j] = c;    // Store each character in map array

      if (c == 'A') {       //TODO can we turn this into a bitshift?
        robot->map.start.x = (j-1)/2;
        robot->map.start.y = (i-1)/2;
      }

      if (c == 'B') {       //TODO this should also be a bitshift?
        robot->map.finish.x = (j-1)/2;
        robot->map.finish.y = (i-1)/2;
      }
    }
  }

  // Set robot current position to map start position
  robot->pos.x = robot->map.start.x;
  robot->pos.y = robot->map.start.y;
}


void node_map_load(volatile Robot *robot) {
  volatile unsigned int i,j;
  // From the map size the amount of nodes in the map can be calculated
  // TODO save in node struct
  // TODO turn into bitshifts?
  robot->map.nSize.x = (robot->map.size.x-1)/2;
  robot->map.nSize.y = (robot->map.size.y-1)/2;

  // Declare node map of correct size
  volatile Nodes **array;
  array = malloc(robot->map.nSize.x * sizeof(Nodes*));
  for(i=0; i<robot->map.nSize.x; i++) {
    array[i] = malloc(robot->map.nSize.y * sizeof(Nodes));
  }

  // Store the pointer to the nodes in map struct
  // Data can now be written to the allocated array through the struct
  robot->map.node = array;

  // Build hex value that contains data about the walls surrounding each node
  unsigned char hex;

  // loop through all nodes positions in the map (avoid walls)
  for (i=robot->map.size.y; i>1; i-=2) {
    for (j=robot->map.size.x; j>1; j-=2) {
      // For each node check walls in the 8 directions and build 8-bit value
      // # means the direction is closed by a wall, if no wall it is open
        //TODO this stuff looks neat, but takes forever
      hex = 0;
      hex += (robot->map.segments[i-1][j  ] == '#') ? North : 0;
      hex += (robot->map.segments[i  ][j+1] == '#') ? East : 0;
      hex += (robot->map.segments[i+1][j  ] == '#') ? South : 0;
      hex += (robot->map.segments[i  ][j-1] == '#') ? West : 0;
      hex += (robot->map.segments[i-1][j+1] == '#') ? NorthEast : 0;
      hex += (robot->map.segments[i+1][j+1] == '#') ? SouthEast : 0;
      hex += (robot->map.segments[i+1][j-1] == '#') ? SouthWest : 0;
      hex += (robot->map.segments[i-1][j-1] == '#') ? NorthWest : 0;

      // Save final 8-bit wall value
      robot->map.node[(i-1)/2][(j-1)/2].walls = hex;

      // Save nodes own x,y position on node map
      // Nodes position is calculated based on the position in segment map
      // Example: First node top left will have position 0,0 and so on
      // TODO make this bitshifts
      robot->map.node[(i-1)/2][(j-1)/2].position.x = (i-1)/2;
      robot->map.node[(i-1)/2][(j-1)/2].position.y = (j-1)/2;
    }
  }
  P1OUT ^= 0x01;
}

// Input for walls is a hex value eg. FF means walls all around
// Check the 8 individual hex values and update the correct map array values
//
// should update the node at the current position, which is the same node on map or node.map
void map_update(volatile Robot *robot, volatile unsigned char hex) {

  // Convert node coordinate to map coordinate
  volatile int i = robot->pos.y*2+1;
  volatile int j = robot->pos.x*2+1;

  // Update all 8 neighbors according to the hex wall value
  // Done by comparing bitwise each neighbor of the node to the hex wall value
  // Equal values puts a wall in the given direction by storing a '#'
  // Not equal stores a ' ' (space)
  robot->map.segments[i-1][j+0] = (hex & North) ? '#' : ' ';
  robot->map.segments[i-0][j+1] = (hex & East) ? '#' : ' ';
  robot->map.segments[i+1][j-0] = (hex & South) ? '#' : ' ';
  robot->map.segments[i-0][j-1] = (hex & West) ? '#' : ' ';
  robot->map.segments[i-1][j+1] = (hex & NorthEast) ? '#' : ' ';
  robot->map.segments[i+1][j+1] = (hex & SouthEast) ? '#' : ' ';
  robot->map.segments[i+1][j-1] = (hex & SouthWest) ? '#' : ' ';
  robot->map.segments[i-1][j-1] = (hex & NorthWest) ? '#' : ' ';

  // Map is now up to date, so rebuild nodes based on the updated map
  free(robot->map.node); // Free current nodes
  node_map_load(robot); // Rebuild nodes
}


//[DEV] prints every element from a Node
void map_print_node(volatile Nodes *node){
  int ownX, ownY;
  int parX, parY;
  char move=0;

  ownX = node->position.x; ownY = node->position.y;
  if (node->parent){
    parX = node->parent->position.x;
    parY = node->parent->position.y;
  }

  if (node->parent){
    //adds all movements together
    if (ownX<parX) move+=North;       //Something north
    if (ownY>parY) move+=East;       //Something east
    if (ownX>parX) move+=South;       //Something south
    if (ownY<parY) move+=West;       //Something west

    //checks for two movements
    if (((move!=North)&&(move!=East)&&(move!=South)&&(move!=West))){
      if (move==North+East) move=NorthEast;     //North and East
      else if (move==South+East) move=SouthEast;//South and East
      else if (move==South+West) move=SouthWest;//South and West
      else if (move==North+West) move=NorthWest;//North and West
    }
  }
}
