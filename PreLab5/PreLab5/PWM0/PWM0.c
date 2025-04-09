/*
 * PWM0.c
 *
 * Created: 8/4/2025 15:09:57
 *  Author: Jorge Cruz
 */ 
#include "PWM0.h"

void pwm1_init(void){

// Configurar PB1 (OC1A) como salida
DDRB |= (1 << PORTB1);

// Modo Fast PWM con TOP = ICR1
TCCR1A = (1 << COM1A1) | (1 << WGM11);  // Se limpia el 0CR1A por comparaci�n
TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8

ICR1 = 40000;  // TOP para 20ms (50Hz) con F_CPU = 16MHz y prescaler = 8

OCR1A = 1000;
}

void pwm1_set_pulse(uint16_t pulse_us) {
	// pulse_us en microsegundos (por ejemplo 1000 a 2000)
	// Convertir a ticks del timer (16 MHz / 8 = 2 MHz ? 1 tick = 0.5 us)
	if (pulse_us < 1000) pulse_us = 1000;
	if (pulse_us > 5000) pulse_us = 5000;
	
	OCR1A = (pulse_us);
}