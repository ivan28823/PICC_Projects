#include <16f628a.h>

#use delay(int=4000000)
#fuses NOWDT
#fuses MCLR
#fuses NOPUT
#fuses INTRC
#fuses NOBROWNOUT
#fuses NOLVP
#fuses NOCPD
#fuses NOPROTECT
#use fast_io(b) 

void main(){
   set_tris_b(0b00000000);
   do{
   output_b(0b11001100);
   delay_ms(50);
   output_b(0);
   delay_ms(50);
   output_b(0b11001100);
   delay_ms(50);
   output_b(0);
   delay_ms(50);
   output_b(0b11001100);
   delay_ms(50);
   output_b(0);
   delay_ms(50);
   output_b(0b11001100);
   delay_ms(50);
   output_b(0);
   delay_ms(450);
   output_b(0b00110011);
   delay_ms(50);
   output_b(0);
   delay_ms(50);
   output_b(0b00110011);
   delay_ms(50);
   output_b(0);
   delay_ms(50);
   output_b(0b00110011);
   delay_ms(50);
   output_b(0);
   delay_ms(50);
   output_b(0b00110011);
   delay_ms(50);
   output_b(0);
   delay_ms(450);
   }
   while(TRUE);
   
}
