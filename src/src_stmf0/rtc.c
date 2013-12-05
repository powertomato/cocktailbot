
//RTC_DateTypeDef date;

#include <rtc.h>
#include <platform.h>

void rtc_init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_BackupAccessCmd(ENABLE); //needed?
	/* use LSE-clock X3=32768 KHz, C 
	RCC_LSEConfig(RCC_LSE_ON);

	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET){};
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();

	RTC_InitTypeDef rtc_init;

	rtc_init.RTC_AsynchPrediv = 0xFF;
	rtc_init.RTC_SynchPrediv = 0x7F;
	rtc_init.RTC_HourFormat = RTC_HourFormat_24; */

	RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div32);
	
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();

	RTC_InitTypeDef rtc_init;

	rtc_init.RTC_SynchPrediv = 0x7a0;
	rtc_init.RTC_AsynchPrediv = 0x7F;
	rtc_init.RTC_HourFormat = RTC_HourFormat_24;

	RTC_Init(&rtc_init);
}

int64_t get_current_time(){
	int64_t ret;
	RTC_TimeTypeDef time;

	ret = RTC_GetSubSecond();
	RTC_GetTime( RTC_Format_BIN, &time );
	
	ret += time.RTC_Hours*60*60*1000;
	ret += time.RTC_Minutes*60*1000;
	ret += time.RTC_Seconds*1000;

	return ret;
}

void wait_until(int64_t time){
	while( (time - get_current_time()) > 0 ) {	}
}
