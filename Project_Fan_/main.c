/*
 * Project_Fan_.c
 *
 * Created: 2023-08-28 오전 10:31:20
 * Author : USER
 */ 

#include "Fan.h"

//ISR(INT4_vect)
//{
	//LED_PORT = 0x00;
	//PORTF |= (1<<PINF4) | (1<<PINF5); // MOtor Break
	//DDRB &= ~(1<<PINB4);
	//LCD_WriteStringXY(0,0,"   Stop mode    ");
	//LCD_WriteStringXY(1,0,"  Power :   0%  ");
	//_delay_ms(3000);
	//Fan_Start_signal();
	//Display_LCD();
	//Fan_run_status = Fan_stop;
	//Fan_continue_run();
//}

int main(void)
{
	Fan_Init();
	Fan_Start_signal();
			
	while (1)
	{
		Fan_Stage();
		Display_LCD();
		Head_spin_op();
	}
}

