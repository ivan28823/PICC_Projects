#include <16f628a.h>

#use delay(int=4000000)
#fuses NOWDT
#fuses NOMCLR
#fuses NOPUT
#fuses NOLVP
#fuses INTRC
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#use fast_io(b)

void main()
{
   int contador=255;
   short cond=0;
   set_tris_b(0);
   set_tris_a(0xFF);
   int8 time=1000;
   output_b(contador);
   delay_ms(2000);
   contador=0;
   output_b(contador);
   delay_ms(1000);
   while(true)
   {
      if(input(pin_a3)==1)
      {
         time=time-100;
         delay_ms(200);
         if(time<100)
         {
            time=1000;
         }
      }
      if(cond==true)
      {
         output_b(contador);
         contador=contador+1;
         delay_ms(time);
         if(contador==255)
         {
            contador=0;
         }
      }
      if(input(PIN_a0)==1)
      {
         cond=true;
         delay_ms(300);
      }
      if(input(PIN_a1)==1)
      {
         cond=false;
         delay_ms(300);
      }
      if(input(PIN_a2)==1)
      {
         contador=0,
         delay_ms(200);
         output_b(contador);
      }
   }  
}
