#include "defs.h"

/*******************
 main.c
*******************/
int main(void) {
  WDTCTL = WDTPW + WDTHOLD;
  go(); // Calls all other functions
  return 0;
}

/*******************
 functions.c
*******************/
// Executes robot behavior instructions
void go(void) {
  P1DIR = 0x01;
  P1OUT = 0x00;
  //----------------------------------SETUP ----------------------------------//

  node_map_load();   // load map into node array

  //---------------------------------RUNNING ---------------------------------//
  //path_calculate();  //calculate path

  //---------------------------------TESTING ---------------------------------//
  int test;
  test = push_queue((char)0x01);

  char testc,testb;
  testc = pop_queue();
  testb = pop_queue();

  P1OUT = 0x01;
}
