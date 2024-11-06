/*
 * adc.c
 *
 * Created: 05/11/2024 08:24:56 p. m.
 *  Author: andro
 */ 

#include <avr/io.h>
#include <stdlib.h>	//Para utilizar las rutinas de conversión a ASCII
#include <avr/interrupt.h>
#include "adc.h"
#include "usart.h"

/************************************************************************
* USO DEL ADC CON INTERRUPCIONES
************************************************************************/

volatile uint8_t pot_selected = 0;

/***Rutina de atención a las interrupciones del convertidor***/
ISR (ADC_vect)
{
	uint8_t low_part = ADCL;
	uint16_t adc_result = (ADCH << 2) | (low_part >> 6);
	//Para el potenciómetro...
	char voltage_string [10];
	float voltage = (adc_result * 5.0) / 1023;
	dtostrf(voltage, 4, 2, voltage_string);
	
	// Envía el valor del voltaje a través de USART
	usart_transmit_string("Potenciómetro ");
	usart_transmit(pot_selected ? '2' : '1'); // Muestra si es POT1 o POT2
	usart_transmit_string(": ");
	usart_transmit_string(voltage_string);
	usart_transmit_string(" V\n");
	
	 // Cambia entre POT1 y POT2
	 pot_selected = !pot_selected;
	 ADC_start_conversion(pot_selected);
	 
}

void ADC_init(void) 
{
	ADCSRA |= (1 << ADEN);   // Habilita el ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler de 128
	ADMUX |= (1 << REFS0);   // Referencia AVCC
	ADMUX |= (1 << ADLAR);   // Justificado a la izquierda
	ADCSRA |= (1 << ADIE);   // Habilita interrupciones del ADC
}

void ADC_start_conversion(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07); // Selecciona el canal (0 o 1)
	ADCSRA |= (1 << ADSC);                     // Inicia la conversión
}