/*
 * Activitylll.c
 *
 * Created: 05/11/2024 08:20:36 p. m.
 * Author : andro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "adc.h"


int main(void) 
{
	init_usart(16);          // Inicializa USART
	ADC_init();              // Inicializa ADC
	ADC_start_conversion(0); // Inicia la primera conversión en el canal 0 (POT1)
	sei(); //Interrupciones generales	
	while (1) 
	{
			}
}

