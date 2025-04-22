/*
 * PWM1.h
 *
 * Created: 9/4/2025 16:19:08
 *  Author: jorge
 */ 


#ifndef PWM1_H_
#define PWM1_H_


#include <avr/io.h>

#define invert 1
#define non_invert 0
void pwm1_init();
void pwm1_set_pulse(uint16_t pulso_us);



#endif /* PWM1_H_ */