/*******************
 defs.h
*******************/
#include <stdio.h>  // Needed for printf
#include <stdlib.h> // Needed for malloc
#include <string.h> // Needed for strtok

#define TRUE 1
#define FALSE 0
#define ROBOT_NAME "MazeRunner"
#define MAP_FILENAME "Maze1 (5x5).txt"

struct Point {
  int x,y;
};

struct Maps {
  struct Point start, finish, size;
  char **segments; // change all map segment chars to uint8_t ?
};

struct Robot {
  struct Point pos;
  struct Maps map;
  // IDEA We could setup other data we need such as:
  // struct Path
  // struct Motors
  // struct LEDs
  signed test:1;
};

// Function declarations
void go();
struct Robot *init_robot();
void map_load(struct Robot *robot);
void map_save(struct Robot *robot);
void map_segment_check(struct Robot *robot);
void robot_print(struct Robot *robot);
int finished(struct Robot *robot);
int str_split(char string[], char delimiters[], int match);
char scan();

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
  //path_calculate(robot);  // Calculate shortest path from msp start to finish

  // While robot has not reached the finish position
  do {
    robot_print(robot);

    // Scan surroundings at current position and compare with map segment
    // if scan and map differs update map segment save file and recalculate path
    map_segment_check(robot);

    // Get which direction to move to next from path: N-S-E-W?
    // depends on how path is stored. next move or next position and then convert to move?
    // anyway i think we need a function that tells motors to move either N-S-E-W
    // path_move(1);

    // Move to next position in path OR path_move(n)? fx +1 -1
    // move(robot);

    // Simulate move south east until finish is reached
    robot->pos.x++;
    robot->pos.y++;
  } while (!finished(robot));

  // While loop has ended so robot must be at finish coordinates
  printf("\nRobot current pos: %d.%d\n", robot->pos.x, robot->pos.y);
  printf("\n### Finishline reached ###\n\n");

  printf("Array size: x=%d y=%d", robot->map.size.x, robot->map.size.y);
}

// Initialize default settings for robot on startup
struct Robot *init_robot() {
  // Dynamically allocate robot struct in memory and return pointer
  struct Robot *robot = malloc(sizeof(struct Robot));
  // Return pointer to the data allocated in memory
  return robot;
}

void robot_print(struct Robot *robot) {
  printf("\n");
  printf("Robot current pos: %d,%d\n", robot->pos.x, robot->pos.y);
  printf("Check map segments[%d][%d] - Map says: %d scan() says: %d (hardcoded value)\n", robot->pos.x, robot->pos.y, robot->map.segments[robot->pos.x][robot->pos.y], scan());
}

// Returns TRUE if robot current position is identical to map finish position
int finished(struct Robot *robot) {

  // Compares robot current position with map finish position
  if(robot->pos.x == robot->map.finish.x && robot->pos.y == robot->map.finish.y) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// TODO Sensor scan
char scan() {
  return 0x0A; // Return scan result - in this case just a hardcoded value
}

// Scan surroundings at current position and compare with map segment
// If it differs update map then save map to file and recalculate path
void map_segment_check(struct Robot *robot) {
  char scan_segment = scan();
  char map_segment = robot->map.segments[robot->pos.x][robot->pos.y];

  // If scan and map segments are NOT identical
  if(scan_segment != map_segment) {
    // Update the segment in the map struct
    //
    // Remember to switch x and y to point to the right map segment
    // because like an n*m matrix arrays has cols first then rows
    //
    // NOTE A function could take x and y correct but is it worth
    // changing this simple oneline call for that? Well maybe (Daniel?)
    robot->map.segments[robot->pos.y][robot->pos.x] = scan_segment;

    // Save struct map data to file
    map_save(robot);

    // Map has changed so calculate shortest path again
    //TODO path_calculate(robot);
  }
}

// Write map data to text file
void map_save(struct Robot *robot) {
  char delimiters[] = " ";

  // Open the file in write mode
  FILE *myfile = fopen(MAP_FILENAME, "w");
  if (!myfile) {
    //return -1; // Error - compiler does not like -1 here
  }

  // Write map start and finish positions
  fprintf(myfile, "Start position: %d.%d\n", robot->map.start.x, robot->map.start.y);
  fprintf(
    myfile, "Finish position: %d.%d\n\n",
    robot->map.finish.x, robot->map.finish.y);  //two linebreaks for blank line
  fprintf(myfile, "Map segments:");         //no line break, gets written in for

  // Write map segments to text file
  for (int i = 0; i < robot->map.size.y; ++i) { // loop rows
    // Linebreak for each row
    fprintf(myfile, "%s", "\n");
    for (int j = 0; j < robot->map.size.x; ++j) { // loop cols
      // Write map segment value to file
      // %02X writes number as hex nn
      fprintf(myfile, "0x%02X", robot->map.segments[i][j]);
      // Write delimiter after map segment unless it is last segment on the row
      if(j + 1 < robot->map.size.x) {
        fprintf(myfile, "%s", delimiters);
      }
    }
  }
  fclose(myfile); // Close
}

// Reads map data from file and saves it in the map struct
void map_load(struct Robot *robot) {
  // Start and finish positions are read from file and saved in robot struct
  //
  // Map segment data is read and saved in the segments array in the map struct
  // This is done by reading line by line and splitting each line is into
  // pieces called tokens with strtok()
  //
  // In C an array and its size must be declared before we can store data in it
  // Since we do not know the needed array size at compile time we wait and
  // calculate the needed size at runtime instead
  //
  // The array size depends on the map size (rows and cols)
  // The maps rows and cols can be calculated by counting the lines in the file
  // and then count how many map segments each line holds
  //
  // For 5 lines of map segments (5 rows) and 5 pieces in each lines (6 cols)
  // a 5x5 array must be used to hold the values

  // Open file
  // *myfile is a pointer to a FILE object
  FILE *myfile = fopen(MAP_FILENAME, "r");

  // Count number of lines (linebreaks \n)
  int ch;
  int lines = 1; // Line counter starts at line 1

  do {
    // fgetc() gets the next character and advance the position indicator
    ch = fgetc(myfile);
    if (ch == '\n') lines++;
  } while (ch != EOF);

  // Set file position back to beginning of file
  rewind(myfile);

  // Read each line into an array
  char *contents[lines]; // Array of pointers one for each line
  size_t size = 0;
  for (int i = 0; i < lines; i++) {
    contents[i] = NULL;
    size = 0;
    // Read a single line from file and store it in contents array (reads until \n)
    // &contents is the address of the first character position where the input string will be stored
    // &size is the address that holds the size of the input buffer
    // or just google the getline() function
    getline(&contents[i], &size, myfile);
  }
  fclose(myfile);

  // Determine map rows and cols
  //
  // Map segments start at line 5 so subtract 4 from total lines = amount of rows
  // Length of last line with map segements +1 char for missing delimiter
  // divided by 5 since each segment and delimiter is 5 chars = amount of cols
  int rows = lines - 4;
  int cols = (strlen(contents[lines - 1]) + 1) / 5;

  char **array; // Pointer the array

  // Allocate memory for the 2D array with size of rows and cols
  // malloc() allocates single block of memory
  // calloc() allocates multiple blocks of memory each of same size and sets all bytes to zero
  array = malloc(rows * sizeof(char*));
  for(int i = 0; i < rows; i++) array[i] = calloc(cols, sizeof(char));

  // Store the pointer to the 2D array in map struct
  // Data can now be written to the allocated array through the struct
  robot->map.segments = array;

  // Save map size (rows and cols) in struct
  robot->map.size.y = rows;
  robot->map.size.x = cols;

  // Save map start and finish positions
  char delimiters[] = " .";
  robot->map.start.x = str_split(contents[0], delimiters, 2);
  robot->map.start.y = str_split(contents[0], delimiters, 3);
  robot->map.finish.x = str_split(contents[1], delimiters, 2);
  robot->map.finish.y = str_split(contents[1], delimiters, 3);

  // Set robot current position to map start position
  robot->pos.x = robot->map.start.x;
  robot->pos.y = robot->map.start.y;

  // Save map segments
  int skip_lines = 4; // Map segments start on line 5 in file so skip 4 lines
  int j;
  char *token;

  // For each line of text split the map segments into individual
  // pieces/tokens by the delimiter and store value in the 2D array
  int i;
  for(i = 0; i < lines-skip_lines; i++) {
    j = 0; // Token counter
    token = strtok(contents[i+skip_lines], delimiters); // Get first token

    // While there are more tokens in string
    while(token != NULL) {
      // Store map segments in array in map struct
      robot->map.segments[i][j] = strtol(token, NULL, 0);
      //printf("array[%d][%d] = %s\n", i, j, token); // Uncomment for debugging
      j++;
      // Move to next token
      token = strtok(NULL, delimiters);
    }
  }
}

// Splits a string into pieces by the delimiters and returns piece n as an int
// Used for reading map start and finish positions from line of text from file
int str_split(char string[], char delimiters[], int piece) {
    char *p = strtok (string, delimiters);
    char *array[5];
    int i = 0;

    while (p != NULL) {
        array[i++] = p;
        p = strtok (NULL, delimiters);
    }

    // Convert string to integer before returning value
    return strtol(array[piece], NULL, 0);
}













/*
void move(char heading) {
  // Get which direction to move to next from path: N-S-E-W?
  // What does motor need? we just send eg. N or we send 8bit?
}

int hextobinary(char hex) {
  // convert 0x01 0x02 etc.. 0x80 to bits
  //0x01 = 0000 0001
  //0x02 = 0000 0010
}

// test this one - i skal gives som hex som alligevel er decimal tal 0x01 = 1
int bit(unsigned int hex, int i) {
    return (hex >> i) & 1;
}

// #define BIT(hex, i) ((hex >> i) & 1)

// binarytohex() needed?

// maybe define bit to binary? BIT1 = 00000001

// https://stackoverflow.com/questions/14005651/converting-hex-to-binary-and-storing-bits-in-an-array

char update_map_segment(void){
  char scan_a=scan();
  char scan_b=scan();
  char scan_c=scan();

  if scan_a=scan_b {return scan_a};
  if scan_a=scan_c {return scan_a};
  if scan_b=scan_c {return scan_b};
  return update_map_segment();
}

char calculate_movement(int x_0, int y_0, int x_1, int y_1) {
  char nibble_1 = x_0 - x_1;
  char nibble_2 = y_0 - y_1;
  char move_char;
  //TODO merge nibbles into move_char
  return move_char;
}

*/

// A*
//
// Pseudocode can be found on wikipedia
//
// Build list:
// 1x list for open nodes
// 1x list for closed nodes (CLOSED set contains nodes that have already been examined - initially empty)
// Each node also keeps a pointer to its parent node so that we can determine how it was found
// 1x struct for returning paths (one or more needed? array of structs??)
// For each node:
// parent
// gScore
// fScore
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
//
// Map is read and saved with the neighbours details already
// would be better if map was entered with 0's and 1's and near cells was read
// and converted into one 8bit hex as we have now an returned by a function
// char neighbours(pos)
// neighbours for a map coordinate eg. 1.1 could be 1101 1001 = 0xC9
//
// how will new map work? empty file? all 0's? filename?
// change filename to file with empty map, but still start and finish. Will that work?
// change char hex values to uint8_t or unsigned char
//
//
// *** Notes
//
// when recalculating path use current position and finish (not map start)
//
// start reading/working on pathfinding?
// map array can be traversed using size and positions can be looked up
