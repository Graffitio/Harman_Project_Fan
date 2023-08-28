/*
 * Project_Fan_.c
 *
 * Created: 2023-08-28 오전 10:31:20
 * Author : USER
 */ 

#include "Fan.h"


int main(void)
{
	Fan_Init();
	Fan_Start_signal();
	
	// Head Spin
	TCCR1A |= (1<<WGM11) | (0<<WGM10); // Fast PWM(mode 14) 세팅
	TCCR1B |= (1<<WGM13) | (1<<WGM12);
	TCCR1A |= (1<<COM1A1) | (0<<COM1A0);
	TCCR1B |= (0<<CS12) | (1<<CS11) | (1<<CS10);
	TCCR1C = 0x00; // default가 0이라 안 써줘도 됨
		
	ICR1 = 4999;

		
	while (1)
	{
		Fan_Stage();
		//BUTTON_spin_getState(&btn_spin);
		//
		//switch (spin_cnt)
		//{
			//case 1:
			//DDRB = (1<<PINB5);
			//while((spin_cnt == 1))
			//{
				//for (int i = 0; i < 180 ; i++)
				//{
					//BUTTON_spin_getState(&btn_spin);
					//Fan_Stage();
					//Spin_start(i);
					//_delay_ms(10);
					//if (spin_cnt != 1)
					//{
						//spin_cnt = 0;
						//break;
					//}
				//}
				//for (int j = 0; j < 180 ; j++)
				//{
					//BUTTON_spin_getState(&btn_spin);
					//Fan_Stage();
					//Spin_start(180-j);
					//_delay_ms(10);
					//if (spin_cnt != 1)
					//{
						//spin_cnt = 0;
						//break;
					//}
				//}
			//}
			//break;
			//
			//default:
			//Fan_Stage();
			//Spin_stop();
			//spin_cnt = 0;
			//break;
		//}
	}
}

