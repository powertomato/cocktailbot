#include <platform.h>

void delay(int);

int main(void) {

	/* GPIOC Periph clock enable */
	BTN_CLOCK_SETUP();
	LED_CLOCK_SETUP();

	{
		GPIO_InitTypeDef gpio_init;
		gpio_init = LED_CONFIG;
		GPIO_Init(LEDPORT, &gpio_init);

		gpio_init = BTN_CONFIG;
		GPIO_Init(BTNPORT, &gpio_init);
	}
	

	while (1) {
		unsigned int i;
		GPIO_SetBits(LEDPORT, LED0_PIN);
		GPIO_ResetBits(LEDPORT, LED1_PIN);
		delay(900000);
		GPIO_SetBits(LEDPORT, LED1_PIN);
		GPIO_ResetBits(LEDPORT, LED0_PIN);
		delay(900000);
	}
}

void delay(int a) {
    volatile int i;
    for (i=0 ; i < a ; i++) { }
}
 
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	while (1) { }
}
#endif


