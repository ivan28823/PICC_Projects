#include <16f648a.h>

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
                                              
#define LCD_ENABLE_PIN  PIN_A0                                    
#define LCD_RS_PIN      PIN_A1                                    
#define LCD_RW_PIN      PIN_A2                                    
#define LCD_DATA4       PIN_B4                                    
#define LCD_DATA5       PIN_B5                                    
#define LCD_DATA6       PIN_B6                                    
#define LCD_DATA7       PIN_B7 
#include <lcd.c>

long num1,num2,num3;
char inte=1,cl=0,tec,reg=0,t1,t2,t3,t4,e1,e2,e3,e4;
short carga;

char teclado();

void main()
{
   lcd_init();
   Trisa=0;
   Trisb=0b00001111;
   portb=0;
   while (true)
   {
      inicio:
         e1=read_eeprom(0);
         e2=read_eeprom(1);
         e3=read_eeprom(2);
         e4=read_eeprom(3);
         carga=read_eeprom(4);
         if((e1+e2+e3+e4)>52)
         {
            write_eeprom(0,0xA);
            write_eeprom(1,0xB);
            write_eeprom(2,0xC);
            write_eeprom(3,0xD);
            write_eeprom(4,0);
            e1=read_eeprom(0);
            e2=read_eeprom(1);
            e3=read_eeprom(2);
            e4=read_eeprom(3);
            carga=read_eeprom(4);
         }
         num1=e1*1000+e2*100+e3*10+e4;
         if(carga==1){goto cierto;}
         lcd_putc("\f");
         lcd_gotoxy(3,1);
         lcd_putc("Ingrese la");
         lcd_gotoxy(5,2);
         lcd_putc("Clave");
         delay_ms(200);
         t1=0;
         t2=0;
         t3=0;
         t4=0;
         reg=0;
         cl=0;
      dig:
         tec=teclado();
         if(tec !=20)
         {
            delay_ms(250);   
            if(tec=='#'){goto dig;}
            if(tec=='*'){goto cambio;}
            switch (reg)
            {
               case 0:
                  reg=1;
                  t1=tec;
                  lcd_putc("\f");
                  lcd_gotoxy(5,1);
                  printf(lcd_putc,"Clave:");
                  lcd_gotoxy(6,2);
                  printf(lcd_putc,"*");
                  goto dig;
               break;
               case 1:
                  reg=2;
                  t2=tec;
                  lcd_gotoxy(7,2);
                  lcd_putc("*");
                  goto dig;
               break;
               case 2:
                  reg=3;
                  t3=tec;
                  lcd_gotoxy(8,2);
                  lcd_putc("*");
                  goto dig;
               break;
               case 3:
                  t4=tec;
                  lcd_gotoxy(9,2);
                  lcd_putc("*");
                  delay_ms(100);
                  switch(cl)
                  {
                     case 0:
                        goto comprobar;
                     break;
                     case 1:
                        goto cambio1;
                     break;
                     case 2:
                        goto cambio2;
                     break;
                     case 3:
                        goto cambio3;
                     break;
                  }
               break;
            }
         }
        goto dig;
         comprobar:
            num2=t1*1000+t2*100+t3*10+t4;
            if(num1==num2)
            {
               goto cierto;
            }
            else
            {
               //write_eeprom(4,0);
               inte++;
               lcd_putc("\f");
               lcd_gotoxy(1,1);
               printf(lcd_putc,"Clave incorrecta");
               delay_ms(1000);
               if(inte>=5)
               {
                  lcd_putc("\f");
                  lcd_gotoxy(3,1);
                  lcd_putc("Bloqueado");
                  lcd_gotoxy(2,2);
                  lcd_putc("espera 5min");
                  delay_ms(999);
                  for(num3=301;num3>0;num3--)
                  {
                     delay_ms(999);
                     lcd_putc("\f");
                     lcd_gotoxy(1,1);
                     printf(lcd_putc,"Segundos=%Lu",num3);
                  }
                  inte=0;
               }
            }
      goto inicio;
      cierto:
               write_eeprom(4,1);
               lcd_putc("\f");
               lcd_gotoxy(1,1);
               printf(lcd_putc,"Clave correcta");
               lcd_gotoxy(3,2);
               printf(lcd_putc,"Matriz 8x8");
               Porta=16;
               inte=0;
               do
               {
                  tec=teclado();
               }
               while(tec<21);
               Porta=0;
               write_eeprom(4,0);
      goto inicio;
             
      cambio:
         reg=0;
         cl=1;
         t1=0;
         t2=0;
         t3=0;
         t4=0;
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         lcd_putc("Clave anterior:");
         delay_ms(1000);
      goto dig;
      cambio1:
         num2=t1*1000+t2*100+t3*10+t4;
         if(num1==num2)
         {
            reg=0;
            cl=2;
            t1=0;
            t2=0;
            t3=0;
            t4=0;
            lcd_putc("\f");
            lcd_gotoxy(2,1);
            lcd_putc("Nueva clave:");
            delay_ms(1000);
            goto dig;
         }
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc,"Clave incorrecta");
         delay_ms(1000);
      goto inicio;
      cambio2:
         num2=t1*1000+t2*100+t3*10+t4;
         reg=0;
         cl=3;
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc,"Repita la clave:");
         delay_ms(1000);
         t1=0;
         t2=0;
         t3=0;
         t4=0;
     goto dig;
     cambio3:
         num3=t1*1000+t2*100+t3*10+t4;
         if(num2==num3)
         {
            write_eeprom(0,t1);
            write_eeprom(1,t2);
            write_eeprom(2,t3);
            write_eeprom(3,t4);
            lcd_putc("\f");
            lcd_gotoxy(1,1);
            lcd_putc("Clave cambiada");
            delay_ms(1000);
            goto inicio;
         }
         else
         {
         lcd_putc("\f");
         lcd_gotoxy(2,1);
         lcd_putc("NO CAMBIADA");
         delay_ms(1000);
         }
   goto inicio;
   }
}


char teclado(void)
{
      Portb=16;
      if(input(pin_b4)==1){return (1);}
      if(input(pin_b5)==1){return (2);}
      if(input(PIN_b6)==1){return (3);}
      if(input(pin_b7)==1){return (10);}
      Porta=32;
      if(input(pin_b4)==1){return (4);}
      if(input(pin_b5)==1){return (5);}
      if(input(PIN_b6)==1){return (6);}
      if(input(pin_b7)==1){return (11);}
      Porta=64;
      if(input(pin_b4)==1){return (7);}
      if(input(pin_b5)==1){return (8);}
      if(input(PIN_b6)==1){return (9);}
      if(input(pin_b7)==1){return (12);}
      Porta=128;
      if(input(pin_b4)==1){return ('*');}
      if(input(pin_b5)==1){return (0);}
      if(input(pin_b6)==1){return ('#');}
      if(input(pin_b7)==1){return (13);}
      
      return 20;
}
