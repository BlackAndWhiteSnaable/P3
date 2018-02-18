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
  map_setup();      //hardcodes the map into memory

  //---------------------------------RUNNING ---------------------------------//
  path_calculate(); //calculate path

  //---------------------------------TESTING ---------------------------------//
  push_queue((char)0x01);

  char testc,testb;
  testc = 0xDD&East;
  testc = 0xDD&(char)East;
  testc = 0xDD&North;
  testc = 0xDD&(char)North;

  testb = pop_queue();

  P1OUT = 0x01;
}

char xy2hex(char x,char y){
    y*=16;
    y+=x;
    return y;
}
char hex2x(char hex){
    hex/=16;
    return hex;
}
char hex2y(char hex){
    hex&=(char)0x0F;
    return hex;
}
