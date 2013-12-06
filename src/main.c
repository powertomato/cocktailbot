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

void delay_ms(int ms) {
	int64_t t;
	int64_t t2;

	t=get_current_time();
	t2=t+1500;
	wait_until(t2);
}

enum {
	WAIT=0,
	THREE_WHEELS,
	TWO_WHEELS,
	ONE_WHEEL,
	SCHENK_EI
} state;



static int w0_pos = 0;
static int w1_pos = 0;
static int w2_pos = 0;
static int64_t last_button_press=0;


#define WHEEL_DELAY 1000
void start_all_wheels() {
	servo_set(0,-96);
	servo_set(1,-110);
	servo_set(2,-127);
	delay_ms(WHEEL_DELAY);
	dig_out_set(MOT1);
	dig_out_set(MOT2);
	dig_out_set(MOT3);
}

void stop_wheel1(){
	dig_out_clr(MOT1);
	servo_set(0,127);
}
void stop_wheel2(){
	dig_out_clr(MOT2);
	servo_set(1,127);
}
void stop_wheel3(){
	dig_out_clr(MOT3);
	servo_set(2,127);
}

int main(void) {
	
	dig_out_init();
	dig_in_init();
	adc_init();

	dig_in_t lever = {DIG_IN1,PULL_DOWN,false}; 
	dig_in_setup(&lever);

	dig_in_t button = {DIG_IN0,PULL_DOWN,false}; 
	dig_in_setup(&button);

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
	adc_setup(WHEEL3);
	adc_setup(WHEEL2);

	servo_set(0,127);
	servo_set(1,127);
	servo_set(2,127);

	adc_start();
	int foo1=0;
	int foo2=0;
	int foo3=0;
	last_button_press = get_current_time();
	while (1) { 

		
		/////////////////
		// WHEEL STUFF //
		/////////////////
		{
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
				if( !w0 ){
					w0_pos = (w0_pos+1) % 6;
				}
			}
			show_number( 1<<w0_pos );
		}

		{
			static bool p_w1 = false;
			int volt = adc_read_mV(WHEEL2);
			bool w1;
			if( p_w1 ) {
				w1 = volt>1300;
			}else{
				w1 = volt>1900;
			}

			if( p_w1 != w1 ) {
				p_w1 = w1;
				if( !w1 ){
					w1_pos = (w1_pos+1) % 6;
				}
			}
			//show_number( 1<<w1_pos );
		}
		
		{
			static bool p_w2 = false;
			int volt = adc_read_mV(WHEEL3);
			bool w2;
			if( p_w2 ) {
				w2 = volt>1300;
			}else{
				w2 = volt>1900;
			}

			if( p_w2 != w2 ) {
				p_w2 = w2;
				if( !w2 ){
					w2_pos = (w2_pos+1) % 6;
				}
			}
			//show_number( 1<<w2_pos );
		} 
		
		///////////////
		// FSM STUFF //
		///////////////

		{
			static bool p_button = false;
			bool s_button = dig_in_read( &button );
			bool button_event = false;

			if( s_button != p_button ) {
				int64_t current_time = get_current_time();
				if( s_button && (current_time-last_button_press) >= 100 ){
					button_event = true;
					last_button_press = current_time;
				}
				p_button = s_button;
			}
			//show_number(state);
			switch( state ) {
				case WAIT:
					//if( dig_in_read(&lever) ) {
					if( button_event ) {
						state = THREE_WHEELS;
						start_all_wheels();
					}
					break;

				case THREE_WHEELS:
					if(button_event) {
						state = TWO_WHEELS;
						stop_wheel1();
					}
					break;
				case TWO_WHEELS:
					if(button_event) {
						state = ONE_WHEEL;
						stop_wheel2();
					}
					break;
				case ONE_WHEEL:
					if(button_event) {
						state = RESET;
						stop_wheel3();
					}
					break;
				case SCHENK_EI:
					if(false) {
						state = RESET;
					}
					break;
			}
			}

		//TODO wtf is this?!
			/* Test DMA1 TC flag */
			//while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET ){}
			/* Clear DMA TC flag */
			//DMA_ClearFlag(DMA1_FLAG_TC1);
		

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


