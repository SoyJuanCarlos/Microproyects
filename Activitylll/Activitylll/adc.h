/*
 * adc.h
 *
 * Created: 05/11/2024 08:25:14 p. m.
 *  Author: andro
 */ 


#ifndef ADC_H_
#define ADC_H_
void ADC_WithInterrupt(void);
void ADC_init(void);
void usart_transmit(unsigned int data);
void usart_transmit_string(char s[]);
#endif /* ADC_H_ */