#include <16f628a.h>

#fuses INTRC_IO
#fuses NOWDT
#fuses NOMCLR
#fuses NOPUT
#fuses NOLVP
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
/*#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06*/
#use fast_io(b)
#use delay(clock=4M)
#define i 1100
#define d 2000
#define c 1600

void pwm_servo(int pin,long alto);
void main()
{
   set_tris_b(0);
   output_low(pin_b0);
   while(true)
   {
      delay_ms(1000);
      pwm_servo(pin_b0,i);
      delay_ms(1000);
      pwm_servo(pin_b0,d);
      delay_ms(1000);
      pwm_servo(pin_b0,c);
      delay_ms(1000);
      //pwm_servo(pin_b0,);
   }
}
void pwm_servo (int pin,long alto)
{
  //pwm a 50hz ancho de pulso 20ms
  long bajo;
  int a;
  bajo=20000-alto;
  for(a=0;a<50;a++)
  {
     output_high(pin);
     delay_us(alto);
     output_low(pin);
     delay_us(bajo);
  }
}
