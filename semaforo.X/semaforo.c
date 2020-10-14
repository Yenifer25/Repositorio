/*
 * File:   semaforo.c
 * Author: USER
 *
 * Created on 2 de octubre de 2020, 09:14 PM
 */


#include <xc.h>
#define _XTAL_FREQ 4000000

int cont=0;

void configurar_puertos(void)
{
    ADCON1=0b00001111;
    TRISD=0b00110000;
    PORTD=0;
    TRISB=1;
}
void TIMER (void)
{//interrupcion RB0
    INTCONbits.GIE=0;   
    INTCONbits.INT0IE=1; 
    INTCONbits.INT0IF=0; 
    INTCON2bits.INTEDG0=1;
    RCONbits.IPEN=1;
    INTCONbits.GIEH=1; 
    INTCONbits.GIEL=1; 
    INTCON2bits.NOT_RBPU=0;
    // configuracion registros timer
    T0CONbits.T0CS=0;   
    T0CONbits.PSA=0;    
    T0CONbits.T0PS=0b111;
    T0CONbits.T08BIT=0; 
    T0CONbits.TMR0ON=1;
    //interrupcion timer0
    INTCONbits.TMR0IF=0;
    INTCONbits.TMR0IE=1;
    INTCONbits.PEIE=1;  
    INTCONbits.GIE=1;  
}

void main(void) 
{
    configurar_puertos ();
    TIMER ();
    TMR0H=(61629)>>8;
    TMR0L=61629;
    while(1)
    {
        if(cont==0)
        {
            PORTDbits.RD0=1;
            PORTDbits.RD1=0;
            PORTDbits.RD2=1;
            PORTDbits.RD3=0;
        }
        
        if(cont==1)
        {
            PORTDbits.RD1=1;
            PORTDbits.RD0=0;
            PORTDbits.RD3=1;
            PORTDbits.RD2=0;
        }
    }           
    return;
}
void __interrupt(high_priority) TIMER0 (void)
{
    if(INTCONbits.TMR0IF)
    {
        cont++;
        TMR0H=(61629)>>8;
        TMR0L=61629;
        INTCONbits.TMR0IF=0;
        if(cont==2)
        {
            cont=0;
        } 
    }  
}

void __interrupt(low_priority) pulsador(void)
{
            if(INTCONbits.INT0IF==1)
            {
                TMR0H=(26473)>>8;
                TMR0L=26473;
                INTCONbits.INT0IF=0; 
                
                if(PORTBbits.RB0==0)
                {
                    PORTDbits.RD0=1;
                    TMR0H=(26473)>>8;
                    TMR0L=26473;
               
                }
            }              
}
        
        
     

