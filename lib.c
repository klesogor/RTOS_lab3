#include <stm32f10x.h>    
#include "lib.h"

void initPort(void);

void lock(struct State* state);
void unlock(struct State* state);
int getStepsAmount(struct State* state);
int getMaskByIndex(struct State* state, int index);
int getNextStepIndex(int index, int stepAmount, int direction);
int opositeDirecion(int dir);
int getCurrentStep(struct State* state);
int getPreviousStep(struct State* state);
void nextStep(struct State* state);
void rotateDegree(struct State* state, GPIO_TypeDef* gpio);

void init()
{
  initPort();
}

void initPort()
{
		GPIO_InitTypeDef      MOTOR_PORT;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
    MOTOR_PORT.GPIO_Mode = GPIO_Mode_Out_PP; 
    MOTOR_PORT.GPIO_Speed = GPIO_Speed_2MHz;
		MOTOR_PORT.GPIO_Pin = INIT_MASK;
		GPIO_Init(GPIOA, &MOTOR_PORT);
}

void lock(struct State* state){
	state->isLocked = true;
}
void unlock(struct State* state){
	state->isLocked = false;
}
bool isLocked(struct State* state){
	return state->isLocked;
}

void doWork(struct State* state, GPIO_TypeDef* gpio){
	if(isLocked(state)) return;
	switch(state->mode){
		case MODE_ROTATE:
			GPIO_ResetBits(gpio,getPreviousStep(state));
			GPIO_SetBits(gpio,getCurrentStep(state));
			nextStep(state);
			return;
		case MODE_DEGREE:
			rotateDegree(state, gpio);
			return;
	}
}

void rotateDegree(struct State* state, GPIO_TypeDef* gpio){
	lock(state);
	int i = 0;
	int totalRotates =  (state->rotationDegree % state->degreePerStep) ?  
											 state->rotationDegree / state->degreePerStep + 1: 
											 state->rotationDegree / state->degreePerStep;
	while(i++ < totalRotates){
		GPIO_ResetBits(gpio,getPreviousStep(state));
		GPIO_SetBits(gpio,getCurrentStep(state));
		nextStep(state);
		osDelay(5);
	}
	
	unlock(state);
}

int getCurrentStep(struct State* state){
	return getMaskByIndex(state,state->currentStepIndex);
}
int getPreviousStep(struct State* state){
	return getMaskByIndex(state,state->currentStepIndex - 1);
}
void nextStep(struct State* state){
	state->currentStepIndex = getNextStepIndex(state->currentStepIndex, getStepsAmount(state), state->dir);
}

int getMaskByIndex(struct State* state, int index){
	int amount = getStepsAmount(state);
	return state->steps[index%amount] | state->steps[getNextStepIndex(index,amount,opositeDirecion(state->dir))];
}

int getNextStepIndex(int index, int stepAmount, int direction){
	switch(direction){
		case DIR_FORWARD:
			return (index +1) % stepAmount;
		case DIR_BACKWARD:
			return (stepAmount + index - 1) % stepAmount;
		default:
			return 0;
	}
}

int opositeDirecion(int dir){
	switch(dir){
		case DIR_FORWARD:
			return DIR_BACKWARD;
		case DIR_BACKWARD:
			return DIR_FORWARD;
		default:
			return -1;
	}
}

int getStepsAmount(struct State* state){
	return sizeof(state->steps)/sizeof(int);
}

bool setMode(struct State* state,int mode){
	if(isLocked(state)) return false;
	state->mode = mode;
	return true;
}
bool setDirection(struct State* state,int dir){
	if(isLocked(state)) return false;
	state->dir = dir;
	return true;
}
