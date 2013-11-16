#include <stm32f0xx.h>
#include <stm32f0xx_conf.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_gpio.h>

#ifndef bool
typedef int bool;
#define true (0==0)
#define TRUE true
#define false (!true)
#define FALSE false
#endif

#include "pin_assignment.h"

