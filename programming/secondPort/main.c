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
  // hardcoded 3x3 map
   map[0][0]=0xDD;  map[0][1]=0xA5;  map[0][2]=0xF7;
   map[1][0]=0xCD;  map[1][1]=0x35;  map[1][2]=0xF7;
   map[2][0]=0xED;  map[2][1]=0x75;  map[2][2]=0xF7;

  mapp[0][0]=0xFF; mapp[0][1]=0xFF; mapp[0][2]=0xFF;
  mapp[1][0]=0xFF; mapp[1][1]=0xFF; mapp[1][2]=0xFF;
  mapp[2][0]=0xFF; mapp[2][1]=0xFF; mapp[2][2]=0xFF;

  mapc[0][0]=0x00; mapc[0][1]=0xFF; mapc[0][2]=0xFF;
  mapc[1][0]=0xFF; mapc[1][1]=0xFF; mapc[1][2]=0xFF;
  mapc[2][0]=0xFF; mapc[2][1]=0xFF; mapc[2][2]=0xFF;

  //positions in hex
  start = 0x00;
  end   = 0x22;
  pos   = 0x00;
  //node_map_load();   // load map into node array

  //---------------------------------RUNNING ---------------------------------//
  path_calculate();  //calculate path

  //---------------------------------TESTING ---------------------------------//
  int test;
  test = push_queue((char)0x01);

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
