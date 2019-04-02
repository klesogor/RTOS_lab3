#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO

#define STEP_1 PIN_0
#define STEP_1_GPIO GPIOA
#define STEP_2 PIN_1
#define STEP_2_GPIO GPIOA
#define STEP_3 PIN_8
#define STEP_3_GPIO GPIOB
#define STEP_4 PIN_9
#define STEP_4_GPIO GPIOB

#define GPIOA_MASK PIN_1 | PIN_2
#define GPIOB_MASK PIN_8 | PIN_9

#define DIRECTION  0
//300 000 microseconds === 300 ms === 0.3s
#define DELAY 300000

void wait (int delay);
void reset(void);
void init();
void initPort(void);
void initSysTick(void);
void SysTick_Handler(void);