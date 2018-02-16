#include "defs.h"

// Scan surroundings at current position and compare with map segment
// If it differs, update map, then save map to file and recalculate path
void map_check() {
  unsigned char scan_segment = scan();
  unsigned char map_segment = robot.map.node[robot.pos.x][robot.pos.y].walls;

  // If scan and map segments are NOT identical
  if(scan_segment != map_segment) {
    // Update the segment at current position in the map struct
    map_update(scan_segment);

  }
  P1OUT ^= 0x01;
}

/*hardcodes node map into memory
 * For values refer to Map2Hex.xlsx
 * in a later update this should be automated
 */
void node_map_load() {
  /*--SIZE
   *
   */
  robot.map.nSize.x = 3;
  robot.map.nSize.y = 3;

  /*--START & FINISH--
   *
   */
  robot.map.start.x = 0;
  robot.map.start.y = 0;

  robot.map.finish.x= 2;
  robot.map.finish.y= 2;

  /*--WALLS--
   *
   */
  robot.map.node[0][0].walls = 0xDD;
  robot.map.node[0][1].walls = 0xA5;
  robot.map.node[0][2].walls = 0xF7;

  robot.map.node[1][0].walls = 0xCD;
  robot.map.node[1][1].walls = 0x35;
  robot.map.node[1][2].walls = 0xF7;

  robot.map.node[2][0].walls = 0xED;
  robot.map.node[2][1].walls = 0x75;
  robot.map.node[2][2].walls = 0xF7;


  /*--MOVECOST
   *
   */
  robot.map.node[0][0].movecost = 0xFFF;
  robot.map.node[0][1].movecost = 0xFFF;
  robot.map.node[0][2].movecost = 0xFFF;

  robot.map.node[1][0].movecost = 0xFFF;
  robot.map.node[1][1].movecost = 0xFFF;
  robot.map.node[1][2].movecost = 0xFFF;

  robot.map.node[2][0].movecost = 0xFFF;
  robot.map.node[2][1].movecost = 0xFFF;
  robot.map.node[2][2].movecost = 0xFFF;

  robot.map.node[robot.map.start.y][robot.map.start.x].movecost = 0;

  P1OUT ^= 0x01;
}

//Updates the map at the current position to hex (sensor input)
void map_update(unsigned char hex) {
  //loading current position
  int curx=0,cury=0;
  curx = robot.pos.x;
  cury = robot.pos.y;

  robot.map.node[curx][cury].walls = hex;

  P1OUT ^= 0x01;
}
