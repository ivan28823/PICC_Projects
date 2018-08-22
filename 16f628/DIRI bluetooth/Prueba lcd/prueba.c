#include <16f628a.h>

#fuses HS,NOWDT,MCLR,NOPUT,NOLVP,NOPROTECT,NOCPD,NOBROWNOUT
#use delay(clock=20M)
#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
//Uso de la comunicacion serial
#use rs232(baud=9600, rcv=PIN_B1, xmit=PIN_B2,parity=n, bits=8, stop=1)

#include <lib_lcd2x4pb.c>

long sensor_distancia(int trig,int echo,long *timer);
int x=1,y=1;
char dato;

#int_rda
void datos_recividos()
{
   dato=getc();
   if(x>20)
   {
      x = 1;
      if(y>4)
         y=1;
      else
         y++;
      //y = (y>4)? 1 : y+1;
   }
   lcd_gotoxy(x,y);
   printf(lcd_putc,"%d",dato);
   x++;
}
void main()
{
   Trisb=0b00000010;
   Trisa=0b00000100;
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
   lcd_init();
   lcd_putc("\f    Bienvenidos\n  Prueba de modulo\n      Bluetooth\n       HC-05");
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   long dis,timer;
   while(true)
   {
      dis=sensor_distancia(pin_a3,pin_a2,&timer);
      printf(lcd_putc,"\fDistancia = %Lucm\nTimer = %Lu",dis,timer);
      delay_ms(500);
   }   
}

long sensor_distancia(int trig,int echo,long *timer)
{
    output_high(trig);                   
    delay_us(20);                       
    output_low(trig);
    while(!input(echo));                     
    set_timer1(0);                         
    while(input(echo));
    *timer=get_timer1();
    return ((get_timer1()/5)/58);
    //return (get_timer1()/290);    
}
