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
  struct Point start;
  struct Point finish;
  struct Point size;
  char **segments;
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
 path.h
*******************/

//proper way
//void path_calculate(struct Robot *robot);
//bodge for testing
void path_calculate(char **map);

/*******************
 main.c
*******************/

int main()
{
  struct Robot *robot;    // Declare empty pointer to a struct of type Robot
  robot = init_robot();   // Allocate structs and return the address to pointer
  path_calculate(robot);
  return 0;
}

// Initialize default settings for robot on startup
struct Robot *init_robot() {
  // Dynamically allocate robot struct in memory and return pointer
  struct Robot *robot = malloc(sizeof(struct Robot));
  // Return pointer to the data allocated in memory
  return robot;
}

void path_calculate(char **map)
{
  printf("Inside path_calculate! \n");
  printf("%c",map[0][1]);
}
