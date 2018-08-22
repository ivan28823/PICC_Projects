#include <16f677.h>
#device adc=16

#FUSES NOWDT                 
#FUSES INTRC_IO               
#FUSES NOMCLR                   
#FUSES NOBROWNOUT
#FUSES NOPUT
#FUSES NOPROTECT
#FUSES NOCPD             
//#define OSC_8MHZ 

#use delay(clock=8000000)
#BYTE TRISA=0x85
#BYTE TRISB=0x86
#BYTE TRISC=0x87
#BYTE PORTA=0x05
#BYTE PORTB=0x06
#BYTE PORTC=0x07

void main()
{
   setup_oscillator(OSC_8MHZ);
   Trisb=0;
   Trisc=0;
   Portc=0;
   Portb=0;
   setup_adc_ports(sAN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   long temp;
   while(true)
   {
       inicio:
       delay_ms(50);
       temp=read_adc();
       if(temp<4718){Portb=0;}
       if(temp<524){Portc=0; goto inicio;}
       if(temp>=5242){Portb=0b11000000; goto cof;}
       if(temp>=4718){Portb=0b01000000; goto cof;}
       cof:
       if(temp>=4194){Portc=0b11111111; goto inicio;}
       if(temp>=3670){Portc=0b01111111; goto inicio;}
       if(temp>=3145){Portc=0b00111111; goto inicio;}
       if(temp>=2621){Portc=0b00011111; goto inicio;}
       if(temp>=2097){Portc=0b00001111; goto inicio;}
       if(temp>=1577){Portc=0b00000111; goto inicio;}
       if(temp>=1048){Portc=0b00000011; goto inicio;}
       if(temp>=524){Portc=0b00000001; goto inicio;}   
   }
}
