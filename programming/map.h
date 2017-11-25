struct Point {
  int x,y;
};

struct Maps {
  struct Point start;
  struct Point finish;
  struct Point size; // Size is amount of nodes in the map
  unsigned char **segments; // 2D array of the map data from text file (user input)
  unsigned char **nodes; // 2D array of each node's 8 neighbours represented in a hex value
};

#include "map.c"
