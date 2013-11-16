
#ifndef PIN_ASSIGNMENT_H__
#define PIN_ASSIGNMENT_H__

#define DIG_OUT_CLK RCC_AHBPeriph_GPIOC
#define DIG_OUT_PORT GPIOC
#define LED0 OUT0
#define LED1 OUT1

enum dig_out_pins{
	OUT0 = GPIO_Pin_8,
	OUT1 = GPIO_Pin_9,
};


#define DIG_IN_CLK RCC_AHBPeriph_GPIOA
#define DIG_INPORT GPIOA
enum dig_in_pins {
	DIG_IN0 = GPIO_Pin_0,
};


typedef struct {
	GPIO_TypeDef* port;
	int pin;
} ch_table_entry_t;
#define _CH_TAB(PORT,PIN) {PORT,PIN}
#define MAX_CHANNELS 16
static ch_table_entry_t channel_table[] = {
	_CH_TAB(GPIOA,GPIO_Pin_0),    // 0
	_CH_TAB(GPIOA,GPIO_Pin_1),    // 1
	_CH_TAB(GPIOA,GPIO_Pin_2),    // 2
	_CH_TAB(GPIOA,GPIO_Pin_3),    // 3
	_CH_TAB(GPIOA,GPIO_Pin_4),    // 4
	_CH_TAB(GPIOA,GPIO_Pin_5),    // 5
	_CH_TAB(GPIOA,GPIO_Pin_6),    // 6
	_CH_TAB(GPIOA,GPIO_Pin_7),    // 7
	_CH_TAB(GPIOB,GPIO_Pin_0),    // 8
	_CH_TAB(GPIOB,GPIO_Pin_1),    // 9
	_CH_TAB(GPIOC,GPIO_Pin_0),    // 10
	_CH_TAB(GPIOC,GPIO_Pin_1),    // 11
	_CH_TAB(GPIOC,GPIO_Pin_2),    // 12
	_CH_TAB(GPIOC,GPIO_Pin_3),    // 13
	_CH_TAB(GPIOC,GPIO_Pin_4),    // 14 
	_CH_TAB(GPIOC,GPIO_Pin_5),    // 15 
};
#define WHEEL1 10
#define WHEEL2 11
#define WHEEL3 15


#endif

