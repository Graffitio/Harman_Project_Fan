/*
 * Fan.c
 *
 * Created: 2023-08-28 오전 11:26:39
 *  Author: USER
 */ 

#include "Fan.h"

void Fan_Init()
{
	// I2C LCD 초기화
	LCD_Init();
	
	// Button Setting
	LED_DDR = 0xff; // PORTA 출력 설정
	
	Button_init(&btnStop, &BUTTON_DDR, &BUTTON_PIN, BUTTON_STOP); // PORTC 0번 핀 입력 활성화
	Button_init(&btn_1stage, &BUTTON_DDR, &BUTTON_PIN, BUTTON_1stage); // PORTC 1번 핀 입력 활성화
	Button_init(&btn_2stage, &BUTTON_DDR, &BUTTON_PIN, BUTTON_2stage); // PORTC 2번 핀 입력 활성화
	Button_init(&btn_3stage, &BUTTON_DDR, &BUTTON_PIN, BUTTON_3stage); // PORTC 3번 핀 입력 활성화
	Button_init(&btn_spin, &BUTTON_DDR, &BUTTON_PIN, BUTTON_spin); // PORTC 4번 핀 입력 활성화
	
	// PWM Setting
	DDRF |= (1<<PINF4) | (1<<PINF5); // PINF4, 5 출력 설정
	TCCR0 |= (1<<CS02) | (1<<CS01) | (0<<CS00); // 256분주
	TCCR0 |= (1<<WGM01) | (1<<WGM00); // Fast PWM mode
	TCCR0 |= (1<<COM01) | (0<<COM00); // 비반전 모드
	DDRB |= (1<<DDRB4); // MOTOR 제어
}

void Fan_Start_signal()
{
	// Fan Start Sign
	LCD_WriteStringXY(0,0," Hello Modesty! ");
	LCD_WriteStringXY(1,0,"Please Press Btn");
}

void Fan_Stage()
{
	if (BUTTON_getState(&btnStop) == ACT_RELEASED)
	{
		LED_PORT = 0x00;
		PORTF |= (1<<PINF4) | (1<<PINF5); // MOtor Break
		LCD_WriteStringXY(0,0,"   Stop mode    ");
		LCD_WriteStringXY(1,0,"  Power :   0%  ");
		_delay_ms(3000);
		Fan_Start_signal();		
	}
	if(BUTTON_getState(&btn_1stage) == ACT_RELEASED)
	{
		LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		// PORTF |= (1<<PINF4) | (1<<PINF5); // Pulse가 중첩되어 더 커지는 것을 방지하기 위한 MOtor Break
		// DDRB &= ~(1<<PINB4); // Pulse가 중첩되어 더 커지는 것을 방지하기 위한 MOtor Break
		LED_PORT = 0x00;
		LED_PORT |= (1<<PINA0);
		DDRB |= (1<<PINB4);
		OCR0 = 64; // 25%
		PORTF &= ~(1<<PINF5); // Motor 정방향 회전
		PORTF |= (1<<PINF4);
		LCD_WriteStringXY(0,0,"   1st Stage    ");
		LCD_WriteStringXY(1,0,"  Power :  25%  ");

	}
	if(BUTTON_getState(&btn_2stage) == ACT_RELEASED)
	{
		LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		// DDRB &= ~(1<<PINB4); // Pulse가 중첩되어 더 커지는 것을 방지하기 위한 MOtor Break
		LED_PORT = 0x00;
		LED_PORT |= (1<<PINA0) | (1<<PINA1);
		DDRB |= (1<<PINB4);
		OCR0 = 128; // 50%
		PORTF &= ~(1<<PINF5); // Motor 정방향 회전
		PORTF |= (1<<PINF4);
		LCD_WriteStringXY(0,0,"   2nd Stage    ");
		LCD_WriteStringXY(1,0,"  Power :  50%  ");
		TWDR = 0x00;
	}
	if(BUTTON_getState(&btn_3stage) == ACT_RELEASED)
	{
		LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		// PORTF |= (1<<PINF4) | (1<<PINF5); // Pulse가 중첩되어 더 커지는 것을 방지하기 위한 MOtor Break
		// DDRB &= ~(1<<PINB4); // Pulse가 중첩되어 더 커지는 것을 방지하기 위한 MOtor Break
		LED_PORT = 0x00;
		LED_PORT |= (1<<PINA0) | (1<<PINA1) | (1<<PINA2);
		DDRB |= (1<<PINB4);
		OCR0 = 255; // 100%
		PORTF &= ~(1<<PINF5); // Motor 정방향 회전
		PORTF |= (1<<PINF4);
		LCD_WriteStringXY(0,0,"   3rd Stage    ");
		LCD_WriteStringXY(1,0,"  Power : 100%  ");
	}
}

void Spin_stop()
{
	TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0)); // PWM 출력 안 되도록
}

void Spin_start(uint8_t degree)
{
	// 0도 : 125 / 180도 : 625
	uint16_t degree_value;
	TCCR1A |= (1<<COM1A1); // PWM 다시 출력되도록
	if (degree_value < 0) // 제한 범위를 벗어나 고장나지 않도록 설정
	{
		degree = 0;
	}
	else if(degree > 180)
	{
		degree = 180;
	}
	degree_value = (uint16_t)((degree/180.0)*500 + 125); // 우리가 흔히 쓰는 각도로 표현하기 위한 식
	OCR1A = degree_value;
}