#include <18F4550.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(crystal=20000000)

//variables generales
char flag_50,flag_100;
int16 pwm_duty;

// interrupcion por timer0
#INT_TIMER0
void  TIMER0_isr(void) 
{
   if(flag_100 && !flag_50){  // si flag_100 == 1 y flag_50 == 0
       pwm_duty = 997;        //ciclo util al 100 
   }else if (!flag_100 && flag_50){ // flag_100 == 0 y flag_50 == 1
       if(pwm_duty > 500)     // si ciclo util es mayor a 500
         pwm_duty -= 100;  // se resta de 100 en 100 el ciclo util
       else    
         pwm_duty = 500;   // se establece en 50%
    }
   flag_50 = 0;   // se resetea flag_50
   flag_100 = 0;  // // se resetea flag_100
}

void main(){
   flag_50 = 0;      //bandera para el 50%
   flag_100 = 0;     //bandera para el 100%
   set_tris_b(0x00); //trisb = 0
   setup_adc(ADC_CLOCK_DIV_64 | ADC_TAD_MUL_8 | VSS_VDD );  // adc clock interno dividido en 64, 8 tda
   setup_adc_ports(AN0);      //puerto analogico
   set_adc_channel(0);     //canal 0
   
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_64);      //840 ms overflow
   setup_timer_2(T2_DIV_BY_1,249,1);      //50.0 us overflow, 50.0 us interrupt  // a 20khz

   setup_ccp1(CCP_PWM|CCP_SHUTDOWN_AC_L|CCP_SHUTDOWN_BD_L);    // ccp como pwm 
   set_pwm1_duty((int16)997);    // ciclo util al 100

   enable_interrupts(INT_TIMER0);      //habilita las interrupciones por timer0
   enable_interrupts(GLOBAL);    // habilita las interrupciones globales 

   long temp;     // variable de temperatura 
   while(TRUE){
      temp = read_adc() >>1;  // lee el adc y lo divide / 2
      //output_b(temp & 0xFF);
      if(temp > 0 && temp <=25){output_b(0x01);pwm_duty = 0;}     // primer rango de temperatura
      else if(temp > 25 && temp <=28){output_b(0x02);pwm_duty = 0;}  // segundo rando de temperatura 
      else if(temp > 28 && temp <=45){output_b(0x04);flag_50 = 1;}      // tercer rango de temperatura 
      else if(temp > 45 && temp <=100){output_b(0x08);flag_100 = 1;}    // curto rango de temperatura 
      set_pwm1_duty(pwm_duty);      // establece el ciclo util 
      delay_ms(100);    // pequeña pausa de 100 ms 
   }

}
