#include <18F4550.h>
// #fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN, MCLR //20MHz
#fuses HS,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL2,CPUDIV1,VREGEN,MCLR,NOBROWNOUT //8MHz
#use delay(clock=48000000)

#include "lib_rf2gh4_10_4550.h" // Librería modificada para el nRF24L01 con el PIC 18F4550.

#byte porta=0xF80               // Dirección de los puertos A, B, C, D y E.
#byte portb=0xF81
#byte portc=0xF82
#byte portd=0xF83
#byte porte=0xF84
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)

int8 ret2;
void pwm_servo (int periodo,long pin,long alto);
long sensor_distancia(long trig,long echo);
long distancia;

#int_ext2                  
void int_RB2()               
{                            
   int8 ret1,recepcion;
   long pwm;
   
   ret1 = RF_RECEIVE();
   if ( (ret1 == 0) || (ret1 == 1) )
   {
      do
      {  
         recepcion=RF_DATA[0];
         switch(recepcion)
         {
            case 0:
               output_low(pin_d0); //adelante
               output_low(pin_d1); //atras
            break;
            case 1:
               if(distancia>20)
               {output_high(pin_d0);
               output_low(pin_d1);}
            break;
            case 2:
               output_high(pin_d1);
               output_low(pin_d0);
            break;
            case 3:
              output_low(pin_d0);
              output_low(pin_d1);
              pwm=pwm-100;
              if(pwm<900)
                  {pwm=900;}
              pwm_servo (5,pin_d2,pwm);
            break;
            case 4:
              output_low(pin_d0);
              output_low(pin_d1);
              pwm=pwm+100;
              if(pwm>2100)
                  {pwm=2100;}
              pwm_servo (5,pin_d2,pwm);
            break;
            case 5:
            if(distancia>20)
            {
               output_high(pin_d0);
                 output_low(pin_d1);
                 pwm=pwm-100;
                 if(pwm<900)
                     {pwm=900;}
                 pwm_servo (5,pin_d2,pwm);
            }
            break;
            case 6:
            if(distancia>20)
            {
               output_high(pin_d0);
              output_low(pin_d1);
              pwm=pwm+100;
              if(pwm>2100)
                  {pwm=2100;}
              pwm_servo (5,pin_d2,pwm);
            }
            break;
            case 7:
            if(distancia>20)
            {
              output_high(pin_d0);
              output_low(pin_d1);
              pwm=1575;
              pwm_servo (5,pin_d2,pwm);
            }
            break;
            case 8:
               output_low(pin_d0);
              output_high(pin_d1);
              pwm=pwm-100;
              if(pwm<900)
                  {pwm=900;}
              pwm_servo (5,pin_d2,pwm);
            break;
            case 9:
               output_low(pin_d0);
              output_high(pin_d1);
              pwm=pwm+100;
              if(pwm>2100)
                  {pwm=2100;}
              pwm_servo (5,pin_d2,pwm);
            break;
            case 10:
               output_low(pin_d0);
              output_high(pin_d1);
              pwm=1575;
              pwm_servo (5,pin_d2,pwm);
            break;
            case 11:
              pwm=1575;
              pwm_servo (5,pin_d2,pwm); 
            break;
         }
         output_toggle(pin_b7);
         ret1 = RF_RECEIVE();
      }while ( (ret1 == 0) || (ret1 == 1) );
   }  
}
/*#INT_TIMER0
void timer0()
{
   int8 var1;
   distancia=sensor_distancia(pin_d3,pin_d4);
   if(distancia>254)
   {
      var1=255;
   }else
   {var1=distancia;}
   RF_DATA[0] =var1;     // El contenido del contador lo cargo en RF_DATA[0] para ser enviado.
   RF_DIR=0x05;           // Dirección del receptor.
   ret2=RF_SEND();
}*/
void main()
{  
   set_tris_a(0b00000001);
   set_tris_b(0b00000101);
   set_tris_c(0b00000000);
   set_tris_d(0b00010000);
   //SETUP_TIMER_0(T0_INTERNAL | T0_DIV_64);
   SETUP_TIMER_1(T1_INTERNAL | T1_DIV_BY_2);
   //ENABLE_INTERRUPTS(INT_TIMER0);
   //ENABLE_INTERRUPTS(Global);
   RF_INT_EN();              // Habilitar interrupción RB0/INT.
   RF_CONFIG_SPI();          // Configurar módulo SPI del PIC.
   RF_CONFIG(0x40,0x0F);     // Configurar módulo RF canal y dirección de recepción de datos para este PIC.
   RF_ON();                  // Activar el módulo RF.
   
   delay_ms(5);// Dejamos como mínimo 2.5ms para dar tiempo a iniciarse el transceptor.
   pwm_servo (30,pin_d2,1575);
   output_d(0);
   output_high(pin_a0);
   long derecha,izquierda;
   while(true)
   {
      if((ret2==1) | (ret2==2))
      {
         output_low(pin_d0);
         output_low(pin_d1);
         output_low(pin_d2);
      }
      if(input(pin_a0)==1)
      {
      output_high(pin_b7);
      output_low(pin_d1);
      //disable_interrupts(global);
         while(true)
         {
            if(sensor_distancia(pin_d3,pin_d4)>25)
            {output_high(pin_d0);}
            else
            {
               output_low(pin_d0);
               pwm_servo (50,pin_d2,900); //izquierda
               izquierda=sensor_distancia(pin_d3,pin_d4);
               pwm_servo (50,pin_d2,2100); //derecha
               derecha=sensor_distancia(pin_d3,pin_d4);
               if(izquierda>derecha)
               {
                  pwm_servo (50,pin_d2,900); //izquierda
                  output_high(pin_d0);
                  delay_ms(600);
                  pwm_servo (50,pin_d2,1575);
               }else
               if(derecha>izquierda)
               {
                  pwm_servo (50,pin_d2,2100);
                  output_high(pin_d0);
                  delay_ms(600);
                  pwm_servo (50,pin_d2,1575);
               }  
            }
         }
      }
   }
}
void pwm_servo (int periodo,long pin,long alto)
{
  //pwm a 50hz ancho de pulso 20ms
  long bajo;
  int a;
  bajo=20000-alto;
  for(a=0;a<periodo;a++)
  {
     !output_high(pin);
     delay_us(alto);
     !output_low(pin);
     delay_us(bajo);
  }
}
long sensor_distancia(long trig,long echo)
{
      output_high(trig);                   
      delay_us(20);                       
      output_low(trig);
      while(!input(echo));                     
      set_timer1(0);                         
      while(input(echo));                     
      return (get_timer1()/58);
      
}
