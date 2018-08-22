#include <16f628a.h>

#fuses INTRC
#fuses NOWDT
#fuses NOMCLR
#fuses NOPUT
#fuses NOLVP
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#use delay(clock=4000000)
#define use_portb_lcd TRUE       
#include <lcd.c>                 

char const abecedario[]={
' ','a','b','c','d','e','f','g','h','i','j','k',
'l','m','n','o','p','q','r','s','t','u','v',
'w','x','y','z','A','B','C','D','E','F','G',
'H','I','J','K','L','M','N','O','P','Q','R','S',
'T','U','V','W','X','Y','Z'},x,y=1;
int32 z=1;
void main()
{        
   lcd_init();
   while(true)
   {
      if(z==0){z=1;}
      for(x=1;x<27;x++)
      {
         if(y==1)
            lcd_gotoxy(x,y);
         else
            lcd_gotoxy((x-16),y);
         if(x>15){y=2;}
         printf(lcd_putc,"%c",abecedario[x]);
         delay_ms(10);
      }
      printf(lcd_putc,"\f");
      y=1;
      
      for(x=27;x<53;x++)
      {
         if(y==1)
            lcd_gotoxy((x-26),y);
         else
            lcd_gotoxy((x-42),y);
         if(x>41){y=2;}
         printf(lcd_putc,"%c",abecedario[x]);
         delay_ms(10);
      }
      printf(lcd_putc,"\f");
      printf(lcd_putc,"Fin de la cadena");
      lcd_gotoxy(2,2);
      printf(lcd_putc,"Num=%Lu",z);
      delay_ms(1000);
      z=z*2;
      printf(lcd_putc,"\f");
      y=1;
   }
}

