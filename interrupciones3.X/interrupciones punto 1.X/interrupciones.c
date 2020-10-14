/*
 * File:   interrupciones.c
 * Author: USER
 *
 * Created on 9 de septiembre de 2020, 06:31 PM
 */


#include <xc.h>
#define _XTAL_FREQ 4000000
#pragma config FOSC=XT_XT
#pragma confi CPUDIV=OSC_PLL2

const int display[10]={0b0000,0b0001,0b0010,0b0011,0b0100,0b0101,0b0110,0b0111,0b1000,0b1001};

void main(void) 
{
    ADCON1=0b00001111;
    INTCON2bits.NOT_RBPU=0;
    
    TRISB=0b11110000;
    PORTB=0b00001111;
  
    TRISD=0;
    PORTD=0;
    
    TRISE=0;
    PORTE=0;
    
    TRISA=1;
    PORTA=0;
    
    INTCONbits.GIEH=1;
    INTCONbits.RBIE=1;
    INTCONbits.RBIF=0;
    RCONbits.IPEN=1;
    
    while(1)
    {
        PORTB=0b11111110;
        PORTB=0b11111101;
        PORTB=0b11111011;
    }
    
    
    return;
}

void __interrupt(low_priority)teclado (void)
{
    char salida;
    PORTD=0x00;
    int a=PORTD;
    
  
    if(PORTBbits.RB0==0)
    {
        if(PORTBbits.RB4==0) {PORTD=0b0001;}        
        if(PORTBbits.RB5==0) {PORTD=0b0100;} 
        if(PORTBbits.RB6==0) {PORTD=0x07;}
        if(PORTBbits.RB7==0) 
        {
            int a=PORTD;
            
            for(int i=0b1001;i>=0b0000;i--)
            {
                PORTD=display[i];
                __delay_ms(1000);
                PORTEbits.RE0=1;
            }
           
        }
        
            
        
        
    }
        if(PORTBbits.RB1==0)
    {
        if(PORTBbits.RB4==0) {PORTD=0b0010;}        
        if(PORTBbits.RB5==0) {PORTD=0b0101;} 
        if(PORTBbits.RB6==0) {PORTD=0b1000;}
        if(PORTBbits.RB7==0) {PORTD=0b0000;}
    }
        if(PORTBbits.RB2==0)
    {
        if(PORTBbits.RB4==0) {PORTD=0b0011;}        
        if(PORTBbits.RB5==0) {PORTD=0b0110;} 
        if(PORTBbits.RB6==0) {PORTD=0b1001;}
      
    }
    
    if(PORTAbits.RA0==1)
    {
        for(int i=0b0000;i<0b1001;i++)
            {
                PORTD=display[i];
                __delay_ms(100);
                PORTEbits.RE0=1;
                __delay_ms(1000);
                PORTEbits.RE0=0;
            }
    }
  
    while(PORTBbits.RB4==0||PORTBbits.RB5==0||PORTBbits.RB6==0||PORTBbits.RB7==0||PORTAbits.RA0==1);
    
    INTCONbits.RBIF=0;
    PORTEbits.RE0=0;
}

void __interrupt() pulsador (void)
{
    
    INTCONbits.GIEL=1;
    TRISAbits.TRISA0=1;
    
    if(PORTAbits.RA0==1)
    {
        INTCONbits.RBIF=0;
        for(int i=0b0000;i<0b1001;i++)
            {
                PORTD=display[i];
                __delay_ms(100);
                PORTEbits.RE0=1;
                __delay_ms(1000);
                PORTEbits.RE0=0;
            }
    }  
}
