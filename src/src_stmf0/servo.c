
#include <platform.h>


#define PERIOD (20000)
#define PULSE_1_0_MS (1000) //Full right
#define PULSE_1_5_MS (1500) //Center
#define PULSE_2_0_MS (2000) //Full left

#define PWM_PORT GPIOA
/*#define TIMER TIM1

#define CH1_PIN GPIO_Pin_9
#define CH2_PIN GPIO_Pin_10
#define CH3_PIN GPIO_Pin_11

#define CH1_PIN_SRC GPIO_PinSource9
#define CH2_PIN_SRC GPIO_PinSource10
#define CH3_PIN_SRC GPIO_PinSource11
*/
#define TIMER TIM2

#define CH1_PIN GPIO_Pin_1
#define CH2_PIN GPIO_Pin_2
#define CH3_PIN GPIO_Pin_3

#define CH1_PIN_SRC GPIO_PinSource1
#define CH2_PIN_SRC GPIO_PinSource2
#define CH3_PIN_SRC GPIO_PinSource3


#define TIM_OC_CONFIG (TIM_OCInitTypeDef){ \
	.TIM_OCMode = TIM_OCMode_PWM1, \
	.TIM_OutputState = TIM_OutputState_Enable, \
	.TIM_OutputNState = TIM_OutputNState_Enable, \
	.TIM_OCPolarity = TIM_OCPolarity_High, \
	.TIM_OCNPolarity = TIM_OCNPolarity_Low, \
	.TIM_OCIdleState = TIM_OCIdleState_Set, \
	.TIM_OCNIdleState = TIM_OCIdleState_Reset, \
}

void servo_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);

	// Configure GPIOs as AF
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_InitStructure.GPIO_Pin = CH1_PIN;
	GPIO_Init(PWM_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CH2_PIN;
	GPIO_Init(PWM_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CH3_PIN;
	GPIO_Init(PWM_PORT, &GPIO_InitStructure);

	// Set AF to OCx
	GPIO_PinAFConfig(PWM_PORT, CH1_PIN_SRC, GPIO_AF_2);
	GPIO_PinAFConfig(PWM_PORT, CH2_PIN_SRC, GPIO_AF_2);
	GPIO_PinAFConfig(PWM_PORT, CH3_PIN_SRC, GPIO_AF_2);

	TIM_TimeBaseInitTypeDef tim_init;

	/* 48MHz/(48*20000) = 50 Hz */
	tim_init.TIM_Prescaler = 48-1;
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_init.TIM_Period = PERIOD;
	tim_init.TIM_ClockDivision = 0;
	tim_init.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit( TIMER, &tim_init );

	TIM_OCInitTypeDef oc_init = TIM_OC_CONFIG;
	oc_init.TIM_Pulse = PULSE_1_5_MS;

	TIM_OC2Init(TIMER, &oc_init);
	TIM_OC3Init(TIMER, &oc_init);
	TIM_OC4Init(TIMER, &oc_init);

	TIM_Cmd(TIMER, ENABLE);
	//TIM_CtrlPWMOutputs(TIMER, ENABLE);
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
			TIM_OC2Init(TIMER, &oc_init);
			break;
		case 1:
			TIM_OC3Init(TIMER, &oc_init);
			break;
		case 2:
			TIM_OC4Init(TIMER, &oc_init);
			break;
		default:
			assert_param(0);
	}
}
