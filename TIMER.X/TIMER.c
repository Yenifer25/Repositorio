/*
 * File:   TIMER.c
 * Author: USER
 *
 * Created on 29 de septiembre de 2020, 02:47 PM
 */


#include <xc.h>
#define _XTAL_FREQ 4000000

int min=0,seg=0,dec_seg=0;
int H,L,BCD;


int visualizar_decseg(void);

void inicializar_puertos(void)
{
    ADCON1=0b00001111;
    TRISC=0;
    PORTC=0;
    
    TRISD=0;
    PORTD=0;
    
    TRISB=0;
    PORTB=0;
    
    TRISA=0;
    PORTA=0;
}
void TIMER0(void)
{
   INTCONbits.GIE=0; //desactivar interrupciones globales
   T0CONbits.T0CS=0; //configurar conteo de reloj temporizador
   T0CONbits.PSA=0; //activar pascal
   T0CONbits.T0PS=0b001; //prescaler 1:256
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
    int x=visualizar_decseg();
    PORTD=x;
    int y=visualizar_seg();
    PORTB=y;
    int z=visualizar_min();
    PORTA=z;
    }
    return;
}

void __interrupt() timer_0 (void)
{
    if(INTCONbits.TMR0IF)
    {
        dec_seg++;
        if(dec_seg==60)
        {
            seg++;
            dec_seg=0;
        }
        if(seg==60)
        {
            min++;
            seg=0;
        }
        if(min==60)
        {
            min=0;
        }
        
        TMR0H=(60536)>>8;
        TMR0L=60536;
        
        INTCONbits.TMR0IF=0;
       
    }
}

int visualizar_decseg(void)
{
    int valor=dec_seg;
    H=0;
    
    if(valor>=10)
    {
        do
        {
            valor=valor-10;
            H++;
        }
        while(valor>=10);
    }
    L=valor;
    H=H<<4;
    BCD=H|L;
    
    return BCD;
    
}

int visualizar_seg(void)
{
    int valor=seg;
    H=0;
    
    if(valor>=10)
    {
        do
        {
            valor=valor-10;
            H++;
        }
        while(valor>=10);
    }
    L=valor;
    H=H<<4;
    BCD=H|L;
    
    return BCD;
}

int visualizar_min(void)
{
    int valor=min;
    H=0;
    
    if(valor>=10)
    {
        do
        {
            valor=valor-10;
            H++;
        }
        while(valor>=10);
    }
    L=valor;
    H=H<<4;
    BCD=H|L;
    
    return BCD;
    
}


