#include <stm32f0xx.h>
#include <stm32f0xx_conf.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_tim.h>

#ifndef bool
typedef int bool;
#define true (0==0)
#define TRUE true
#define false (!true)
#define FALSE false
#endif

#define MAX(X,Y) ((X<Y) ? Y : X)
#define MIN(X,Y) ((X<Y) ? X : Y)

#include "pin_assignment.h"

