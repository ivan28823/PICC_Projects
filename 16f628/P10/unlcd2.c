#include <16f628a.h>

#fuses INTRC_IO
#fuses NOWDT
#fuses NOMCLR
#fuses NOPUT
#fuses NOLVP
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#use delay(clock=4000000)
#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
#define use_portb_lcd TRUE
#include <lcd.c>

int numt=20,e1,e2,e3,e4;

void main()
{
   lcd_init();
   write_eeprom(0,150);
   write_eeprom(1,1);
   write_eeprom(2,9);
   write_eeprom(3,2);
   Trisa=0b11110000;
   Trisb=0;
   portb=0;
   e1=read_eeprom(50);
   e2=read_eeprom(1);
   e3=read_eeprom(2);
   e4=read_eeprom(3);
   lcd_putc("\f");
   lcd_gotoxy(2,1);
   printf(lcd_putc,"Password:");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"EEPROM %u",e1);
   delay_ms(1000);
   while(true)
   {
      numt=20;
      Porta=1;
      if(input(pin_a4)==1){numt=1;}
      if(input(pin_a5)==1){numt=2;}
      if(input(PIN_A6)==1){numt=3;}
      if(input(pin_a7)==1){numt=10;}
      Porta=2;
      if(input(pin_a4)==1){numt=4;}
      if(input(pin_a5)==1){numt=5;}
      if(input(PIN_A6)==1){numt=6;}
      if(input(pin_a7)==1){numt=11;}
      Porta=4;
      if(input(pin_a4)==1){numt=7;}
      if(input(pin_a5)==1){numt=8;}
      if(input(PIN_A6)==1){numt=9;}
      if(input(pin_a7)==1){numt=12;}
      Porta=8;
      if(input(pin_a4)==1){numt=14;}
      if(input(pin_a5)==1){numt=0;}
      if(input(PIN_A6)==1){numt=15;}
      if(input(pin_a7)==1){numt=13;}
   if(numt<16)
   {
      delay_ms(250);
      if(numt>=11){Portb=8;}
      if(numt<11){Portb=0;}
      lcd_putc("\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Numero:%u",numt);
   }
   }
}

