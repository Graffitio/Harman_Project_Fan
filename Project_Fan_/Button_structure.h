/*
 * IncFile1.h
 *
 * Created: 2023-07-11 오후 3:36:39
 *  Author: USER
 */ 


/*
 * IncFile1.h
 *
 * Created: 2023-07-11 오후 3:36:39
 *  Author: USER
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#include <stdint.h>

// LED LAMP 입출력 방향 설정 레지스터와 포트 지정
#define LED_DDR			DDRA // LED LAMP 입출력 방향 설정 레지스터
#define LED_PORT		PORTA // LED LAMP PORT 지정

// BUTTON 입출력 방향 설정 레지스터와 핀 설정
#define BUTTON_DDR		DDRC // BUTTON 입출력 방향 설정 레지스터
#define BUTTON_PIN		PINC // BUTTON을 연결할 PORT의 PIN

// 버튼 동작에 대한 정의
#define BUTTON_STOP		0	// Stop
#define BUTTON_1stage	1	// 1단 25%
#define BUTTON_2stage	2	// 2단 50%
#define BUTTON_3stage	3	// 3단 100%
#define BUTTON_spin		4	// spin

// 버튼 상태 및 액션 상태 정의
enum{PUSHED, RELEASED};
enum{NO_ACT, ACT_PUSH, ACT_RELEASED};
// enum : 일종의 data type으로,
// 일련의 이름을 갖는 상수들의 집합(순서대로 0, 1, 2 ....의 값을 가진다.)

// 버튼 구조체 정의
typedef struct _button{
	volatile uint8_t *ddr; // volatile : 최적화 하지 마라
	volatile uint8_t *pin;
	uint8_t btnPin; // 버튼 핀 번호
	uint8_t prevState; // 이전 버튼 상태
}Button;
int spin_cnt;


void Button_init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum);
uint8_t BUTTON_getState(Button *button);
uint8_t BUTTON_spin_getState(Button *button);

#endif /* INCFILE1_H_ */