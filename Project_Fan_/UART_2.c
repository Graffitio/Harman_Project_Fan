/*
 * UART_2.c
 *
 * Created: 2023-07-26 오전 10:33:10
 *  Author: USER
 */ 

#include "UART_2.h"


void UART0_Init() // UART 통신을 쓰려면, 이거 세팅해줘야 한다.
// PE0, PE1을 쓸 것이다.
// 프로그램 다운로드하는 것과 맞물려 있다.
// UART 통신을 사용하려면, 스위치를 오른쪽으로 토글해줘야 한다. 꼭!
// 1. 프로그램 다운로드 해 -> 해당 창 close
// 2. 스위치 오른쪽으로 토글
// 3. compo 어쩌고 파일 열고
// 4. 프로그램 수정하려면, compo 어쩌고 파일 close하고 스위치 왼쪽으로 토글하고 1번
{
	UBRR0H = 0x00;
	UBRR0L = 0xcf; // 9600bps, 2배속모드를 쓸 것이다.
	
	UCSR0A = (1<<U2X0); // 2배속 모드 셋
	
	// 비동기 모드, 8bit 데이터, 패리티비트 없음, 1비트 stop bit
	//UCSR0C |= (0<<UMSEL0); // 비동기 모드
	//UCSR0C |= (0<<UPM01) | (0<<UPM00); // 패리티 비트 없음
	//UCSR0C |= (0<<USBS0); // 1비트 stop mode
	
	UCSR0B |= (1<<RXEN0); // 수신 가능(RX PIN 허용)
	UCSR0B |= (1<<TXEN0); // 송신 가능(TX PIN 허용)
	
	UCSR0B |= (1<<RXCIE0); // 수신 interrupt Enable
}


void UART0_Transmit(char data)
{
	while (!(UCSR0A & (1<<UDRE0))); // 송신 가능 대기, UDR(송신버퍼)이 비어있는지 체크
	// 비어있으면 UDRE0가 1로 세팅됨.
	// while 문 거짓되면, 빠져 나가서 다음 라인으로
	UDR0 = data; // 데이터 버퍼 레지스터에 데이터 전송
	
	
}


unsigned UART0_Receive(void) // 리턴해주는 값은 없고, 받기만 하므로
{
	while (!(UCSR0A & (1<<RXC0))); // 데이터 수신 대기 // 수신
	return UDR0; // URD0에 있는 데이터를 리턴만 해주면 된다.
}