
#ifndef PIN_ASSIGNMENT_H__
#define PIN_ASSIGNMENT_H__


typedef struct {
	GPIO_TypeDef* port;
	int pin;
} pin_table_entry_t;
#define PIN_ASG(PORT,PIN) {PORT,PIN}

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7
#define LED8 8

static pin_table_entry_t dig_out_table[] = {
	PIN_ASG(GPIOA,GPIO_Pin_8),
	PIN_ASG(GPIOC,GPIO_Pin_9),
	PIN_ASG(GPIOC,GPIO_Pin_8),
	PIN_ASG(GPIOC,GPIO_Pin_7),
	PIN_ASG(GPIOC,GPIO_Pin_6),
	PIN_ASG(GPIOB,GPIO_Pin_15),
	PIN_ASG(GPIOB,GPIO_Pin_14),
	PIN_ASG(GPIOB,GPIO_Pin_13),
};

#define DIG_IN_CLK RCC_AHBPeriph_GPIOA
#define DIG_INPORT GPIOA
enum dig_in_pins {
	DIG_IN0 = GPIO_Pin_0,
};


#define MAX_CHANNELS 16
static pin_table_entry_t channel_table[] = {
	PIN_ASG(GPIOA,GPIO_Pin_0),    // 0
	PIN_ASG(GPIOA,GPIO_Pin_1),    // 1
	PIN_ASG(GPIOA,GPIO_Pin_2),    // 2
	PIN_ASG(GPIOA,GPIO_Pin_3),    // 3
	PIN_ASG(GPIOA,GPIO_Pin_4),    // 4
	PIN_ASG(GPIOA,GPIO_Pin_5),    // 5
	PIN_ASG(GPIOA,GPIO_Pin_6),    // 6
	PIN_ASG(GPIOA,GPIO_Pin_7),    // 7
	PIN_ASG(GPIOB,GPIO_Pin_0),    // 8
	PIN_ASG(GPIOB,GPIO_Pin_1),    // 9
	PIN_ASG(GPIOC,GPIO_Pin_0),    // 10
	PIN_ASG(GPIOC,GPIO_Pin_1),    // 11
	PIN_ASG(GPIOC,GPIO_Pin_2),    // 12
	PIN_ASG(GPIOC,GPIO_Pin_3),    // 13
	PIN_ASG(GPIOC,GPIO_Pin_4),    // 14 
	PIN_ASG(GPIOC,GPIO_Pin_5),    // 15 
};

#define WHEEL1 10
#define WHEEL2 11
#define WHEEL3 15


#endif

