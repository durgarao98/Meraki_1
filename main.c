/*
 */

#include <avr/io.h>
#include<stdint.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#define SET_BIT(PORT, BIT) PORT|=(1<<BIT)
#define CLR_BIT(PORT, BIT) PORT&=!(1<<BIT)

int main(void)
{

    // Insert code
SET_BIT(DDRD,PD6);//PD6(OCOA pin) as output
CLR_BIT(DDRD,PD2);
CLR_BIT(DDRD,PD3);

SET_BIT(PORTD,PD2);
SET_BIT(PORTD,PD3);

EICRA&=!(1<<ISC00);
EICRA|=(1<<ISC01);

EICRA&=!(1<<ISC10);
EICRA|=(1<<ISC11);

EIMSK|=((1<<INT1)|(1<<INT0));

TCCR0A|=((1<<WGM01)|(1<<WGM00));

TCCR0A|=(1<<COM0A1);
TCCR0A&=!(1<<COM0A0);

TCCR0B|=((1<<CS00)|(1<<CS02));
TCCR0B&=!(1<<CS01);

TCNT0=0X00;
OCR0A=128;
sei();

    while(1)
    {

    }

    return 0;
}
ISR(INT0_vect)
{
    cli();
    if(OCR0A<255){
        OCR0A=OCR0A+12.75;
    }
    sei();
}
ISR(INT1_vect)
{
    cli();
    if(OCR0A>0){
        OCR0A=OCR0A
        -12.75;
    }
    sei();
}
