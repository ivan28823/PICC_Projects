#include <16f628a.h>
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
   #define use_portb_kbd TRUE
   #include <kbd.c>
   #include <lcd420.c>
//Prototipos de funciones
   long teclado_numeros(int y);
   short pausa_tec(long t);
//Variables generales
   short aux=false;
   int i,tec,modo,sentido;
   long pausa,pasos,pa,numero[4]; 
   //float ;
//Programa principal
void main()
{
   port_b_pullups(true);
   trisa=0b10110000;
   porta=0;
   kbd_init();
   lcd_init();
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
   lcd_putc("\f    Bienvenidos\n\n   Control de un\n Motor paso a paso");
   delay_ms(2000);
   while(true)
   {
      porta=0;
      lcd_putc("\fMenu:\n1=Pasos izquierda\n2=Pasos derecha\n3=Giro infinito");
      do
      {
         tec=kbd_getc();
         if((tec=='*') || (tec=='#'))
            tec=0;
         else
         {
            tec-=48;
            if (tec>3)
               tec=0;
         }
      }while(!tec);
      modo=tec;
      if(modo==3)
      {
         lcd_putc("\fEstablece el sentido\nPress:* izq # der");
         do
         {
            tec=kbd_getc();
            if((tec=='*') || (tec=='#'))
               sentido=tec;
            else
               tec=0;
         }while(!tec);
         lcd_gotoxy(1,2);
         switch(sentido)
         {
            case '*':
               lcd_putc("     Izquierda    ");
            break;
            case '#':
               lcd_putc("     Derecha      ");
            break;
         }
         lcd_gotoxy(2,3);
         lcd_putc("Pausa entre pasos:");
         pausa=teclado_numeros(4);
         if(pausa>1000)
            pausa=1000;
         else 
            if(pausa<1)
               pausa=1;
         lcd_gotoxy(3,4);
         printf(lcd_putc,"%Lu milisegundos",pausa);
         lcd_gotoxy(1,1);
         lcd_putc("   Giro inifinito   ");
         delay_ms(200);
         aux=true;
         while(aux)
         {
            if(sentido=='*')
               porta=1;
            else
               porta=8;
            for(i=0;i<4;i++)
            {
               aux=pausa_tec(pausa);
               if(sentido=='*')
                  porta*=2;
               else
                  porta/=2;
               if(aux==false)
               break;
            }
         }
      }
      else
      {
         lcd_putc("\fSeleccione el numero\n de pasos en el\n sentido");
         lcd_gotoxy(10,3);
         if(modo==1)
            lcd_putc("izquierdo");
         else
            lcd_putc("derecho");
         delay_ms(1500);
         lcd_putc("\fEstablece los pasos:");
         pasos=teclado_numeros(2);
         lcd_gotoxy(2,3);
         lcd_putc("Establece la pausa");
         pausa=teclado_numeros(4);
         if(pausa>1000)
            pausa=1000;
         else
            if(pausa<1)
               pausa=1;
         delay_ms(1000);
         printf(lcd_putc,"\f Motor paso a paso\nPasos=0 de %Lu\nPausa= %Lu\nSentido",pasos,pausa);
         lcd_gotoxy(9,4);
         if(modo==1)
            lcd_putc("izquierdo");
         else
            lcd_putc("derecho");
         aux=true;
         for(pa=0;pa<pasos;pa++)
         {
            lcd_gotoxy(7,2);
            printf(lcd_putc,"%Lu de %Lu  ",pa,pasos);
            if(modo==1)
               porta=1;
            else
               porta=8;
            for(i=0;i<4;i++)
            {
               aux=pausa_tec(pausa);
               if(modo==1)
                  porta*=2;
               else
                  porta/=2;
               if(aux==false)
               break;
            }
            if(aux==false)
               break;
         }
      }
   }
}
long teclado_numeros(int y)
{
   for(i=0;i<4;i++)
   {
      do
      {
         tec=kbd_getc();
         if((tec=='*') | (tec=='#'))
            tec=0;
      }while(!tec);
      numero[i]=tec-48;
      lcd_gotoxy(i+8,y);
      printf(lcd_putc,"%Lu",numero[i]);
      delay_ms(150);
   }
   return(numero[0]*1000+numero[1]*100+numero[2]*10+numero[3]);
}
short pausa_tec(long t)
{
   long tp;
   short ind=true;
   for(tp=0;tp<t;tp++)
   {
      delay_us(950);
      if (kbd_getc()!=0)
      {
         ind=false;
         break;
      }
   }
   return (ind);
}
