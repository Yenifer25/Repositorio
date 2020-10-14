/*
 * File:   TIMER 22.c
 * Author: USER
 *
 * Created on 30 de septiembre de 2020, 05:29 PM
 */


#include <xc.h>

int und=0,dec=0;


void inicializar_puertos(void)
{
    ADCON1=0b00001111;
    
    TRISD=0;
    PORTD=0;
    
    TRISB=0;
    PORTB=0;
    
    TRISE=0;
    PORTE=0;
    
    TRISAbits.RA4=1;
    TRISCbits.RC0=1;
}

void TIMER0(void)
{
   INTCONbits.GIE=0; //desactivar interrupciones globales
   T0CONbits.T0SE=1; //configurar conteo de reloj T0CKI
   T0CONbits.T0CS=1;
   T0CONbits.PSA=1; //desactivar pascal
   T0CONbits.T08BIT=1; // 16 bits para contar
   T0CONbits.TMR0ON=1; //inicio de cuenta
   INTCONbits.TMR0IF=0; //desactivar bandera
   INTCONbits.TMR0IE=1; //permitir interrupcion
   INTCONbits.PEIE=1; // permitir interrupcion de perisferico
   INTCONbits.GIE=1; // habilitar interruociones globales
}

void TIMER1(void)
{
    T1CONbits.TMR1CS=1;
    T1CONbits.RD16=0;
    T1CONbits.T1CKPS=00;
    T1CONbits.TMR1ON=1;
    PIR1bits.TMR1IF=0;
    PIE1bits.TMR1IE=1;
}


void main(void) 
{
    inicializar_puertos();
    TIMER0();
    TIMER1();

    while(1)
    {
        int x=visualizar_unidades();
        PORTD=x;
        int y=visualizar_decenas();
        PORTB=y; 
    }
    return;
}
int visualizar_unidades(void)
{
    int a=TMR0-TMR1;
    und=a%10;
 
    if(a>30)
    {
        PORTEbits.RE0=1;
    }
    else
    {
        PORTEbits.RE0=0;
    }
    return und;
}
int visualizar_decenas(void)
{
    int b=TMR0-TMR1;
    dec=b/10;
    
        if(b>30)
    {
        PORTEbits.RE0=1;
    }
    else
    {
        PORTEbits.RE0=0;
    }
    return dec;
}


