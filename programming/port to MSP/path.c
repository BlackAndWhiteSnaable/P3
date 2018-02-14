#include "defs.h"

///finds all neighbors of a node and sets them as pointers
void path_set_neighbors(Robot *robot) {
  unsigned int i,j,stopi, stopj;
  stopi = robot->map.nSize.x;
  stopj = robot->map.nSize.y;
  for (i = 0; i<stopi; i++){
    for (j=0; j<stopj; j++){
      if (!(robot->map.node[i][j].walls & North)){
        robot->map.node[i][j].n=&robot->map.node[i-1][j];
      } else {
        robot->map.node[i][j].n=NULL;
      }
      if (!(robot->map.node[i][j].walls & East)){
        robot->map.node[i][j].e=&robot->map.node[i][j+1];
      } else {
        robot->map.node[i][j].e=NULL;
      }
      if (!(robot->map.node[i][j].walls & South)){
        robot->map.node[i][j].s=&robot->map.node[i+1][j];
      } else {
        robot->map.node[i][j].s=NULL;
      }
      if (!(robot->map.node[i][j].walls & West)){
        robot->map.node[i][j].w=&robot->map.node[i][j-1];
      } else {
        robot->map.node[i][j].w=NULL;
      }

      if (!(robot->map.node[i][j].walls & NorthEast)){
        robot->map.node[i][j].ne=&robot->map.node[i-1][j+1];
      } else {
        robot->map.node[i][j].ne=NULL;
      }
      if (!(robot->map.node[i][j].walls & SouthEast)){
        robot->map.node[i][j].se=&robot->map.node[i+1][j+1];
      } else {
        robot->map.node[i][j].se=NULL;
      }
      if (!(robot->map.node[i][j].walls & SouthWest)){
        robot->map.node[i][j].sw=&robot->map.node[i+1][j-1];
      } else {
        robot->map.node[i][j].sw=NULL;
      }
      if (!(robot->map.node[i][j].walls & NorthWest)){
        robot->map.node[i][j].nw=&robot->map.node[i-1][j-1];
      } else {
        robot->map.node[i][j].nw=NULL;
      }

      robot->map.node[i][j].movecost = 0xFFF; //set movecost to something high
                                              //reset to 0 for start later
      robot->map.node[i][j].parent = NULL;    //set parent pointer to NULL

    }
  }
  //set movecost for the current position to 0
  robot->map.node[robot->pos.x][robot->pos.y].movecost = 0;
}

///calculates the path from the current position
void path_calculate(Robot *robot) {
  P1OUT &= ~0x01;
  //--------------------------------- SETUP-----------------------------------//
  //declare all variables needed in scope
  unsigned int curx = 0;
  unsigned int cury = 0;          //to keep track of your food/position on the map
                          //should not be necessary, but would clean up the code
  Nodes *currNode = NULL;        //the Node currently looked at

  //make sure that all nodes have the correct neighbors
  path_set_neighbors(robot);

  //start calculating from current position
  curx = robot->pos.x;
  cury = robot->pos.y;
  push_queue(&robot->unchecked, &robot->map.node[curx][cury]);
  currNode = pop(&robot->unchecked);

  //----------------------------------CALC------------------------------------//
  int deadcount=0;
  // until we reach the finish
  while ((curx!=robot->map.finish.y)||(cury!=robot->map.finish.x)){
    if (currNode==NULL){
      break;
    }
    //catching infinite loops
    if (deadcount++>=(robot->map.nSize.x)*(robot->map.nSize.y)){
      break;
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
      push_queue(&robot->unchecked, currNode->nw);
    }


    push_stack(&robot->checked, currNode);

    currNode = pop(&robot->unchecked);
  }

  P1OUT |= 0x01;
  path_calculate_movement(robot);
}

///calculates the movement stack out of the checked stack.
void path_calculate_movement(Robot *robot){
  P1OUT &= ~0x01;
  //pop from stack until start is reached
  //-------------------------------- VARIABLES--------------------------------//
  int deadcount=0;
  int parX=0,parY=0;
  int ownX=0,ownY=0;
  unsigned char move=0;
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
    if (ownX<parX) move+=North;       //Something North
    if (ownY>parY) move+=East;       //Something East
    if (ownX>parX) move+=South;       //Something South
    if (ownY<parY) move+=West;       //Something West

    //checks for two movements
    if (((move!=North)&&(move!=East)&&(move!=South)&&(move!=West))){
      if      (move==North+East) move=NorthEast;//North and East
      else if (move==South+East) move=SouthEast;//South and East
      else if (move==South+West) move=SouthWest;//South and West
      else if (move==North+West) move=NorthWest;//North and West
    }
    //------------------------Save To Movement Stack------------------------//
    push_move_stack(&robot->movement, move);
    //TODO
    P1OUT |= 0x01;
    while (((parNode=pop(&robot->checked))->position.x!=parX)||
           (parNode->position.y!=parY)){}
    currNode=parNode;
    P1OUT &= ~0x01;
  }
}
