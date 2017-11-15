#include <msp430x20x3.h>
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
TACCR0 = 5000;
TACTL = MC_1 | ID_0 | TASSEL_1 | TACLR;       //configure timer A

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
  volatile unsigned int step, counter;
  step = 1;
  counter = 0;
  if(x == 1){
    while(counter < 100){
      while((TACTL & 0x0001) == 0){}
      TACTL &= ~0x0001;
    }
  }
}
void 






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
  TACCR0 = 5000;
  TACTL = MC_1 | ID_0 | TASSEL_1 | TACLR;       //configure timer A
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
