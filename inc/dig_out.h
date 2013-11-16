#ifndef DIG_OUT_H__
#define DIG_OUT_H__

#include <dig_in.h> //pull_res_t

typedef struct {
	int dig_out_pin;
	enum pull_res_t pull_res;
} dig_out_t;


void dig_out_init();
void dig_out_setup(dig_out_t *t);

void dig_out_set(dig_out_t *t);
void dig_out_clr(dig_out_t *t);
void dig_out_toggle(dig_out_t* t);

#endif //DIG_OUT_H__
