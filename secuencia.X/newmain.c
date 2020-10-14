/*
 * File:   newmain.c
 * Author: USER
 *
 * Created on 18 de agosto de 2020, 08:50 PM
 */



#include <xc.h>
#define _XTAL_FREQ 16000000
void main(void)
{
    ADCON1=0b00001111;
    TRISD=0b00000000;
    PORTD=0b00000000;
    while(1)
    {
    while(1)
    {
        if(PORTAbits.RA2==1)
        {
            while(!PORTAbits.RA2)
            {
        
    
    PORTD=0b10000000;
    __delay_ms(100);
    PORTD=0b01000000;
    __delay_ms(100);
    PORTD=0b00100000;
    __delay_ms(100);
    PORTD=0b00010000;
    __delay_ms(100);
    PORTD=0b00001000;
    __delay_ms(100);
    PORTD=0b00000100;
    __delay_ms(100);
    PORTD=0b00000010;
    __delay_ms(100);
    PORTD=0b00000001;
    __delay_ms(100);
    
    //CAMBIO DE DIRECCION
    PORTD=0b00000010;
    __delay_ms(100);
    PORTD=0b00000100;
    __delay_ms(100);
    PORTD=0b00001000;
    __delay_ms(100);
    PORTD=0b00010000;
    __delay_ms(100);
    PORTD=0b00100000;
    __delay_ms(100);
    PORTD=0b01000000;
    __delay_ms(100);
    PORTD=0b10000000;
    __delay_ms(100);
    }
    }
    }
    }
         
    return;
}
