/*
 * PreLab5.c
 *
 * Created: 8/4/2025 14:55:11
 * Author : Jorge Cruz
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "PWM0/PWM0.h"

volatile uint8_t valor_adc = 0;
uint8_t duty = 63;
uint8_t cant_volt = 0;
void setup();



int main(void)
{
	setup();
	pwm1_init();
	initADC();

    while (1) 
    {
    }
}

void setup(){
	
	cli();
	CLKPR = (1 << CLKPCE);
	initADC();
	sei();

	
	
}



ISR (ADC_vect){
	
    valor_adc = ADCH;  

    // Mapear 0-255 a 1000-2000 us
    uint16_t pulse_us =  ((uint16_t)valor_adc * 4000) / 255 +1200;
    pwm1_set_pulse(pulse_us);

	
	ADCSRA |= (1 << ADSC);
}

void initADC(){
	
	ADMUX = 0;
	ADMUX |= (1 << REFS0) | (1 << ADLAR) | (1<< MUX2)| (1<<MUX1);
	
	ADCSRA = 0;
	ADCSRA |= (1 << ADPS1) |(1<<ADPS0) | (1<< ADEN) | (1<<ADIE);
	
	ADCSRA |= (1 << ADSC);
}
