/*
 * File:   punto 2.c
 * Author: USER
 *
 * Created on 18 de agosto de 2020, 10:56 PM
 */


#include <xc.h>
#define _XTAL_FREQ 16000000
void main(void) {
    TRISB=0b00000000;
    PORTB=0X00;
    ADCON1=0B00001111;
    
   
    
    while(1)
        {
        
        if(PORTAbits.RA2==1)
            {
             
                
             PORTB=0b10000000;
             __delay_ms(400);
             PORTB=0b11000000;
               __delay_ms(400);
             PORTB=0b11100000;
               __delay_ms(400);
             PORTB=0b11110000;
               __delay_ms(400);
             PORTB=0b11111000;
               __delay_ms(400);
             PORTB=0b11111100;
               __delay_ms(400);
             PORTB=0b11111110;
               __delay_ms(400);
             PORTB=0b11111111;
               __delay_ms(400);
               
               PORTB=0b11111110;
               __delay_ms(400);
                PORTB=0b11111100;
               __delay_ms(400);
               PORTB=0b11111000;
               __delay_ms(400);
                PORTB=0b11110000;
               __delay_ms(400);
               PORTB=0b11100000;
               __delay_ms(400);
              PORTB=0b11000000;
               __delay_ms(400);
                  PORTB=0b10000000;
             __delay_ms(400);
                PORTB=0b00000000;
             __delay_ms(400);
            }
       
        }
 

}