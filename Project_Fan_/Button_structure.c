/*
 * Button_structure.c
 *
 * Created: 2023-07-11 오후 3:36:35
 *  Author: USER
 */ 
#include "Button_structure.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

// 버튼 초기화 함수 정의
void Button_init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum)
{
	button->ddr = ddr; // 버튼의 입출력 방향 레지스터 설정
	button->pin = pin; // 버튼의 상태를 읽을 포트 레지스터 설정
	button->btnPin = pinNum; // 버튼 핀 번호 설정
	button->prevState = RELEASED; // 초기화, 아무것도 안 누른 상태
	*button->ddr &= ~(1 << button->btnPin); // 버튼 핀을 입력으로 설정, ->가 *보다 빠름
}

// 버튼 상태 반환 함수 정의
uint8_t BUTTON_getState(Button *button)
{
	uint8_t curState = *button->pin & (1<<button->btnPin); // 버튼 상태를 읽어옴
	
	if ((curState == PUSHED) && (button->prevState == RELEASED)) // 버튼을 안 누른 상태에서 누르면,
	{
		_delay_ms(50); // 디바운스 코드
		button->prevState = PUSHED; // 버튼을 누른 상태로 변환
		return ACT_PUSH; // 버튼이 눌려 있음을 반환
	}
	else if((curState != PUSHED) && (button->prevState == PUSHED)) // 버튼을 누른 상태에서 떼면,
	{
		_delay_ms(50); // 디바운스 코드
		button->prevState = RELEASED; // 버튼을 땐 상태로 변환
		return ACT_RELEASED; // 버튼이 떨어진 것을 반환
	}
	return NO_ACT; // 아무 것도 안 했을 때
}

uint8_t BUTTON_spin_getState(Button *button)
{
	uint8_t curState = *button->pin & (1<<button->btnPin); // 버튼 상태를 읽어옴
	
	if ((curState == PUSHED) && (button->prevState == RELEASED)) // 버튼을 안 누른 상태에서 누르면,
	{
		_delay_ms(50); // 디바운스 코드
		button->prevState = PUSHED; // 버튼을 누른 상태로 변환
		return ACT_PUSH; // 버튼이 눌려 있음을 반환
	}
	else if((curState != PUSHED) && (button->prevState == PUSHED)) // 버튼을 누른 상태에서 떼면,
	{
		_delay_ms(50); // 디바운스 코드
		button->prevState = RELEASED; // 버튼을 땐 상태로 변환
		spin_cnt++;
		return ACT_RELEASED, spin_cnt; // 버튼이 떨어진 것을 반환
	}
	return NO_ACT; // 아무 것도 안 했을 때
}