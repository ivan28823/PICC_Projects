#include <16f677.h>
#device adc=16

#fuses NOWDT,INTRC_IO,MCLR,NOBROWNOUT,NOPUT,PROTECT,CPD,IESO,FCMEN
#use delay(clock=4M)

#byte TRISA = 0x85
#byte TRISB = 0x86
#byte TRISC = 0x87
#byte PORTA = 0x05
#byte PORTB = 0x06
#byte PORTC = 0x07
//Puerto A
#bit sensor     = 0x05.0
#bit pin_intext = 0x05.1
#bit pin_abrir  = 0x05.4
#bit pin_cerrar = 0x05.5
//Puerto B
#bit trisadcb4  = 0x86.4
#bit trisadcb5  = 0x86.5
#bit adcB5      = 0x06.5
#bit ilumin     = 0x06.6

#define tam_psw      10
#define sensibilidad 18000

#include <lcd_pc_a_677.c>
#include <keypad_4x4.c>
//Uso de variables generales
   short flag_touch=false;
   const char master_key[tam_psw+1]={"0ABCD28823"};
   int inten=0,t0=0;
   char key,psw[tam_psw],psw1[tam_psw],psw_intr[tam_psw];
   //long ;
//Prototipos de funciones
   void AbrirIntExt();
   void LucesLcd();
   void IntrClave(char *clave);
   short CompararClave(char *s1,char *s2);
   short IsMaster(char *sm);
   char ReciveTecla();
   short IsTouched();
   void Abrir();
//Interrupción Externa
#int_ext
void AbrirIntExt()
{
   if(flag_touch)
   {
      if(!ilumin)
      {
         enable_interrupts(int_timer0);
         ilumin=true;
      }
      t0=0;
      pin_intext=false;
      Abrir();      
   }
   else
      flag_touch=true;
}
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
   setup_oscillator(OSC_4MHZ);
   lcd_init();
   TRISC=0x00; TRISA=0x0D; TRISB=0x00; 
   PORTC=0x00; PORTA=0x00; PORTB=0x00; 
   setup_adc_ports(sAN10 | sAN11);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_timer_0(T0_INTERNAL|T0_DIV_256);
   set_adc_channel(11);
   delay_ms(250);
   enable_interrupts(int_ext);
   ext_int_edge(l_to_h);
   enable_interrupts(GLOBAL);
   if(read_eeprom(255)!=1)
   {
      for (int i = 0; i < tam_psw; ++i)
         write_eeprom(i,master_key[i]);
      write_eeprom(255,1);
   }
   for (int i = 0; i < tam_psw; ++i)
      psw[i]=read_eeprom(i);
   while(true)
   {
      lcd_putc("\f   Introduce\n   la Clave");
      do
      {
         key=ReciveTecla();
         delay_ms(15);
      }while(!key);
      delay_ms(250);
      if (key=='*')
      {
         IntrClave(psw_intr);
         if (CompararClave(psw,psw_intr) || IsMaster(psw_intr))
         {
            lcd_putc("\f Introduce una\n  nueva clave");
            delay_ms(1200);
            IntrClave(psw_intr);
            lcd_putc("\f   Vuelvela a\n   introducir");
            delay_ms(1200);
            IntrClave(psw1);
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
      else
      {
         IntrClave(psw_intr);
         if (CompararClave(psw,psw_intr))
         {
            inten=0;
            lcd_putc("\f   Abierto");
            Abrir();
         }
         else
         {
            lcd_putc("\f   Clave\n  Incorrecta");
            inten++;
         }            
         if(inten>5)
            for (long j = 5*inten; j>0 ; --j)
            {
               printf(lcd_putc,"\f   Bloqueado\n espera %Lu seg", j);
               for (int i = 0; i < 10; ++i)
               {
                  key=ReciveTecla();
                  delay_ms(80);
               }
            }
      }
      delay_ms(1000);
   }
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
         if(key=='*' || key=='#')
            key=0;
         delay_ms(15);
      }while(!key);
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
   pin_intext=IsTouched(); 
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
   short m_touch=false;
   long value=0;
   for(int i = 0; i < 40; ++i)
   {
      trisadcb4=false;
      trisadcb5=false;
      adcB5=true;
      set_adc_channel(11);
      delay_us(20);
      trisadcb4=true;
      set_adc_channel(10);
      value+=read_adc()/40;   
   }
   m_touch = (value<sensibilidad)? true : false;
   return m_touch;
}
void Abrir()
{
   pin_abrir=true;
   for (int i = 0; i < 200; ++i)
   {
      pin_abrir = (sensor)? false : true;
      delay_ms(9);
   }
   pin_abrir=false;
   pin_cerrar=true;
   delay_ms(500);
   pin_cerrar=false;
   delay_ms(500);
}
