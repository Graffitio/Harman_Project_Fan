/*
 * Fan.h
 *
 * Created: 2023-08-28 오전 11:26:50
 *  Author: USER
 */ 


#ifndef FAN_H_
#define FAN_H_

#include <avr/io.h> // AVR 입출력 헤더 파일
#include <util/delay.h> // 딜레이 함수 헤더 파일
#include <avr/interrupt.h> // 인터럽트 헤더 파일
#include "Button_structure.h" // 버튼 관련 헤더 파일
#include "I2C_LCD.h" // I2C LCD 관련 헤더 파일
#include "UART_2.h" // UART 통신 관련 헤더 파일

#define Fan_stop	0
#define Fan_1st		1
#define Fan_2nd		2
#define Fan_3rd		3
#define Fan_initial 4
#define PRESCALER 1024

// 버튼 객체들 선언
Button btnStop;
Button btn_1stage;
Button btn_2stage;
Button btn_3stage;
Button btn_spin;
int Fan_run_status;
//uint8_t distance;

// 함수 원형 선언
void Fan_Init(); // 팬 초기화 함수
void Fan_Stage(); // 팬 스테이지 동작 함수
void Fan_Start_signal(); // 팬 시작 신호 출력 함수
void Spin_stop(); // 회전 정지 함수
void Spin_start(uint8_t degree); // 회전 시작 함수
void Fan_continue_run();
void Display_LCD();
void Head_spin_op();
void Spin_status_LED();
//uint8_t measure_distance();
//void Timer_init();


#endif /* FAN_H_ */