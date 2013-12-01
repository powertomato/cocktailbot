#include <platform.h>
#include <dig_in.h>
#include <dig_out.h>
#include <adc.h>

extern void servo_init();

int main(void) {
	dig_out_init();
	dig_in_init();
	adc_init();

	dig_in_t b0 = {DIG_IN0,PULL_DOWN,false}; 
	dig_in_t not_b0 = {DIG_IN0,PULL_UP,true};
	dig_in_setup(&b0);

	int i;
	for(i=LED0; i<=LED7; i++ ) {
		dig_out_setup(i,PULL_NO);
	}

	servo_init();
	adc_setup(WHEEL1);
	adc_setup(WHEEL2);
	adc_setup(WHEEL3);

	while (1) { 
		/*
		int volt = adc_read_mV(WHEEL1);
		if( volt>1500 ){
			dig_out_set( &l1 );
		}else{
			dig_out_clr( &l1 );
		}
		*/

		{
			static bool p_b0 = false;
			bool s_b0 = dig_in_read( &b0 );
			if( s_b0 != p_b0 ) {
				p_b0 = s_b0;
				if(!p_b0){
					servo_set(0,0);
				}else{
					servo_set(0,-127);
				}
			}
		}
		if( dig_in_read( &b0 ) ){
			dig_out_set( LED6 );
		}else{
			dig_out_clr( LED6 );
		}
			
	}
}
 
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	while (1) { }
}
#endif


