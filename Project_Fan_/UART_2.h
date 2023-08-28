/*
 * UART_2.h
 *
 * Created: 2023-07-26 오전 10:33:19
 *  Author: USER
 */ 


#ifndef UART_2_H_
#define UART_2_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>



void UART0_Init();
void UART0_Transmit(char data);
unsigned UART0_Receive(void);


#endif /* UART_2_H_ */