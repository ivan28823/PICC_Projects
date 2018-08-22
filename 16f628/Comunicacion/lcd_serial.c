/*
Uso de una LCD serial conectda a un sólo pin del microcontrolador.
Ivan Moreno

Incluir en el programa principal:


/////////////////////////////////////////////////////////////////////////////////////
//Para usar el lcd pues usa 6 bits de stop                                         //
#use rs232(baud=9600, xmit=PIN_A0, parity=n, bits=8, stop=1,  force_sw, stream=lcd)//
#include <lcd_serial.c>                                                            //
/////////////////////////////////////////////////////////////////////////////////////


Funciones:

lcd_serial_init();
      Sirve para inicial el lcd 
lcd_serial_gotoxy(posicion en x,posicion en y);
      x= posicion en x no mayor a 16
      y= posicion en y no mayor a 2
lcd_clear();
      Sirve para borrar la pantalla lcd
fprintf(lcd,"Cadena de caracteres"); 

fputc('C');
   Donde c es un sólo caracter
*/
void lcd_serial_init()
{
   delay_ms(10);
}
void lcd_serial_gotoxy(int x,int y)
{
   fputc('°',lcd);
   //delay_ms(3);
   fputc(x,lcd);
   //delay_ms(3);
   fputc(y,lcd);
   //delay_ms(3);
}
void lcd_clear()
{
   fputc('ñ',lcd);
   //delay_ms(3);
}
