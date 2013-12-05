
#ifndef RTC_H__
#define RTC_H__

#include <stdint.h>

void rtc_init();
int64_t get_current_time();
void wait_until(int64_t time);

#endif //RTC_H__
