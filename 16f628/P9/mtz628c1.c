#include <16f628a.h>

#fuses HS
#fuses NOWDT
#fuses NOMCLR
#fuses NOPUT
#fuses NOLVP
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#use delay(clock=20000000)

#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06

char const sec[]=
{
0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//8
0b11111,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//16
0b00100,0b11111+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//24
0b00100,0b00100+224,0b11111+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//32
0b11111,0b00100+224,0b00100+64,0b11111+224,0b00000,0b00000+160,0b00000+224,0b00000,//40
0b00000,0b11111+224,0b00100+64,0b00100+224,0b11111,0b00000+160,0b00000+224,0b00000,//48
0b11111,0b00000+224,0b11111+64,0b00100+224,0b00100,0b11111+160,0b00000+224,0b00000,//56
0b10101,0b11111+224,0b00000+64,0b11111+224,0b00100,0b00100+160,0b11111+224,0b00000,//64
0b10101,0b10101+224,0b11111+64,0b00000+224,0b11111,0b00100+160,0b00100+224,0b11111,//72
0b00000,0b10101+224,0b10101+64,0b11111+224,0b00000,0b11111+160,0b00100+224,0b00100,//80
0b11111,0b00000+224,0b10101+64,0b10101+224,0b11111,0b00000+160,0b11111+224,0b00100,//88
0b10001,0b11111+224,0b00000+64,0b10101+224,0b10101,0b11111+160,0b00000+224,0b11111,//96
0b10001,0b10001+224,0b11111+64,0b00000+224,0b10101,0b10101+160,0b11111+224,0b00000,//104
0b00000,0b10001+224,0b10001+64,0b01110+224,0b00000,0b10101+160,0b10101+224,0b11111,//112
0b11111,0b00000+224,0b10001+64,0b10001+224,0b01110,0b00000+160,0b10101+224,0b10101,//120
0b00100,0b11111+224,0b00000+64,0b10001+224,0b10001,0b01110+160,0b00000+224,0b10101,//128
0b00100,0b00100+224,0b11111+64,0b00000+224,0b10001,0b10001+160,0b01110+224,0b00000,//136
0b11111,0b00100+224,0b00100+64,0b11111+224,0b00000,0b10001+160,0b10001+224,0b01110,//144
0b00000,0b11111+224,0b00100+64,0b00100+224,0b11111,0b00000+160,0b10001+224,0b10001,//152
0b01110,0b00000+224,0b11111+64,0b00100+224,0b00100,0b11111+160,0b00000+224,0b10001,//160
0b10001,0b01110+224,0b00000+64,0b11111+224,0b00100,0b00100+160,0b11111+224,0b00000,//168
0b10001,0b10001+224,0b01110+64,0b00000+224,0b11111,0b00100+160,0b00100+224,0b11111,//176
0b01110,0b10001+224,0b10001+64,0b01110+224,0b00000,0b11111+160,0b00100+224,0b00100,//184
0b00000,0b01110+224,0b10001+64,0b10001+224,0b01110,0b00000+160,0b11111+224,0b00100,//192
0b11111,0b00000+224,0b01110+64,0b10001+224,0b10001,0b01110+160,0b00000+224,0b11111,//200
0b00101,0b11111+224,0b00000+64,0b01110+224,0b10001,0b10001+160,0b01110+224,0b00000,//208
0b00111,0b00101+224,0b11111+64,0b00000+224,0b01110,0b10001+160,0b10001+224,0b01110,//216
0b00000,0b00111+224,0b00101+64,0b11111+224,0b00000,0b01110+160,0b10001+224,0b10001,//224
0b11100,0b00000+224,0b00111+64,0b00101+224,0b11111,0b00000+160,0b01110+224,0b10001,//232
0b10100,0b11100+224,0b00000+64,0b00111+224,0b00101,0b11111+160,0b00000+224,0b01110,//240
0b11100,0b10100+224,0b11100+64,0b00000+224,0b00111,0b00101+160,0b11111+224,0b00000,//248
0b00000,0b11100+224,0b10100+64,0b11100+224,0b00000,0b00111+160,0b00101+224,0b11111,//256
0b11100,0b00000+224,0b11100+64,0b10100+224,0b11100,0b00000+160,0b00111+224,0b00101,//264
0b00100,0b11100+224,0b00000+64,0b11100+224,0b10100,0b11100+160,0b00000+224,0b00111,//272
0b00000,0b00100+224,0b11100+64,0b00000+224,0b11100,0b10100+160,0b11100+224,0b00000,//280
0b01110,0b00000+224,0b00100+64,0b11100+224,0b00000,0b11100+160,0b10100+224,0b11100,//288
0b10001,0b01110+224,0b00000+64,0b00100+224,0b11100,0b00000+160,0b11100+224,0b10100,//296
0b10001,0b10001+224,0b01110+64,0b00000+224,0b00100,0b11100+160,0b00000+224,0b11100,//304
0b00000,0b10001+224,0b10001+64,0b01110+224,0b00000,0b00100+160,0b11100+224,0b00000,//312
0b11111,0b00000+224,0b10001+64,0b10001+224,0b01110,0b00000+160,0b00100+224,0b11100,//320
0b00100,0b11111+224,0b00000+64,0b10001+224,0b10001,0b01110+160,0b00000+224,0b00100,//328
0b00100,0b00100+224,0b11111+64,0b00000+224,0b10001,0b10001+160,0b01110+224,0b00000,//336
0b11111,0b00100+224,0b00100+64,0b11111+224,0b00000,0b10001+160,0b10001+224,0b01110,//344
0b00000,0b11111+224,0b00100+64,0b00100+224,0b11111,0b00000+160,0b10001+224,0b10001,//352
0b00000,0b00000+224,0b11111+64,0b00100+224,0b00100,0b11111+160,0b00000+224,0b10001,//360
0b11111,0b00000+224,0b00000+64,0b11111+224,0b00100,0b00100+160,0b11111+224,0b00000,//368
0b00000,0b11111+224,0b00000+64,0b00000+224,0b11111,0b00100+160,0b00100+224,0b11111,//376
0b11111,0b00000+224,0b11111+64,0b00000+224,0b00000,0b11111+160,0b00100+224,0b00100,//384
0b00010,0b11111+224,0b00000+64,0b11111+224,0b00000,0b00000+160,0b11111+224,0b00100,//392
0b00100,0b00010+224,0b11111+64,0b00000+224,0b11111,0b00000+160,0b00000+224,0b11111,//400
0b01000,0b00100+224,0b00010+64,0b11111+224,0b00000,0b11111+160,0b00000+224,0b00000,//408
0b11111,0b01000+224,0b00100+64,0b00010+224,0b11111,0b00000+160,0b11111+224,0b00000,//416
0b00000,0b11111+224,0b01000+64,0b00100+224,0b00010,0b11111+160,0b00000+224,0b11111,//424
0b01110,0b00000+224,0b11111+64,0b01000+224,0b00100,0b00010+160,0b11111+224,0b00000,//432
0b10001,0b01110+224,0b00000+64,0b11111+224,0b01000,0b00100+160,0b00010+224,0b11111,//440
0b10001,0b10001+224,0b01110+64,0b00000+224,0b11111,0b01000+160,0b00100+224,0b00010,//448
0b00000,0b10001+224,0b10001+64,0b01110+224,0b00000,0b11111+160,0b01000+224,0b00100,//456
0b00000,0b00000+224,0b10001+64,0b10001+224,0b01110,0b00000+160,0b11111+224,0b01000,//464
0b00000,0b00000+224,0b00000+64,0b10001+224,0b10001,0b01110+160,0b00000+224,0b11111,//472
0b00000,0b00000+224,0b00000+64,0b00000+224,0b10001,0b10001+160,0b01110+224,0b00000,//480
0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b10001+160,0b10001+224,0b01110,//488
0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b10001+224,0b10001,//496
0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b10001,//504
0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//512

0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//512
0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b10001,//504
0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b10001+224,0b10001,//496
0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b10001+160,0b10001+224,0b01110,//488
0b00000,0b00000+224,0b00000+64,0b00000+224,0b10001,0b10001+160,0b01110+224,0b00000,//480
0b00000,0b00000+224,0b00000+64,0b10001+224,0b10001,0b01110+160,0b00000+224,0b11111,//472
0b00000,0b00000+224,0b10001+64,0b10001+224,0b01110,0b00000+160,0b11111+224,0b01000,//464
0b00000,0b10001+224,0b10001+64,0b01110+224,0b00000,0b11111+160,0b01000+224,0b00100,//456
0b10001,0b10001+224,0b01110+64,0b00000+224,0b11111,0b01000+160,0b00100+224,0b00010,//448
0b10001,0b01110+224,0b00000+64,0b11111+224,0b01000,0b00100+160,0b00010+224,0b11111,//440
0b01110,0b00000+224,0b11111+64,0b01000+224,0b00100,0b00010+160,0b11111+224,0b00000,//432
0b00000,0b11111+224,0b01000+64,0b00100+224,0b00010,0b11111+160,0b00000+224,0b11111,//424
0b11111,0b01000+224,0b00100+64,0b00010+224,0b11111,0b00000+160,0b11111+224,0b00000,//416
0b01000,0b00100+224,0b00010+64,0b11111+224,0b00000,0b11111+160,0b00000+224,0b00000,//408
0b00100,0b00010+224,0b11111+64,0b00000+224,0b11111,0b00000+160,0b00000+224,0b11111,//400
0b00010,0b11111+224,0b00000+64,0b11111+224,0b00000,0b00000+160,0b11111+224,0b00100,//392
0b11111,0b00000+224,0b11111+64,0b00000+224,0b00000,0b11111+160,0b00100+224,0b00100,//384
0b00000,0b11111+224,0b00000+64,0b00000+224,0b11111,0b00100+160,0b00100+224,0b11111,//376
0b11111,0b00000+224,0b00000+64,0b11111+224,0b00100,0b00100+160,0b11111+224,0b00000,//368
0b00000,0b00000+224,0b11111+64,0b00100+224,0b00100,0b11111+160,0b00000+224,0b10001,//360
0b00000,0b11111+224,0b00100+64,0b00100+224,0b11111,0b00000+160,0b10001+224,0b10001,//352
0b11111,0b00100+224,0b00100+64,0b11111+224,0b00000,0b10001+160,0b10001+224,0b01110,//344
0b00100,0b00100+224,0b11111+64,0b00000+224,0b10001,0b10001+160,0b01110+224,0b00000,//336
0b00100,0b11111+224,0b00000+64,0b10001+224,0b10001,0b01110+160,0b00000+224,0b00100,//328
0b11111,0b00000+224,0b10001+64,0b10001+224,0b01110,0b00000+160,0b00100+224,0b11100,//320
0b00000,0b10001+224,0b10001+64,0b01110+224,0b00000,0b00100+160,0b11100+224,0b00000,//312
0b10001,0b10001+224,0b01110+64,0b00000+224,0b00100,0b11100+160,0b00000+224,0b11100,//304
0b10001,0b01110+224,0b00000+64,0b00100+224,0b11100,0b00000+160,0b11100+224,0b10100,//296
0b01110,0b00000+224,0b00100+64,0b11100+224,0b00000,0b11100+160,0b10100+224,0b11100,//288
0b00000,0b00100+224,0b11100+64,0b00000+224,0b11100,0b10100+160,0b11100+224,0b00000,//280
0b00100,0b11100+224,0b00000+64,0b11100+224,0b10100,0b11100+160,0b00000+224,0b00111,//272
0b11100,0b00000+224,0b11100+64,0b10100+224,0b11100,0b00000+160,0b00111+224,0b00101,//264
0b00000,0b11100+224,0b10100+64,0b11100+224,0b00000,0b00111+160,0b00101+224,0b11111,//256
0b11100,0b10100+224,0b11100+64,0b00000+224,0b00111,0b00101+160,0b11111+224,0b00000,//248
0b10100,0b11100+224,0b00000+64,0b00111+224,0b00101,0b11111+160,0b00000+224,0b01110,//240
0b11100,0b00000+224,0b00111+64,0b00101+224,0b11111,0b00000+160,0b01110+224,0b10001,//232
0b00000,0b00111+224,0b00101+64,0b11111+224,0b00000,0b01110+160,0b10001+224,0b10001,//224
0b00111,0b00101+224,0b11111+64,0b00000+224,0b01110,0b10001+160,0b10001+224,0b01110,//216
0b00101,0b11111+224,0b00000+64,0b01110+224,0b10001,0b10001+160,0b01110+224,0b00000,//208
0b11111,0b00000+224,0b01110+64,0b10001+224,0b10001,0b01110+160,0b00000+224,0b11111,//200
0b00000,0b01110+224,0b10001+64,0b10001+224,0b01110,0b00000+160,0b11111+224,0b00100,//192
0b01110,0b10001+224,0b10001+64,0b01110+224,0b00000,0b11111+160,0b00100+224,0b00100,//184
0b10001,0b10001+224,0b01110+64,0b00000+224,0b11111,0b00100+160,0b00100+224,0b11111,//176
0b10001,0b01110+224,0b00000+64,0b11111+224,0b00100,0b00100+160,0b11111+224,0b00000,//168
0b01110,0b00000+224,0b11111+64,0b00100+224,0b00100,0b11111+160,0b00000+224,0b10001,//160
0b00000,0b11111+224,0b00100+64,0b00100+224,0b11111,0b00000+160,0b10001+224,0b10001,//152
0b11111,0b00100+224,0b00100+64,0b11111+224,0b00000,0b10001+160,0b10001+224,0b01110,//144
0b00100,0b00100+224,0b11111+64,0b00000+224,0b10001,0b10001+160,0b01110+224,0b00000,//136
0b00100,0b11111+224,0b00000+64,0b10001+224,0b10001,0b01110+160,0b00000+224,0b10101,//128
0b11111,0b00000+224,0b10001+64,0b10001+224,0b01110,0b00000+160,0b10101+224,0b10101,//120
0b00000,0b10001+224,0b10001+64,0b01110+224,0b00000,0b10101+160,0b10101+224,0b11111,//112
0b10001,0b10001+224,0b11111+64,0b00000+224,0b10101,0b10101+160,0b11111+224,0b00000,//104
0b10001,0b11111+224,0b00000+64,0b10101+224,0b10101,0b11111+160,0b00000+224,0b11111,//96
0b11111,0b00000+224,0b10101+64,0b10101+224,0b11111,0b00000+160,0b11111+224,0b00100,//88
0b00000,0b10101+224,0b10101+64,0b11111+224,0b00000,0b11111+160,0b00100+224,0b00100,//80
0b10101,0b10101+224,0b11111+64,0b00000+224,0b11111,0b00100+160,0b00100+224,0b11111,//72
0b10101,0b11111+224,0b00000+64,0b11111+224,0b00100,0b00100+160,0b11111+224,0b00000,//64
0b11111,0b00000+224,0b11111+64,0b00100+224,0b00100,0b11111+160,0b00000+224,0b00000,//56
0b00000,0b11111+224,0b00100+64,0b00100+224,0b11111,0b00000+160,0b00000+224,0b00000,//48
0b11111,0b00100+224,0b00100+64,0b11111+224,0b00000,0b00000+160,0b00000+224,0b00000,//40
0b00100,0b00100+224,0b11111+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//32
0b00100,0b11111+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//24
0b11111,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//16
0b00000,0b00000+224,0b00000+64,0b00000+224,0b00000,0b00000+160,0b00000+224,0b00000,//8
};
   int time=0;
   long b=0,cs=8,c=0;
   
void main()
{
   Trisb=0;
   Trisa=0;
   Portb=0;
   Porta=0;
   for(time=0;time<10;time++)
   {
      Porta=1;
      delay_ms(1);
      Porta=0;
   }
   while(true)
   {
      for(time=0;time<5;time++)
      {
         Porta=2; Porta=3; Porta=0;
         for(b=c;b<cs;b++)
         {
            Portb=sec[b];
            delay_ms(2);
            Porta=1; Porta=0;
         }
      }
   cs=cs+8;
   c=c+8;
   if(cs>1024){cs=8; c=0;}
   }
}

