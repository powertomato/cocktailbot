#include <platform.h>
#include <dig_in.h>
#include <dig_out.h>
#include <adc.h>

int main(void) {
	dig_out_init();
	dig_in_init();
	adc_init();

	dig_in_t b0 = {DIG_IN0,PULL_DOWN,false}; 
	dig_in_t not_b0 = {DIG_IN0,PULL_UP,true};
	dig_in_setup(&b0);

	dig_out_t l0 = {LED0,PULL_NO};
	dig_out_t l1 = {LED1,PULL_NO};
	dig_out_setup(&l0);
	dig_out_setup(&l1);

	adc_setup(WHEEL1);
	adc_setup(WHEEL2);
	adc_setup(WHEEL3);

	while (1) { 
		int volt = adc_read_mV(WHEEL1);
		if( volt>1500 ){
			dig_out_set( &l1 );
		}else{
			dig_out_clr( &l1 );
		}
		if( dig_in_read( &b0 ) ){
			dig_out_set( &l0 );
		}else{
			dig_out_clr( &l0 );
		}

			
	}
}
 
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	while (1) { }
}
#endif


