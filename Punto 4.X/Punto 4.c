/*
 * File:   Punto 4.c
 * Author: USER
 *
 * Created on 19 de agosto de 2020, 12:18 AM
 */


#include <xc.h>
#define _XTAL_FREQ 16000000
void main(void) {
    ADCON1=0b00001111;
    TRISA=0b00000100;
    PORTA=0X00;
   
    while(1)
        {
        if(PORTAbits.RA2==1)
            {
             
             PORTA=0b00000010;   
             __delay_ms(500);
             PORTA=0b00000000;      
             __delay_ms(500);
            
            }
       
        }
}