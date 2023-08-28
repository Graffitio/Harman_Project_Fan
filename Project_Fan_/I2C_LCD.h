/*
 * I2C.h
 *
 * Created: 2023-07-25 오후 3:06:22
 *  Author: USER
 */ 


#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#include "I2C.h" // I2C 관련 헤더 파일 포함

#define LCD_RS	0 // LCD의 Register Select 핀 번호, Control reg : 0 / Data Reg : 1
#define LCD_RW	1 // LCD의 Read/Write 핀 번호
#define LCD_E	2 // LCD의 Enable 핀 번호
#define LCD_BACKLIGHT	3 // LCD의 백라이트 핀 번호

#define LCD_DEV_ADDR	(0x27<<1) // I2C LCD의 디바이스 주소, <<1 : Write 모드 유지

#define COMMAND_DISPLAY_CLEAR	0x01 // 디스플레이 지우기 명령
#define COMMAND_DISPLAY_ON		0x0c // 디스플레이 켜기 명령
#define COMMAND_DISPLAY_OFF		0x08 // 디스플레이 끄기 명령
#define COMMAND_4_BIT_MODE		0x28 // 4비트 모드로 설정 명령
#define COMMAND_ENTRY_MODE		0x06 // 엔트리 모드 설정 명령

// 함수 원형 선언
void LCD_Data4bit(uint8_t data); // 4비트 데이터 전송 함수
void LCD_EnablePin(); // Enable 핀을 제어하는 함수
void LCD_WriteCommand(uint8_t commandData); // 명령어를 LCD에 전송하는 함수
void LCD_WriteData(uint8_t charData); // 데이터를 LCD에 전송하는 함수
void LCD_BackLight(); // LCD 백라이트 제어 함수
void LCD_gotoXY(uint8_t row, uint8_t col); // LCD 화면 커서 위치 설정 함수
void LCD_WriteString(char *string); // 문자열을 LCD에 출력하는 함수
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string); // 특정 위치에 문자열 출력 함수
void LCD_Init(); // LCD 초기화 함수

#endif /* I2C.LCD_H_ */