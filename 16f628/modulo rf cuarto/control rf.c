#include <16f628a.h>
#fuses INTRC_IO
#fuses NOWDT
#fuses NOMCLR
#fuses NOPUT
#fuses NOLVP
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#use delay(clock=4M)
#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06

void main()
{
   Trisa=0xFF;
   Trisb=0;
   Portb=0;
   while(true)
   {
      while(input(pin_a0))
         output_high(pin_b0);
      while(input(pin_a1))
         output_low(pin_b0);
      while(input(pin_a3))
         output_high(pin_b1);
      while(input(pin_a4))
         output_low(pin_b1);   
         
   }
}
