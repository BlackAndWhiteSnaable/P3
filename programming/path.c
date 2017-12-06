#include "defs.h"

/// Testing examples of queue push/pop functions
void path_test(Robot *robot) {

  // Set some dummy movecost values for testing
  robot->map.node[0][0].movecost = 5;
  robot->map.node[0][1].movecost = 10;
  robot->map.node[0][2].movecost = 20;
  robot->map.node[0][3].movecost = 4;

  // Push some nodes to queue
  printf("\nPushing 4 node elements to queue\n");
  push_queue(&robot->unchecked, &robot->map.node[0][0]);
  push_queue(&robot->unchecked, &robot->map.node[0][1]);
  push_queue(&robot->unchecked, &robot->map.node[0][2]);
  push_queue(&robot->unchecked, &robot->map.node[0][3]);

  Nodes *node; // Empty pointer used for nodes returned when popping

  // Pop 2 of the 4 elements in the queue
  node = pop(&robot->unchecked);
  printf("\nPopped queue element, node returned: node->movecost=%d\n", node->movecost);

  node = pop(&robot->unchecked);
  printf("Popped queue element, node returned: node->movecost=%d\n", node->movecost);

  // Print what is in the queue
  printf("\nUnchecked queue:\n");
  print_queue(robot->unchecked);

  printf("\nPushing 4 node elements to stack\n");
  push_stack(&robot->checked, &robot->map.node[0][0]);
  push_stack(&robot->checked, &robot->map.node[0][1]);
  push_stack(&robot->unchecked, &robot->map.node[0][2]);
  push_stack(&robot->unchecked, &robot->map.node[0][3]);

  node = pop(&robot->checked);
  printf("\nPopped stack element, node returned: node->movecost=%d\n", node->movecost);


  printf("\nChecked stack:\n");
  print_stack(robot->checked);

}

///finds all neighbors of a node and sets them as pointers
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

      //printf("[%2i][%2i] has been linked\n",i,j);
    }
  }
}

//calculates the path at some point
void path_calculate(Robot *robot) {
  Nodes *currentNode;     //the Node currently looked at (should be popped from priority queue)
  int curx,cury;          //to keep track of your food/position on the map
  curx = robot->pos.x;    //we start with the current position of the robot, should be start at first execution
  cury = robot->pos.y;    //TODO is pos == start?
  currentNode = &robot->map.node[curx][cury];     //TODO pop from queue?
  //TODO is the current position at the first position in queue?
  printf("currently calculating position [%02i][%02i]\n",curx,cury);
  while (curx!=robot->map.finish.x && cury!=robot->map.finish.y){   //do until we reach the finish
    //TODO pop from priority queue
    //TODO 8 if (neighbor exists && neighbor.movement > own.movement+1)
      //TODO update neighbor.movecost
      //TODO check whether neighbor is in priority queue, move to right position
    curx++;
    cury++;
    //TODO
    printf("not done calculating yet\n");
  }
  printf("done calculating\n");
}
