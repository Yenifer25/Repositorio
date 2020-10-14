/*
 * File:   interrupciones2.c
 * Author: USER
 *
 * Created on 15 de septiembre de 2020, 08:02 PM
 */


#include <xc.h>
#define _XTAL_FREQ 4000000
#pragma config FOSC=XT_XT
#pragma confi CPUDIV=OSC_PLL2
#pragma config PLLDIV=1;

const int display[10]={0b0000,0b0001,0b0010,0b0011,0b0100,0b0101,0b0110,0b0111,0b1000,0b1001};// Arreglo para numeros del display
int unidades (void);
int decenas (void);

void main(void) 
{
    TRISB=0b11111111; // puerto B como entrada
    
    TRISD=0;// puerto D como salida
    PORTD=0;// Inicializar en 0
    
    TRISE=0;//puerto E como salida
    PORTE=0;// Inicializar en 0
    
    TRISA=0b00000001;// RA0 como entrada. RA1-RA6 como salida
    PORTA=0;// Inicializar en 0
    
    TRISC=0;//puerto C como salida
    PORTC=0;// Inicializar en 0
    
    // configuracion modulo ADC
    
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    ADCON0bits.CHS0=0;
    
    //configuración de tiempo de adquisición
    
    ADCON2bits.ACQT=2;
    ADCON2bits.ADCS=4;
    ADCON2bits.ADFM=1;
    ADCON1bits.PCFG=0b1110; // AN0 entrada analogica
    //iniciar el conversor
    ADCON0bits.ADON=1;
    
    //Configuración modulo interrupciones
    
    INTCON2bits.RBIP=0; // RB4 a RB7 interrupcion baja por cambio de estado
    INTCON2bits.NOT_RBPU=0; // Activar resistencias de pull up
    INTCONbits.GIE=1; // Habilitar interrupciones globales
    INTCONbits.RBIE=1; // Bit de permiso de la interrupcion por cambio de estado
    INTCONbits.RBIF=0; // Bandera de interrupcion por cambio de estado
    
    // registros de prioridades
    
    RCONbits.IPEN=1; // Activar jerarquia de interrupciones
    INTCONbits.GIEH=1; // Activar prioridad alta
    INTCONbits.GIEL=1; // Activar prioridad baja
    INTCONbits.INT0IE=1; // Bit de permiso de la interrupcion INT0
    INTCONbits.INT0IF=0; // Bandera de interrupcion INT0
    
    while(1)
    {
        PORTA=0b11111101;     // Correr 0 en el puerto a para las columnas
        PORTA=0b11111011;                 //del teclado matricial
        PORTA=0b11110111;
        
        //Iniciar conversor analogico-digital
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.GO_DONE==1);
        
        float volt;
        int adc,temp;
            
        adc=ADRESH<<8; // justificacion a la derecha
        adc=adc+ADRESL;
        volt=adc;
        volt=(adc*5.0)/1023.0;//conversión BCD a 7 segmentos
            
        temp=volt/0.01; // ya que la sencibilidad del lm35 es de 10mv/c
        
        if(temp<=60) 
        {
            PORTEbits.RE1=0;
        }
        else
        {
            PORTEbits.RE1=1;
        }
       
        // Interrupcion RB0 alta prioridad pulsador de mantenimiento
        
 if(PORTBbits.RB0==1)
    {
         INTCONbits.INT0F=0;
         for(int i=0b0000;i<=0b1001;i++) //conteo del 0 al 9
            {
             PORTC=0;
             PORTD=display[i];
             __delay_ms(1000);
             
            }
         for(int i=0;i<3;i++) // led enciende y apaga 3 veces
         {
            PORTEbits.RE0=1;
            __delay_ms(1000);
            PORTEbits.RE0=0;
            __delay_ms(1000);
         }   
         PORTD=0;
    }   
    }
    return;
}

// Interrupcion baja prioridad teclado matricial

void __interrupt(low_priority)teclado (void)
{
    int a,j,cont=0;
   
    if(cont==0)
    {
        a= decenas();
        PORTC=a;
        cont++;  
    }
  
    if(cont==1)
    {
        j= unidades ();
        PORTD=j;
        cont++;
    }
    
    if(cont==2)
    {
        cont=0;
    }
    
    while(PORTBbits.RB4==0||PORTBbits.RB5==0||PORTBbits.RB6==0||PORTBbits.RB7==0);
    
    INTCONbits.RBIF=0; // sale de la interrupcion
    PORTEbits.RE0=0;
}

// Funcion para las unidades

int unidades (void)
{
    char salida;
    
    if(PORTAbits.RA1==0)
    {
        if(PORTBbits.RB4==0) {salida='1';}        
        if(PORTBbits.RB5==0) {salida='4';} 
        if(PORTBbits.RB6==0) {salida='7';}
        if(PORTBbits.RB7==0) 
        {
            for(int i=salida;i>=0b0000;i--) // Microondas en marcha
            {
                PORTD=display[i];
                __delay_ms(1000);
                PORTEbits.RE0=1;
            }
        }
    }
        if(PORTAbits.RA2==0)
    {
        if(PORTBbits.RB4==0) {salida='2';}        
        if(PORTBbits.RB5==0) {salida='5';} 
        if(PORTBbits.RB6==0) {salida='8';}
        if(PORTBbits.RB7==0) {salida='0';}
    }
        if(PORTAbits.RA3==0)
    {
        if(PORTBbits.RB4==0) {salida='3';}        
        if(PORTBbits.RB5==0) {salida='6';} 
        if(PORTBbits.RB6==0) {salida='9';}
    }
    salida=salida-'0';
    return salida;
}

// Funcion para las decenas

int decenas (void)
{
    char sal;
    
    if(PORTAbits.RA1==0)
    {
        if(PORTBbits.RB4==0) {sal='1';}        
        if(PORTBbits.RB5==0) {sal='3';} 
        if(PORTBbits.RB6==0) {sal='7';}
        if(PORTBbits.RB7==0) 
        {
            for(int i=sal;i>=0b0000;i--)
            {
                PORTD=display[i];
                __delay_ms(1000);
                PORTEbits.RE0=1;
            }
        }
    }
        if(PORTAbits.RA2==0)
    {
        if(PORTBbits.RB4==0) {sal='2';}        
        if(PORTBbits.RB5==0) {sal='5';} 
        if(PORTBbits.RB6==0) {sal='8';}
        if(PORTBbits.RB7==0) {sal='0';}
    }
        if(PORTAbits.RA3==0)
    {
        if(PORTBbits.RB4==0) {sal='3';}        
        if(PORTBbits.RB5==0) {sal='6';} 
        if(PORTBbits.RB6==0) {sal='9';}
    }
    sal=sal-'0';
    return sal;
}

