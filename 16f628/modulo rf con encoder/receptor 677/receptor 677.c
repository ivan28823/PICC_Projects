#include <16F677.h>
#device adc=8
#FUSES NOWDT,HS,NOPUT,MCLR,NOPROTECT,NOCPD,NOBROWNOUT,IESO,FCMEN
#use delay(clock=8M)

#define c 1585
#define pin_c0 Adelante //c0
#define pin_c1 atras    //c1
#define pin_c2 ervo


#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
#BYTE TRISC=0x87
#BYTE PORTC=0x07

void modo_automatico();
void pwm_servo(int periodo,int pin,long alto);
long sensor_distancia(int trig,int echo);
int pulsadores();

long pwm=c,izquierda,derecha;
int timer=0;
short modo=0,servo=0;

#INT_TIMER0
void timer0()
{
   timer++;
   if(timer>20)
   {
      if(read_adc()>230)
      {output_low(pin_a2);}
      else
      {output_high(pin_a2);}
      if(modo==0)
      {
         timer=0;
         output_high(pin_c3);
         delay_us(200);
         output_low(pin_c3);
         delay_ms(270);
      }
      else
      {
         while(pulsadores()==11)
         {
            modo=0;
         }
      }
   }
}

void main()
{
   
   SETUP_ADC(ADC_CLOCK_DIV_2);
   SETUP_ADC_PORTS(sAN0 | VSS_VREF);
   SET_ADC_CHANNEL(0);
   SETUP_TIMER_0(T0_INTERNAL  | T0_DIV_256);
   SETUP_TIMER_1(T1_INTERNAL  | T1_DIV_BY_2);
   ENABLE_INTERRUPTS(INT_TIMER0);
   ENABLE_INTERRUPTS(Global);
   Trisb=0b11111011;
   trisa=255;
   trisc=0b00100000;
   Portc=0;
   while(true)
   {
      
      switch(pulsadores())
      {
         case 0:
            output_low(pin_c0); //adelante
            output_low(pin_c1); //atras
         break;
         case 1:
            output_high(pin_c0); //adelante
            output_low(pin_c1); //atras
         break;
         case 2:
            output_low(pin_c0); //adelante
            output_high(pin_c1); //atras
         break;
         case 3:
            output_low(pin_c0);
            output_low(pin_c1);
            pwm=pwm-40;
            if(pwm<900)
               {pwm=900;}
            servo=1;
         break;
         case 4:
            output_low(pin_c0);
            output_low(pin_c1);
            pwm=pwm+40;
            if(pwm>2100)
               {pwm=2100;}
            servo=1;
         break;
         case 5:
            output_low(pin_c0);
            output_low(pin_c1);
            pwm=c;
            servo=1;
         break;
         case 6:
            output_high(pin_c0);
            output_low(pin_c1);
            pwm=pwm-40;
            if(pwm<900)
               {pwm=900;}
            servo=1;
         break;
         case 7:
            output_high(pin_c0);
            output_low(pin_c1);
            pwm=pwm+40;
            if(pwm>2100)
               {pwm=2100;}
            servo=1;
         break;
         case 8:
            output_high(pin_c0);
            output_low(pin_c1);
            pwm=c;
            servo=1;
         break;
         case 9:
            output_low(pin_c0);
            output_high(pin_c1);
            pwm=pwm-40;
            if(pwm<900)
               {pwm=900;}
            servo=1;
         break;
         case 10:
            output_low(pin_c0);
            output_high(pin_c1);
            pwm=pwm+40;
            if(pwm>2100)
               {pwm=2100;}
            servo=1;
         break;
         case 11:
            switch(modo)
            {case 0: modo=1;
            break;
            case 1: modo=0;
            break;}
            while(pulsadores()==11);
         break;
      }
      if(servo==1)
      {
         servo=0;
         pwm_servo (8,pin_c2,pwm);
      }
      if(modo==1)
      {
         do
         {
            modo_automatico();
         }while(modo);
      }
   }
   
}
void pwm_servo(int periodo,int pin,long alto)
{
  //pwm a 50hz ancho de pulso 20ms
  long bajo;
  int a;
  bajo=20000-alto;
  for(a=0;a<periodo;a++)
  {
     output_high(pin);
     delay_us(alto);
     output_low(pin);
     delay_us(bajo);
  }
}
long sensor_distancia(int trig,int echo)
{
      output_high(trig);                   
      delay_us(20);                       
      output_low(trig);
      while(!input(echo));                     
      set_timer1(0);                         
      while(input(echo));                     
      return (get_timer1()/58);    
}

int pulsadores()
{
   if((!input(pin_b7) &&  !input(pin_b6) &&  input(pin_b5) &&  input(pin_b4))==1)
   {return(5);}
   if((input(pin_b7) &&  !input(pin_b6) &&  input(pin_b5) &&  !input(pin_b4))==1)
   {return(6);}
   if((input(pin_b7) &&  !input(pin_b6) &&  !input(pin_b5) &&  input(pin_b4))==1)
   {return(7);}
   if((input(pin_b7) &&  !input(pin_b6) &&  input(pin_b5) &&  input(pin_b4))==1)
   {return(8);}
   if((!input(pin_b7) &&  input(pin_b6) &&  input(pin_b5) &&  !input(pin_b4))==1)
   {return(9);}
   if((!input(pin_b7) &&  input(pin_b6) &&  !input(pin_b5) &&  input(pin_b4))==1)
   {return(10);}
   if((!input(pin_b7) &&  input(pin_b6) &&  input(pin_b5) &&  input(pin_b4))==1)
   {return(11);}
   if((input(pin_b7) &&  !input(pin_b6) &&  !input(pin_b5) &&  !input(pin_b4))==1)
   {return(1);}
   if((!input(pin_b7) &&  input(pin_b6) &&  !input(pin_b5) &&  !input(pin_b4))==1)
   {return(2);}
   if((!input(pin_b7) &&  !input(pin_b6) &&  input(pin_b5) &&  !input(pin_b4))==1)
   {return(3);}
   if((!input(pin_b7) &&  !input(pin_b6) &&  !input(pin_b5) &&  input(pin_b4))==1)
   {return(4);}
   if((input(pin_b7) &&  input(pin_b6) &&  input(pin_b5) &&  input(pin_b4))==1)
   {return(0);}
   if((!input(pin_b7) &&  !input(pin_b6) &&  !input(pin_b5) &&  !input(pin_b4))==1)
   {return(0);}
}

void modo_automatico()
{
   if(sensor_distancia(pin_c4,pin_c5)>30)
      {output_high(pin_c0);
       output_low(pin_c1);}
      else
      {
         output_low(pin_c0);
         pwm_servo (50,pin_c2,900); //izquierda
         izquierda=sensor_distancia(pin_c4,pin_c5);
         pwm_servo (50,pin_c2,2100); //derecha
         derecha=sensor_distancia(pin_c4,pin_c5);
         if(izquierda>derecha)
         {
            pwm_servo (40,pin_c2,2100);
            output_high(pin_c1);
            delay_ms(500);
            output_low(pin_c1);
            pwm_servo (40,pin_c2,900); //izquierda
            output_high(pin_c0);
            delay_ms(700);
            pwm_servo (50,pin_c2,c);
         }
         else
         {
            pwm_servo (40,pin_c2,900);
            output_high(pin_c1);
            delay_ms(500);
            output_low(pin_c1);
            pwm_servo (40,pin_c2,2100);
            output_high(pin_c0);
            delay_ms(700);
            pwm_servo (40,pin_c2,c);
         }  
      }
}

