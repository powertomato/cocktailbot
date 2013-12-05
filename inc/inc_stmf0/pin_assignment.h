
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

#define MOT1 8
#define MOT2 9
#define MOT3 10

#define PUMP1 11
#define PUMP2 12
#define PUMP3 13
#define PUMP4 14
#define PUMP5 15
#define PUMP6 16
#define PUMP7 17
#define PUMP8 18
#define PUMP9 19
#define PUMP10 20
#define PUMP11 21
#define PUMP12 22

#define DIG_OUT_MAX 22

static pin_table_entry_t dig_out_table[] = {
	PIN_ASG(GPIOA,GPIO_Pin_8),
	PIN_ASG(GPIOC,GPIO_Pin_9),
	PIN_ASG(GPIOC,GPIO_Pin_8),
	PIN_ASG(GPIOC,GPIO_Pin_7),
	PIN_ASG(GPIOC,GPIO_Pin_6),
	PIN_ASG(GPIOB,GPIO_Pin_15),
	PIN_ASG(GPIOB,GPIO_Pin_14),
	PIN_ASG(GPIOB,GPIO_Pin_13),

	PIN_ASG(GPIOB,GPIO_Pin_12),
	PIN_ASG(GPIOF,GPIO_Pin_0),
	PIN_ASG(GPIOF,GPIO_Pin_1),

	PIN_ASG(GPIOC,GPIO_Pin_12),
	PIN_ASG(GPIOC,GPIO_Pin_11),
	PIN_ASG(GPIOC,GPIO_Pin_10),
	PIN_ASG(GPIOA,GPIO_Pin_15),
	PIN_ASG(GPIOF,GPIO_Pin_6),
	PIN_ASG(GPIOF,GPIO_Pin_7),

	PIN_ASG(GPIOB,GPIO_Pin_7),
	PIN_ASG(GPIOB,GPIO_Pin_6),
	PIN_ASG(GPIOB,GPIO_Pin_5),
	PIN_ASG(GPIOB,GPIO_Pin_4),
	PIN_ASG(GPIOB,GPIO_Pin_8),
	PIN_ASG(GPIOD,GPIO_Pin_2),
};

#define DIG_IN_CLK RCC_AHBPeriph_GPIOA
#define DIG_INPORT GPIOA
enum dig_in_pins {
	DIG_IN0 = GPIO_Pin_0,
};


#define MAX_CHANNELS 3
static pin_table_entry_t channel_table[] = {
	PIN_ASG(GPIOA,GPIO_Pin_0),    // 0
	PIN_ASG(GPIOA,GPIO_Pin_1),    // 1
	PIN_ASG(GPIOA,GPIO_Pin_2),    // 2
};

#define WHEEL1 0
#define WHEEL2 1
#define WHEEL3 2


#endif

