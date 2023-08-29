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
	
	// Head Spin
	TCCR1A |= (1<<WGM11) | (0<<WGM10); // Fast PWM(mode 14) 세팅
	TCCR1B |= (1<<WGM13) | (1<<WGM12);
	TCCR1A |= (1<<COM1A1) | (0<<COM1A0);
	TCCR1B |= (0<<CS12) | (1<<CS11) | (1<<CS10);
	TCCR1C = 0x00; // default가 0이라 안 써줘도 됨		
	ICR1 = 4999;
	
	//ISR
	//EICRB |=  (1<<ISC41) | (0<<ISC40);
	//EIMSK |=  (1<<INT4);
	//DDRE &= ~(1<<DDRE4);
	//sei();
		
}

void Fan_Start_signal()
{
	// Fan Start Sign
	LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
	LCD_WriteStringXY(0,0," Hello Modesty! ");
	LCD_WriteStringXY(1,0,"Please Press Btn");
	_delay_ms(3000);
	Fan_run_status = Fan_initial;
}

void Fan_Stage()
{
	if (BUTTON_getState(&btnStop) == ACT_RELEASED)
	{
		//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		LED_PORT = 0x00;
		PORTF |= (1<<PINF4) | (1<<PINF5); // MOtor Break
		LCD_WriteStringXY(0,0,"   Stop mode    ");
		LCD_WriteStringXY(1,0,"  Power :   0%  ");
		Fan_run_status = Fan_stop;
		spin_cnt = 0;
		//_delay_ms(3000);
		//Fan_Start_signal();
		//Fan_run_status = Fan_stop;		
	}
	if(BUTTON_getState(&btn_1stage) == ACT_RELEASED)
	{
		//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
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
		Spin_status_LED();
		Fan_run_status = Fan_1st;

	}
	if(BUTTON_getState(&btn_2stage) == ACT_RELEASED)
	{
		//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		// DDRB &= ~(1<<PINB4); // Pulse가 중첩되어 더 커지는 것을 방지하기 위한 MOtor Break
		LED_PORT = 0x00;
		LED_PORT |= (1<<PINA0) | (1<<PINA1);
		DDRB |= (1<<PINB4);
		OCR0 = 128; // 50%
		PORTF &= ~(1<<PINF5); // Motor 정방향 회전
		PORTF |= (1<<PINF4);
		LCD_WriteStringXY(0,0,"   2nd Stage    ");
		LCD_WriteStringXY(1,0,"  Power :  50%  ");
		Spin_status_LED();
		Fan_run_status = Fan_2nd;
	}
	if(BUTTON_getState(&btn_3stage) == ACT_RELEASED)
	{
		//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
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
		Spin_status_LED();
		Fan_run_status = Fan_3rd;
	}
}

void Fan_continue_run()
{
	switch (Fan_run_status)
	{
		case 0:
			//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
			LED_PORT = 0x00;
			PORTF |= (1<<PINF4) | (1<<PINF5); // MOtor Break
			DDRB &= ~(1<<PINB4);
			LCD_WriteStringXY(0,0,"   Stop mode    ");
			LCD_WriteStringXY(1,0,"  Power :   0%  ");
			Fan_run_status = Fan_stop;
			spin_cnt = 0;
			Spin_status_LED();
			Fan_Stage();
			break;
		
		case 1 :
			//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
			LED_PORT = 0x00;
			LED_PORT |= (1<<PINA0);
			DDRB |= (1<<PINB4);
			OCR0 = 64; // 25%
			PORTF &= ~(1<<PINF5); // Motor 정방향 회전
			PORTF |= (1<<PINF4);
			LCD_WriteStringXY(0,0,"   1st Stage    ");
			LCD_WriteStringXY(1,0,"  Power :  25%  ");
			Fan_run_status = Fan_1st;
			Spin_status_LED();
			Fan_Stage();
		break;
		
		case 2 :
			//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
			LED_PORT = 0x00;
			LED_PORT |= (1<<PINA0) | (1<<PINA1);
			DDRB |= (1<<PINB4);
			OCR0 = 128; // 50%
			PORTF &= ~(1<<PINF5); // Motor 정방향 회전
			PORTF |= (1<<PINF4);
			LCD_WriteStringXY(0,0,"   2nd Stage    ");
			LCD_WriteStringXY(1,0,"  Power :  50%  ");
			Fan_run_status = Fan_2nd;
			Spin_status_LED();
			Fan_Stage();
		break;
		
		case 3 :
			//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
			LED_PORT = 0x00;
			LED_PORT |= (1<<PINA0) | (1<<PINA1) | (1<<PINA2);
			DDRB |= (1<<PINB4);
			OCR0 = 255; // 100%
			PORTF &= ~(1<<PINF5); // Motor 정방향 회전
			PORTF |= (1<<PINF4);
			LCD_WriteStringXY(0,0,"   3rd Stage    ");
			LCD_WriteStringXY(1,0,"  Power : 100%  ");
			Fan_run_status = Fan_3rd;
			Spin_status_LED();
			Fan_Stage();
		break;
		
		//case 4 :
			//Fan_Start_signal();
		//break;
	}
}

void Display_LCD()
{
	switch (Fan_run_status)
	{
		case 0:
		//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		LCD_WriteStringXY(0,0,"   Stop mode    ");
		LCD_WriteStringXY(1,0,"  Power :   0%  ");
		//Spin_status_LED();
		Fan_run_status = Fan_stop;
		Fan_Stage();
		break;
		
		case 1 :
		//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		LCD_WriteStringXY(0,0,"   1st Stage    ");
		LCD_WriteStringXY(1,0,"  Power :  25%  ");
		//Spin_status_LED();
		Fan_run_status = Fan_1st;
		Fan_Stage();
		Fan_continue_run();
		break;
		
		case 2 :
		//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		LCD_WriteStringXY(0,0,"   2nd Stage    ");
		LCD_WriteStringXY(1,0,"  Power :  50%  ");
		//Spin_status_LED();
		Fan_run_status = Fan_2nd;
		Fan_Stage();
		Fan_continue_run();
		break;
		
		case 3 :
		//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		LCD_WriteStringXY(0,0,"   3rd Stage    ");
		LCD_WriteStringXY(1,0,"  Power : 100%  ");
		//Spin_status_LED();
		Fan_run_status = Fan_3rd;
		Fan_Stage();
		Fan_continue_run();
		break;
		
		//case 4 :
		//Fan_Start_signal();
		//break;
	}
}

void Head_spin_op()
{
	BUTTON_spin_getState(&btn_spin);
	switch (spin_cnt)
	{
		case 1:
		//Spin_status_LED();
		Fan_continue_run();
		Display_LCD();
		DDRB = (1<<PINB5);
		BUTTON_spin_getState(&btn_spin);
		while((spin_cnt == 1))
		{
			Spin_status_LED();
			for (int i = 0; i < 90 ; i++)
			{
				//Spin_status_LED();
				BUTTON_spin_getState(&btn_spin);
				Fan_continue_run();
				Display_LCD();
				Spin_start(2*i);
				//_delay_ms(5);
				if (spin_cnt != 1)
				{
					Display_LCD();
					spin_cnt = 0;
					break;
				}
			}
			for (int j = 0; j < 90 ; j++)
			{
				//Spin_status_LED();
				BUTTON_spin_getState(&btn_spin);
				Fan_continue_run();
				Display_LCD();
				Spin_start(180-2*j);
				//_delay_ms(5);
				if (spin_cnt != 1)
				{
					Display_LCD();
					spin_cnt = 0;
					break;
				}
			}
		}
		break;
	
		default:
		BUTTON_spin_getState(&btn_spin);
		Spin_status_LED();
		Fan_continue_run();
		Display_LCD();
		Spin_stop();
		spin_cnt = 0;
		break;
	}
}

void Spin_status_LED()
{
	if (spin_cnt == 1)
	{
		LED_PORT |= (1<<PINA3);
	}
	// else LED_PORT &= ~(1<<PINA3);
}

void Spin_stop()
{
	LED_PORT &= ~(1<<PINA3);
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