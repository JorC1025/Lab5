/*
 * PWM1.c
 *
 * Created: 9/4/2025 16:18:53
 *  Author: jorge
 */ 
#include "PWM1.h"

void pwm1_init(){

	// Configurar PB2 (OC1B) como salida
DDRB |= (1 << DDB2);
TCCR1A |= (1 << COM1B1);  



}

void pwm1_set_pulse(uint16_t pulso_us) {
	// pulse_us en microsegundos (por ejemplo 1000 a 2000)
	// Convertir a ticks del timer (16 MHz / 8 = 2 MHz ? 1 tick = 0.5 us)



	OCR1B = pulso_us;
}