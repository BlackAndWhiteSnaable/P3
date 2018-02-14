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

  }
}


void map_load(Robot *robot) {
/* Change to map load starts here */

  //------------------------------START MANUAL------------------------------//
  // Manually set map size
  const int rows = 7;       // Size of map (newlines)
  const int cols = 7;       // Size of map (characters)

  // Save map size (rows and cols) in struct
  robot->map.size.x = cols;
  robot->map.size.y = rows;

  //Manually set start position
  robot->map.start.x = 0;
  robot->map.start.x = 0;

  // Set robot current position to map start position
  robot->pos.x = robot->map.start.x;
  robot->pos.y = robot->map.start.y;

  //Manually set finish position
  robot->map.finish.x = 2;
  robot->map.finish.y = 2;

  // Map data
  strcpy(robot->map.segments[0],  "#######");
  strcpy(robot->map.segments[1],  "#A o o#");
  strcpy(robot->map.segments[2],  "## ####");
  strcpy(robot->map.segments[3],  "#o o o#");
  strcpy(robot->map.segments[4],  "## ####");
  strcpy(robot->map.segments[5],  "#o o B#");
  strcpy(robot->map.segments[6],  "#######");
  //-------------------------------END MANUAL-------------------------------//

  P1OUT ^= 0x01;
}


void node_map_load(Robot *robot) {
  int i=0,j=0;
  unsigned int ni,nj;
  // From the map size the amount of nodes in the map can be calculated
  // TODO save in node struct
  // TODO turn into bitshifts?
  robot->map.nSize.x = (robot->map.size.x-1)/2;
  robot->map.nSize.y = (robot->map.size.y-1)/2;

  // Declare node map of correct size
  Nodes **array;
  array = malloc(robot->map.nSize.x * sizeof(Nodes*));
  int stopi = robot->map.nSize.x;
  for(i=0 ; i<stopi; i++) {
    array[i] = malloc(robot->map.nSize.y * sizeof(Nodes));
  }

  // Store the pointer to the nodes in map struct
  // Data can now be written to the allocated array through the struct
  robot->map.node = array;

  // Build hex value that contains data about the walls surrounding each node
  unsigned char hex;

  // loop through all nodes positions in the map (avoid walls)
  for (i = (robot->map.size.y)-2; i>=1; i-=2) {
    for (j=(robot->map.size.x)-2; j>=1; j-=2) {
      //divide size to nSize
      ni = (i-1)/2;
      nj = (j-1)/2;
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
      robot->map.node[ni][nj].walls = hex;

      // Save nodes own x,y position on node map
      // Nodes position is calculated based on the position in segment map
      // Example: First node top left will have position 0,0 and so on
      // TODO make this bitshifts
      robot->map.node[ni][nj].position.x = ni;
      robot->map.node[ni][nj].position.y = nj;
    }
  }
  P1OUT ^= 0x01;
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

  P1OUT ^= 0x01;
}
