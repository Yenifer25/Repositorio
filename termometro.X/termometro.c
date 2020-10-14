/*
 * File:   termometro.c
 * Author: USER
 *
 * Created on 11 de octubre de 2020, 01:35 PM
 */
#include <xc.h>
#include<stdio.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#include "LCD.h"
#pragma config PLLDIV=1

float volt,temp,tempK,tempF;
int adc;
char str[20];

void configurar_puertos(void)
{
    //Configuración puerto A como entrada
    TRISA=1;
    //Configuración puertos E, D, C como salidas
    TRISE=0;
    TRISC=0;
    // Inicializar puertos en 0
    PORTE=0;
    PORTC=0;
}
void configurar_ADCON (void)
{
    //configuracion 5v como voltaje de referencia
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    //Configuracion de entradas analogicas
    ADCON1bits.PCFG=0b0011;
    //seleccion de canal AN0
    ADCON0bits.CHS0=0;
    //configuración de tiempo de adquisición
    ADCON2bits.ACQT=2;
    ADCON2bits.ADCS=4;
    ADCON2bits.ADFM=1;
    //iniciar el conversor
    ADCON0bits.ADON=1;
}

void configurar_interrupcion (void)
{
    INTCONbits.GIE=0;//desctivar interrupciones globales
    T0CONbits.T0SE=1; //configurar conteo de reloj T0CKI
    T0CONbits.T0CS=1;//timer como contador
    T0CONbits.PSA=1;//deshabilitar prescaler
    T0CONbits.T08BIT=0;//16 bits para contar
    T0CONbits.TMR0ON=1;//encendet tmr
    INTCONbits.TMR0IE=1;//permitir interrupcion por desbordamiento
    INTCONbits.TMR0IF=0;//bandera en 0
    INTCONbits.PEIE=1;//permitir interrupcion de perisferico
    INTCONbits.GIE=1;//activar interrupciones globales
}

void main(void)
{
    configurar_puertos();
    configurar_ADCON();
    configurar_interrupcion ();
    
    while(1)
    {
        LATD=0x01;
       ADCON0bits.GO_DONE=1;
       while(ADCON0bits.GO_DONE==1);

        adc=ADRESH<<8;
        adc=adc+ADRESL;
        volt=adc;
        volt=(adc*5.0)/1023.0;//conversión BCD 
        temp=volt*100; // ya que la sencibilidad del lm35 es de 10mv/c

        if(TMR0==0)
        {
        sprintf(str,"%2.2f c",temp);
        lcd_init();//inicializar led
        lcd_print("la temperatura");
        lcd_print_with_position(1,2,"es:");
        lcd_print_with_position(6,2,str);
        }
        
        if(TMR0==1)
        {
            tempK=(temp+273.15);
            sprintf(str,"%2.2f k",tempK);
            lcd_print_with_position(1,2,"es:");
            lcd_print_with_position(6,2,str);
            __delay_ms(100);
        }
        
        if(TMR0==2)
        {
            tempF=((temp*9/5)+32);
            sprintf(str,"%2.2f F",tempF);
            lcd_print_with_position(1,2,"es:");
            lcd_print_with_position(6,2,str);
            __delay_ms(100);
        }
    }

    return;
}

