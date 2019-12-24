
#include "stm32f4xx.h"
#include<stdint.h>
// implement handler function for triggered watchdog interrupt handler

void WWDG_IRQHandler(void)    // handler function for watchdog interrupt
{
	for(int i=0; i<50; i++) ;

}

void generate_interrupt(void)
{
	
NVIC_EnableIRQ(WWDG_IRQn);  //simulating watchdog interrupt 
NVIC_SetPendingIRQ(WWDG_IRQn);//trigring watchdog interrupt
	
}

void  call_application_task(void){

}
void RTOS_init(void)
{
	/* doing RTOS releted low level initialization*/
	/*assume this is as a kernel code doing each and every initializations*/
	/* before calling USER application code changing PAL to NPAL*/
	
	
	
	uint32_t value = __get_CONTROL();
	value |= 0x01;                          // changing 0th bit of value variable,
	__set_CONTROL(value);                   //writing whole value variable to CONTROL register to change access level to NPAL(unpriviledge)
	
	call_application_task();
	
}


int main(void)
{	
	RTOS_init(); 
	generate_interrupt();	
 	while(1);
  return 0 ; 	
}


