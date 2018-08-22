#include <16f677.h>
#device adc=10

#FUSES NOWDT                 
#FUSES INTRC_IO               
#FUSES NOMCLR                   
#FUSES NOBROWNOUT
#FUSES NOPUT
#FUSES NOPROTECT
#FUSES NOCPD              

#use delay(clock=8000000)
#BYTE TRISA=0x85
#BYTE TRISB=0x86
#BYTE TRISC=0x87
#BYTE PORTA=0x05
#BYTE PORTB=0x06
#BYTE PORTC=0x07
//uso de una LCD
#define LCD_ENABLE_PIN  PIN_C0                                   
#define LCD_RS_PIN      PIN_C1                                    
#define LCD_RW_PIN      PIN_C2                                    
#define LCD_DATA4       PIN_B4                                      
#define LCD_DATA5       PIN_B5                                    
#define LCD_DATA6       PIN_B6                                    
#define LCD_DATA7       PIN_B7
#include <lcd.c>
//alias a pines
#define izq       PIN_A5
#define cent      PIN_A4
#define der       PIN_A3
//#define der       PIN_A1
//#define cent      PIN_A4
//#define izq       PIN_A5
//Prototipo de funciones
   int botones(void);
//variables generales
   short vaux,rv;
   int i,bot,modo,dir;
   long p,adc,pasos,pause;
   //float ;
//Programa principal
void main()
{
   setup_oscillator(OSC_8MHZ);
   Trisa=0xFF;
   Trisb=0;
   Trisc=0;
   Portc=0;
   setup_adc_ports(sAN2);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(2);
   delay_us(15);
   lcd_init();
   lcd_putc("\fControl de Motor\n  Paso a Paso");
   delay_ms(1000);
   for(;;)
   {
      Portc=0;
      rv=0;
      lcd_putc("\fBoton izquierdo:\ngiro a la izqier");
      delay_ms(1000);
      lcd_putc("\f Boton centro:\npara un giro inf");
      delay_ms(1000);
      lcd_putc("\fBoton derecho:\n giro a la dere");
      delay_ms(1000);
      lcd_putc("\fPresione un\n  Boton...");
      do
      {
         bot=botones();
      }while(!bot);
      delay_ms(150);
      if(bot=='c')
      {
         vaux=false;
         modo='c';
      }
      else
      {
         vaux=true;
         modo=bot;
         lcd_putc("\fEstablece # paso\ncon el pot");
         delay_ms(1500);
      }
      while(vaux)
      {
         adc=read_adc();
         if(adc>1000)
            adc=1000;
         if(adc<1)
            adc=1;
         if(rv==0)
            {printf(lcd_putc,"\fPasos =%lu\npres un boton",adc);}
         else
            {printf(lcd_putc,"\fPausa =%lu\npres un boton",adc);}
         for(i=0;i<255;i++)
         {
            if(botones()!=0)
            {
               if(rv==0)
               {   
                  rv=1;
                  pasos=adc;
                  delay_ms(100);
                  break;
               }
               else
               {   
                  vaux=false;
                  pause=adc;
                  delay_ms(200);
                  break;
               }
            }   
         }
         delay_ms(90);
      }
      if (modo=='c')
      {
         lcd_putc("\fElige el sentido\n");
         do
         {
            bot=botones();
            if(bot=='c')
               bot=0;
         }while(!bot);
         printf(lcd_putc,"Sentido=  %c ",bot);
         dir=bot;
         delay_ms(500);
         lcd_putc("\f   Retardo:");
         while(true)
         {
            if(dir=='d')
            {
               portc=128;
               for(i=0;i<4;i++)
               {
                  delay_ms(adc);
                  portc/=2;
               }
            }
            else
            {
               portc=16;
               for(i=0;i<4;i++)
               {
                  delay_ms(adc);
                  portc*=2;
               }
            }
            adc=read_adc();
            if(adc>1000)
               adc=1000;
            if(adc<1)
               adc=1;
            lcd_gotoxy(6,2);
            printf(lcd_putc,"%lu ms  ",adc);
            if(botones()!=0)
               break;
         }
      }
      else
      {
         Printf(lcd_putc,"\f\nPausa=%lu %c"pause,modo);
         for(p=0;p<=pasos;p++)
         {
            lcd_gotoxy(1,1);
            if(modo=='i')
            {
               Printf(lcd_putc,"%Lu de %Lu pas   ",p,pasos);
               portc=16;
            }
            else
            {
               Printf(lcd_putc,"%Lu de %Lu pas   "p,pasos);
               portc=128;
            }
            for(i=0;i<4;i++)
            {
               delay_ms(pause);
               if(modo=='i')
                  portc*=2;
               else
                  portc/=2;
            }
            if(botones()!=0)
               break;
         }
      }
   }
}
int botones()
{
   if(input(izq)==0)
      return ('i');
   if(input(cent)==0)
      return ('c');
   if(input(der)==0)
      return ('d');
   return (0);
}
