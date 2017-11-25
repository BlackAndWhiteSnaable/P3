struct Robot {
  struct Point pos;
  struct Maps map;
  struct Nodes **node; // testing node struts in 2D array
  // IDEA We could setup other data we need such as:
  // struct Path
  // struct Motors
  // struct LEDs
};

struct Robot *init_robot();
void robot_print(struct Robot *robot);
