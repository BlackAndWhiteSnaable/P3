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
 */
void map_setup(void) {
    //positions in hex
    start = 0x00;
    end   = 0x22;
    pos   = 0x11;

    // hardcoded 3x3 map
     map[0][0]=0xDD;  map[0][1]=0x81;  map[0][2]=0xF7;
     map[1][0]=0xCD;  map[1][1]=0x00;  map[1][2]=0x37;
     map[2][0]=0xED;  map[2][1]=0x64;  map[2][2]=0x77;

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
