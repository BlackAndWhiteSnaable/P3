#include "defs.h"

/// Testing examples of queue push/pop functions
void path_test(Robot *robot) {

  // Set some dummy movecost values for testing
  robot->map.node[0][0].movecost = 5;
  robot->map.node[0][1].movecost = 10;
  robot->map.node[0][2].movecost = 20;
  robot->map.node[0][3].movecost = 4;

  // Push some nodes to queue
  printf("\n[INFO]\tPushing 4 node elements to queue\n");
  push_queue(&robot->unchecked, &robot->map.node[0][0]);
  push_queue(&robot->unchecked, &robot->map.node[0][1]);
  push_queue(&robot->unchecked, &robot->map.node[0][2]);
  push_queue(&robot->unchecked, &robot->map.node[0][3]);

  Nodes *node; // Empty pointer used for nodes returned when popping

  // Pop 2 of the 4 elements in the queue
  node = pop(&robot->unchecked);
  printf("\n[INFO]\tPopped queue element, node returned: node->movecost=%d\n", node->movecost);

  node = pop(&robot->unchecked);
  printf("[INFO]\tPopped queue element, node returned: node->movecost=%d\n", node->movecost);

  // Print what is in the queue
  printf("\n\tUnchecked queue:\n");
  print_queue(robot->unchecked);

  printf("\n[INFO]\tPushing 4 node elements to stack\n");
  push_stack(&robot->checked, &robot->map.node[0][0]);
  push_stack(&robot->checked, &robot->map.node[0][1]);
  push_stack(&robot->unchecked, &robot->map.node[0][2]);
  push_stack(&robot->unchecked, &robot->map.node[0][3]);

  node = pop(&robot->checked);
  printf("\n[INFO]\tPopped stack element, node returned: node->movecost=%d\n", node->movecost);


  printf("\nChecked stack:\n");
  print_stack(robot->checked);

}

///finds all neighbors of a node and sets them as pointers
void path_set_neighbors(Robot *robot) {
  printf("\n[INFO]\tStarted linking nodes to neighbors\n");
  for (int i = 0; i<(robot->map.size.x-1)/2; i++){
    for (int j=0; j<(robot->map.size.y-1)/2; j++){
      if (!(robot->map.node[i][j].walls & N)) robot->map.node[i][j].n=&robot->map.node[i][j-1];
      if (!(robot->map.node[i][j].walls & E)) robot->map.node[i][j].e=&robot->map.node[i+1][j];
      if (!(robot->map.node[i][j].walls & S)) robot->map.node[i][j].s=&robot->map.node[i][j+1];
      if (!(robot->map.node[i][j].walls & W)) robot->map.node[i][j].w=&robot->map.node[i-1][j];

      if (!(robot->map.node[i][j].walls & NE)) robot->map.node[i][j].ne=&robot->map.node[i+1][j-1];
      if (!(robot->map.node[i][j].walls & SE)) robot->map.node[i][j].se=&robot->map.node[i+1][j+1];
      if (!(robot->map.node[i][j].walls & SW)) robot->map.node[i][j].sw=&robot->map.node[i-1][j+1];
      if (!(robot->map.node[i][j].walls & NW)) robot->map.node[i][j].nw=&robot->map.node[i-1][j-1];

      //printf("[INFO]\t[%2i][%2i] has been linked\n",i,j);
    }
  //printf("\n");
  }
  printf("[INFO]\tDone linking nodes to neighbors\n");
}

///calculates the path from the current position
void path_calculate(Robot *robot) {
  //declare all variable needed in scope
  int curx,cury;          //to keep track of your food/position on the map
                          //should not be necessary, but would clean up the code
  Nodes *currentNode;     //the Node currently looked at

  //make sure that all nodes have the correct neighbors
  path_set_neighbors(robot);

  //start calculating from current position, not start
  curx = robot->pos.x;
  cury = robot->pos.y;

  //[DEV] checks if robot is at start position
  if (curx==robot->map.start.x && cury==robot->map.start.y){
    printf("\n[DEV]\tRobot is at start position\n");
  } else {
    printf("\n[DEV]\tRobot is at position [%02i][%02i]\n",curx,cury);
  }

  printf("\n[DEV]\tThis is how far I am programming --Daniel\n\n\n");

  //check whether queue is empty, if yes, push start on queue
  currentNode=pop(&robot->unchecked);
  //if (!currentNode) push_queue(robot->unchecked, robot->map.node[][])

  currentNode = &robot->map.node[curx][cury];     //TODO pop from queue?
  //TODO is the current position at the first position in queue?
  printf("[DEBUG]\tcurrently calculating position [%02i][%02i]\n",curx,cury);
  while (curx!=robot->map.finish.x && cury!=robot->map.finish.y){   //do until we reach the finish
    //TODO pop from priority queue
    //TODO 8 if (neighbor exists && neighbor.movement > own.movement+1)
      //TODO update neighbor.movecost
      //TODO check whether neighbor is in priority queue, move to right position
    curx++;
    cury++;
    //TODO
    printf("[INFO]\tnot done calculating yet\n");
    printf("[INFO]\tCurrent position: [%02i][%02i]\n",curx,cury);
  }
  printf("[INFO]\tdone calculating\n");
}
