#include <16f628a.h>

#fuses HS
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
#use delay(clock=20000000)

byte const sec1[8]={255,129,129,129,129,129,129,255};
byte const sec2[8]={66,255,66,66,66,66,255,66};
byte const sec3[8]={36,36,255,36,36,255,36,36};
byte const sec4[8]={24,24,24,255,255,24,24,24};
byte const sec5[8]={255,255,255,255,255,255,255,255};
byte const sec6[8]={255,254,252,248,240,224,192,128};
byte const sec7[8]={255-1,255-2,255-4,255-8,255-16,255-32,255-64,255-128};

void main()
{
   Trisb=0;
   Trisa=0;
   Portb=0;
   Porta=0;
   int time=0;
   int tm=30;
   int b=0;
   for(time=0;time<8;time++)
   {
      Porta=1;
      delay_ms(1);
      Porta=0;
   }
   while(true)
   {
      for(time=0;time<tm;time++)
      {
         Porta=2; Porta=3; Porta=0;
         for(b=0;b<8;b++)
         {
            Portb=sec1[b];
            delay_ms(2);
            Porta=1; Porta=0;
         }
      }
      for(time=0;time<tm;time++)
      {
         Porta=2; Porta=3; Porta=0;
         for(b=0;b<8;b++)
         {
            Portb=sec2[b];
            delay_ms(2);
            Porta=1; Porta=0;
         }
      }
      for(time=0;time<tm;time++)
      {
         Porta=2; Porta=3; Porta=0;
         for(b=0;b<8;b++)
         {
            Portb=sec3[b];
            delay_ms(2);
            Porta=1; Porta=0;
         }
      }
      for(time=0;time<tm;time++)
      {
         Porta=2; Porta=3; Porta=0;
         for(b=0;b<8;b++)
         {
            Portb=sec4[b];
            delay_ms(2);
            Porta=1; Porta=0;
         }
      }
      for(time=0;time<tm;time++)
      {
         Porta=2; Porta=3; Porta=0;
         for(b=0;b<8;b++)
         {
            Portb=sec5[b];
            delay_ms(2);
            Porta=1; Porta=0;
         }
      }
      for(time=0;time<tm;time++)
      {
         Porta=2; Porta=3; Porta=0;
         for(b=0;b<8;b++)
         {
            Portb=sec6[b];
            delay_ms(2);
            Porta=1; Porta=0;
         }
      }
      for(time=0;time<255;time++)
      {
         Porta=2; Porta=3; Porta=0;
         for(b=0;b<8;b++)
         {
            Portb=sec7[b];
            delay_ms(2);
            Porta=1; Porta=0;
         }
      }
   }
}
