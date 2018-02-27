#include "defs.h"

// Scan surroundings at current position and compare with map segment
// If it differs, update map and recalculate path
void map_check() {
  char scan_segment = scan();
  char map_segment = map[hex2y(pos)][hex2x(pos)];

  // If scan and map segments are NOT identical
  if(scan_segment != map_segment) {
    // Update the segment at current position in the map struct
    map_update(scan_segment);
    path_calculate();
  }
  P1OUT ^= 0x01;
}

/*hardcodes node map into memory
 * For values refer to Map2Hex.xlsx
 * in a later update this should be automated
 * this is the original map, which should never get modified!
 */
void map_hardcode() {
    //positions in hex
    start = 0x00;
    end   = 0x22;

    // hardcoded 3x3 map
    orig[0][0]=0xDD;  orig[0][1]=0x81;  orig[0][2]=0xB7;
    orig[1][0]=0xCD;  orig[1][1]=0x00;  orig[1][2]=0x37;
    orig[2][0]=0xED;  orig[2][1]=0x64;  orig[2][2]=0x77;
}
/*
 *
 */
void map_load() {
  //load map into modifiable memory
  //don't look here for segment checking, will be different after pathfinding
  map[0][0]=orig[0][0]; map[0][1]=orig[0][1]; map[0][2]=orig[0][2];
  map[1][0]=orig[1][0]; map[1][1]=orig[1][1]; map[1][2]=orig[1][2];
  map[2][0]=orig[2][0]; map[2][1]=orig[2][1]; map[2][2]=orig[2][2];

  map_reset_parents();

  map_reset_cost();

}

void map_reset_parents(){
  mapp[0][0]=0xFF; mapp[0][1]=0xFF; mapp[0][2]=0xFF;
  mapp[1][0]=0xFF; mapp[1][1]=0xFF; mapp[1][2]=0xFF;
  mapp[2][0]=0xFF; mapp[2][1]=0xFF; mapp[2][2]=0xFF;

  // flag start parent as 0xDA (german for "there")
  mapp[hex2y(pos)][hex2x(pos)]=0xDA;
}

void map_reset_cost(){
  mapc[0][0]=0xFF; mapc[0][1]=0xFF; mapc[0][2]=0xFF;
  mapc[1][0]=0xFF; mapc[1][1]=0xFF; mapc[1][2]=0xFF;
  mapc[2][0]=0xFF; mapc[2][1]=0xFF; mapc[2][2]=0xFF;

  // set starting position cost to 0
  mapc[hex2y(pos)][hex2x(pos)]=0;
}

//Updates the map at the current position to hex (sensor input)
void map_update(unsigned char hex) {
  map[hex2y(pos)][hex2x(pos)] = hex;
  map_reset_cost();
  map_reset_parents();

  P1OUT ^= 0x01;
}
