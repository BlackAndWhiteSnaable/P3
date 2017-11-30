#include "defs.h"

void path_test(Robot *robot) {

  // Initialize head of priority queues
  TopStack *unchecked;
  unchecked = init_queue();

  TopStack *checked;
  checked = init_queue();

  // Set some dummy movecost values for testing
  robot->map.node[0][0].movecost = 4;
  robot->map.node[0][1].movecost = 3;
  robot->map.node[0][2].movecost = 2;
  robot->map.node[0][3].movecost = 1;

  // Push some nodes to queue
  push(unchecked, &robot->map.node[0][0]);
  push(unchecked, &robot->map.node[0][1]);
  push(checked, &robot->map.node[0][2]);
  push(checked, &robot->map.node[0][3]);

  //pop(ts);          // remove first element from stack
  //emptyStack(ts);   // remove all elements from stack

  // Print queues
  printf("\nUnchecked:\n");
  printStack(unchecked);

  printf("\nChecked:\n");
  printStack(checked);
}

//finds all neighbors of a node and sets them as pointers
void path_set_neighbors(Robot *robot) {
  printf("\n");
  for (int i = 0; i<(robot->map.size.x-1)/2; i++){
  printf("\n");
    for (int j=0; j<(robot->map.size.y-1)/2; j++){
      if (!(robot->map.node[i][j].walls & N)) robot->map.node[i][j].n=&robot->map.node[i][j-1];
      if (!(robot->map.node[i][j].walls & E)) robot->map.node[i][j].e=&robot->map.node[i+1][j];
      if (!(robot->map.node[i][j].walls & S)) robot->map.node[i][j].s=&robot->map.node[i][j+1];
      if (!(robot->map.node[i][j].walls & W)) robot->map.node[i][j].w=&robot->map.node[i-1][j];

      if (!(robot->map.node[i][j].walls & NE)) robot->map.node[i][j].ne=&robot->map.node[i+1][j-1];
      if (!(robot->map.node[i][j].walls & SE)) robot->map.node[i][j].se=&robot->map.node[i+1][j+1];
      if (!(robot->map.node[i][j].walls & SW)) robot->map.node[i][j].sw=&robot->map.node[i-1][j+1];
      if (!(robot->map.node[i][j].walls & NW)) robot->map.node[i][j].nw=&robot->map.node[i-1][j-1];

      printf("[%2i][%2i] has been linked\n",i,j);
    }
  }
}

//calculates the path
void path_calculate(Robot *robot) {
  Nodes *currentNode;
  int curx,cury;
  curx = robot->pos.x;
  cury = robot->pos.y;
  currentNode = &robot->map.node[curx][cury];
  printf("currently calculating position [%02i][%02i]\n",curx,cury);
  while (curx!=robot->map.finish.x && cury!=robot->map.finish.y){
    curx++;
    cury++;
    printf("not done calculating yet\n");
  }
  printf("done calculating\n");
}
