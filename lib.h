#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO

#define STEP_1 GPIO_Pin_0
#define STEP_1_GPIO GPIOA
#define STEP_2 GPIO_Pin_1
#define STEP_2_GPIO GPIOA
#define STEP_3 GPIO_Pin_8
#define STEP_3_GPIO GPIOB
#define STEP_4 GPIO_Pin_9
#define STEP_4_GPIO GPIOB

#define GPIOA_MASK GPIO_Pin_1 | GPIO_Pin_2
#define GPIOB_MASK GPIO_Pin_8 | GPIO_Pin_9

#define DIRECTION  0
//300 000 microseconds === 300 ms === 0.3s
#define DELAY 300000

void wait (int delay);
void reset(void);
void init();
void initPort(void);
void initSysTick(void);
void SysTick_Handler(void);