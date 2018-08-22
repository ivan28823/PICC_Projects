#include <16f886.h>
#device adc=10

#FUSES NOWDT,HS,MCLR,NOBROWNOUT,NOPUT,NOPROTECT,NOCPD,IESO,FCMEN
#use delay(clock=20M)

#BYTE TRISA=0x85
#BYTE TRISB=0x86
#BYTE TRISC=0x87
#BYTE PORTA=0x05
#BYTE PORTB=0x06
#BYTE PORTC=0x07
#BIT CLR=PORTB.0
#BIT CLK=PORTB.1
#BIT DTA=PORTB.2
const int abcd[]=
{
      //Codigo ascii  '0' = 48                    Char      PI    PF    ID
      62 ,  69 ,  73 ,  81 ,  62 ,  0  ,  // 0  De 0  -  5     0
      17 ,  33 ,  127   ,  1  ,  1  ,  0  ,  // 1  De 6  -  11       1
      33 ,  67 ,  69 ,  73 ,  49 ,  0  ,  // 2  De 12 -  17       2
      34 ,  65 ,  73 ,  73 ,  54 ,  0  ,  // 3  De 18 -  23       3
      12 ,  20 ,  36 ,  127   ,  4  ,  0  ,  // 4  De 24 -  29       4
      114   ,  81 ,  81 ,  81 ,  78 ,  0  ,  // 5  De 30 -  35       5
      62 ,  73 ,  73 ,  73 ,  38 ,  0  ,  // 6  De 36 -  41       6
      64 ,  71 ,  72 ,  80 ,  96 ,  0  ,  // 7  De 42 -  47       7
      54 ,  73 ,  73 ,  73 ,  54 ,  0  ,  // 8  De 48 -  53       8
      50 ,  73 ,  73 ,  73 ,  62 ,  0  ,  // 9  De 54 -  59       9
      //10 elementos de 0 a 59
      //Codigo ascii  'A' = 65
      31 ,  36 ,  68 ,  68 ,  127   ,  0  ,  // A  De 60 -  65       10
      127   ,  73 ,  73 ,  73 ,  54 ,  0  ,  // B  De 66 -  71       11
      62 ,  65 ,  65 ,  65 ,  34 ,  0  ,  // C  De 72 -  77       12
      127   ,  65 ,  65 ,  65 ,  62 ,  0  ,  // D  De 78 -  83       13
      127   ,  73 ,  73 ,  73 ,  65 ,  0  ,  // E  De 84 -  89       14
      127   ,  72 ,  72 ,  72 ,  64 ,  0  ,  // F  De 90 -  95       15
      62 ,  65 ,  65 ,  69 ,  38 ,  0  ,  // G  De 96 -  101   16
      127   ,  8  ,  8  ,  8  ,  127   ,  0  ,  // H  De 102   -  107   17
      0  ,  65 ,  127   ,  65 ,  0  ,  0  ,  // I  De 108   -  113   18
      0  ,  2  ,  65 ,  65 ,  126   ,  0  ,  // J  De 114   -  119   19
      127   ,  8  ,  20 ,  34 ,  65 ,  0  ,  // K  De 120   -  125   20
      127   ,  1  ,  1  ,  1  ,  1  ,  0  ,  // L  De 126   -  131   21
      127   ,  32 ,  24 ,  32 ,  127   ,  0  ,  // M  De 132   -  137   22
      127   ,  16 ,  8  ,  4  ,  127   ,  0  ,  // N  De 138   -  143   23
      62 ,  65 ,  65 ,  65 ,  62 ,  0  ,  // O  De 144   -  149   24
      127   ,  72 ,  72 ,  72 ,  48 ,  0  ,  // P  De 150   -  155   25
      60 ,  66 ,  66 ,  66 ,  61 ,  0  ,  // Q  De 156   -  161   26
      127   ,  72 ,  76 ,  74 ,  49 ,  0  ,  // R  De 162   -  167   27
      50 ,  73 ,  73 ,  73 ,  38 ,  0  ,  // S  De 168   -  173   28
      64 ,  64 ,  127   ,  64 ,  64 ,  0  ,  // T  De 174   -  179   29
      126   ,  1  ,  1  ,  1  ,  126   ,  0  ,  // U  De 180   -  185   30
      124   ,  2  ,  1  ,  2  ,  124   ,  0  ,  // V  De 186   -  191   31
      126   ,  1  ,  6  ,  1  ,  126   ,  0  ,  // W  De 192   -  197   32
      99 ,  20 ,  8  ,  20 ,  99 ,  0  ,  // X  De 198   -  203   33
      114   ,  9  ,  9  ,  9  ,  126   ,  0  ,  // Y  De 204   -  209   34
      67 ,  69 ,  73 ,  81 ,  97 ,  0  ,  // Z  De 210   -  215   35
      //26 elementos de 60 a 215
      //Codigo ascii  'a' = 97
      6  ,  21 ,  21 ,  21 ,  15 ,  0  ,  // a  De 216   -  221   36
      63 ,  9  ,  9  ,  9  ,  6  ,  0  ,  // b  De 222   -  227   37
      14 ,  17 ,  17 ,  17 ,  9  ,  0  ,  // c  De 228   -  233   38
      6  ,  9  ,  9  ,  9  ,  63 ,  0  ,  // d  De 234   -  239   39
      14 ,  21 ,  21 ,  21 ,  13 ,  0  ,  // e  De 240   -  245   40
      8  ,  31 ,  40 ,  40 ,  0  ,  0  ,  // f  De 246   -  251   41
      25 ,  37 ,  37 ,  37 ,  62 ,  0  ,  // g  De 252   -  257   42
      63 ,  8  ,  8  ,  8  ,  7  ,  0  ,  // h  De 258   -  263   43
      0  ,  9  ,  47 ,  1  ,  0  ,  0  ,  // i  De 264   -  269   44
      2  ,  1  ,  1  ,  1  ,  94 ,  0  ,  // j  De 270   -  275   45
      63 ,  4  ,  10 ,  17 ,  0  ,  0  ,  // k  De 276   -  281   46
      62 ,  1  ,  1  ,  1  ,  0  ,  0  ,  // l  De 282   -  287   47
      31 ,  16 ,  15 ,  16 ,  31 ,  0  ,  // m  De 288   -  293   48
      31 ,  16 ,  16 ,  15 ,  0  ,  0  ,  // n  De 294   -  299   49
      14 ,  17 ,  17 ,  17 ,  14 ,  0  ,  // o  De 300   -  305   50
      63 ,  36 ,  36 ,  36 ,  24 ,  0  ,  // p  De 306   -  311   51
      24 ,  36 ,  36 ,  36 ,  63 ,  0  ,  // q  De 312   -  317   52
      0  ,  15 ,  16 ,  16 ,  0  ,  0  ,  // r  De 318   -  323   53
      9  ,  21 ,  21 ,  21 ,  18 ,  0  ,  // s  De 324   -  329   54
      16 ,  16 ,  62 ,  17 ,  17 ,  0  ,  // t  De 330   -  335   55
      30 ,  1  ,  1  ,  2  ,  31 ,  0  ,  // u  De 336   -  341   56
      0  ,  30 ,  1  ,  1  ,  30 ,  0  ,  // v  De 342   -  347   57
      30 ,  1  ,  14 ,  1  ,  30 ,  0  ,  // w  De 348   -  353   58
      17 ,  10 ,  4  ,  10 ,  17 ,  0  ,  // x  De 354   -  359   59
      57 ,  5  ,  5  ,  5  ,  62 ,  0  ,  // y  De 360   -  365   60
      17 ,  19 ,  21 ,  25 ,  17 ,  0  ,  // z  De 366   -  371   61
      //26 elementos de 216 a 371
      //Codigo ascii  ' ' = 32
      0  , 0  ,  0  ,  0 , 0  ,  0    // Espacio De 372 - 377    62
      //1 elemento de 272 a 377 
};
int id_letras(char c)
{
   return ((c==' ' || c==0)?62 : (c>='a')? c-61 : (c>='A')? c-55 : c-48);
}
void Mostrar(int carateres[],int tam,int tiempo)
{ 
   int letras_arr[48],inicio=0,id_char=8;
   long i_mat,i,j;
   for (i = 0; i < 8; ++i)
   {
      i_mat=id_letras(carateres[i]);
      for (j = 0; j < 6; ++j)
         letras_arr[j+(i*6)]=abcd[j+(i_mat*6)];
   }
   do
   {
      for (j = 0; j < tiempo; ++j)
      {
         DTA=1;
         CLK=1;
         DTA=0;
         CLK=0;
         for (i = inicio; i < inicio+40 ; ++i)
         {
            Portc=letras_arr[i];
            delay_us(800);
            CLK=1;
            CLK=0;
         }
      }
      inicio++;
      if(inicio>5)
      {
         for (i = 0; i < 42; ++i)
            letras_arr[i]=letras_arr[i+6];
         i_mat = (id_char<tam)? id_letras(carateres[id_char]) : 62 ;
         for (i = 0; i < 6; ++i)
            letras_arr[i+42]=abcd[i+(i_mat*6)];
         id_char++;
         inicio=0;
      }
   }while(id_char<=tam);
}
//Programa pricipal
void main()
{
   Trisc=0;Portc=0;
   Trisb=0;Portb=0;
   Trisa=0xFF; //0b11111111
   //setup_oscillator(OSC_8MHZ);
   CLR=0;CLR=1;
   //const int m_t1=80;
   //const int cmsj[m_t1]=
   //{"Vumetro Matriz Hecha por ivan288823 del CECYT 3 del IPN ESIMEZ Diciembre 2015  "};
   //int msj_m[7];
   //int k,l,aux=0;
   //char msj[50]={"Hola mundo por ivan28823"};
   while(true)
   {
      //for (k = 0 , l = aux; k < 7; ++k , ++l)
      //   msj_m[k]=cmsj[l];
      //Mostrar(msj,50,15);
      //aux=(aux+3<m_t1)? aux+1 : 0;
      //aux++;
      Portc=0;
      DTA=1;
      CLK=1;
      DTA=0;
      CLK=0;
      for(int i=0;i<40;i++)
      {
         delay_us(1500);
         CLK=1;
         CLK=0;
         Portc++;
      }
   }
}
