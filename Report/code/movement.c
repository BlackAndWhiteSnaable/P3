#include <msp430x20x3.h>

#define North           0x01
#define East            0x02
#define South           0x04
#define West            0x08

#define NorthEast       0x10
#define SouthEast       0x20
#define SouthWest       0x40
#define NorthWest       0x80

void stepping(void){
  unsigned int step = 1, counter = 0;   //defining step and counter 
                                        //variable           
  CCR0 = 8000;                          //upper limit for the timer
  TACTL = MC_1 | ID_0 | TASSEL_2 |TACLR;//initializing timer, up mode
                                        //divided by 1, source select,
                                        //clear
  while(counter < 1000){                //number of steps
    while((TACTL & 0x0001) == 0){}      //halfstepping from here down
    TACTL &= ~0x0001;                   //resetting the interrupt flag
    if(step == 1){                      //A1
      P1OUT &= ~(BIT1 + BIT2 + BIT3);
      P1OUT |= BIT4;
      step++;
      counter++;
    }
    else if(step == 2){                 //A1 B1
      P1OUT |= BIT1 + BIT4;
      P1OUT &= ~(BIT2 + BIT3);
      step++;
      counter++;
     }
    else if(step == 3){                 //B1
      P1OUT |= BIT1;
      P1OUT &= ~(BIT2 + BIT3 + BIT4);
      step++;
      counter++;
     }
    else if(step == 4){                 //B1 A2
      P1OUT |= BIT1 + BIT3;
      P1OUT &= ~(BIT2 + BIT4);
      step++;
      counter++;
    }
    else if(step == 5){                 //A2
      P1OUT &= ~(BIT1 + BIT2 + BIT4);
      P1OUT |= BIT3;
      step++;
      counter++;
    }
    else if(step == 6){                 //A2 B2
      P1OUT &= ~(BIT1 + BIT4);
      P1OUT |= BIT2 + BIT3;
      step++;
      counter++;
    }
    else if(step == 7){                 //B2
      P1OUT &= ~(BIT1 + BIT3 + BIT4);
      P1OUT |= BIT2;
      step++;
      counter++;
    }
    else if(step == 8){                 //B2 A1
      P1OUT &= ~(BIT1 + BIT3);
      P1OUT |= BIT2 + BIT4;
      step = 1;
      counter++;
    }
  }
}

void moveNorthWest(void){
  P1OUT |= BIT5                         //enable pair of wheels
  P1OUT |= BIT6;                        //choose direction                                                                                    
  stepping();                           //call stepping function
  P1OUT &= ~BIT5;                       //disable pair of wheels
}

void moveSouthEast(void){
  P1OUT |= BIT5;                        //enable pair of wheels
  P1OUT &= ~BIT6;                       //choose direction
  stepping();                           //call stepping funtion
  P1OUT &= ~BIT5;                       //disable pair of wheels
}

void moveNorthEast(void){
  P1OUT |= BIT7;                        //enable pair of wheels
  P2OUT |= BIT7;                        //choose direction
  stepping();                           //call stepping funtcion
  P1OUT &= ~BIT7;                       //disable pair of wheels 
}

void moveSouthWest(void){
  P1OUT |= BIT7;                        //enable the pair of wheels
  P2OUT &= ~BIT7;                       //choose direction
  stepping();                           //call stepping function
  P2OUT &= ~BIT7;                       //disable pair of wheels
}

void moveNorth(void){
  P1OUT |= BIT5;                        //enable first pair of wheels
  P1OUT |= BIT6;                        //choose direction
  P1OUT |= BIT7;                        //enable second pair of wheels
  P2OUT |= BIT7;                        //choose direction
  stepping();                           //call stepping funcion
  P1OUT &= ~(BIT5 + BIT7);              //disable both pairs of wheels
}

void moveWest(void){
  P1OUT |= BIT5;                        //enable first pair of wheels
  P1OUT |= BIT6;                        //choose direction
  P1OUT |= BIT7;                        //enable second pair of wheels
  P2OUT &= ~BIT7;                       //choose direction                               
  stepping();                           //call stepping function
  P1OUT &= ~(BIT5 + BIT7);              //disable both pairs of wheels
}

void moveSouth(void){
  P1OUT |= BIT5 + BIT7;                 //enable first pair of wheels
  P1OUT &= ~BIT6;                       //choose direction        
  P1OUT |= BIT7;                        //enable second pair of wheels
  P2OUT &= ~BIT7;                       //choose direction
  stepping();                           //call stepping function
  P1OUT &= ~(BIT5 + BIT7);              //disable both pairs of wheels
}

void moveEast(void){
  P1OUT |= BIT5 + BIT7;                 //enable first pair of wheels
  P1OUT &= ~BIT6;                       //choose direction 
  P2OUT |= BIT7;                        //enable second pair of wheels
  P1OUT |= BIT7;                        //choose direction
  stepping();                           //call stepping function
  P1OUT &= ~(BIT5 + BIT7);              //disable both pairs of wheels 
}

void move(unsigned int x){
  switch(x){
  case 0x01: moveNorth();       break;  
  case 0x02: moveEast();        break;
  case 0x04: moveSouth();       break;
  case 0x08: moveWest();        break;
  case 0x10: moveNorthEast();   break;
  case 0x20: moveSouthEast();   break;
  case 0x40: moveSouthWest();   break;
  case 0x80: moveNorthWest();   break;
  }
}