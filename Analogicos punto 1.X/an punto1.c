/*
 * File:   an punto1.c
 * Author: USER
 *
 * Created on 24 de agosto de 2020, 08:12 PM
 */

#include <xc.h>
#pragma config FOSC=XT_XT
#pragma config CPUDIV=OSC1_PLL2
                                  


void main(void) {
    int adc;
    int volt,ud,dec;
   int display[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
   
    TRISA=0b00000001;
    TRISB=0;
    TRISD=0;
       
    
    PORTB=0;
    PORTD=0;
    
    
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    
    ADCON1bits.PCFG=0b1101;

    
    ADCON0bits.CHS0=0;
   
    ADCON2bits.ACQT=2;
    ADCON2bits.ADCS=4;
    ADCON2bits.ADFM=1;
    
    ADCON0bits.ADON=1;
    
    while(1)
    {
        
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.GO_DONE==1);
        
        adc=ADRESH;
        
        adc=adc<<8;
        adc=adc+ADRESL;
        volt=(adc*5)/1024;
        volt=volt*10;
        if(volt>9){
        dec=volt/10;}
        else{
        ud=volt%10;}
        
        for(int n=0;n<20;n++){
            PORTD=(display[dec]);
       
         if(volt==0||volt<1)
        {
             
            PORTD=63;
            }
        else if(volt==1||volt<2){
           
            PORTD=6;
        ;}
        else if(volt==2||volt<3){
         
            PORTD=91;
            ;
            }
        else if(volt==3||volt<4){
            
            PORTD=79;
           }
        else if (volt==4||volt<5){
           
            PORTD=102;
            ;
        }
        else if (volt==5||volt<6){
            
            PORTD=109;
            
        }
         
         for(int c=0;c<20;c++){
             
        if(volt==0||volt<1)
        {
            
            PORTB=63;}
        else if(volt==1||volt<2){
        
            PORTB=6;}
        else if(volt==2||volt<3){
           
            PORTB=91;
            }
        else if(volt==3||volt<4){
            PORTB=(display[ud]);
            PORTB=79;
           }
        else if (volt==4||volt<5){
         PORTB=(display[ud]);
            PORTB=102;
        }
        else if (volt==5||volt<6){
            PORTB=(display[ud]);
            PORTB=109;
        }
        else if (volt==6||volt<7){
           PORTB=(display[ud]);
            PORTB=125;
        }
        else if (volt==7||volt<8){
           PORTB=(display[ud]);
            PORTB=7;
        }
        else if (volt==8||volt<9){
            PORTB=(display[ud]);
            PORTB=127;
        }
        else if (volt==9||volt<10){
            PORTB=(display[ud]);
            PORTB=111;
        }
        
        }
        }
    }
    return;
}
