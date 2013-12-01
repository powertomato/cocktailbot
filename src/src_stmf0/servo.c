
#include <platform.h>


#define PERIOD 20000
#define PULSE_1_0_MS (1000-1) //Full right
#define PULSE_1_5_MS (1500-1) //Center
#define PULSE_2_0_MS (2000-1) //Full left

#define TIM_OC_CONFIG (TIM_OCInitTypeDef){ \
	.TIM_OCMode = TIM_OCMode_PWM2, \
	.TIM_OutputState = TIM_OutputState_Enable, \
	.TIM_OutputNState = TIM_OutputNState_Enable, \
	.TIM_OCPolarity = TIM_OCPolarity_Low, \
	.TIM_OCNPolarity = TIM_OCNPolarity_High, \
	.TIM_OCIdleState = TIM_OCIdleState_Set, \
	.TIM_OCNIdleState = TIM_OCIdleState_Reset, \
}

void servo_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* GPIOA, GPIOB and GPIOE Clocks enable */
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);

	/* GPIOA Configuration: Channel 1, 2, 3, 4 and Channel 1N as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		/*| GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_7*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_2);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11n, GPIO_AF_2);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_2);

	TIM_TimeBaseInitTypeDef tim_init;

	/* 48MHz/(48*20000) = 50 Hz */
	tim_init.TIM_Prescaler = 48;
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_init.TIM_Period = PERIOD;
	tim_init.TIM_ClockDivision = 0;
	tim_init.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit( TIM1, &tim_init );

	TIM_OCInitTypeDef oc_init = TIM_OC_CONFIG;
	oc_init.TIM_Pulse = PULSE_1_5_MS;

	TIM_OC3Init(TIM1, &oc_init);
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/**
 * @param pos Servo position.
 *         0   = Middle
 *        -127 = Max left
 *        +127 = max right
 */
void servo_set(int num, int8_t pos) {
	int wpulse;
	uint16_t pulse;

	TIM_OCInitTypeDef oc_init;

	oc_init = TIM_OC_CONFIG;

	wpulse = ((int)pos)*500/127 +PULSE_1_5_MS;
	pulse = MIN(PULSE_2_0_MS,wpulse);
	pulse = MAX(PULSE_1_0_MS,wpulse);
	oc_init.TIM_Pulse = pulse;

	switch( num ) {
		case 0:
			TIM_OC3Init(TIM1, &oc_init);
			break;
		case 1:
			//TIM_OCxInit(TIM1, &oc_init);
			break;
		case 2:
			//TIM_OCxInit(TIM1, &oc_init);
			break;
		default:
			assert_param(0);
	}
}
