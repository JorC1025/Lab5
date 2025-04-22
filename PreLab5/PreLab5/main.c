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
#include "PWM1/PWM1.h"
#include "LEDPOT/LEDPOT.h"

volatile uint8_t valor_adc1 = 0;
volatile uint8_t valor_adc2 = 0;
uint16_t pulso_us = 1000;
uint16_t pulse_us = 1000;
uint8_t duty = 63;
uint8_t cant_volt = 0;
uint8_t canal_adc = 0;
uint8_t contador = 0;
uint8_t pwmmanual = 0;
void setup();
void initADC();


int main(void)
{

	setup();
    while (1) 
    {
    }
}

void setup(){
	
	cli();

	initADC();
	pwm0_init();
	pwm1_init();
	initTM0();
	DDRC &= ~(1<<DDC3);
	DDRC &= ~(1<<DDC2);
	DDRC &= ~(1<<DDC1);
	sei();

	
	
}



ISR (ADC_vect){
	



	if (canal_adc==0)
	{
		
		ADMUX = 0;
		ADMUX = (1 << REFS0) | (1 << ADLAR) | (1 << MUX0);
		canal_adc++;
		pulse_us =  ((uint32_t)ADCH * 3850) / 255 +1200; //Se convierte el adch al pulso por medio de la ecuación según el prescaler
		pwm0_set_pulse(pulse_us); 
		

	} else if (canal_adc==1){
		
		ADMUX = 0;
		ADMUX = (1 << REFS0) | (1 << ADLAR) | (1 << MUX1); 
		canal_adc++;
		pulso_us =  ((uint32_t)ADCH * 3850) / 255 + 1200;
		pwm1_set_pulse(pulso_us); //Se llama a la función de este servo

	} else if (canal_adc==2) {
		
			ADMUX = 0;
			ADMUX = (1 << REFS0) | (1 << ADLAR) | (1 << MUX1)| (1 << MUX0); //Selección de canal
			canal_adc = 0; //Se reinicia la fila de los canales
			pwmmanual = ADCH; //Se utiliza una variable esta vez debido a la comparación

			_delay_us(20);
		
	}
	
    // Mapear 0-255 a 1000-2000 us

	
	ADCSRA |= (1 << ADSC);
}

void initADC(){
	

	ADMUX = 0;
	ADMUX = (1 << REFS0) | (1 << ADLAR) | (1 << MUX0);

	
	ADCSRA = 0;
	ADCSRA |= (1 << ADPS1) |(1<<ADPS0) | (1<< ADEN) | (1<<ADIE);
	
	ADCSRA |= (1 << ADSC);
	canal_adc = 0;
}

ISR (TIMER0_OVF_vect){
	
	

		contador++;

	if (contador>pwmmanual)	
	{
		PORTB |= (1<<PORTB3);
	}
	else if (contador<pwmmanual)
	{
		PORTB &= ~(1<<PORTB3);
	}
	
}