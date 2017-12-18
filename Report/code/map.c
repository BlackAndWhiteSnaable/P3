#include "defs.h"

/// Scan surroundings at current position and compare with map segment
void map_check(Robot *robot) {
  char scan_segment = scan();
  char map_segment =robot->map.node[robot->pos.x][robot->pos.y].walls;
  if(scan_segment != map_segment) {   //segment changed
    map_update(robot, scan_segment);
    map_save(robot);                  //save to file
    path_calculate(robot);            //recalculate
  }
}

/// Write map data to text file
void map_save(Robot *robot) {
  // Open the file in write mode
  FILE *myfile = fopen(MAP_FILENAME, "w");
  // Write map segments to text file
  for (int i = 0; i < robot->map.size.y; ++i) {   // loop rows
    for (int j = 0; j < robot->map.size.x; ++j) { // loop cols
      fprintf(myfile, "%c", robot->map.segments[i][j]);
    }
    if(i < robot->map.size.y - 1) {               //not last line
      fprintf(myfile, "\n");                      //ad linebreak
    }
  }
  fclose(myfile);                                 // Close file
}

///Reads user input file, stores map data in struct
void map_load(Robot *robot) {
  // Open file in read mode
  FILE *myfile = fopen(MAP_FILENAME, "r");

  // Count number of lines and characters
  int rows = 1;       // Counts newlines
  int cols = 0;       // Counts characters
  int c;              // Holds each character as it is read from file

  while ((c = fgetc(myfile)) != EOF) { // Read file characterwise
    if (c == '\n') {  // end of the line (linebreak)
      rows++;         // Count the line
      cols = 0;       // Reset character counter
    } else cols++;    // Count characters
  }
  rewind(myfile);     // reset file pointer

  unsigned char **array; // Pointer to array
  array = malloc(rows * sizeof(char*));
  for (int i=0; i<rows; i++) array[i] = calloc(cols, sizeof(char));
  // Store the pointer to the 2D array in map struct
  robot->map.segments = array;
  // Save map size (rows and cols) in struct
  robot->map.size.x = cols;
  robot->map.size.y = rows;
  // Fill map array with map data from file
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      c = fgetc(myfile);            // Read next character from file
      robot->map.segments[i][j] = c;// Store each character in array
      if (c == 'A') {               // found starting position
        robot->map.start.x = (j-1)/2;
        robot->map.start.y = (i-1)/2;
        printf("[INFO]\tStart position:  [%2d][%2d]\n",
              robot->map.start.x, robot->map.start.y);
      }
      if (c == 'B') {               // found finish position
        robot->map.finish.x = (j-1)/2;
        robot->map.finish.y = (i-1)/2;
        printf("[INFO]\tFinish position: [%2d][%2d]\n",
              robot->map.finish.x, robot->map.finish.y);
      }
    }
    fgetc(myfile);  // don't save newline
  }
  fclose(myfile);   // close file

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

/// loads a node map from the saved map
void node_map_load(Robot *robot) {
  // calculate and store the amount of nodes
  robot->map.nSize.x = (robot->map.size.x-1)/2;
  robot->map.nSize.y = (robot->map.size.y-1)/2;

  Nodes **array;  // Declare node array of correct size
  array = malloc(robot->map.nSize.x * sizeof(Nodes*));
  for(int i=0; i<robot->map.nSize.x; i++) {
    array[i] = malloc(robot->map.nSize.y * sizeof(Nodes));
  }
  robot->map.node = array;  // store array in struct
  //----------------------- Calculate Walls-----------------------//
  unsigned char hex;
  // loop through all nodes positions in the textmap
  for (int i=1; i<robot->map.size.y; i+=2) {
    for (int j=1; j<robot->map.size.x; j+=2) {
      // For each node check in 8 directions and build 8-bit value
      // # means a wall exists, space means a path exists
      hex = 0;    //reset for each node
      hex += (robot->map.segments[i-1][j+0] == '#') ? North : 0;
      hex += (robot->map.segments[i-0][j+1] == '#') ? East  : 0;
      hex += (robot->map.segments[i+1][j-0] == '#') ? South : 0;
      hex += (robot->map.segments[i-0][j-1] == '#') ? West  : 0;
      hex += (robot->map.segments[i-1][j+1] == '#') ? NorthEast : 0;
      hex += (robot->map.segments[i+1][j+1] == '#') ? SouthEast : 0;
      hex += (robot->map.segments[i+1][j-1] == '#') ? SouthWest : 0;
      hex += (robot->map.segments[i-1][j-1] == '#') ? NorthWest : 0;
      robot->map.node[(i-1)/2][(j-1)/2].walls = hex;  //save in struct
      // Save node position on node map
      robot->map.node[(i-1)/2][(j-1)/2].position.x = (i-1)/2;
      robot->map.node[(i-1)/2][(j-1)/2].position.y = (j-1)/2;
    }
  }
}

/// updates the map file at the current position to the given value
void map_update(Robot *robot, char hex) {

  // Convert node coordinate to map coordinate
  int i = robot->pos.y*2+1;
  int j = robot->pos.x*2+1;

  // Update all 8 neighbors according to the hex wall value
  robot->map.segments[i-1][j+0] = (hex & North) ? '#' : ' ';
  robot->map.segments[i-0][j+1] = (hex & East)  ? '#' : ' ';
  robot->map.segments[i+1][j-0] = (hex & South) ? '#' : ' ';
  robot->map.segments[i-0][j-1] = (hex & West)  ? '#' : ' ';
  robot->map.segments[i-1][j+1] = (hex & NorthEast) ? '#' : ' ';
  robot->map.segments[i+1][j+1] = (hex & SouthEast) ? '#' : ' ';
  robot->map.segments[i+1][j-1] = (hex & SouthWest) ? '#' : ' ';
  robot->map.segments[i-1][j-1] = (hex & NorthWest) ? '#' : ' ';

  // Map is now up to date, rebuild nodes based on the updated map
  free(robot->map.node);  // Free current nodes
  node_map_load(robot);   // Rebuild nodes
}
