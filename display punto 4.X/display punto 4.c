/*
 * File:   display punto 4.c
 * Author: USER
 *
 * Created on 5 de septiembre de 2020, 11:36 PM
 */


#include <xc.h>
#pragma config FOSC=XT_XT
#pragma config CPUDIV=OSC1_PLL2
  
void main(void) {
    //Configuración puerto A como entrada
    TRISA=1;
    //Configuración puertos B, D, C como salidas
    TRISB=0;
    TRISD=0;
    TRISC=0;
    TRISE=1;
    // Inicializar puertos en 0
    PORTB=0;
    PORTD=0;
    PORTC=0;
    PORTE=0;
    //configuracion 5v como voltaje de referencia
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    //Configuracion de entradas analogicas
    ADCON1bits.PCFG=0b1101;
    //seleccion de canal AN0
    ADCON0bits.CHS0=0;
    //configuración de tiempo de adquisición
    ADCON2bits.ACQT=2;
    ADCON2bits.ADCS=4;
    ADCON2bits.ADFM=1;
    //iniciar el conversor
    ADCON0bits.ADON=1;
    
    while(1)
    {
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.GO_DONE==1);
        //iniciar el conversor
            float volt;
            int dec,adc,temp;
            
        adc=ADRESH<<8;
        adc=adc+ADRESL;
        volt=adc;
        volt=(adc*5.0)/1023.0;
        PORTB=volt;
        adc=volt*10;
        dec=adc%10;
        PORTD=dec;
        temp=volt/0.01; // ya que la sencibilidad del lm35 es de 10mv/c
        
        //176° F equivalen a 80°C
        
        //logica combinacional 
        
        if(temp>=80 && RE0==1 && RE1==1) 
        {
            PORTCbits.RC0=1;
        }
        else if (temp<=80 && RE0==1 && RE2==1)
        {
            PORTCbits.RC0=1;
        }
        else if (temp<=80 && RE1==1)
        {
            PORTCbits.RC0=1;
        }
        else if (temp>=80 && RE2==1)
        {
            PORTCbits.RC0=1;
        }
        else
        {
            PORTCbits.RC0=0;
        }
    }
}
