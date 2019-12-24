
#include "stm32f407xx.h"

//we have to implement the watchdog interrupt handler 

void WWDG_IRQHandler(void)
{
	for(int i=0 ; i < 50 ; i++);
	
		/* Lets try to move the processor to privileged access level */
	uint32_t value = __get_CONTROL();   // we are in interrupt handling function, means in Handler mode, now we can 
	value &= ~0x01;                     //change CONTROL REGISTER and clear its first bit to go into piviledge mode  
	__set_CONTROL(value);
	
}

void generate_interrupt(void)
{
	//Lets simulate the watchdog interrupt
  NVIC_EnableIRQ(WWDG_IRQn);
	NVIC_SetPendingIRQ(WWDG_IRQn);
}

void call_application_Task(void)
{
	/* This is user appilcation task */
	
	/* Lets try to move the processor to privileged access level */
	uint32_t value = __get_CONTROL();
	value &= ~0x01; 
	__set_CONTROL(value); // Not going into priviledge Access level cause "code is in Thread mode and in unpreviledge mode"
                              // so it cant excess(write) the CONTROL register that we are changing to go into priviledge Access level
	
	generate_interrupt(); // we are only able to go into PAL from NPAL, by going into HAndler mode(executing any interrupt or exception)
                              //and in this interrupts handler function we can smartly place our CONTROL REGISTER clearing code. 
}

void RTOS_init(void)
{
	/*does RTOS related low level inits */
	
	/*before calling application task , change the access level to un-privileged
	access level */
	uint32_t value = __get_CONTROL();
	value |= 0x01;
	__set_CONTROL(value);
	
	call_application_Task();
}

int main(void)
{
	NVIC_EnableIRQ(WWDG_IRQn);
	RTOS_init();
	while(1);
	return 0;
}
