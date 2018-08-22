#include <16f628a.h>
#fuses HS
#fuses NOWDT
#fuses NOMCLR
#fuses NOPUT
#fuses NOLVP
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#use delay(clock=8000000)
/*#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
*/                                              
#define LCD_ENABLE_PIN  PIN_A0                                    
#define LCD_RS_PIN      PIN_A1                                    
#define LCD_RW_PIN      PIN_A2                                    
#define LCD_DATA4       PIN_B4                                    
#define LCD_DATA5       PIN_B5                                    
#define LCD_DATA6       PIN_B6                                    
#define LCD_DATA7       PIN_B7
#include <lcd.c>
#use rs232(baud=9600, xmit=PIN_B1, rcv=PIN_B2,parity=n, bits=8, stop=1)
int caracter=0,x=1,y=1;
void main()
{
   
   lcd_init();
   puts("    Power by CH-INC");
   puts("========================");
   puts("Este programa sirve para");
   puts("escrivir en una pantalla");
   puts(" LCD, debes de presionar");
   puts("una tecla que se escrivira");
   puts("   en la pantalla LCD");
   puts("Presiona una tecla:");
   puts("===========================");
   while(true)
   {
      while(kbhit()==false);
      caracter=getc();
      if (caracter=='@')
      {
         puts("Defina posicion en x:");
         puts("Carcter---Hex---Posicion");
         puts("   1      31        1");
         puts("   2      32        2");
         puts("   3      33        3");
         puts("   4      34        4");
         puts("   5      35        5");
         puts("   6      36        6");
         puts("   7      37        7");
         puts("   8      38        8");
         puts("   9      39        9");
         puts("   :      3A        10");
         puts("   ;      3B        11");
         puts("   <      3C        12");
         puts("   =      3D        13");
         puts("   >      3E        14");
         puts("   ?      3F        15");
         puts("   @      40        16");
         
         while(kbhit()==false);
         x=getc();
         x=x-48;
         if((x<=0) | (x>16)){x=1;}
         
         puts("Defina posicion en y:");
         while(kbhit()==false);
         y=getc();
         y=y-48;
         if((y<=0) | (y>2)){y=1;}
         puts("Escriba otra tecla");
         while(kbhit()==false);
         caracter=getc();
      }
      
      lcd_gotoxy(x,y);
      lcd_putc(caracter);
      printf("Posicion x= %u\n\r",x);
      printf("Posicion y= %u\n\r",y);
      puts("Escriba otra tecla");
      x++;
      if(y==2)
      {
         if(x>16){x=1; y=1;}
      }
      if(x>16){x=1; y=2;}
      caracter=0;
   }
}
