#include <msp430x20x3.h>


void main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                             
  unsigned volatile int step, counter;
  step = 1;
  counter = 0;
  P1DIR |= 0x02;                                //p1.1 to B1            P3
  P1DIR |= 0x04;                                //p1.2 to B2            P4       
  P1DIR |= 0x08;                                //p1.3 to A2            P5
  P1DIR |= 0x10;                                //p1.4 to A1            P6
  P1DIR |= 0x20;                                //p1.5 tristate buffer, enable or disable pair of wheels
  P1DIR |= 0x40;                                //p1.6 to tristate buffers, to select the direction of rotation
  TACCR0 = 8000;                                //delay between the steps
  TACTL = MC_1 | ID_0 | TASSEL_2 | TACLR;       //configure timer A0
  P1OUT |= 0x20;                                //enable first pair of wheels
  P1OUT |= 0x40;                                //choose direction
  while(counter < 2000){                        //number of steps
    while((TACTL & 0x0001) == 0){}              //halfstepping from here down
    TACTL &= ~0x0001;
    if(step == 1){                      //A1
      P1OUT &= ~0x02;
      P1OUT &= ~0x04;
      P1OUT &= ~0x08;
      P1OUT |= 0x10;
      step++;
      counter++;
    }
    else if(step == 2){                 //A1 B1
      P1OUT |= 0x02;
      P1OUT &= ~0x04;
      P1OUT &= ~0x08;
      P1OUT |= 0x10;
      step++;
      counter++;
    }
    else if(step == 3){                 //B1 
      P1OUT |= 0x02;
      P1OUT &= ~0x04;
      P1OUT &= ~0x08;
      P1OUT &= ~0x10;
      step++;
      counter++;
      }
    else if(step == 4){                 //B1 A2
      P1OUT |= 0x02;
      P1OUT &= ~0x04;
      P1OUT |= 0x08;
      P1OUT &= ~0x10;
      step++;
      counter++;
    }
    else if(step == 5){                 //A2 
      P1OUT &= ~0x02;
      P1OUT &= ~0x04;
      P1OUT |= 0x08;
      P1OUT &= ~0x10;
      step++;
      counter++;
    }
    else if(step == 6){                 //A2 B2
      P1OUT &= ~0x02;
      P1OUT |= 0x04;
      P1OUT |= 0x08;
      P1OUT &= ~0x10;
      step++;
      counter++;
    }
    else if(step == 7){                 //B2
      P1OUT &= ~0x02;
      P1OUT |= 0x04;
      P1OUT &= ~0x08;
      P1OUT &= ~0x10;
      step++;
      counter++;
      }
    else if(step == 8){                 //B2 A1
      P1OUT &= ~0x02;
      P1OUT |= 0x04;
      P1OUT &= ~0x08;
      P1OUT |= 0x10;
      step = 1;
      counter++;
    }
  }                                   //end program
  P1OUT &= ~0x02;
  P1OUT &= ~0x04;
  P1OUT &= ~0x08;
  P1OUT &= ~0x10;
}

/*
#define N       1
#define E       2
#define S       4
#define W       8
#define NE      16
#define SE      32
#define SW      64
#define NW      128

WDTCTL = WDTPW | WDTHOLD;                       //Stop Watchdog Timer
P1DIR |= 0x02;                                  //configure p1.1 P3 as output
P1DIR |= 0x04;                                  //configure p1.2 P4 as output
P1DIR |= 0x08;                                  //configure p1.3 P5 as ouptut
P1DIR |= 0x10;                                  //configure p1.4 P6 as output
P1DIR |= 0x20;                                  //configure p1.5 P7 as output
P1DIR |= 0x40;                                  //configure p1.6 p8 as output
P1DIR |= 0x80;                                  //configure p1.7 p9 as output
P2DIR |= 0x40;                                  //configure p2.6    as output
P2DIR |= 0x80;                                  //configure p2.7    as output          

void main(void){
  move(N);
  move(E);
  move(S);
  move(W);
  move(NE);
  move(SE);
  move(SW);
  move(NW);
}
void move(uint8_t x){
  switch(x){
  case 1: moveNorth(); break;
  case 2: moveEast(); break;
  case 4: moveSouth(); break;
  case 8: moveWest(); break;
  case 16: moveNorthEast(); break;
  case 32: moveSouthEast(); break;
  case 64: moveSouthWest(); break;
  case 128: moveNorthWest(); break;
  }
}

void moveNorth(){
  TACCR0 = 5000;
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;
  volatile unsigned int step, counter;
  step = 1;
  counter = 0;
  while(counter <= 5000){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    if(step == 1){}
    else if(step == 2){}
    else if(step == 3){}
    else if(step == 4){};
  }
}
void moveEast(){
  TACCR0 = 5000;
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;
  volatile unsigned int step, counter;
  step = 1;
  counter = 0;
  while(counter <= 5000){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    if(step == 1){}
    else if(step == 2){}
    else if(step == 3){}
    else if(step == 4){};
  }
}
void moveSouth(){
  TACCR0 = 5000;
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;
  volatile unsigned int step, counter;
  step = 1;
  counter = 0;
  while(counter <= 5000){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    if(step == 1){}
    else if(step == 2){}
    else if(step == 3){}
    else if(step == 4){};
  }
}
void moveWest(){
  TACCR0 = 5000;
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;
  volatile unsigned int step, counter;
  step = 1;
  counter = 0;
  while(counter <= 5000){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    if(step == 1){}
    else if(step == 2){}
    else if(step == 3){}
    else if(step == 4){};
  }
}
void moveNorthEast(){
  TACCR0 = 5000;
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;
  volatile unsigned int step, counter;
  step = 1;
  counter = 0;
  while(counter <= 7500){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    if(step == 1){}
    else if(step == 2){}
    else if(step == 3){}
    else if(step == 4){};
  }
}
void moveSouthEast(){
  TACCR0 = 5000;
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;
  volatile unsigned int step, counter;
  step = 1;
  counter = 0;
  while(counter <= 7500){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    if(step == 1){}
    else if(step == 2){}
    else if(step == 3){}
    else if(step == 4){};
  }
}
void moveSouthWest(){
  TACCR0 = 7500;
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;
  volatile unsigned int step, counter;
  step = 1;
  counter = 0;
  while(counter <= 5000){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    if(step == 1){}
    else if(step == 2){}
    else if(step == 3){}
    else if(step == 4){};
  }
}
void moveNorhtWest(){
  TACCR0 = 7500;
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;
  volatile unsigned int step, counter;
  step = 1;
  counter = 0;
  while(counter <= 5000){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    if(step == 1){}
    else if(step == 2){}
    else if(step == 3){}
    else if(step == 4){};
  }
}*/


/*
void main (void){
  volatile unsigned int step, counter;          //declare variable for steps
  step = 1;                                     //initialize variable for steps
  counter = 0;
  WDTCTL = WDTPW | WDTHOLD;                     //Stop Watchdog Timer
  P1DIR |= 0x02;                                //configure p1.1 P3 as output
  P1DIR |= 0x04;                                //configure p1.2 P4 as output
  P1DIR |= 0x08;                                //configure p1.3 P5 as ouptut
  P1DIR |= 0x10;                                //configure p1.4 P6 as output
  //TACCR0 = 5000;
  TACTL = MC_2 | ID_0 | TASSEL_1 | TACLR;       //configure timer A
  while(counter < 100){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    if(step == 1){
      P1OUT |= 0x02;
      P1OUT &= ~0x04;
      P1OUT &= ~0x08;
      P1OUT &= ~0x10;
      step++;
      counter++;
    }
    else if(step == 2){
      P1OUT &= ~0x02;
      P1OUT |= 0x04;
      P1OUT &= ~0x08;
      P1OUT &= ~0x10;
      step++;
      counter++;
    }
    else if(step == 3){
      P1OUT &= ~0x02;
      P1OUT &= ~0x04;
      P1OUT |= 0x08;
      P1OUT &= ~0x10;
      step++;
      counter++;
    }
    else if(step == 4){
      P1OUT &= ~0x02;
      P1OUT &= ~0x04;
      P1OUT &= ~0x08;
      P1OUT |= 0x10;
      step = 1;
      counter++;
    }
  }                                   //end program
  P1OUT &= ~0x02;
  P1OUT &= ~0x04;
  P1OUT &= ~0x08;
  P1OUT &= ~0x10;
}*/
