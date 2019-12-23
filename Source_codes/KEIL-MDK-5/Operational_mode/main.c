// checking Operational modes on STM32, wheenever interrupt is occure controller switches from THREAD mode to HANDLER mode.
// by default controller is on THRRREAd mode. 
// check follwing code on debug mode setting break points



#include "stm32f407xx.h"

//we have to implement the watchdog interrupt handler 

void WWDG_IRQHandler(void)
{
	for(int i=0 ; i < 50 ; i++);
	
}

void generate_interrupt(void)
{
	//Lets simulate the watchdog interrupt
	NVIC_EnableIRQ(WWDG_IRQn);
	NVIC_SetPendingIRQ(WWDG_IRQn);
}

int main(void)
{
  	generate_interrupt();
  	while(1);
 	return 0;
}
