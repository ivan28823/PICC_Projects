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

int unid=0; //0b10010011
int dece=0; //0b00001011
int cent=0; //0b00000111
void condicion();
int const disp[10]={63,6,91,79,102,109,125,7,127,111};
void main()
{
   int unidd=0;
   int deced=0;
   int centd=0;
   trisa=0b00000011;
   trisb=0;
   Portb=0;
   Porta=255;
   while(true)
   {
      condicion();
      switch(unid)
      {
         case 0:
            unidd=disp[0];
            break;
         case 1:
            unidd=disp[1];
            break;
         case 2:
            unidd=disp[2];
            break;
         case 3:
            unidd=disp[3];
            break;   
         case 4:
            unidd=disp[4];
            break;
         case 5:
            unidd=disp[5];
            break;
         case 6:
            unidd=disp[6];
            break;
         case 7:
            unidd=disp[7];
            break;
         case 8:
            unidd=disp[8];
            break;
         case 9:
            unidd=disp[9];
            break;
         case 10:
            dece++; unid=0;
            break;
      }
   Portb=unidd; Porta=0b10010011;
   delay_ms(1);
   
      switch(dece)
      {
         case 0:
            deced=disp[0];
            break;
         case 1:
            deced=disp[1];
            break;
         case 2:
            deced=disp[2];
            break;
         case 3:
            deced=disp[3];
            break;   
         case 4:
            deced=disp[4];
            break;
         case 5:
            deced=disp[5];
            break;
         case 6:
            deced=disp[6];
            break;
         case 7:
            deced=disp[7];
            break;
         case 8:
            deced=disp[8];
            break;
         case 9:
            deced=disp[9];
            break;
         case 10:
            cent++; dece=0;
            break;
      }
      
   Portb=deced; Porta=0b00001011;
   delay_ms(1);
   
    switch(cent)
      {
         case 0:
            centd=disp[0];
            break;
         case 1:
            centd=disp[1];
            break;
         case 2:
            centd=disp[2];
            break;
         case 3:
            centd=disp[3];
            break;   
         case 4:
            centd=disp[4];
            break;
         case 5:
            centd=disp[5];
            break;
         case 6:
            centd=disp[6];
            break;
         case 7:
            centd=disp[7];
            break;
         case 8:
            centd=disp[8];
            break;
         case 9:
            centd=disp[9];
            break;
         case 10:
            cent=0; dece=0; unid=0;
            break;
      }
   
   Portb=centd; Porta=0b00000111;
   delay_ms(1);
   }
}

void condicion()
{
   if(input(pin_a1)==0)
   {
      while(input(pin_a1)==0){delay_ms(1);}
      delay_ms(20);
      unid++;
   }
   if(input(pin_a0)==0)
   {
      unid=0;
      dece=0;
      cent=0;
   }
}

