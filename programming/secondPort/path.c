#include "defs.h"


void path_calculate() {
  /*--VARIABLE DECLARATION--
   * current: x,y,node(walls),cost,position
   * general: endx&y
   */
  char cx, cy, cnode, cpos, endx, endy;
  unsigned int ccost;

  endx=hex2x(end);endy=hex2y(end);

  /*TAKE START NODE*/
  cpos=pos;
  cx=hex2x(cpos); cy=hex2y(cpos);
  /*WHILE NOT AT THE END*/
  while(cx!=endx||cy!=endy){
    cx=hex2x(cpos); cy=hex2y(cpos);
    cnode= map[cx][cy];
    ccost=mapc[cx][cy];
    /*NORTH*/
    if((cnode&North)==0){
      /*REMOVE NEIGHBOUR AS NEIGHBOUR*/
      map [cx  ][cy  ]|=North;
      /*REMOVE PARENT AS NEIGHBOUR*/
      map [cx-1][cy  ]|=South;
      if(mapc[cx-1][cy  ]>ccost+10){
        /*CHANGE MOVECOST*/
        mapc[cx-1][cy  ]=ccost+10;
        /*SAVE PATH(PARENT)*/
        mapp[cx-1][cy  ]=xy2hex(cx,cy);
        /*PUT INTO QUEUE*/
        push_queue(xy2hex(cx-1,cy  ));
      }
    }
    /*EAST*/
    if((cnode&East)==0){
      /*REMOVE NEIGHBOUR AS NEIGHBOUR*/
      map [cx  ][cy  ]|=East;
      /*REMOVE PARENT AS NEIGHBOUR*/
      map [cx  ][cy+1]|=West;
      if(mapc[cx  ][cy+1]>ccost+10){
        /*CHANGE MOVECOST*/
        mapc[cx  ][cy+1]=ccost+10;
        /*SAVE PATH(PARENT)*/
        mapp[cx  ][cy+1]=xy2hex(cx,cy);
        /*PUT INTO QUEUE*/
        push_queue(xy2hex(cx  ,cy+1));
      }
    }
    /*SOUTH*/
    if((cnode&South)==0){
      /*REMOVE NEIGHBOUR AS NEIGHBOUR*/
      map [cx  ][cy  ]|=South;
      /*REMOVE PARENT AS NEIGHBOUR*/
      map [cx+1][cy  ]|=North;
      if(mapc[cx+1][cy  ]>ccost+10){
        /*CHANGE MOVECOST*/
        mapc[cx+1][cy  ]=ccost+10;
        /*SAVE PATH(PARENT)*/
        mapp[cx+1][cy  ]=xy2hex(cx,cy);
        /*PUT INTO QUEUE*/
        push_queue(xy2hex(cx+1,cy  ));
      }
    }
    /*WEST*/
    if((cnode&West)==0){
      /*REMOVE NEIGHBOUR AS NEIGHBOUR*/
      map [cx  ][cy  ]|=West;
      /*REMOVE PARENT AS NEIGHBOUR*/
      map [cx  ][cy-1]|=East;
      if(mapc[cx  ][cy-1]>ccost+10){
        /*CHANGE MOVECOST*/
        mapc[cx  ][cy-1]=ccost+10;
        /*SAVE PATH(PARENT)*/
        mapp[cx  ][cy-1]=xy2hex(cx,cy);
        /*PUT INTO QUEUE*/
        push_queue(xy2hex(cx  ,cy-1));
      }
    }

    /*NORTHEAST*/
    if((cnode&NorthEast)==0){
      /*REMOVE NEIGHBOUR AS NEIGHBOUR*/
      map [cx  ][cy  ]|=NorthEast;
      /*REMOVE PARENT AS NEIGHBOUR*/
      map [cx-1][cy+1]|=SouthWest;
      if(mapc[cx-1][cy+1]>ccost+14){
        /*CHANGE MOVECOST*/
        mapc[cx-1][cy+1]=ccost+14;
        /*SAVE PATH(PARENT)*/
        mapp[cx-1][cy+1]=xy2hex(cx,cy);
        /*PUT INTO QUEUE*/
        push_queue(xy2hex(cx-1,cy+1));
      }
    }
    /*SOUTHEAST*/
    if((cnode&SouthEast)==0){
      /*REMOVE NEIGHBOUR AS NEIGHBOUR*/
      map [cx  ][cy  ]|=SouthEast;
      /*REMOVE PARENT AS NEIGHBOUR*/
      map [cx+1][cy+1]|=NorthWest;
      if(mapc[cx+1][cy+1]>ccost+14){
        /*CHANGE MOVECOST*/
        mapc[cx+1][cy+1]=ccost+14;
        /*SAVE PATH(PARENT)*/
        mapp[cx+1][cy+1]=xy2hex(cx,cy);
        /*PUT INTO QUEUE*/
        push_queue(xy2hex(cx+1,cy+1));
      }
    }
    /*SOUTHWEST*/
    if((cnode&SouthWest)==0){
      /*REMOVE NEIGHBOUR AS NEIGHBOUR*/
      map [cx  ][cy  ]|=SouthWest;
      /*REMOVE PARENT AS NEIGHBOUR*/
      map [cx+1][cy-1]|=NorthEast;
      if(mapc[cx+1][cy-1]>ccost+14){
        /*CHANGE MOVECOST*/
        mapc[cx+1][cy-1]=ccost+14;
        /*SAVE PATH(PARENT)*/
        mapp[cx+1][cy-1]=xy2hex(cx,cy);
        /*PUT INTO QUEUE*/
        push_queue(xy2hex(cx+1,cy-1));
      }
    }
    /*NORTHWEST*/
    if((cnode&NorthWest)==0){
      /*REMOVE NEIGHBOUR AS NEIGHBOUR*/
      map [cx  ][cy  ]|=NorthWest;
      /*REMOVE PARENT AS NEIGHBOUR*/
      map [cx-1][cy-1]|=SouthEast;
      if(mapc[cx-1][cy-1]>ccost+14){
        /*CHANGE MOVECOST*/
        mapc[cx-1][cy-1]=ccost+14;
        /*SAVE PATH(PARENT)*/
        mapp[cx-1][cy-1]=xy2hex(cx,cy);
        /*PUT INTO QUEUE*/
        push_queue(xy2hex(cx-1,cy-1));
      }
    }
    /*PUSH CURRENT NODE TO STACK*/
    push_stack(cpos);

    /*TAKE NEXT NODE FROM QUEUE*/
    cpos=pop_queue();
  }
  path_calculate_movement();

}

///calculates the movement stack out of the checked stack.
void path_calculate_movement(){
  //pop from stack until start is reached
  //-------------------------------- VARIABLES--------------------------------//
  int parX=0,parY=0;
  int ownX=0,ownY=0;
  char move=0;
  char currNode=0x00, parNode=0x00;
  //----------------------------LOOP THROUGH STACK----------------------------//
  currNode=pop_stack();

  while(currNode!=start){ //while not looking at the final node
    ownX = hex2x(currNode);
    ownY = hex2y(currNode);
    parX = hex2x(mapp[ownY][ownX]);
    parY = hex2y(mapp[ownY][ownX]);
    //----------------------- Generate Movement Stack-----------------------//
    //TODO test
    //TODO can maybe be done in one step (checking for two movements)
    //adds all movements together
    move=0;
    if (ownX<parX) move+=North;       //Something North
    if (ownY>parY) move+=East;       //Something East
    if (ownX>parX) move+=South;       //Something South
    if (ownY<parY) move+=West;       //Something West

    //checks for two movements
    if ((move!=North)&&(move!=East)&&(move!=South)&&(move!=West)){
      if      (move==North+East) move=NorthEast;//North and East
      else if (move==South+East) move=SouthEast;//South and East
      else if (move==South+West) move=SouthWest;//South and West
      else if (move==North+West) move=NorthWest;//North and West
    }
    //------------------------Save To Movement Stack------------------------//
    push_move_stack(move);
    //TODO
    P1OUT |= 0x01;
    //while (((parNode=pop(&robot.checked))->position.x!=parX)||
    //       (parNode->position.y!=parY)){}
    currNode=parNode;
    P1OUT ^= 0x01;
  }
}
