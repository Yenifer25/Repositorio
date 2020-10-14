/*
 * File:   TIMER 2.c
 * Author: USER
 *
 * Created on 30 de septiembre de 2020, 05:22 PM
 */


#include <xc.h>

int inc=0;

void inicializar_puertos(void)
{
    ADCON1=0b00001111;
    TRISC=0;
    PORTC=0;
    
    TRISD=0;
    PORTD=0;
    
    TRISB=0;
    PORTB=0;
    
    TRISA=1;
  
}
void TIMER0(void)
{
   INTCONbits.GIE=0; //desactivar interrupciones globales
   T0CONbits.T0SE=1; //configurar conteo de reloj T0CKI
   T0CONbits.PSA=1; //desactivar pascal
   T0CONbits.T08BIT=0; // 16 bits para contar
   T0CONbits.TMR0ON=1; //inicio de cuenta
   INTCONbits.TMR0IF=0; //desactivar bandera
   INTCONbits.TMR0IE=1; //permitir interrupcion
   INTCONbits.PEIE=1; // permitir interrupcion de perisferico
   INTCONbits.GIE=1; // habilitar interruociones globales
}

void main(void) 
{
    inicializar_puertos();
    TIMER0();
    
    TMR0H=(60536)>>8;
    TMR0L=60536;
    
    while(1)
    {
        PORTD=inc;
    }
}

void __interrupt() timer_0 (void)
{
    
    if(PORTAbits.RA4==1)
    {
        inc++;
        
        TMR0H=(60536)>>8;
        TMR0L=60536;
        
        INTCONbits.TMR0IF=0;
       
    }
}
