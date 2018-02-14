#include <msp430.h>

#define North       0x01
#define East        0x02
#define South       0x04
#define West        0x08

#define NorthEast   0x10
#define SouthEast   0x20
#define SouthWest   0x40
#define NorthWest   0x80

void initializePins()
{
    P1DIR |= 0x04;
    P1DIR |= 0x08;
    P1DIR |= 0x10;
    P1DIR |= 0x20;
    P4DIR |= 0x01;
    P4DIR |= 0x08;
    P3DIR |= 0x80;
    P8DIR |= 0x04;
}

void stepping(void)
{
    unsigned volatile int step = 1, counter = 0;        //defining step
    TA0CCR0 = 10000;
    TA0CTL = MC_1 + ID_0 + TASSEL_2 + TACLR;
    while(counter < 1000)
    {
        while((TA0CCTL0 & BIT0) == 0){}
        TA0CCTL0 &= ~BIT0;
        if(step == 1)                           //A1
        {
            P1OUT &= ~BIT2;
            P1OUT &= ~BIT3;
            P1OUT &= ~BIT4;
            P1OUT |= BIT5;
            step++;
            counter++;
        }
        else if(step == 2)                      //A1B1
        {
            P1OUT |= BIT2;
            P1OUT &= ~BIT3;
            P1OUT &= ~BIT4;
            P1OUT |= BIT5;
            step++;
            counter++;
        }
        else if(step == 3)                      //B1
        {
            P1OUT |= BIT2;
            P1OUT &= ~BIT3;
            P1OUT &= ~BIT4;
            P1OUT &= ~BIT5;
            step++;
            counter++;
        }
        else if(step == 4)
        {                                       // B1 A2
            P1OUT |= BIT2;
            P1OUT &= ~BIT3;
            P1OUT |= BIT4;
            P1OUT &= ~BIT5;
            step++;
            counter++;
        }
        else if(step == 5)                     //A2
        {
            P1OUT &= ~BIT2;
            P1OUT &= ~BIT3;
            P1OUT |= BIT4;
            P1OUT &= ~BIT5;
            step++;
            counter++;
        }
          else if(step == 6)                    // A2 B2
          {
              P1OUT &= ~BIT2;
              P1OUT |= BIT3;
              P1OUT |= BIT4;
              P1OUT &= ~BIT5;
              step++;
              counter++;
          }
          else if(step == 7)                    //B2
          {
              P1OUT &= ~BIT2;
              P1OUT |= BIT3;
              P1OUT &= ~BIT4;
              P1OUT &= ~BIT5;
              step++;
              counter++;
          }
          else if(step == 8)                    //B2 A1
          {
              P1OUT &= ~BIT2;
              P1OUT |= BIT3;
              P1OUT &= ~BIT4;
              P1OUT |= BIT5;
              step = 1;
              counter++;
          }
    }
}

void moveNorthWest()
{
    P4OUT |= BIT3;                                      //enable pair
    P4OUT |= BIT0;                                      //select direction
    stepping();                                         //call stepping function
    P4OUT &= ~BIT3;                                     //disable pair of wheels
}

void moveSouthEast()
{
    P4OUT |= BIT3;                                      //enable pair
    P4OUT &= ~BIT0;                                     //select direction
    stepping();                                         //call stepping function
    P4OUT &= ~BIT3;                                     //disable pair of wheels
}

void moveNorthEast()
{
    P3OUT |= BIT7;                                      //enable pair
    P8OUT |= BIT2;                                      //select direction
    stepping();                                         //call stepping function
    P3OUT &= ~BIT7;                                     //disable pair of wheels
}

void moveSouthWest()
{
    P3OUT |= BIT7;                                      //enable pair
    P8OUT &= ~BIT2;                                     //select direction
    stepping();                                         //call stepping function
    P3OUT &= ~BIT7;                                     //disable pair of wheels
}
void moveNorth()
{
    P4OUT |= BIT3;
    P4OUT |= BIT0;
    P3OUT |= BIT7;
    P8OUT |= BIT2;
    stepping();
    P4OUT &= ~ BIT3;
    P3OUT &= ~ BIT7;
}
void moveWest()
{
    P4OUT |= BIT3;
    P4OUT |= BIT0;
    P3OUT |= BIT7;
    P8OUT &= ~BIT2;
    stepping();
    P4OUT &= ~ BIT3;
    P3OUT &= ~ BIT7;
}
void moveSouth()
{
    P4OUT |= BIT3;
    P4OUT &= ~BIT0;
    P3OUT |= BIT7;
    P8OUT &= ~BIT2;
    stepping();
    P4OUT &= ~ BIT3;
    P3OUT &= ~ BIT7;
}
void moveEast()
{
    P4OUT |= BIT3;
    P4OUT &= ~BIT0;
    P3OUT |= BIT7;
    P8OUT |= BIT2;
    stepping();
    P4OUT &= ~ BIT3;
    P3OUT &= ~ BIT7;
}
void move(volatile unsigned int x)
{
    switch(x)
    {
    case 0x01: moveNorth();         break;
    case 0x02: moveEast();          break;
    case 0x04: moveSouth();         break;
    case 0x08: moveWest();          break;
    case 0x10: moveNorthEast();     break;
    case 0x20: moveSouthEast();     break;
    case 0x40: moveSouthWest();     break;
    case 0x80: moveNorthWest();     break;
    }
}
void delay()
{
    unsigned volatile long i = 200000;
    while(i > 0)
        i--;
}
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    delay();
    move(North);
    delay();
    move(South);
    delay();
    move(East);
    delay();
    move(West);
    delay();
    move(SouthEast);
    delay();
    move(NorthWest);
    delay();
    move(SouthWest);
    delay();
    move(NorthEast);
}
