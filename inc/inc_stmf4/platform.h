#include <stm32f4xx.h>
#include <stm32f4xx_conf.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

/* led configuration */
#define LED_CLOCK_SETUP() RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE)
#define LEDPORT GPIOD
#define LED0_PIN GPIO_Pin_12
#define LED1_PIN GPIO_Pin_15

#define LED_CONFIG (GPIO_InitTypeDef){ \
	.GPIO_Pin = LED0_PIN | LED1_PIN, \
	.GPIO_Mode = GPIO_Mode_OUT, \
	.GPIO_OType = GPIO_OType_PP, \
	.GPIO_Speed = GPIO_Speed_50MHz, \
	.GPIO_PuPd = GPIO_PuPd_NOPULL }

#define BTN_CLOCK_SETUP() RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE)
#define BTNPORT GPIOA
#define BTNPIN  GPIO_Pin_0

#define BTN_CONFIG (GPIO_InitTypeDef){ \
	.GPIO_Pin = BTNPIN, \
	.GPIO_Mode = GPIO_Mode_IN, \
	.GPIO_OType = GPIO_OType_PP, \
	.GPIO_Speed = GPIO_Speed_50MHz, \
	.GPIO_PuPd = GPIO_PuPd_DOWN }

