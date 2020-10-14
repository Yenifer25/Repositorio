/*
 * File:   PWM2.c
 * Author: USER
 *
 * Created on 4 de octubre de 2020, 05:25 PM
 */


#include <xc.h>
int cont=0;
void TIMER0 (void)
{
    INTCONbits.GIE=0;
    INTCONbits.PEIE=1;
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    INTCONbits.GIE=1;
    // timer
    T0CONbits.TMR0ON=1;
    T0CONbits.T08BIT=1;
    T0CONbits.T0CS=0;
    T0CONbits.PSA=0;
    T0CONbits.T0PS=0b111;
}

void __interrupt() TIMER_0 (void)
{
    if(cont==0)
    {
        LATAbits.LA0 = !LATAbits.LA0;
        TMR0=256-51;
        cont=1;
        PORTA=TMR0;
    }
    else if(cont==1)
    {
        TMR0=51;
        cont=0;
        PORTA=TMR0;
    }
    
    TMR0IF=0;
}

void main(void) {
    TRISA=0;
    PORTA=0;
    TIMER0 ();
    while(1)
    {
        
    }
    return;
}
