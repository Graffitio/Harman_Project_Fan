/*
 * I2C.h
 *
 * Created: 2023-07-25 오후 2:29:25
 *  Author: USER
 */ 


#ifndef I2C_H_
#define I2C_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define I2C_DDR	DDRD
#define I2C_SCL	PORTD0 // clock은 PORTD0
#define I2C_SDA	PORTD1 // 


void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_TxData(uint8_t data);
void I2C_TxByte(uint8_t devAddrRW, uint8_t data);


#endif /* I2C_H_ */