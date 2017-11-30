#include <msp430x20x3.h>
#define North           1
#define East            2
#define South           4
#define West            8
#define NorthEast       16
#define SouthEast       32
#define SouthWest       64
#define NorthWest       128


void stepping(void){
  int step = 1, counter = 0;
  CCR0 = 8000;
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;
  while(counter < 1000){                        //number of steps
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
  }
}
void moveNorthWest(void){
  P1OUT |= 0x20;                                //enable the pair of wheels
  P1OUT |= 0x40;                                //choose direction
  stepping();                                     
  P1OUT &= ~0x20;
}
void moveSouthEast(void){
  P1OUT |= 0x20;                                //enable the pair of wheels
  P1OUT &= ~0x40;                               //choose direction
  stepping();
  P1OUT &= ~0x20;
}
void moveNorthEast(void){
  P1OUT |= 0x80;                                //enable the pair of wheels
  P2OUT |= 0x80;                                //choose direction
  stepping();
  P1OUT &= ~0x80;
}
void moveSouthWest(void){
  P1OUT |= 0x80;                                //enable the pair of wheels
  P2OUT &= ~0x80;                               //choose direction
  stepping();
  P2OUT &= ~0x80;
}
void moveNorth(void){
  P1OUT |= 0x20;                                //enable first pair of wheels
  P1OUT |= 0x40;                                //select direction
  P1OUT |= 0x80;                                //enable second pair of wheels
  P2OUT |= 0x80;                                //select direction
  stepping();
  P1OUT &= ~0x20;
  P1OUT &= ~0x80;
}
void moveWest(void){
  P1OUT |= 0x80;                                //enable first pair of wheels
  P2OUT &= ~0x80;                               //select direction
  P1OUT |= 0x20;                                //enable second pair of wheels
  P1OUT |= 0x40;                                //select direction
  stepping();
  P1OUT &= ~0x20;
  P1OUT &= ~0x80; 
}
void moveSouth(void){
  P1OUT |= 0x80;                                //enable first pair of wheels
  P2OUT &= ~0x80;                               //select direction
  P1OUT |= 0x20;                                //enable second pair of wheels
  P1OUT &= ~0x40;                               //select direction
  stepping();
  P1OUT &= ~0x20;
  P1OUT &= ~0x80;
  
}
void moveEast(void){
  P1OUT |= 0x80;                                //enable first pair of wheels
  P2OUT |= 0x80;                                //select direction
  P1OUT |= 0x20;                                //enable second pair of wheels
  P1OUT &= ~0x40;                               //select direction
  stepping();
  P1OUT &= ~0x20;
  P1OUT &= ~0x80;
}

void move(unsigned volatile int x){
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

void wait(void){
  TACTL = MC_2 | ID_3 | TASSEL_2 |TACLR;
  unsigned volatile int waitingTime = 0;
  while(waitingTime < 10){
    while((TACTL & 0x0001) == 0){}
    TACTL &= ~0x0001;
    waitingTime++;
  }
}

void main(void){
  WDTCTL = WDTPW | WDTHOLD;                       //Stop Watchdog Timer
  P1DIR |= 0x02;                                  //configure p1.1 P3 as output step1
  P1DIR |= 0x04;                                  //configure p1.2 P4 as output step2
  P1DIR |= 0x08;                                  //configure p1.3 P5 as ouptut step3
  P1DIR |= 0x10;                                  //configure p1.4 P6 as output step4
  P1DIR |= 0x20;                                  //configure p1.5 P7 as output enable first pair
  P1DIR |= 0x40;                                  //configure p1.6 p8 as output select direction of first pair
  P1DIR |= 0x80;                                  //configure p1.7 p9 as output enable second pair
  P2SEL = 0;
  P2DIR |= 0x80;                                  //configure p2.7 p12 as output select direction of second pair
  P1OUT &= ~0x02;  
  P1OUT &= ~0x04;                            
  P1OUT &= ~0x08;                                 
  P1OUT &= ~0x10;                                  
  P1OUT &= ~0x20;                                 
  P1OUT &= ~0x40;                                  
  P1OUT &= ~0x80;
  P2OUT &= ~0x80; 
  move(NorthWest);
  wait();
  move(SouthEast);
  wait();
  move(NorthEast);
  wait();
  move(SouthWest);
  wait();
  move(North);
  wait();
  move(South);
  wait();
  move(West);
  wait();
  move(East);
}
