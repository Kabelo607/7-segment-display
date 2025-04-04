#include <reg51.h> //include headerfile for 8051 registers


 sbit block = P1^0; //port and pin to create wave on
 int i=1; //counter variable
 unsigned char A;
 unsigned int speed = 2; // speed variable (to change duty cycle)
 //function to create an interrupt so pulses switches between high and low
 void tim0 (void) interrupt 1
  {
 i++;

 if (i == 11)
 {
 i =1;
 }
 if (i < (speed+1))
 {
 block = 1; //high
 }
 else
 {
 block = 0; //low
 }
 }

 void main (void)
 {
 //timer setup
 TMOD = 0x02; //set timer mode to timer 0, mode 2
 IE = 0x82 ; //set value for the interrupt enable
 SCON = 0x50; //set value for serial connect register
 TH0 = 0xFB;// set timer to be high for 10% of the total period
 TH1 = -3; //baud rate = 9600
 TR0 = 1; //activate timer 0


 while (1)
 {
 while(RI != 0) //while the user entered a value...
 {
 A = SBUF; //move the user's entered value into A
 if((A == '+')) //test whether user entered a +
 {
 if (speed != 9)
 {
 speed++; //increase speed (duty cycle)
 }
 }
 else if (A=='-') //test to see whether the user entered a -
 {
 if (speed != 1)
 {
 speed--; //decrease speed (duty cycle)
 }
 }
 RI = 0; //allow user to enter something again by clearing receive intterupt register
 }}}
