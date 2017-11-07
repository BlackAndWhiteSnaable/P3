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
//void path_calculate(char map[5][5]);

/*******************
 main.c
*******************/

int main()
{
  char map[5][5] = {
    {0x06, 0x0C, 0x06, 0x0E, 0x0C},
    {0x05, 0x07, 0x0F, 0x0F, 0x0D},
    {0x05, 0x05, 0x01, 0x07, 0x0D},
    {0x05, 0x07, 0x0E, 0x0F, 0x0D},
    {0x01, 0x03, 0x0B, 0x0B, 0x09}
    /*
    {'A', 'A', 'A', 'A', 'A'},
    {'A', 'A', 'A', 'A', 'A'},
    {'A', 'A', 'A', 'A', 'A'},
    {'A', 'A', 'A', 'A', 'A'},
    {'A', 'A', 'A', 'A', 'A'}
    */
    /*
    {'1', '6', '3', '4', '5'},
    {'F', 'G', 'H', 'I', 'J'},
    {'K', 'L', 'M', 'N', 'O'},
    {'P', 'Q', 'R', 'S', 'T'},
    {'U', 'V', 'W', 'X', 'Y'}
    */
  };
  path_calculate(map, 0, 0, 1, 1);
  return 0;
}

void path_calculate(char map[][5], int startX, int startY, int stopX,  int stopY)
{
  printf("Inside path_calculate! \n");
  for (int i = 0; i<5;i++){
    for (int j = 0; j<5;j++){
      printf("0x%.2x ",map[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  //totally useless, but this prints a representation of a rectangular graph
  for (int i = 0; i<5;i++){
    for (int j = 0; j<5;j++){
      switch(map[i][j]) {
        case 0x06:
          printf("%c",218);
          break;
        case 0x0c:
          printf("%c",191);
          break;
        case 0x03:
          printf("%c",192);
          break;
        case 0x09:
          printf("%c",217);
          break;

        case 0x0B:
          printf("%c",193);
          break;
        case 0x0E:
          printf("%c",194);
          break;
        case 0x07:
          printf("%c",195);
          break;
        case 0x0A:
          printf("%c",196);
          break;
        case 0x0F:
          printf("%c",197);
          break;
        case 0x05:
          printf("%c",179);
          break;
        case 0x0D:
          printf("%c",180);
          break;

        default:
          printf(" ");
      }
    }
    printf("\n");
  }
 }
