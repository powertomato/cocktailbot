
#ifndef ADC_H__
#define ADC_H__

void adc_init();
void adc_setup(int channel);
int adc_read(int channel);
int adc_read_mV(int channel);

#endif //ADC_H__
