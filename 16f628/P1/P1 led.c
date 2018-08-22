#include <16f628a.h>
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOPUT                    //No Power Up Timer
#FUSES INTRC_IO                    //Internal RC Osc
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOPROTECT                //Code not protected from reading
#use delay(clock=4000000)
#use fast_io(a)
#use fast_io(a)

void main()
{
   set_tris_b(0);
   set_tris_a(0);
   output_b(0);
   int a;
   while(true)
   {
      for(a=0;a<255;a++)
      {
         output_a(a);
         output_b(a);
         delay_ms(300);
      }
   }
}
