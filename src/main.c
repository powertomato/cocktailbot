
#include <stm32f0xx.h>
#include <stm32f0xx_conf.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_gpio.h>


int main(void) {
	/*!< At this stage the microcontroller clock setting is already configured, 
	  this is done through SystemInit() function which is called from startup
	  file (startup_stm32f0xx.s) before to branch to application main.
	  To reconfigure the default setting of SystemInit() function, refer to
	  system_stm32f0xx.c file */

	/* GPIOC Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	/* Configure PC10 and PC11 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	while (1) {
		unsigned int i;
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
		/*for(i=0xFFFFFFFF; i>0; i--);
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);*/
	}
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	while (1) { }
}
#endif


__asm__(""
		".globl _exit\n"
		"_exit:\n"
		"b     .\n");
