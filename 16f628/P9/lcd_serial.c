/*
Uso de una LCD serial conectda a un sólo pin del microcontrolador.
Ivan Moreno

Incluir en el programa principal:


/////////////////////////////////////////////////////////////////////////////////////
//Se requiere de estas lineas para uso de lcd serial                                        //
#use rs232(baud=9600, xmit=PIN_A0, parity=n, bits=8, stop=1,  force_sw, stream=lcd)//
#include <lcd_serial.c>                                                            //
/////////////////////////////////////////////////////////////////////////////////////


Fuinciones:

lcd_serial_init();
      Sirve para inicial el lcd 
lcd_serial_gotoxy(posicion en x,posicion en y);
      x= posicion en x no mayor a 16
      y= posicion en y no mayor a 2
lcd_clear();
      Sirve para borrar la pantalla lcd
*/
void lcd_serial_init()
{
   delay_ms(30);
}
void lcd_serial_gotoxy(int x,int y)
{
   fputc('°',lcd);
   delay_ms(1);
   fputc(x,lcd);
   delay_ms(1);
   fputc(y,lcd);
   delay_ms(1);
}
void lcd_clear()
{
   fputc('ñ',lcd);
   delay_ms(1);
}
