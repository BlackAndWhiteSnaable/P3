/*******************
 defs.h
*******************/
#include <stdio.h>  // Needed for printf
#include <stdlib.h> // Needed for malloc
#include <string.h> // Needed for strtok

#define TRUE 1
#define FALSE 0
/*******************
 path.h
*******************/
//some defines to make life easier
#define COST_90 10  //1.0*10
#define COST_45 14  //1.4*10  then we don't need floats

#define N 1
#define E 2
#define S 4
#define W 8

#define NE 16
#define SE 32
#define SW 64
#define NW 128

//proper way
//void path_calculate(struct Robot *robot);

//bodge for testing
//just look how many variables I'm moving around
void path_calculate(unsigned char map[][5], int cost[][5], char [][5], int startX, int startY, int stopX,  int stopY);

void printNode(char node);

int path_only_x(unsigned char coordinate);
int path_only_y(unsigned char coordinate);

/*******************
 main.c
*******************/

struct PathFInding {
  //cost map
  //parent map
  //list unchecked
  //list checked
  //wall map
};

int main()
{
  //dummy map, several tests in comments
  unsigned char map[5][5] = {
    {0x06, 0x0C, 0x06, 0x0E, 0x0C},
    {0x05, 0x07, 0x0F, 0x2F, 0x4D},
    {0x05, 0x05, 0x01, 0x17, 0x8D},
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
  //dummy cost, should also be in robot struct
  //initialized to be higher than ever possible on 5x5
  //TODO should maybe be initialized to 0
  int cost[5][5] = {
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  };

  //dummy parent
  //values here shouldn't matter, as they should get overwritten without being checked
  char parent[5][5] = {
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  };
  //should be called with values read from the input
  //or values from inside robot struct
  //or basically with the struct*
  path_calculate(map, cost, parent, 4, 1, 4, 4);
  return 0;

}

//evaluates a node and prints all interesting values about it (for now)
//map is the map (DUH), cost the array of movement cost
//x and y are the current position,
char path_evaluate_node(unsigned char map[][5], int cost[][5], char parent[][5], int x, int y, int finalX, int finalY)
{
  if (x==finalX && y==finalY) return (char)0xFF;    //checking whether we reached the destination
  if (cost[x][y]==255) cost[x][y]=0;                //should only happen when evaluating the starting node
  int nextX,nextY;    //where to go next, gets calculated from where we are
  char next;
  char current = (((char)x)<4)+(char)x;       //mash x and y in here
  printf("Position (%i,%i) looks like this: \n\t",x,y);
  printNode(map[x][y]);
  printf("\nHas this value: \n\t0x%.2x \n",map[x][y]);
  printf("Possible directions to move and connected Neighbours are:\n");
  //doesn't only print the connected neighbours, but also updates their cost
  //and should also update the parent
  if (map[x][y]&N)
  {
    printf("\tN\t");
    //if moving north, x decreases and y stays
    nextX = x-1;
    nextY = y;
    printf("\t(%i,%i)\n",nextX,nextY);
    if (cost[nextX][nextY]==255)
    //compares the currently stored cost with the newly calculated
    if (cost[x][y]+COST_90 < cost[nextX][nextY] || cost[nextX][nextY]==255)
    {
      cost[nextX][nextY] = cost[x][y]+COST_90;
      parent[nextX][nextY] = current;
    }
  }
  if (map[x][y]&E)
  {
    printf("\tE\t");
    nextX = x;
    nextY = y+1;
    printf("\t(%i,%i)\n",nextX,nextY);
    if (cost[nextX][nextY]==255)
    //compares the currently stored cost with the newly calculated
    if (cost[x][y]+COST_90 < cost[nextX][nextY] || cost[nextX][nextY]==255)
    {
      cost[nextX][nextY] = cost[x][y]+COST_90;
      parent[nextX][nextY] = current;
    }
  }
  if (map[x][y]&S)
  {
    printf("\tS\t");
    nextX = x+1;
    nextY = y;
    printf("\t(%i,%i)\n",nextX,nextY);
    if (cost[nextX][nextY]==255)
    //compares the currently stored cost with the newly calculated
    if (cost[x][y]+COST_90 < cost[nextX][nextY] || cost[nextX][nextY]==255)
    {
      cost[nextX][nextY] = cost[x][y]+COST_90;
      parent[nextX][nextY] = current;
    }
  }
  if (map[x][y]&W)
  {
    printf("\tW\t");
    nextX = x;
    nextY = y-1;
    printf("\t(%i,%i)\n",nextX,nextY);
    if (cost[nextX][nextY]==255)
    //compares the currently stored cost with the newly calculated
    if (cost[x][y]+COST_90 < cost[nextX][nextY] || cost[nextX][nextY]==255)
    {
      cost[nextX][nextY] = cost[x][y]+COST_90;
      parent[nextX][nextY] = current;
    }
  }
  if (map[x][y]&NE)
  {
    printf("\tNE\t");
    nextX = x-1;
    nextY = y+1;
    printf("\t(%i,%i)\n",nextX,nextY);
    if (cost[nextX][nextY]==255)
    //compares the currently stored cost with the newly calculated
    if (cost[x][y]+COST_45 < cost[nextX][nextY] || cost[nextX][nextY]==255)
    {
      cost[nextX][nextY] = cost[x][y]+COST_45;
      parent[nextX][nextY] = current;
    }
  }
  if (map[x][y]&SE)
  {
    printf("\tSE\t");
    nextX = x+1;
    nextY = y+1;
    printf("\t(%i,%i)\n",nextX,nextY);
    if (cost[nextX][nextY]==255)
    //compares the currently stored cost with the newly calculated
    if (cost[x][y]+COST_45 < cost[nextX][nextY] || cost[nextX][nextY]==255)
    {
      cost[nextX][nextY] = cost[x][y]+COST_45;
      parent[nextX][nextY] = current;
    }
  }
  if (map[x][y]&SW)
  {
    printf("\tSW\t");
    nextX = x+1;
    nextY = y-1;
    printf("\t(%i,%i)\n",nextX,nextY);
    if (cost[nextX][nextY]==255)
    //compares the currently stored cost with the newly calculated
    if (cost[x][y]+COST_45 < cost[nextX][nextY] || cost[nextX][nextY]==255)
    {
      cost[nextX][nextY] = cost[x][y]+COST_45;
      parent[nextX][nextY] = current;
    }
  }
  if (map[x][y]&NW)
  {
    printf("\tNW\t");
    nextX = x-1;
    nextY = y-1;
    printf("\t(%i,%i)\n",nextX,nextY);
    if (cost[nextX][nextY]==255)
    //compares the currently stored cost with the newly calculated
    if (cost[x][y]+COST_45 < cost[nextX][nextY] || cost[nextX][nextY]==255)
    {
      cost[nextX][nextY] = cost[x][y]+COST_45;
      parent[nextX][nextY] = current;
    }
  }

  printf("\n\nCostMap looks like this:\n\n");
  for (int i = 0; i<5;i++){
    for (int j = 0; j<5;j++){
      printf("%.2i \t",(cost[i][j])/10);
    }
    printf("\n");
  }

  printf("\n\nParentMap looks like this:\n\n");
  for (int i = 0; i<5;i++){
    for (int j = 0; j<5;j++){
      printf("%.2i \t",(parent[i][j]));
    }
    printf("\n");
  }

  //mashing x and y into one char
  next = (((char)nextX)<4)+(char)nextY;
  return next;
}

void path_calculate(unsigned char map[][5], int cost[][5], char parent[][5], int startX, int startY, int stopX,  int stopY)
{
  //TODO implement list of unchecked nodes
  char result = path_evaluate_node(map,cost,parent,startX,startY,stopX,stopY);
  if (result==(char)0xFF)
  {
    printf("Done calculating path!\n");
  }

  printf("\n\nParentMap inside path_calculate looks like this:\n\n");
  for (int i = 0; i<5;i++){
    for (int j = 0; j<5;j++){
      printf("%.2i \t",(parent[i][j]));
    }
    printf("\n");
  }

  printf("\n\nMap looks like this:\n\n");
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
      printNode(map[i][j]);
    }
    printf("\n");
  }
}


//TODO this function sorts through the unchecked node list, organizing them by cost lowest to highest
char path_sort_unchecked(char unchecked[], int length, char cost[][5])
{
  //TODO traverse through unchecked
  //find smallest cost
  return 'x';
}

//returns the x part of a coordinate stored in a char
int path_only_x(unsigned char coordinate)
{
  unsigned int re = (int)coordinate;
  return re>>4;
}

int path_only_y(unsigned char coordinate)
{
  return (int)coordinate&0x0F;
}

//prints a character that shows what the given node looks like
//works only for 90 degrees, because there are no nice characters for the rest
//doesn't work for single directions either
void printNode(char node)
{
  switch(node) {        //  N E S W
    case 0x06:
      printf("%c",218); //  - E S -
      break;
    case 0x0c:
      printf("%c",191); //  - - S W
      break;
    case 0x03:
      printf("%c",192); //  N E - -
      break;
    case 0x09:
      printf("%c",217); //  N - - W
      break;

    case 0x0B:
      printf("%c",193); //  N E - W
      break;
    case 0x0E:
      printf("%c",194); //  - E S W
      break;
    case 0x07:
      printf("%c",195); //  N E S -
      break;
    case 0x0A:
      printf("%c",196); //  - E - W
      break;
    case 0x0F:
      printf("%c",197); //  N E S W
      break;
    case 0x05:
      printf("%c",179); //  N - S -
      break;
    case 0x0D:
      printf("%c",180); //  N - S W
      break;

    default:
      printf("?");      //  Everything not mentioned above
  }
}
