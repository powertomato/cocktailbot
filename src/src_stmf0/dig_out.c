
#include <dig_out.h>

#define DIG_OUT_CONFIG (GPIO_InitTypeDef){ \
	.GPIO_Pin = 0, \
	.GPIO_Mode = GPIO_Mode_OUT, \
	.GPIO_OType = GPIO_OType_PP, \
	.GPIO_Speed = GPIO_Speed_50MHz, \
	.GPIO_PuPd = GPIO_PuPd_DOWN }


void dig_out_init(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC,ENABLE);
}

void dig_out_setup(int pin, enum pull_res_t pull_res){
	GPIO_InitTypeDef gpio_init = DIG_OUT_CONFIG;
	gpio_init.GPIO_Pin =  dig_out_table[pin].pin;
	switch ( pull_res ) {
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
	GPIO_Init( dig_out_table[pin].port, &gpio_init);
}

void dig_out_set(int pin) {
	GPIO_SetBits( dig_out_table[pin].port, dig_out_table[pin].pin);
}

void dig_out_clr(int pin) {
	GPIO_ResetBits( dig_out_table[pin].port, dig_out_table[pin].pin);
}

void dig_out_toggle(int pin){
	if( GPIO_ReadOutputDataBit( dig_out_table[pin].port, dig_out_table[pin].pin) ){
		dig_out_set(pin);
	}else{
		dig_out_clr(pin);
	}
}
