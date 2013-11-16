
#include <dig_in.h>

#define DIG_IN_CONFIG (GPIO_InitTypeDef){ \
	.GPIO_Pin = 0, \
	.GPIO_Mode = GPIO_Mode_IN, \
	.GPIO_OType = GPIO_OType_PP, \
	.GPIO_Speed = GPIO_Speed_50MHz, \
	.GPIO_PuPd = GPIO_PuPd_DOWN }



void dig_in_init(){
	RCC_AHBPeriphClockCmd(DIG_IN_CLK,ENABLE);
}

void dig_in_setup(dig_in_t *t){
	GPIO_InitTypeDef gpio_init = DIG_IN_CONFIG;
	gpio_init.GPIO_Pin = t->dig_in_pin;
	switch ( t->pull_res ) {
		case PULL_UP:
			gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
			break;
		case PULL_DOWN:
			//default
			break;
		case PULL_NO:
			gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
			break;
		default:
			assert_param(0);
	}
	GPIO_Init(DIG_INPORT, &gpio_init);
}

bool dig_in_read(dig_in_t *t) {
	bool ret = GPIOA->IDR;
	ret = ret & t->dig_in_pin;
	ret = t->low_active ? !ret : !!(ret);
	return ret;
}
