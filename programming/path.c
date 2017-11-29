#include "defs.h"

void path_test(Robot *robot) {

  // Initialize head of priority queues for the queues unchecked and checked
  TopStack *unchecked;
  unchecked = init_queue();

  TopStack *checked;
  checked = init_queue();

  // Set some dumme movecost values for testing
  robot->map.node[0][0].movecost = 1;
  robot->map.node[0][1].movecost = 2;
  robot->map.node[0][2].movecost = 3;
  robot->map.node[0][3].movecost = 4;

  // Push some values
  push(unchecked, &robot->map.node[0][0]);
  push(unchecked, &robot->map.node[0][1]);
  push(checked, &robot->map.node[0][2]);
  push(checked, &robot->map.node[0][3]);

  //pop(ts);          // remove first element from stack
  //emptyStack(ts);   // remove all elements from stack

  // Print queues
  printf("\nUnchecked:\n");
  printStack(unchecked);

  printf("\nChecked:\n");
  printStack(checked);
}
