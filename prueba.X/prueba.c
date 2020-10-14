/*
 * File:   prueba.c
 * Author: USER
 *
 * Created on 2 de septiembre de 2020, 09:47 PM
 */


#include <xc.h>
#pragma config FOSC=XT_XT
#pragma config CPUDIV=OSC1_PLL2
  
void main(void) {
    
    float dec,volt;
    int ud,adc;
    
    TRISA=0b00000001;
    TRISB=0;
    TRISD=0;
     
    PORTB=0;
    PORTD=0;
    
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    
    ADCON1bits.PCFG=0b1101;
    
    ADCON0bits.CHS0=0;
    
    ADCON2bits.ACQT=2;
    ADCON2bits.ADCS=4;
    ADCON2bits.ADFM=1;
    
    ADCON0bits.ADON=1;
    
    while(1)
    {
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.GO_DONE==1);
        //iniciar el conversor
        adc=ADRESH;
        adc=adc<<8;
        adc=adc+ADRESL;
        volt=(adc*5.0)/1023.0;
        
        //Descomposicion de numeros
        dec=(volt/10);
        ud=volt-(dec*10);
        //visualizar valores
        PORTD=dec; 
        PORTB=ud;  
    }
}