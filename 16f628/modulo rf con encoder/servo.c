#include <16f628a.h>

#fuses INTRC_IO
#fuses NOWDT
#fuses NOMCLR
#fuses NOPUT
#fuses NOLVP
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
#use fast_io(b)
#use fast_io(a)
#use delay(clock=4M)


void pwm_servo(int pin,long alto);
long sensor_distancia(int echo,int trig);
int contador=0;

#INT_TIMER0
void estado()
{
   contador++;
   if(contador>35)
   {
      contador=0;
      output_high(pin_b7);
      delay_us(300);
      output_low(pin_b7);
   }
}
void main()
{
   set_tris_b(0b00010000);
   set_tris_a(255);
   output_b(0);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_timer_0(T0_INTERNAL|T0_DIV_256);
   ENABLE_INTERRUPTS(INT_TIMER0);
   ENABLE_INTERRUPTS(GLOBAL);
   long pwm=1500,distancia;
   short ac=0;
   pwm_servo(pin_b0,1500);
   while(true)
   {
      while(input(pin_a0) && input(pin_a1) && input(pin_a2) && input(pin_a3))
      {output_b(0);
         }
         if((input(pin_a0) & input(pin_a1) & input(pin_a2) & !input(pin_a3))==1)
         {  output_low(pin_b2);
            while(input(pin_a0) & input(pin_a1) & input(pin_a2) & !input(pin_a3));
            output_toggle(pin_b1);
         }
         distancia=sensor_distancia(pin_b4,pin_b5);
         if(distancia>20)
         {
            if(input(pin_a2)==1)
               {output_high(pin_b2);}
            else
               {output_low(pin_b2);}
         }
         else
         {
            output_low(pin_b2);
         }
            if(input(pin_a3)==1)
               {output_high(pin_b3);}
            else
               {output_low(pin_b3);}
            if(input(pin_a1)==1)
            {
               ac=1;
               pwm=pwm-100;
               if(pwm<900)
                  {pwm=900;}
            }
            if(input(pin_a0)==1)
            {
               pwm=pwm+100;
               if(pwm>2100)
                  {pwm=2100;}
               ac=1;
            }
            if((input(pin_a0) & input(pin_a1))==1)
            {
               pwm=1500;
               ac=1;
            }
            if(ac==1)
            {
               pwm_servo(pin_b0,pwm);
               ac=0;
            }
   }
}
void pwm_servo (int pin,long alto)
{
  //pwm a 50hz ancho de pulso 20ms
  long bajo;
  int a;
  bajo=20000-alto;
  for(a=0;a<5;a++)
  {
     output_high(pin);
     delay_us(alto);
     output_low(pin);
     delay_us(bajo);
  }
}
long sensor_distancia(int echo,int trig)
{
      output_high(trig);                   
      delay_us(20);                       
      output_low(trig);
      while(!input(echo));                     
      set_timer1(0);                         
      while(input(echo));                     
      return (get_timer1()/58);
      
}
