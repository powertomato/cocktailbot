
#include <adc.h>
#include <platform.h>
#include <stm32f0xx_adc.h>
#include <stm32f0xx_gpio.h>

#define ADC_CONFIG (ADC_InitTypeDef){ \
	.ADC_Resolution = ADC_Resolution_12b, \
	.ADC_ContinuousConvMode = ENABLE, \
	.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None, \
	.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO, \
	.ADC_DataAlign = ADC_DataAlign_Right, \
	.ADC_ScanDirection = ADC_ScanDirection_Upward }

#define ADC_CH_CONFIG (GPIO_InitTypeDef){ \
	.GPIO_Pin = 0, \
	.GPIO_Mode = GPIO_Mode_AN, \
	.GPIO_Speed = GPIO_Speed_50MHz,\
	.GPIO_PuPd = GPIO_PuPd_DOWN }
#define ADC_SAMPLE_TIME ADC_SampleTime_239_5Cycles

static bool ch_enable[MAX_CHANNELS];

void adc_init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);

	DMA_InitTypeDef dma_init;
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = MAX_CHANNELS;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
	ADC_DMACmd(ADC1, ENABLE);  

	/* DMA1 Channel1 enable */
	DMA_Cmd(DMA1_Channel1, ENABLE);

	ADC_InitTypeDef adc_init_cfg;
	adc_init_cfg = ADC_CONFIG;
	ADC_Init(ADC1, &adc_init_cfg);
}

void adc_start(){
	ADC_GetCalibrationFactor(ADC1);
	ADC_Cmd(ADC1, ENABLE);

	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
	ADC_StartOfConversion(ADC1);
}

void adc_setup(int channel){
	GPIO_InitTypeDef gpio_init = ADC_CH_CONFIG;
	gpio_init.GPIO_Pin = channel_table[channel].pin;
	GPIO_Init(channel_table[channel].port, &gpio_init);

	switch( channel ) {
		case 0: ADC_ChannelConfig(ADC1, ADC_Channel_0 , ADC_SAMPLE_TIME); break;
		case 1: ADC_ChannelConfig(ADC1, ADC_Channel_1 , ADC_SAMPLE_TIME); break;
		case 2: ADC_ChannelConfig(ADC1, ADC_Channel_2 , ADC_SAMPLE_TIME); break;
		case 3: ADC_ChannelConfig(ADC1, ADC_Channel_3 , ADC_SAMPLE_TIME); break;
		case 4: ADC_ChannelConfig(ADC1, ADC_Channel_4 , ADC_SAMPLE_TIME); break;
		case 5: ADC_ChannelConfig(ADC1, ADC_Channel_5 , ADC_SAMPLE_TIME); break;
		case 6: ADC_ChannelConfig(ADC1, ADC_Channel_6 , ADC_SAMPLE_TIME); break;
		case 7: ADC_ChannelConfig(ADC1, ADC_Channel_7 , ADC_SAMPLE_TIME); break;
		case 8: ADC_ChannelConfig(ADC1, ADC_Channel_8 , ADC_SAMPLE_TIME); break;
		case 9: ADC_ChannelConfig(ADC1, ADC_Channel_9 , ADC_SAMPLE_TIME); break;
		case 10: ADC_ChannelConfig(ADC1, ADC_Channel_10 , ADC_SAMPLE_TIME); break;
		case 11: ADC_ChannelConfig(ADC1, ADC_Channel_11 , ADC_SAMPLE_TIME); break;
		case 12: ADC_ChannelConfig(ADC1, ADC_Channel_12 , ADC_SAMPLE_TIME); break;
		case 13: ADC_ChannelConfig(ADC1, ADC_Channel_13 , ADC_SAMPLE_TIME); break;
		case 14: ADC_ChannelConfig(ADC1, ADC_Channel_14 , ADC_SAMPLE_TIME); break;
		case 15: ADC_ChannelConfig(ADC1, ADC_Channel_15 , ADC_SAMPLE_TIME); break;
	}
	ch_enable[channel] = true;
	adc_start();
}


int adc_read(int channel){
	static int last_channel = 0;
	if( !(ch_enable[channel]) ) {
		return -1;
	}
	int i;
	for( i = 0; i<MAX_CHANNELS; i++) {
		last_channel = (last_channel+1) % MAX_CHANNELS;
		if( ch_enable[last_channel] ){
			while( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET );
			volatile int val = ADC_GetConversionValue(ADC1);
			if( last_channel == channel ){
				return val;
			}
		}
	}
}

int adc_read_mV(int channel) {
	int val = adc_read(channel);
	if( val > 0 ){
		return (val * 3300)/0xFFF; /* val*3300 mV / 2^12-1 */
	}
	return val;
}
