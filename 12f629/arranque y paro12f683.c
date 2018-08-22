#include <12f683.h>

#FUSES NOWDT                   
#FUSES INTRC_IO                       
#FUSES NOPUT                   
#FUSES NOMCLR                   
#FUSES NOPROTECT                
#FUSES NOCPD                   
#FUSES NOBROWNOUT              
#FUSES NOIESO                   
#FUSES FCMEN                    
#use delay(clock=4000000)
#use fast_io(a)
void main()
{
   setup_oscillator(OSC_4MHZ);
   set_tris_a(0b111000);
   output_a(0);
   while (true)
   {
      if(input(pin_a5)==1)
      {
         output_high(pin_a0);
         while(input(pin_a5));
      }
      if(input(pin_a4)==1)
      {
         output_low(pin_a0);
         while(input(pin_a4));
      }
   }  
}
