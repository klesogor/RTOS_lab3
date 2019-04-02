#include "lib.h"

void wait (void)
{
  int  d;
  for (d = 0; d < FAST_SPEED; d++);
}

void init(void)
{
  initSysTick();
  initPort();
}

void initPort(void)
{
		GPIO_InitTypeDef      MOTOR_PORT_B;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
    MOTOR_PORT_B.GPIO_Mode = GPIO_Mode_Out_PP; 
    MOTOR_PORT_B.GPIO_Speed = GPIO_Speed_2MHz;
		MOTOR_PORT_B.GPIO_Pin = PIN_8 | PIN_9;
		GPIO_Init(MOTOR_PORT , &MOTOR_PORT_B);

    GPIO_InitTypeDef      MOTOR_PORT_A;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
    MOTOR_PORT_A.GPIO_Mode = GPIO_Mode_Out_PP; 
    MOTOR_PORT_A.GPIO_Speed = GPIO_Speed_2MHz;
		MOTOR_PORT_A.GPIO_Pin = PIN_1 | PIN_2;
		GPIO_Init(MOTOR_PORT , &MOTOR_PORT_A);
}

void reset(void)
{
  GPIO_ResetBits(GPIOA, GPIOA_MASK);
  GPIO_ResetBits(GPIOB, GPIOB_MASK);
}

void initSysTick(){
	if (SysTick_Config(SystemCoreClock / 1000000))//every microsecond
	{
		while (1);	// in case SysTick_Config() failed just wait here
	}
}

static __IO int sysTickCnt = 0;

void delay(int nTime)
{
	sysTickCnt = nTime;
	while(sysTickCnt != 0)
		;
}

void SysTick_Handler(void)
{
	if (sysTickCnt != 0)
	{
		sysTickCnt--;
	}
}