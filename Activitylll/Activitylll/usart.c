/*
 * usart.c
 *
 * Created: 06/11/2024 02:55:07 a. m.
 *  Author: andro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

volatile char usart_received_char;  // Variable global para almacenar el carácter recibido

ISR (USART_RX_vect) {
	usart_received_char = UDR0;    // Guarda el carácter recibido en la variable global
}

void init_usart(unsigned int baudrate) {
	UCSR0A = (1 << U2X0);  // Modo doble velocidad
	UBRR0H = (unsigned char) (baudrate >> 8);
	UBRR0L = (unsigned char) baudrate;

	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);  // 8 bits de datos
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);    // Habilita RX y TX
	UCSR0B |= (1 << RXCIE0);                 // Activa interrupciones de recepción
}

unsigned char usart_receive(void) 
{
	while (!(UCSR0A & (1 << RXC0)));  // Espera a recibir un dato
	return UDR0;
}

void usart_transmit(unsigned int data) {
	while (!(UCSR0A & (1 << UDRE0)));  // Espera hasta que el buffer esté vacío
	UDR0 = data;  // Envía el dato
}

void usart_transmit_string(char s[]) {
	int i = 0;
	while (s[i] != '\0') {
		usart_transmit(s[i++]);
	}
}
