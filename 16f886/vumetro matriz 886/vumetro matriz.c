#include <16f886.h>
#device adc=10

#FUSES NOWDT,INTRC_IO,MCLR,NOBROWNOUT,NOPUT,NOPROTECT,NOCPD,IESO,FCMEN
#use delay(clock=8M)

#BYTE TRISA=0x85
#BYTE TRISB=0x86
#BYTE TRISC=0x87
#BYTE PORTA=0x05
#BYTE PORTB=0x06
#BYTE PORTC=0x07

void anuncio(int letrero);
int comprobar_adc(long analog);
//Programa pricipal
void main()
{
   Trisc=0;Portc=0;
   Trisb=0;Portb=0;
   Trisa=0xFF;
   setup_oscillator(OSC_8MHZ);
   setup_adc_ports(sAN0 | sAN1 | VSS_VREF);
   setup_adc(ADC_CLOCK_INTERNAL);
   anuncio(1);
   short f_mod=false;
   int modo=2;
   while(true)
   {
      set_adc_channel(modo-1);
      delay_us(15);
      if(!f_mod)
      {   
         anuncio(modo+1);
         f_mod=true;
      }
      portb=1;
      for(int j=0;j<8;++j)
      {
         Portc=comprobar_adc(read_adc());
         delay_us(2250);
         portb<<=1;
         if(!input(PIN_A5))
         {
            if(modo==1)
               modo=2;
            else
               modo=1;
            f_mod=false;
            delay_ms(200);
            break;
         }
      }
   }
}
void anuncio(int letrero)
{
   const int letras[]={
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*C*/ 126   ,  255   ,  195   ,  195   ,  195   ,  195   ,  231   ,  102   ,  0  ,
   /*E*/   255   ,   255   ,   219   ,   219   ,   219   ,   219   ,   195   ,   195   ,   0   ,
   /*C*/ 126   ,  255   ,  195   ,  195   ,  195   ,  195   ,  231   ,  102   ,  0  ,
   /*Y*/ 224   ,  112   ,  48 ,  63 ,  63 ,  48 ,  112   ,  224   ,  0  ,
   /*T*/ 192   ,  192   ,  192   ,  255   ,  255   ,  192   ,  192   ,  192   ,  0  ,
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*3*/ 0  ,  66 ,  219   ,  219   ,  219   ,  219   ,  255   ,  102   ,  0  ,
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*I*/ 195   ,  195   ,  195   ,  255   ,  255   ,  195   ,  195   ,  195   ,  0  ,
   /*P*/   255   ,   255   ,   204   ,   204   ,   204   ,   204   ,   252   ,   120   ,   0   ,
   /*N*/ 255   ,  255   ,  96 ,  48 ,  24 ,  12 ,  255   ,  255   ,  0  ,
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*S*/   114   ,   251   ,   219   ,   219   ,   219   ,   219   ,   223   ,   78   ,   0   ,
   /*C*/ 126   ,  255   ,  195   ,  195   ,  195   ,  195   ,  231   ,  102   ,  0  ,
   /*E*/   255   ,   255   ,   219   ,   219   ,   219   ,   219   ,   195   ,   195   ,   0   ,
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*6*/   126   ,   255   ,   219   ,   219   ,   219   ,   219   ,   219   ,   78   ,   0   ,
   /*I*/ 195   ,  195   ,  195   ,  255   ,  255   ,  195   ,  195   ,  195   ,  0  ,
   /*M*/ 255   ,  255   ,  96 ,  56 ,  56 ,  96 ,  255   ,  255   ,  0  ,
   /*3*/ 0  ,  66 ,  219   ,  219   ,  219   ,  219   ,  255   ,  102   ,  0  ,
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*I*/ 195   ,  195   ,  195   ,  255   ,  255   ,  195   ,  195   ,  195   ,  0  ,
   /*V*/ 252   ,  254   ,  3  ,  3  ,  3  ,  3  ,  254   ,  252   ,  0  ,
   /*A*/   127   ,   255   ,   204   ,   204   ,   204   ,   204   ,   255   ,   127   ,   0   ,
   /*N*/ 255   ,  255   ,  96 ,  48 ,  24 ,  12 ,  255   ,  255   ,  0  ,
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*M*/ 255   ,  255   ,  96 ,  56 ,  56 ,  96 ,  255   ,  255   ,  0  ,
   /*O*/ 126   ,  255   ,  195   ,  195   ,  195   ,  195   ,  255   ,  126   ,  0  ,
   /*R*/   255   ,   255   ,   216   ,   220   ,   222   ,   219   ,   249   ,   112   ,   0   ,
   /*E*/   255   ,   255   ,   219   ,   219   ,   219   ,   219   ,   195   ,   195   ,   0   ,
   /*N*/ 255   ,  255   ,  96 ,  48 ,  24 ,  12 ,  255   ,  255   ,  0  ,
   /*O*/ 126   ,  255   ,  195   ,  195   ,  195   ,  195   ,  255   ,  126   ,  0  ,   
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   //Mensaje 1 de 0 a 266
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*M*/ 255   ,  255   ,  96 ,  56 ,  56 ,  96 ,  255   ,  255   ,  0  ,
   /*O*/ 126   ,  255   ,  195   ,  195   ,  195   ,  195   ,  255   ,  126   ,  0  ,
   /*D*/ 255   ,  255   ,  195   ,  195   ,  195   ,  195   ,  126   ,  60 ,  0  ,
   /*O*/ 126   ,  255   ,  195   ,  195   ,  195   ,  195   ,  255   ,  126   ,  0  ,
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*1*/ 3  ,  51 ,  99 ,  255   ,  127   ,  3  ,  3  ,  3  ,  0  ,
   //Mensaje 2 de 267 a 321
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*M*/ 255   ,  255   ,  96 ,  56 ,  56 ,  96 ,  255   ,  255   ,  0  ,
   /*O*/ 126   ,  255   ,  195   ,  195   ,  195   ,  195   ,  255   ,  126   ,  0  ,
   /*D*/ 255   ,  255   ,  195   ,  195   ,  195   ,  195   ,  126   ,  60 ,  0  ,
   /*O*/ 126   ,  255   ,  195   ,  195   ,  195   ,  195   ,  255   ,  126   ,  0  ,
   /* */ 0,0,0,//////////////////////////////////////////////////////////////////////3
   /*2*/ 49 ,  115   ,  71 ,  207   ,  219   ,  243   ,  227   ,  67 ,  0  ,
   //Mensaje 3 de 322 a 376
   };   
   long inicio,fin,fin_msj;
   switch(letrero)
   {
      case 1:inicio=0;fin_msj=266;
      break;
      case 2:inicio=267;fin_msj=321;
      break;
      case 3:inicio=322;fin_msj=376;
      break;
   }
   fin=inicio+8;
   do
   {
      for (int j = 0; j < 12; ++j)
      {
         Portb=1;
         for (long i = inicio; i < fin; ++i)
         {
            Portc=letras[i];
            delay_us(2300);
            Portb<<=1;
         }
      }
      inicio++;fin++;
   }while(fin<=fin_msj);
}
int comprobar_adc(long analog)
{
   int valor=1;
   if(analog<=114) valor=0;
   else if(analog<=277) valor=1;
   else if(analog<=341) valor=3;
   else if(analog<=455) valor=7;
   else if(analog<=568) valor=15;
   else if(analog<=682) valor=31;
   else if(analog<=796) valor=63;
   else if(analog<=910) valor=127;
   else if(analog>910) valor=255;
   return valor;
}