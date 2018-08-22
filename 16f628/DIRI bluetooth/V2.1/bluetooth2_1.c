#include <16f648a.h>
#fuses HS,NOWDT,MCLR,NOPUT,NOLVP,NOPROTECT,NOCPD,NOBROWNOUT
#use delay(clock=20M)
/////////////////////////////////////////////////////////////
#define  Servo    PIN_B0
#define  RX       PIN_B1
#define  TX       PIN_B2
#define  Atras    PIN_B4
#define  LucesD   PIN_B5
#define  LucesT   PIN_B6
#define  Led_on   PIN_B7
#define  ECHO     PIN_A0
#define  TRIG     PIN_A1
#define  Adelante PIN_A2

#define v_centro    1425  //1250
#define v_derecha   1775
#define v_izquierda 1075
#define v_inc       175
/////////////////
#BYTE TRISA=0x85
#BYTE PORTA=0x05
#BYTE TRISB=0x86
#BYTE PORTB=0x06
//Uso de la comunicacion serial
#use rs232(baud=9600, rcv=RX, xmit=TX,parity=n, bits=8, stop=1)
//Variables generales
  short flag=false,f_inter=false,f_auto=false;
  int dato=0,t0=0;
  long pwm=v_centro,c_util=0,izquierda,derecha,vaux;
//Prototipos de funciones
  void pwm_servo(int pin,int periodo,long alto);
  void opciones();
  void recepciion_datos();
  long sensor_distancia(int s_trig,int s_echo);
  void modo_automatico();
//Recepcion del bluetooth
#int_rda   //Interrupcion por comunicacion serial
void recepciion_datos()
{
  dato=getc();
  flag=true;
}
#int_timer0   //Interrupcion por timer 0
void Intermitentes()
{
  if(t0>38)
  {
    output_toggle(LucesT);
    t0=0;
  }
  else
    t0++;
}
//Programa principal
void main()
{
  Trisa=0xF1;Porta=0;
  Trisb=0x02;Portb=0;
  setup_ccp1(CCP_PWM);
  setup_timer_0(T0_INTERNAL|T0_DIV_256);
  setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
  setup_timer_2(T2_DIV_BY_1,255,1);
  set_pwm1_duty(0);
  while(input(PIN_A4));
  pwm_servo(Servo,25,pwm);
  enable_interrupts(INT_RDA);
  enable_interrupts(GLOBAL);
  output_high(Led_on);
  do
  {
    opciones();
  }while(true);
}
void pwm_servo(int pin,int periodo,long alto)
{
  long bajo=20000-alto; //pwm a 50hz ancho de pulso 20ms
  for(int a=0;a<periodo;a++)
  {
    output_high(pin);
    delay_us(alto);
    output_low(pin);
    delay_us(bajo);
  }
}
void opciones()
{
  if(f_auto)
    modo_automatico();
  if (flag)
  {
    flag=false;
    if(!f_auto)
    {
      if((dato>='0' && dato <='9') || dato=='q')
      {
        vaux=dato-48;
        c_util = (dato=='q')? 1023 : vaux*102;     
        set_pwm1_duty(c_util);
      }
      else 
        switch(dato)
        {
          case 'V': //Modo automatico encendido
            f_auto=true;
            pwm_servo(Servo,25,v_centro);
            set_pwm1_duty(1023);
            break;
          case 'F':   //Adelante
            output_high(Adelante);
            break;
          case 'B':   //Atras
            output_high(Atras);
            break;
          case 'L':   //Izquierda
            if(pwm>v_izquierda)
            {
              pwm-=v_inc;
              pwm_servo(Servo,25,pwm);
            }
            break;
          case 'R':   //Derecha
            if(pwm<v_derecha)
            {
              pwm+=v_inc;
              pwm_servo(Servo,25,pwm);
            }
            break;
          case 'I':   //Adelante - Derecha
            output_high(Adelante);
            if(pwm<v_derecha)
            {
              pwm+=v_inc;
              pwm_servo(Servo,25,pwm);
            }
            break;
          case 'J':   //Atras - Derecha
            output_high(Atras);
            if(pwm<v_derecha)
            {
              pwm+=v_inc;
              pwm_servo(Servo,25,pwm);
            }
            break;
          case 'G':   //Adelante Izquierda
            output_high(Adelante);
            if(pwm>v_izquierda)
            {
              pwm-=v_inc;
              pwm_servo(Servo,25,pwm);
            }
            break;
          case 'H':   //Adelante Izquierda
            output_high(Atras);
            if(pwm>v_izquierda)
            {
              pwm-=v_inc;
              pwm_servo(Servo,25,pwm);
            }
            break;
          case 'S':   //Stop
            output_low(Adelante);
            output_low(Atras);
            break;
          }
    }
    switch(dato)
    {
    //No dependientes del modo automatico
    case 'v':
      f_auto=false;
      output_low(Adelante);
      output_low(Atras);
      break;
    case 'D':   //Desconectado
      Portb=0x80;
      disable_interrupts(int_timer0);
      reset_cpu();
      break;
     case 'X':   //Intermitentes on
      set_timer0(0);
      f_inter=true; 
      enable_interrupts(int_timer0);
      break;
    case 'x':   //Intermitentes off
      disable_interrupts(int_timer0);
      f_inter=false;
      output_low(LucesT);
      break;
    case 'W': //Luces D on
      output_high(LucesD);
      break;
    case 'w': //Luces D off
      output_low(LucesD);
      break;
    case 'U': //Luces T on
      if(!f_inter)
        output_high(LucesT);
      break;
    case 'u': //Luces T off
      if(!f_inter)
        output_low(LucesT);
      break;
    } 
  }
}
long sensor_distancia(int s_trig,int s_echo)
{
  output_high(s_trig);                   
  delay_us(20);                       
  output_low(s_trig);
  while(!input(s_echo));                     
  set_timer1(0);                         
  while(input(s_echo));                     
  return (get_timer1()/290);    
}
void modo_automatico()
{
  if(sensor_distancia(TRIG,ECHO)>25)
  {
    output_high(Adelante);
    output_low(Atras);
  }
  else
  {
    output_low(Adelante);
    pwm_servo(Servo,40,v_izquierda); //izquierda
    izquierda=sensor_distancia(TRIG,ECHO);
    pwm_servo(Servo,40,v_derecha); //derecha
    derecha=sensor_distancia(TRIG,ECHO);
    if(izquierda>derecha)
    {
      pwm_servo(Servo,40,v_derecha);
      output_high(Atras);
      delay_ms(500);
      output_low(Atras);
      pwm_servo(Servo,40,v_izquierda); //izquierda
      output_high(Adelante);
      delay_ms(700);
      pwm_servo(Servo,40,v_centro);
    }
    else
    {
      pwm_servo(Servo,40,v_izquierda);
      output_high(Atras);
      delay_ms(500);
      output_low(Atras);
      pwm_servo(Servo,40,v_derecha);
      output_high(Adelante);
      delay_ms(700);
      pwm_servo(Servo,40,v_centro);
    }  
  }
}
