
#include <dig_out.h>

#define DIG_OUT_CONFIG (GPIO_InitTypeDef){ \
	.GPIO_Pin = 0, \
	.GPIO_Mode = GPIO_Mode_OUT, \
	.GPIO_OType = GPIO_OType_PP, \
	.GPIO_Speed = GPIO_Speed_50MHz, \
	.GPIO_PuPd = GPIO_PuPd_DOWN }


void dig_out_init(){
	RCC_AHBPeriphClockCmd(DIG_OUT_CLK,ENABLE);
}

void dig_out_setup(dig_out_t *t){
	GPIO_InitTypeDef gpio_init = DIG_OUT_CONFIG;
	gpio_init.GPIO_Pin = t->dig_out_pin;
	switch ( t->pull_res ) {
		case PULL_UP:
			gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
			break;
		case PULL_DOWN:
			gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;
			break;
		case PULL_NO:
			//default
			break;
		default:
			assert_param(0);
	}
	GPIO_Init(DIG_OUT_PORT, &gpio_init);
}

void dig_out_set(dig_out_t *t) {
	GPIO_SetBits(DIG_OUT_PORT, t->dig_out_pin);
}

void dig_out_clr(dig_out_t *t) {
	GPIO_ResetBits(DIG_OUT_PORT, t->dig_out_pin);
}

void dig_out_toggle(dig_out_t* t){
	if( GPIO_ReadOutputDataBit(DIG_OUT_PORT, t->dig_out_pin) ){
		dig_out_set(t);
	}else{
		dig_out_clr(t);
	}
}
