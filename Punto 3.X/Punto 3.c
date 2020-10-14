/*
 * File:   Punto 3.c
 * Author: USER
 *
 * Created on 18 de agosto de 2020, 11:27 PM
 */

#include <xc.h>
#define _XTAL_FREQ 16000000
void main(void) {
    ADCON1=0b00001111;
    TRISA=0b00000000;
    PORTA=0X00;
   
    while(1)
        {
        if(PORTAbits.RA2==1)
            { 
             PORTA=0b00000010;   //4
             __delay_ms(200);
             PORTA=0b00010010;      //5
               __delay_ms(200);
             PORTA=0b00001010;      //6    
               __delay_ms(200);
             PORTA=0b00011010;
               __delay_ms(200);     //7
             PORTA=0b00000000;
               __delay_ms(200);
             
            }
       
        }
 

}

