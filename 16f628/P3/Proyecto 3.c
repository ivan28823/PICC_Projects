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
   set_tris_b(0b00000000);
   int x=1;
   while(true)
   {
     x=1;
     for(int y=0;y<8;y++)
     {
      output_b(x);
      delay_ms(30);
      x=x<<1;
     }
     x=128;
     for(int xy=0;xy<8;xy++)
     {
      output_b(x);
      delay_ms(30);
      x=x>>1;
     }
   }
}
