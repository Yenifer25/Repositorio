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
    
    INTCONbits.GIE=1;
    INTCONbits.RBIE=1;
    INTCONbits.RBIF=0;
    
    while(1)
    {
        PORTB=0b11111110;
        PORTB=0b11111101;
        PORTB=0b11111011;
    }
    return;
}
int unidades (void)
{
    PORTD=0x00;
    int a=PORTD;
    char sal;
    const int display[10]={0b0000,0b0001,0b0010,0b0011,0b0100,0b0101,0b0110,0b0111,0b1000,0b1001};
  
    if(PORTBbits.RB0==0)
    {
        if(PORTBbits.RB4==0) {sal='1';}        
        if(PORTBbits.RB5==0) {sal='4';} 
        if(PORTBbits.RB6==0) {sal='7';}
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
        if(PORTBbits.RB4==0) {sal='2';}        
        if(PORTBbits.RB5==0) {sal='5';;} 
        if(PORTBbits.RB6==0) {sal='8';}
        if(PORTBbits.RB7==0) {sal='0';}
    }
        if(PORTBbits.RB2==0)
    {
        if(PORTBbits.RB4==0) {sal='3';}        
        if(PORTBbits.RB5==0) {sal='6';} 
        if(PORTBbits.RB6==0) {sal='9';}
      
    }
    
    sal = sal - '0';
    return sal;
    
}

int decenas (void)
{
    PORTD=0x00;
    int b=PORTD;
    char salida;
    const int display[10]={0b0000,0b0001,0b0010,0b0011,0b0100,0b0101,0b0110,0b0111,0b1000,0b1001};
        
    if(PORTBbits.RB0==0)
    {
        if(PORTBbits.RB4==0) {PORTD=0b0001;}        
        if(PORTBbits.RB5==0) {PORTD=0b0100;} 
        if(PORTBbits.RB6==0) {PORTD=0b0111;}
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
    
    return b;
}
void __interrupt()teclado (void)
{
    int n=0;
    int x;
    int y;
    int z;
    int imp;
    if(n==0)
    {
        x = decenas();
        y = x*16;
        n++;
    }
    else
    {
        z = unidades();
        n++;
    }
    
    imp = y+z;
    
    PORTD=imp;
    
    if(n==2)
    {
        n=0;
    }
   
    while(PORTBbits.RB4==0||PORTBbits.RB5==0||PORTBbits.RB6==0||PORTBbits.RB7==0||PORTAbits.RA0==1);
    
    INTCONbits.RBIF=0;
    PORTEbits.RE0=0;
}