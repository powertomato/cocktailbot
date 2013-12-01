#ifndef DIG_OUT_H__
#define DIG_OUT_H__

#include <dig_in.h> //pull_res_t

typedef struct {
	int pin;
	
	enum pull_res_t pull_res;
} dig_out_t;


void dig_out_init();
void dig_out_setup(int pin, enum pull_res_t pull_res);

void dig_out_set(int pin);
void dig_out_clr(int pin);
void dig_out_toggle(int pin);

#endif //DIG_OUT_H__
