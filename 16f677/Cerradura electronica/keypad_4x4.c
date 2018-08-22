///////////////////////////////////////////////////////////////////////
// Libreria: KBD4x4.C
//
// char kbd_getc()   Devuelve el código ASCII de la tecla pulsada.
//         Si no se pulsó ninguna, devuelve 0.
//
// Conexiones del teclado.
//            RB0 RB1 RB2 RB3
//             ^   ^   ^   ^
//             |   |   |   |
//           |---|---|---|---|
//  RB4 ---> | 1 | 2 | 3 | A |
//           |---|---|---|---|
//  RB5 ---> | 6 | 5 | 4 | B |
//           |---|---|---|---|
//  RB6 ---> | 7 | 8 | 9 | C |
//           |---|---|---|---|
//  RB7 ---> | * | 0 | # | D |
//           |---|---|---|---|
///////////////////////////////////////////////////////////////////////

// Caracteres ASCII asociados a cada tecla:
char const KEYS[4][4] = {{'1','4','7','*'},
                         {'2','5','8','0'},
                         {'3','6','9','#'},
                         {'A','B','C','D'}};

#byte kbd_port_c = 0x07


char kbd_getc()
{
  char tecla=0;
  int f,c,t,i,j;

  set_tris_c(0b00001111); // RB7-RB4 salidas, RB3-RB0 entradas

  for(f=0x10, i=0; i<4; f<<=1, i++)
  {
    for(c=0x01, j=0; j<4; c<<=1, j++)
    {
      kbd_port_c = ~f;
      delay_cycles(1);
      t = kbd_port_c & 0x0F;
      t = ~(t | 0xF0);
      if(t == c)
      {
        delay_ms(20);
        tecla=KEYS[i][j];
        while(t==c)
        {
          restart_wdt();
          t = kbd_port_c & 0x0F;
          t = ~(t | 0xF0);
        }
        break;
      }
    }
    if(tecla)
      break;
  }
  return tecla;
}
