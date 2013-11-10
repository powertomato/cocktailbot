#include <stm32f0xx.h>
#include <stm32f0xx_conf.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_gpio.h>

/* led configuration */
#define LED_CLOCK_SETUP() RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE)
#define LEDPORT GPIOC
#define LED0_PIN GPIO_Pin_8
#define LED1_PIN GPIO_Pin_9

#define LED_CONFIG (GPIO_InitTypeDef){ \
	.GPIO_Pin = LED0_PIN | LED1_PIN, \
	.GPIO_Mode = GPIO_Mode_OUT, \
	.GPIO_OType = GPIO_OType_PP, \
	.GPIO_Speed = GPIO_Speed_50MHz, \
	.GPIO_PuPd = GPIO_PuPd_NOPULL }

#define BTN_CLOCK_SETUP() RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE)
#define BTNPORT GPIOA
#define BTNPIN  GPIO_Pin_0

#define BTN_CONFIG (GPIO_InitTypeDef){ \
	.GPIO_Pin = BTNPIN, \
	.GPIO_Mode = GPIO_Mode_IN, \
	.GPIO_OType = GPIO_OType_PP, \
	.GPIO_Speed = GPIO_Speed_50MHz, \
	.GPIO_PuPd = GPIO_PuPd_DOWN }

