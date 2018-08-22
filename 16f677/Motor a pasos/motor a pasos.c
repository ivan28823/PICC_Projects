#include <16f628a.h>
#fuses INTRC
#fuses NOWDT
#fuses NOMCLR
#fuses NOPUT
#fuses NOLVP
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#use delay(clock=4000000)
#BYTE TRISA=0X85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
//Variables generales
   short inf;
   int i,vel,pasos,lado;
   //long ;
   //float ;
//Interrupcion_externa
#int_ext
void reset(void)
{
   
}
//Prototipos de funciones
   void led_blink(int rep);
//Programa Principal
void main()
{
   Trisa=0b01111111;
   Trisb=0b11110000;
   Portb=0;
   enable_interrupts(int_ext);
   enable_interrupts(global);
   for(;;)
   {
      led_blink(5);
      while(!(input(pin_b2) | input(pin_b1)));
      vel=input_a();
      led_blink(3);
      pasos=input_a();
      if(pasos>=255)
         inf=true;
      for(i=0;i<pasos;i++)
      {
         portb=0b00010000;
         portb<<=1;
      }
      
   }
}
void led_blink(int rep)
{
   for(int r=0;r<rep;++r)
   {
      output_high(pin_a7);
      delay_ms(200);
      output_high(pin_a7);
      delay_ms(200);
   }
}
