/*
 * File:   TM1.c
 * Author: USER
 *
 * Created on 1 de octubre de 2020, 07:52 PM
 */


#include <xc.h>

void timer1(void)
{
    T1CONbits.RD16=0;
    T1CONbits.T1CKPS=00;
    T1CONbits.TMR1ON=1;
    T1CONbits.TMR1CS=1;
    INTCONbits.GIE=0;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    PIR1bits.TMR1IF=0;
    PIE1bits.TMR1IE=1;
}

void registros()
{
    TRISCbits.RC0=1;
    TRISD=0;
    PORTD=0;
}
void main(void) {
    
    registros();
    timer1();
    
   TMR1=0;
    while(1)
    {
        PORTD=TMR1;
        
    }
   
    return;
}


