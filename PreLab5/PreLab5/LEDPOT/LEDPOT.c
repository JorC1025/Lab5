/*
 * LEDPOT.c
 *
 * Created: 21/4/2025 17:55:13
 *  Author: jorge
 */ 
#include "LEDPOT.h"
void initTM0(){
	
	DDRB |= (1 << DDB3);
	TCCR0A = 0;
	TCCR0B = 0;
	TCCR0B |= (1<<CS00);
	TIMSK0 |= (1<<TOIE0);
}