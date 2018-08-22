#include <16f648a.h>
#fuses HS
#fuses MCLR
#fuses NOWDT
#fuses NOPUT
#fuses NOLVP
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#use delay(clock=4M)
#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
//Uso de librerias
   #include <lcd420.c>
//Prototipos de funciones
   char teclado_getc(void);
//Variables generales
   //short aux=false;
   //int i,tec,modo,sentido;
   //long pausa,pasos,pa,numero[4]; 
   //float ;
//Programa principal
void main()
{
   port_b_pullups(true);
   trisa=0b10110000;
   porta=0;
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
   lcd_init();
   lcd_putc("\f    Bienvenidos\n\n   Control de un\n Motor paso a paso");
   delay_ms(2000);
   int c;
   long t;
   while(true)
   {
      set_timer1(0);
      c=teclado_getc();
      t=get_timer1();
      if(c!=0)
      {
         delay_ms(150);
         printf(lcd_putc,"\fTecla= %c\nTiempo= %Lu us",c,t);
      }
   }
}
char teclado_getc(void)
{
   set_tris_b(0b11100000);
   portb=0b00011100;
   if(input(pin_b5)==0) return ('1');
   if(input(pin_b6)==0) return ('2');
   if(input(pin_b7)==0) return ('3');
   if(input(pin_a4)==0) return ('A');
   portb=0b00011010;
   if(input(pin_b5)==0) return ('4');
   if(input(pin_b6)==0) return ('5');
   if(input(pin_b7)==0) return ('6');
   if(input(pin_a4)==0) return ('B');
   portb=0b00010110;
   if(input(pin_b5)==0) return ('7');
   if(input(pin_b6)==0) return ('8');
   if(input(pin_b7)==0) return ('9');
   if(input(pin_a4)==0) return ('C');
   portb=0b00001110;
   if(input(pin_b5)==0) return ('*');
   if(input(pin_b6)==0) return ('0');
   if(input(pin_b7)==0) return ('#');
   if(input(pin_a4)==0) return ('D');
   return (0);
}
