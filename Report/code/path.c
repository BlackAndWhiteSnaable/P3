#include "defs.h"

///finds all neighbors of a node and sets them as pointers
void path_set_neighbors(Robot *robot) {
  printf("\n[INFO]\tStarted linking nodes to neighbors\n");
  //---------------------------2D for loop--------------------------//
  for (int i = 0; i<(robot->map.size.x-1)/2; i++){
    for (int j=0; j<(robot->map.size.y-1)/2; j++){
      if (!(robot->map.node[i][j].walls & N))   //NORTH exists
        {robot->map.node[i][j].n=&robot->map.node[i-1][j];}
      else {robot->map.node[i][j].n=NULL;}
      if (!(robot->map.node[i][j].walls & E))   //EAST exists
        {robot->map.node[i][j].e=&robot->map.node[i][j+1];}
      else {robot->map.node[i][j].e=NULL;}
      if (!(robot->map.node[i][j].walls & S))   //SOUTH exists
        {robot->map.node[i][j].s=&robot->map.node[i+1][j];}
      else {robot->map.node[i][j].s=NULL;}
      if (!(robot->map.node[i][j].walls & W))   //WEST exists
        {robot->map.node[i][j].w=&robot->map.node[i][j-1];}
      else {robot->map.node[i][j].w=NULL;}

      if (!(robot->map.node[i][j].walls & NE))
        {robot->map.node[i][j].ne=&robot->map.node[i-1][j+1];}
      else {robot->map.node[i][j].ne=NULL;}
      if (!(robot->map.node[i][j].walls & SE))
        {robot->map.node[i][j].se=&robot->map.node[i+1][j+1];}
      else {robot->map.node[i][j].se=NULL;}
      if (!(robot->map.node[i][j].walls & SW))
        {robot->map.node[i][j].sw=&robot->map.node[i+1][j-1];}
      else {robot->map.node[i][j].sw=NULL;}
      if (!(robot->map.node[i][j].walls & NW))
        {robot->map.node[i][j].nw=&robot->map.node[i-1][j-1];}
      else {robot->map.node[i][j].nw=NULL;}

      robot->map.node[i][j].movecost = 0xFFF; //set movecost high
      robot->map.node[i][j].parent = NULL;    //point parent to NULL
    }
  }
  //-------------------------END 2D for loop------------------------//
  //set movecost for the current position to 0
  robot->map.node[robot->pos.x][robot->pos.y].movecost = 0;
  printf("[INFO]\tDone linking nodes to neighbors\n");
}

///calculates the path from the current position
void path_calculate(Robot *robot) {
  //---------------------------- SETUP------------------------------//
  //declare all variables needed in scope
  int curx,cury;          //keeps track of position on the map
  Nodes *currNode;        //the Node currently looked at

  path_set_neighbors(robot);  //make sure that all nodes are set up

  //-------------------------SETUP FOR CALC-------------------------//
  curx = robot->pos.x;    //start calculating from current position
  cury = robot->pos.y;
  push_queue(&robot->unchecked, &robot->map.node[curx][cury]);
  currNode =pop(&robot->unchecked);

  //------------------------------CALC------------------------------//
  int deadcount=0;
  printf("\n\n[INFO]\tstarted path calculation\n\n");
  //----------------------WHILE not at finish-----------------------//
  while ((curx!=robot->map.finish.y)||(cury!=robot->map.finish.x)){
    if (currNode==NULL){
      printf("[WARN]\tsomething went wrong, current node is NULL\n");
      break;
    }
    if (deadcount++>=(robot->map.nSize.x)*(robot->map.nSize.y)){
        printf("[ERROR]\tEVERYTHING WENT WRONG, looping\n"); return;
    } //catching infinite loops
    curx = currNode->position.x;
    cury = currNode->position.y;

    /*explaining the ifs below
    checks whether the neighbor exists, then if movecost is smaller
      updates neighbor movecost
      updates neighbor parent
      remove parent as neighbor
      pushes neighbor on queue
    */

    //-------------------------------STRAIGHTS--------------------//
    if(currNode->n&&(currNode->n->movecost > currNode->movecost+10))
    { currNode->n->movecost = currNode->movecost+10;
      currNode->n->parent = currNode;
      currNode->n->s = NULL;
      push_queue(&robot->unchecked, currNode->n); }
    if(currNode->e&&(currNode->e->movecost > currNode->movecost+10))
    { currNode->e->movecost = currNode->movecost+10;
      currNode->e->parent = currNode;
      currNode->e->w = NULL;
      push_queue(&robot->unchecked, currNode->e); }
    if(currNode->s&&(currNode->s->movecost > currNode->movecost+10))
    { currNode->s->movecost = currNode->movecost+10;
      currNode->s->parent = currNode;
      currNode->s->n = NULL;
      push_queue(&robot->unchecked, currNode->s); }
    if(currNode->w&&(currNode->w->movecost > currNode->movecost+10))
    { currNode->w->movecost = currNode->movecost+10;
      currNode->w->parent = currNode;
      currNode->w->e = NULL;
      push_queue(&robot->unchecked, currNode->w); }

    //-------------------------------DIAGONALS--------------------//
    if(currNode->ne&&(currNode->ne->movecost > currNode->movecost+14))
    { currNode->ne->movecost = currNode->movecost+14;
      currNode->ne->parent = currNode;
      currNode->ne->sw = NULL;
      push_queue(&robot->unchecked, currNode->ne); }
    if(currNode->se&&(currNode->se->movecost > currNode->movecost+14))
    { currNode->se->movecost = currNode->movecost+14;
      currNode->se->parent = currNode;
      currNode->se->nw = NULL;
      push_queue(&robot->unchecked, currNode->se); }
    if(currNode->sw&&(currNode->sw->movecost > currNode->movecost+14))
    { currNode->sw->movecost = currNode->movecost+14;
      currNode->sw->parent = currNode;
      currNode->sw->ne = NULL;
      push_queue(&robot->unchecked, currNode->sw); }
    if(currNode->nw&&(currNode->nw->movecost > currNode->movecost+14))
    { currNode->nw->movecost = currNode->movecost+14;
      currNode->nw->parent = currNode;
      currNode->nw->se = NULL;
      push_queue(&robot->unchecked, currNode->nw); }

    push_stack(&robot->checked, currNode);  //mark current as checked
    printf("[INFO]\tNode [%2d][%2d] computed!\n",curx,cury);

    currNode = pop(&robot->unchecked);  //get a new node from queue
  }//---------------------------END WHILE---------------------------//

  printf("\n[INFO]\tDone calculating path!\n");
  path_calculate_movement(robot);
}

///calculates the movement stack out of the checked stack
void path_calculate_movement(Robot *robot){
  //pop from stack until start is reached
  //--------------------------- VARIABLES---------------------------//
  int parX=0,parY=0;
  int ownX=0,ownY=0;
  char move=0;
  Nodes *currNode = NULL, *parNode = NULL;
  //-----------------------LOOP THROUGH STACK-----------------------//
  currNode=pop(&robot->checked);
  while(currNode->movecost!=0){ //start has movecost 0
    ownX = currNode->position.x;
    ownY = currNode->position.y;
    parX = currNode->parent->position.x;
    parY = currNode->parent->position.y;
    //----------------------Generate Movement---------------------//
    move=0;   //resets move, then adds all movements together
    if (ownX<parX) move+=N;         //Something North
    if (ownY>parY) move+=E;         //Something East
    if (ownX>parX) move+=S;         //Something South
    if (ownY<parY) move+=W;         //Something West

    //checks for two movements (indicates diagonal movement)
    if (((move!=N)&&(move!=E)&&(move!=S)&&(move!=W))){
      if      (move==N+E) move=NE;  //North and East
      else if (move==S+E) move=SE;  //South and East
      else if (move==S+W) move=SW;  //South and West
      else if (move==N+W) move=NW;  //North and West
    }   //now we know the exact moving direction!
    //-------------------Save To Movement Stack-------------------//
    push_move_stack(&robot->movement, move);
    //TODO
    while (((parNode=pop(&robot->checked))->position.x!=parX)||
           (parNode->position.y!=parY)){}
    currNode=parNode;
  }
}
