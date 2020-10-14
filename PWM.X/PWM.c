/*
 * File:   PWM.c
 * Author: USER
 *
 * Created on 4 de octubre de 2020, 03:22 PM
 */


#include <xc.h>

#define _XTAL_FREQ 32000000
int cont = 0;//contador



void __interrupt()ISR_TIMER0 (void)
{
    
    if(cont==0)//si pasaron 100 ms
        cont++; //incrementar contador
    {
     LATAbits.LATA0 = LATAbits.LATA0+1;//cambio de estado
     cont = 0;//reinicie contador
    }
    TMR0H = (300)>>8;//desbordamiento cada 1ms
TMR0L=300;
    INTCONbits.TMR0IF = 0;//limpia la bandera de TMR0
}

void main (void)
{

//puerto
TRISA = 0;//puerto A como salida
PORTA = 0;//limpia puerto A
//configurar interrupcion 
INTCONbits.TMR0IE = 1;//habilita interrucion TMR0
INTCONbits.TMR0IF = 0;//limpia flag de interrupcion TMR0
INTCONbits.GIE = 1;//habilita interrupcion global
//configurracion del timer0
T0CONbits.T08BIT=1;
T0CONbits.T0CS = 0;//como temporizador Fosc/4
T0CONbits.T0SE = 0;//seleccion de flanco
T0CONbits.PSA = 0;//asignar prescaler
T0CONbits.T0PS = 0b111;//prescaler 1:256
//carga de temporizacion
TMR0H = (300)>>8;//desbordamiento cada 1ms
TMR0L=300;
while (1);
  return; 
}

