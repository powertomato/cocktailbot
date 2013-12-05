#include <platform.h>
#include <dig_in.h>
#include <dig_out.h>
#include <adc.h>
#include <rtc.h>
#include <servo.h>

extern void servo_init();

void show_number(uint8_t n) {
	int i;
 	for(i=0; i<8; i++){
 		if(n & (1<<i)) {
			dig_out_set( LED0+i );
		}else{
			dig_out_clr( LED0+i );
		}
	}
}

int main(void) {
	
	dig_out_init();
	dig_in_init();
	adc_init();

	dig_in_t b0 = {DIG_IN0,PULL_DOWN,false}; 
	dig_in_t not_b0 = {DIG_IN0,PULL_UP,true};
	dig_in_setup(&b0);

	int i;
	for(i=0; i<=LED7; i++ ) {
		dig_out_setup(i,PULL_NO);
	}
	for(i=LED7+1; i<=22; i++ ) {
		dig_out_setup(i,PULL_DOWN);
	}

	servo_init();
	rtc_init();
	adc_setup(WHEEL1);
	adc_setup(WHEEL2);
	adc_setup(WHEEL3);

	while (1) { 
		
		{
			static int w0_pos = 0;
			static bool p_w0 = false;
			int volt = adc_read_mV(WHEEL1);
			bool w0;
			if( p_w0 ) {
				w0 = volt>1300;
			}else{
				w0 = volt>1900;
			}

			if( p_w0 != w0 ) {
				p_w0 = w0;
				if( w0 ){
					dig_out_set( LED0 );
				}else{
					dig_out_clr( LED0 );
					w0_pos = (w0_pos+1) % 6;
				}
			}
			show_number( 1<<w0_pos );
		}
		

		/* while(1){
			static int num=5;
			static bool p_b0 = false;
			bool s_b0 = dig_in_read( &b0 );

//			if( s_b0 != p_b0 ) {
//				p_b0 = s_b0;
//				if(!p_b0){
					show_number( num );
					dig_out_clr( PUMP1+num );
					num = (num + 1) % 6;
					dig_out_set( PUMP1+num );
//				}
//			}
//
			int64_t t=get_current_time();
			int64_t t2=t+1500;
			wait_until(t2);
		} */
		/*{
			static bool p_b0 = false;
			bool s_b0 = dig_in_read( &b0 );
			if( s_b0 != p_b0 ) {
				p_b0 = s_b0;
				if(!p_b0){
					int64_t t=get_current_time();
					int64_t t2=t+1000;
					wait_until(t2);
					dig_out_clr( LED1 );
					servo_set(0,127);
					servo_set(0,0);
				}else{
					int64_t t=get_current_time();
					int64_t t2=t+1000;
					wait_until(t2);
					dig_out_set( LED1 );
					servo_set(0,127);
				}
			}
		}*/
		/*if( dig_in_read( &b0 ) ){
			int64_t t=get_current_time();
			int64_t t2=t+1000;
			wait_until(t2);
			dig_out_set( LED1 );
		}else{
			dig_out_clr( LED1 );
		}*/
			
	}
}
 
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	while (1) { }
}
#endif


