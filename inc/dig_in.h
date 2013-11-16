
#ifndef BUTTON_H__
#define BUTTON_H__

#include <platform.h> //bool

enum pull_res_t {
	PULL_UP,
	PULL_DOWN,
	PULL_NO
};

typedef struct {
	int dig_in_pin;
	enum pull_res_t pull_res;
	bool low_active;
} dig_in_t;

void dig_in_init();
void dig_in_setup(dig_in_t *t);
bool dig_in_read(dig_in_t *t);

#endif
