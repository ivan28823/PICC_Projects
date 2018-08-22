#include <16f677.h>
#device adc=16

#fuses NOWDT,INTRC_IO,MCLR,NOBROWNOUT,NOPUT,NOPROTECT,NOCPD,IESO,FCMEN
#use delay(clock=4M)

#byte TRISA=0x85
#byte TRISB=0x86
#byte TRISC=0x87
#byte PORTA=0x05
#byte PORTB=0x06
#byte PORTC=0x07

#bit ilumin=PORTB.6
#bit trisadcb4=TRISB.4
#bit trisadcb5=TRISB.5
#bit adcB4=PORTB.4
#bit adcB5=PORTB.5

#define tam_psw 10
#define sensibilidad 15000

#include <lcd_pc_a_677.c>
#include <keypad_4x4.c>
//Uso de variables generales
   short flag,m_touch=false;
   const char master_key[tam_psw+1]={"20821997CD"};
   int inten=0,t0=0;
   char key,psw1[tam_psw],psw[tam_psw],psw_intr[tam_psw];
   //long ;
//Prototipos de funciones
   void LucesLcd();
   void IntrClave(char *clave);
   short CompararClave(char *s1,char *s2);
   short IsMaster(char *sm);
   char ReciveTecla();
   short IsTouched();
   void Abrir();
//Interrupcion Timer0
#int_timer0
void LucesLcd()
{
   if (t0>120)
   {
      t0=0;
      disable_interrupts(int_timer0);
      ilumin=false;
   }
   else 
      t0++;
}
//Programa principal
void main()
{
   delay_ms(250);
   setup_oscillator(OSC_4MHZ);
   TRISC=0;TRISA=0;TRISB=0;
   PORTC=0;PORTA=0;PORTB=0;
   setup_adc_ports(sAN10);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_timer_0(T0_INTERNAL|T0_DIV_256);
   enable_interrupts(GLOBAL);
   lcd_init();
   if(read_eeprom(255)!=1)
   {
      for (int i = 0; i < tam_psw; ++i)
         write_eeprom(i,master_key[i]);
      write_eeprom(255,1);
   }
   for (int i = 0; i < tam_psw; ++i)
      psw[i]=read_eeprom(i);
   do
   {
      while(true)
      {
         lcd_putc("\f   Introduce\n   la Clave");
         do
         {
            key=ReciveTecla();
            if(m_touch)
               break;
            delay_ms(15);
         }while(!key);
         if(m_touch)
            break;
         delay_ms(250);
         flag = (key=='*')? false : true;
         if (flag)
         {
            IntrClave(psw_intr);
            if(m_touch)
               break;
            if (CompararClave(psw,psw_intr))
            {
               inten=0;
               Abrir();
            }
            else
            {
               lcd_putc("\f   Clave\n  Incorrecta");
               inten++;
            }            
            if(inten>5)
               for (long i = 5*inten; i >0 ; --i)
               {
                  m_touch=IsTouched();
                  if(m_touch)
                     break;
                  printf(lcd_putc,"\f   Bloqueado\n espera %Lu seg", i );
                  delay_ms(950);
               }
         }
         else
         {
            IntrClave(psw_intr);
            if(m_touch)
               break;
            if (CompararClave(psw,psw_intr) || IsMaster(psw_intr))
            {
               lcd_putc("\f Introduce una\n  nueva clave");
               delay_ms(1200);
               IntrClave(psw_intr);
               if(m_touch)
                  break;
               lcd_putc("\f   Vuelvela a\n   introducir");
               delay_ms(1200);
               IntrClave(psw1);
               if(m_touch)
                  break;
               if(CompararClave(psw1,psw_intr))
               {
                  lcd_putc("\f  La clave ha\n sido cambiada");
                  for (int i = 0; i < tam_psw; ++i)
                  {
                     write_eeprom(i,psw_intr[i]);
                     psw[i]=psw_intr[i];
                  }
                  delay_ms(500);
               }
               else
                  lcd_putc("\f Las claves no\n  coinciden!!!");
            }
            else
               lcd_putc("\f   Clave\n  Incorrecta");
         }
         delay_ms(1000);
      }
      if(m_touch)
      {
         if(!ilumin)
         {
            enable_interrupts(int_timer0);
            ilumin=true;
         }
         t0=0;
         Abrir();
      }
      delay_ms(500);
   }while(true);
}
void IntrClave(char *clave)
{
   lcd_init();
   lcd_putc("\f  Clave:\n  [          ]");
   lcd_gotoxy(4,2);
   for (int i = 0; i < tam_psw ; ++i)
   {
      do
      {        
         key=ReciveTecla();
         if(m_touch)
            break;
         if(key=='*' || key=='#')
            key=0;
         delay_ms(30);
      }while(!key);
      if(m_touch)
         break;
      delay_ms(150);
      clave[i]=key;
      lcd_putc('*');
   }
   delay_ms(500);
}
short CompararClave(char *s1,char *s2)
{
   for (int i = 0; i < tam_psw; ++i)
      if(s1[i]!=s2[i])
         return 0;
   return 1;
}
short IsMaster(char *sm)
{
   for (int i = 0; i < tam_psw; ++i)
      if(master_key[i]!=sm[i])
         return 0;
   return 1;
}
char ReciveTecla()
{
   m_touch=IsTouched(); 
   char tecla=kbd_getc();
   if (tecla)
   {
      if(!ilumin)
      {
         enable_interrupts(int_timer0);
         ilumin=true;
      }
      t0=0;
   }   
   return tecla;
}
short IsTouched()
{
   long value=0;
   for(int i = 0; i < 40; ++i)
   {
      trisadcb4=false;
      trisadcb5=false;
      adcB5=true;
      set_adc_channel(11);
      delay_us(20);
      adcB5=false;
      adcB4=false;
      trisadcb4=true;
      set_adc_channel(10);
      value+=read_adc()/40;   
   }
   if (value<sensibilidad)
      return 1;
   else
      return 0;
}
void Abrir()
{
   lcd_putc("\f   Abierto");
   delay_ms(1000);
}
