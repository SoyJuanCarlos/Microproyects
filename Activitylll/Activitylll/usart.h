/*
 * usart.h
 *
 * Created: 06/11/2024 02:55:43 a. m.
 *  Author: andro
 */ 


#ifndef USART_H_
#define USART_H_

void init_usart(unsigned int baudrate);        // Inicializa USART con el baudrate especificado
unsigned char usart_receive(void);             // Recibe un carácter
void usart_transmit(unsigned int data);        // Transmite un carácter
void usart_transmit_string(char s[]);          // Transmite una cadena de caracteres

#endif /* USART_H_ */
