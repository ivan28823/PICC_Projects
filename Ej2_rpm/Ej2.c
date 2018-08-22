#include <18F4550.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)

#bit RBPU = 0xFF1.7     // pull-up all port b

#include "PID_v1.c"     //libreria para el manejo de un controilador PID
/// static variables
static int32 millis=0;      // variable que cuenta los milisegundos
static int16 cnt_rps=0;     // variable que cuenta las repeticiones por segundo
/// variables auxiliares
int32 last_time;
int16 rpm;
// Working PID variables
PidType  myPID; // structura a el controlador PID
/// prototipo de funciones
void clrf_ptr(int8 * ptr,int8 len,int8 v);
void num_to_arr_num(int8 * ptr,unsigned int num,int8 len);
void show_count(int8 rpm1,int8 rmp2);
int8 select_disp(int8 dig);
int8 dec_to_disp(int8 num);
// interrupcion por el timer0
#INT_TIMER0
void TMR_isr(){
    set_timer0(60536);  // precarga el timer
    millis++; // se incrementan los milisegundos
}
// interrupcion externa
#INT_EXT
void  EXT_isr(void){
    cnt_rps++;  // cuenta las rps
}

void main(){
  //inicializa el controlador pid
  //PID_init(PID, kp,ki,kd, direccion)
  PID_init(&myPID,   0.07,  0.095,  0.7,   0);
  PID_SetMode(&myPID,1);
  PID_SetOutputLimits(&myPID,0,990);  //establece limites
  PID_SetSampleTime(&myPID,500);  // tiempo de muestreo

   RBPU = 0;  // pull-up todo el puerto b
   set_tris_d(0); // establece I/O
   set_tris_b(0xFF);  // establece I/O
   set_tris_c(0); // establece I/O

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);      //13 ms overflow
   setup_timer_2(T2_DIV_BY_1,249,1);      //50.0 us overflow, 50.0 us interrupt

   // configura el pwm
   setup_ccp1(CCP_PWM|CCP_SHUTDOWN_AC_L|CCP_SHUTDOWN_BD_L);
   set_pwm1_duty((int16)997);    //estblece el ciclo util
   enable_interrupts(INT_TIMER0);   //interrupcion por timer0
   enable_interrupts(INT_EXT_H2L);  //interrupcion externa
   enable_interrupts(GLOBAL); // habilita todas las interrupcicones

   int8 a;  // variable auxiliar
   while(TRUE){
      if(millis - last_time > 499){ // cada 500ms de muestra
        cnt_rps = cnt_rps << 1; // cnt_rps * 2
        myPID.myInput = (float) cnt_rps; // establece dato de entrada
        rpm = cnt_rps > 99? 99 : cnt_rps ;  //para mostrar en el display
        last_time = millis; // el ultimo dato se guarda para hacer la resta
        cnt_rps = 0;  // resetea la variable
      }
      a = input_b() >> 1; // lee el puerto
      a = a>99? 99 : a; //muestra en display
      myPID.mySetpoint =  (float) a;  // establece el punto de control
      PID_Compute(&myPID);  // computa el PID
      set_pwm1_duty((int16)myPID.myOutput);  // saca el dato via pwm

      show_count(rpm,a);  // muestra los datos en el display
   }

}
void clrf_ptr(int8 * ptr,int8 len,int8 v){  //limpia el vector
    while(--len)  *(ptr + len) = v;
}
void num_to_arr_num(int8 * ptr,int8 num,int8 len){  // de numero a arreglo
    for(clrf_ptr(ptr,len,0);num>9;*ptr++ = num%10,num/=10);
    *ptr = num%10;
}
void show_count(int8 rpm1,int8 rpm2){ // muestra los datos en display
  static int8 num[4];
  num_to_arr_num(num,rpm1,2);
  num_to_arr_num(num+2,rpm2,2);
  for(int8 i=0; i<4; ++i){
    output_c(0xFF );
    output_d(dec_to_disp(num[i]));
    output_c(select_disp(i));
    delay_ms(2);
  }
}
int8 select_disp(int8 dig){ // selecciona el display
  return *((int8 *)"\xC2\xC1\x83\x43" + dig);
}
int8 dec_to_disp(int8 num){ // de numero a numero en display
  return *((int8 *)"\xC0\xF9\xA4\xB0\x99\x92\x82\xF8\x80\x98\xBF\xFF" + num);
}