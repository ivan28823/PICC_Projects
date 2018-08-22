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
#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
//#BYTE OPTION_REG=0x81

void main()
{
   Trisa=255;
   Trisb=0;
   Portb=0;
   int valor;
   while(true)
   {
   valor=Porta;
   Portb=valor;
   
/*      Portb=0b00000001;
      delay_ms(200);
      Portb=2;
      delay_ms(200);
      Portb=4;
      delay_ms(200);
      Portb=8;
      delay_ms(200);
      Portb=16;
      delay_ms(200);
      Portb=32;
      delay_ms(200);
      Portb=64;
      delay_ms(200);
      Portb=128;
      delay_ms(200);
     */
   }
}
