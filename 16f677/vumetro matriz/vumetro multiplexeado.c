#include <16f677.h>
#device adc=8

#FUSES NOWDT,HS,MCL,NOBROWNOUT,NOPUT,NOPROTECT,NOCPD,IESO,FCMEN
#use delay(clock=20M)

#BYTE TRISA=0x85
#BYTE TRISB=0x86
#BYTE TRISC=0x87
#BYTE PORTA=0x05
#BYTE PORTB=0x06
#BYTE PORTC=0x07

#use fast_io(c)
#use fast_io(b)
#use fast_io(a)
int time,i,sec[8],vca;
int comprobar_adc(int analog);
int ufono(int uf);
void texto();
short txt=0;
#int_ext
void cambio()
{
   delay_ms(300);
   switch(vca)
   {
      case 0:
         vca=10;
         txt=0;
      break;
      case 10:
         vca=101;
         txt=0;
      break;
      case 101:
         vca=11;
         txt=0;
      break;
      case 11:
         vca=0;
         txt=0;
      break;
   }
   
}
void main()
{
Trisc=0;
Portc=0;
Trisb=0b00110000;
Portb=0;
Trisa=255;
setup_adc_ports(sAN0 | sAN10 | sAN11 | VSS_VREF);
setup_adc(ADC_CLOCK_DIV_2);
enable_interrupts(int_ext);
ext_int_edge(h_to_l);
enable_interrupts(global);
   for(i=0;i<9;i++)
   { output_high(pin_b6);
     output_low(pin_b6);
     sec[i]=0; }
     vca=10;
   for(;;)
  {
      while((vca==0) || (vca==11))
      {
         if(txt==0)
            {texto();}
         for(time=0;time<6;time++)
         {
            output_high(pin_b7);
            output_high(pin_b6);
            output_low(pin_b7);
            output_low(pin_b6);
            for(i=0;i<8;i++)
            {
               portc=sec[i];
               delay_us(2300);
               output_high(pin_b6); 
               output_low(pin_b6);
            }
         }
         set_adc_channel(vca);
         delay_us(15);
         for(i=0;i<8;i++)
            {sec[i]=sec[i+1];}
         sec[7]=comprobar_adc(read_adc());
      }
      while(vca==10)
      {
            if(txt==0)
            {texto();}
            set_adc_channel(10);
            delay_us(15);
            output_high(pin_b7);
            output_high(pin_b6);
            output_low(pin_b7);
            output_low(pin_b6);
            for(i=0;i<8;i++)
            {
               portc=sec[i];
               delay_us(2000);
               sec[i]=comprobar_adc(read_adc());
               output_high(pin_b6); 
               output_low(pin_b6);
            }
      }
      while(vca==101)
      {
         if(txt==0)
            {texto();}
         for(time=0;time<2;time++)
         {
            output_high(pin_b7);
            output_high(pin_b6);
            output_low(pin_b7);
            output_low(pin_b6);
            for(i=0;i<8;i++)
            {
               portc=sec[i];
               delay_us(2200);
               output_high(pin_b6); 
               output_low(pin_b6);
            }
         }
         set_adc_channel(10);
         delay_us(15);
         for(i=0;i<8;i++)
            {sec[i]=sec[i+1];}
         sec[7]=ufono(read_adc());
      }
  }
}

int comprobar_adc(int analog)
{
   if(analog<=10)
      return (0);
   if(analog<=31)
      return (128);
   if(analog<=63)
      return (192);
   if(analog<=95)
      return (224);
   if(analog<=127)
      return (240);
   if(analog<=160)
      return (248);
   if(analog<=191)
      return (252);
   if(analog<=223)
      return (254);
   if(analog>=224)
      return (255);
}
int ufono(int uf)
{
   if(uf<=50)
      return (0);
   if(uf<=64)
      return (24);
   if(uf<=128)
      return (60);
   if(uf<=191)
      return (126);
   if(uf>=192)
      return (255);
}
void texto()
{  
   char const tex[32]=
   {  
      0b00000000,0b00000000,0b10000100,0b10000010,0b11111111,0b10000000,0b10000000,0b00000000,
      0b00000000,0b00000100,0b11100010,0b10010001,0b10001001,0b10000110,0b00000000,0b00000000,
      0b00000000,0b00000100,0b10000010,0b10010001,0b10011001,0b01100110,0b00000000,0b00000000,
      0b00000000,0b00010000,0b00011000,0b00010100,0b00010010,0b11111111,0b00010000,0b00000000,
   },inicio,tope;
   if(vca==10)
      {inicio=0; tope=7;}
   if(vca==101)
      {inicio=9; tope=16;}
   if(vca==11)
      {inicio=17; tope=24;}
   if(vca==0)
      {inicio=25; tope=32;}
   for(time=0;time<100;time++)
      {
         output_high(pin_b7);
         output_high(pin_b6);
         output_low(pin_b7);
         output_low(pin_b6);
         for(i=inicio;i<tope;i++)
         {
            portc=tex[i];
            delay_ms(2);
            output_high(pin_b6); 
            output_low(pin_b6);
         }
      }
   txt=1;
}

