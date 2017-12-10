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
      //printf("[INFO]\tlinking\t[%2i][%2i]\n",i,j);
      if (!(robot->map.node[i][j].walls & N)){
        robot->map.node[i][j].n=&robot->map.node[i-1][j];
      } else {
        robot->map.node[i][j].n=NULL;
      }
      if (!(robot->map.node[i][j].walls & E)){
        robot->map.node[i][j].e=&robot->map.node[i][j+1];
      } else {
        robot->map.node[i][j].e=NULL;
      }
      if (!(robot->map.node[i][j].walls & S)){
        robot->map.node[i][j].s=&robot->map.node[i+1][j];
      } else {
        robot->map.node[i][j].s=NULL;
      }
      if (!(robot->map.node[i][j].walls & W)){
        robot->map.node[i][j].w=&robot->map.node[i][j-1];
      } else {
        robot->map.node[i][j].w=NULL;
      }

      if (!(robot->map.node[i][j].walls & NE)){
        robot->map.node[i][j].ne=&robot->map.node[i-1][j+1];
      } else {
        robot->map.node[i][j].ne=NULL;
      }
      if (!(robot->map.node[i][j].walls & SE)){
        robot->map.node[i][j].se=&robot->map.node[i+1][j+1];
      } else {
        robot->map.node[i][j].se=NULL;
      }
      if (!(robot->map.node[i][j].walls & SW)){
        robot->map.node[i][j].sw=&robot->map.node[i+1][j-1];
      } else {
        robot->map.node[i][j].sw=NULL;
      }
      if (!(robot->map.node[i][j].walls & NW)){
        robot->map.node[i][j].nw=&robot->map.node[i-1][j-1];
      } else {
        robot->map.node[i][j].nw=NULL;
      }

      robot->map.node[i][j].movecost = 0xFFF; //set movecost to something high
                                              //reset to 0 for start later
      robot->map.node[i][j].parent = NULL;    //set parent pointer to NULL

      //map_print_node(&robot->map.node[i][j]);

      //printf("[INFO]\t[%2i][%2i] has been linked\n",i,j);
    }
  //printf("\n");
  }
  //set movecost for the current position to 0
  robot->map.node[robot->pos.x][robot->pos.y].movecost = 0;
  printf("[INFO]\tDone linking nodes to neighbors\n");
}

///calculates the path from the current position
void path_calculate(Robot *robot) {
  //--------------------------------- SETUP-----------------------------------//
  //declare all variables needed in scope
  int curx,cury;          //to keep track of your food/position on the map
                          //should not be necessary, but would clean up the code
  Nodes *currNode;        //the Node currently looked at

  //make sure that all nodes have the correct neighbors
  path_set_neighbors(robot);

  //start calculating from current position
  curx = robot->pos.x;
  cury = robot->pos.y;
  push_queue(&robot->unchecked, &robot->map.node[curx][cury]);
  currNode =pop(&robot->unchecked);

  //----------------------------------CALC------------------------------------//
  int deadcount=0;
  printf("\n\n[INFO]\tstarted path calculation\n\n");
  // until we reach the finish
  while ((curx!=robot->map.finish.y)||(cury!=robot->map.finish.x)){
    if (currNode==NULL){
      printf("[WARN]\tsomething went wrong\n");
      break;
    }
    //catching infinite loops
    if (deadcount++>=(robot->map.nSize.x)*(robot->map.nSize.y)){
        printf("[ERROR]\tEVERYTHING WENT WRONG\n"); return;
    }
    curx = currNode->position.x;
    cury = currNode->position.y;

    /*explaining the if once
    //checks whether the neighbor exists, then if movecost is smaller
      //updates neighbor movecost
      //updates neighbor parent
      //remove parent as neighbor
      //prints neighbor (debugging)
      //pushes neighbor on queue
    */

    //------------------------------------STRAIGHTS-------------------------//
    if (currNode->n && (currNode->n->movecost > currNode->movecost+10)){
      currNode->n->movecost = currNode->movecost+10;
      currNode->n->parent = currNode;
      currNode->n->s = NULL;
      //map_print_node(currNode->n);
      push_queue(&robot->unchecked, currNode->n);
    }
    if (currNode->e && (currNode->e->movecost > currNode->movecost+10)){
      currNode->e->movecost = currNode->movecost+10;
      currNode->e->parent = currNode;
      currNode->e->w = NULL;
      //map_print_node(currNode->e);
      push_queue(&robot->unchecked, currNode->e);
    }
    if (currNode->s && (currNode->s->movecost > currNode->movecost+10)){
      currNode->s->movecost = currNode->movecost+10;
      currNode->s->parent = currNode;
      currNode->s->n = NULL;
      //map_print_node(currNode->s);
      push_queue(&robot->unchecked, currNode->s);
    }
    if (currNode->w && (currNode->w->movecost > currNode->movecost+10)){
      currNode->w->movecost = currNode->movecost+10;
      currNode->w->parent = currNode;
      currNode->w->e = NULL;
      //map_print_node(currNode->w);
      push_queue(&robot->unchecked, currNode->w);
    }

    //------------------------------------DIAGONALS-------------------------//
    if (currNode->ne && (currNode->ne->movecost > currNode->movecost+14)){
      currNode->ne->movecost = currNode->movecost+14;
      currNode->ne->parent = currNode;
      currNode->ne->sw = NULL;
      //map_print_node(currNode->n);
      push_queue(&robot->unchecked, currNode->ne);
    }
    if (currNode->se && (currNode->se->movecost > currNode->movecost+14)){
      currNode->se->movecost = currNode->movecost+14;
      currNode->se->parent = currNode;
      currNode->se->nw = NULL;
      //map_print_node(currNode->se);
      push_queue(&robot->unchecked, currNode->se);
    }
    if (currNode->sw && (currNode->sw->movecost > currNode->movecost+14)){
      currNode->sw->movecost = currNode->movecost+14;
      currNode->sw->parent = currNode;
      currNode->sw->ne = NULL;
      //map_print_node(currNode->sw);
      push_queue(&robot->unchecked, currNode->sw);
    }
    if (currNode->nw && (currNode->nw->movecost > currNode->movecost+14)){
      currNode->nw->movecost = currNode->movecost+14;
      currNode->nw->parent = currNode;
      currNode->nw->se = NULL;
      //map_print_node(currNode->nw);
      push_queue(&robot->unchecked, currNode->nw);
    }


    push_stack(&robot->checked, currNode);
    printf("[INFO]\tNode [%2d][%2d] computed!\n",curx,cury);

    currNode = pop(&robot->unchecked);
  }

  printf("\n[INFO]\tDone calculating path!\n");

  path_calculate_movement(robot);
}

///calculates the movement stack out of the checked stack.
///give pointer to a robot struct
void path_calculate_movement(Robot *robot){
  //pop from stack until start is reached
  //-------------------------------- VARIABLES--------------------------------//
  int deadcount=0;
  int parX=0,parY=0;
  int ownX=0,ownY=0;
  char move=0;
  Nodes *currNode = NULL, *parNode = NULL;
  //----------------------------LOOP THROUGH STACK----------------------------//
  currNode=pop(&robot->checked);
  while(currNode->movecost!=0){ //start has movecost 0
    deadcount++;
    ownX = currNode->position.x;
    ownY = currNode->position.y;
    parX = currNode->parent->position.x;
    parY = currNode->parent->position.y;
    //----------------------- Generate Movement Stack-----------------------//
    //adds all movements together
    move=0;
    if (ownX<parX) move+=N;       //Something North
    if (ownY>parY) move+=E;       //Something East
    if (ownX>parX) move+=S;       //Something South
    if (ownY<parY) move+=W;       //Something West

    //checks for two movements
    if (((move!=N)&&(move!=E)&&(move!=S)&&(move!=W))){
      if      (move==N+E) move=NE;//North and East
      else if (move==S+E) move=SE;//South and East
      else if (move==S+W) move=SW;//South and West
      else if (move==N+W) move=NW;//North and West
    }
    printf("[DEV]\tmoving direction: 0x%02x\n",move);
    //------------------------Save To Movement Stack------------------------//
    push_move_stack(&robot->movement, move);
    //TODO
    while (((parNode=pop(&robot->checked))->position.x!=parX)||
           (parNode->position.y!=parY)){}
    currNode=parNode;
  }
}
