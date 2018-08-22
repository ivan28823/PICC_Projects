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
#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
#include <stdlib.h>
                                              
#define LCD_ENABLE_PIN  PIN_A0                                    
#define LCD_RS_PIN      PIN_A1                                    
#define LCD_RW_PIN      PIN_A2                                    
#define LCD_DATA4       PIN_B4                                    
#define LCD_DATA5       PIN_B5                                    
#define LCD_DATA6       PIN_B6                                    
#define LCD_DATA7       PIN_B7
#include <lcd.c>

char tec[4],ee[5],rep,numt,inte,cl=0;
long contra,num,num1,numero[2];
char teclado();

void main()
{
   lcd_init ();
   Trisb = 0b00001111;
   Portb = 0;
   Trisa = 0;
   Porta = 0;

   while (true)
   {
      /*for (rep = 0; rep >= 4; rep++)
      {
         ee[rep] = read_eeprom (rep) ;
      }*/
      rep=0;
      while(rep<=4)
      {
         ee[rep]=read_eeprom(rep);
         //printf(lcd_putc,"\f%u",tec[rep]);
         //delay_ms(500);
         rep++;
      }
      
      
      
      if ((ee[0] + ee[1] + ee[2] + ee[3]) > 52)
      {
         for (rep = 0; rep >= 4; rep++)
         {
            write_eeprom (rep, 0) ;
            for (rep = 0; rep >= 3; rep++)
            {
               ee[rep] = read_eeprom (rep) ;
            }
         }
      }
      inicio:
      cl = 0;
      /*for (rep = 0; rep >= 4; rep++)
      {
         ee[rep] = read_eeprom (rep) ;
      }*/
      
      
      rep=0;
      while(rep<=3)
      {
         ee[rep]=read_eeprom(rep);
         //printf(lcd_putc,"\f%u",tec[rep]);
         //delay_ms(500);
         rep++;
      }
      
      
      
      
      
      contra = ee[0] * 1000 + ee[1] * 100 + ee[2] * 10 + ee[3];
      //lcd_putc ("\f");
      //lcd_gotoxy (4, 1) ;
      lcd_putc ("\f    Ingrese la\n");
      //lcd_gotoxy (6, 2) ;
      lcd_putc ("      Clave");
      delay_ms (1000);

      dig:
      //lcd_putc ("\f");
      //lcd_gotoxy (5, 1) ;
      lcd_putc ("\f     Clave:");
      rep = 0;

      while (rep <= 3)
      {
         numt = teclado ();
         if (numt == '#'){numt = 20; }
         if (numt != 20)
         {
            delay_ms (300);

            if (numt == '*')
            {
               cl = 1;
               //lcd_putc ("\f");
               //lcd_gotoxy (1, 1) ;
               lcd_putc ("\f Clave anterior:");
               delay_ms (1000);
               goto dig;
            }

            tec[rep] = numt;
            lcd_gotoxy ( (6 + rep), 2);
            lcd_putc (" * ");
            rep++;
         }
      }

      switch (cl)
      {
      case 1:
         //goto cambio1;
            numero[0] = tec[0] * 1000 + tec[1] * 100 + tec[2] * 10 + tec[3];
   
            if (contra == (numero[0]))
            {
               cl = 2;
               lcd_putc ("\f Nueva clave:");
               delay_ms (1000);
               goto dig;
            }
   
            else
            {
               //lcd_putc ("\f");
               //lcd_gotoxy (1, 1) ;
               printf (lcd_putc, "\fClave incorrecta") ;
               delay_ms (1000);
            }
   
            goto inicio;
         break;
         case 2:
         //goto cambio2;
            num = tec[0] * 1000 + tec[1] * 100 + tec[2] * 10 + tec[3];
            cl = 3;
            //lcd_putc ("\f");
            //lcd_gotoxy (1, 1) ;
            printf (lcd_putc, "\fRepita la clave:") ;
            delay_ms (1000);
            goto dig;
         break;

         case 3:
         //goto cambio3;
            num1 = (tec[0] * 1000 + tec[1] * 100 + tec[2] * 10 + tec[3]);
   
            if (num == num1)
            {
               rep=0;
               while(rep<=3)
               {
                  write_eeprom (rep, tec[rep]);
                  printf(lcd_putc,"\f%u",tec[rep]);
                  delay_ms(500);
                  rep++;
               }
               //lcd_putc ("\f");
               //lcd_gotoxy (1, 1) ;
               lcd_putc ("\fClave cambiada");
               delay_ms (1000);
               goto inicio;
            }
   
            else
            {
               //lcd_putc ("\f");
               //lcd_gotoxy (2, 1) ;
               lcd_putc ("\f NO CAMBIADA");
               delay_ms (1000);
            }
   
            goto inicio;
         break;
         default:
            goto compara;
         break;
      }

      compara:
      numero[0] = tec[0] * 1000 + tec[1] * 100 + tec[2] * 10 + tec[3];

      if (contra == (numero[0]))
      {
         inte = 0;
         write_eeprom (4, 1) ;
         //lcd_putc ("\f");
         //lcd_gotoxy (2, 1) ;
         lcd_putc ("\f  Clave correcta\n");
         //lcd_gotoxy (3, 2) ;
         lcd_putc ("   Matriz 8x8");
         output_high(pin_a3);

         do
         {
            numt = teclado ();
         }
         while (numt < 21) ;
         output_low(pin_a3);
         write_eeprom (4, 0) ;
         goto inicio;
      }

      else
      {
         inte++;
         //lcd_putc ("\f");
         //lcd_gotoxy (1, 1) ;
         lcd_putc ("\fClave incorrecta");
         delay_ms (1000);

         if (inte >= 5)
         {
            //lcd_putc ("\f");
            //lcd_gotoxy (3, 1) ;
            lcd_putc ("\f   Bloqueado\n");
            //lcd_gotoxy (2, 2) ;
            lcd_putc ("  espera 5min");
            delay_ms (999);
            for (num = 301; num > 0; num--)
            {
               delay_ms (999);
               //lcd_putc ("\f");
               //lcd_gotoxy (1,1) ;
               printf(lcd_putc,"\fSegundos= %Lu    ",num);
            }

            inte = 0;
         }

         //goto inicio;
      }

      goto inicio;

      /*cambio:
      cl = 1;
      lcd_putc ("\f");
      lcd_gotoxy (1, 1) ;
      lcd_putc ("Clave anterior:");
      delay_ms (1000);
      goto dig;

      cambio1:
      numero[0] = tec[0] * 1000 + tec[1] * 100 + tec[2] * 10 + tec[3];

      if (contra == numero[0])
      {
         cl = 2;
         lcd_putc ("\f");
         lcd_gotoxy (2, 1) ;
         lcd_putc ("Nueva clave:");
         delay_ms (1000);
         goto dig;
      }

      lcd_putc ("\f");
      lcd_gotoxy (1, 1) ;
      printf (lcd_putc, "Clave incorrecta") ;
      delay_ms (1000);
      goto inicio;

      cambio2:
      numero[0] = tec[0] * 1000 + tec[1] * 100 + tec[2] * 10 + tec[3];
      cl = 3;
      lcd_putc ("\f");
      lcd_gotoxy (1, 1) ;
      printf (lcd_putc, "Repita la clave:") ;
      delay_ms (1000);
      goto dig;

      cambio3:
      numero[1] = tec[0] * 1000 + tec[1] * 100 + tec[2] * 10 + tec[3];

      if (numero[0] == numero[1])
      {
         for (rep = 0; rep >= 3; rep++)
         {
            write_eeprom (rep, tec[rep]) ;
         }

         lcd_putc ("\f");
         lcd_gotoxy (1, 1) ;
         lcd_putc ("Clave cambiada");
         delay_ms (1000);
         goto inicio;
      }

      else
      {
         lcd_putc ("\f");
         lcd_gotoxy (2, 1) ;
         lcd_putc ("NO CAMBIADA");
         delay_ms (1000);
      }

      goto inicio; */
   }
}

char teclado()
{
   delay_ms (100);
   Portb = 16;
   if (input (pin_b0) == 1){return (7) ; }
   if (input (pin_b1) == 1){return (8) ; }
   if (input (PIN_b2) == 1){return (9) ; }
   if (input (pin_b3) == 1){return (0xA); }
   Portb = 32;
   if (input (pin_b0) == 1){return (4) ; }
   if (input (pin_b1) == 1){return (5) ; }
   if (input (PIN_b2) == 1){return (6) ; }
   if (input (pin_b3) == 1){return (0xB); }
   Portb = 64;
   if (input (pin_b0) == 1){return (1) ; }
   if (input (pin_b1) == 1){return (2) ; }
   if (input (PIN_b2) == 1){return (3) ; }
   if (input (pin_b3) == 1){return (0xC); }
   Portb = 128;
   if (input (pin_b0) == 1){return ('*'); }
   if (input (pin_b1) == 1){return (0) ; }
   if (input (pin_b2) == 1){return ('#'); }
   if (input (pin_b3) == 1){return (0xD); }
   
   return (20);
}

