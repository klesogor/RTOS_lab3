#include "lib.h"
#include <cmsis_os.h>

int substep_num = 0;
int time_steps[] = {STEP_1, STEP_2, STEP_3, STEP_4};

void handler(void const *param);
void poolIO(struct State* target);
osTimerDef(timer_main_handle, handler);


int main(void){
	int steps[] = {STEP_1,STEP_2,STEP_3,STEP_4};
	struct State state = {
		steps,
		0,
		DIR_FORWARD,
		MODE_ROTATE,
		false,
		20,
		5
	};
	osTimerId timer_main = osTimerCreate(osTimer(timer_main_handle), osTimerPeriodic, (void *)&state);	
	init();
	osKernelInitialize ();
	osTimerStart(timer_main, 50);	
	osKernelStart ();  
}

void handler(void const *param){
	struct State *state = (struct State*)param;
	poolIO(state);
	doWork(state,GPIO);
}

void poolIO(struct State* state){
	if(GPIO_ReadInputDataBit(GPIO,DIR_PIN)){
		setDirection(state, DIR_BACKWARD);
	} else {
		setDirection(state, DIR_FORWARD);
	}
	if(GPIO_ReadInputDataBit(GPIO,MODE_PIN)){
		setMode(state, MODE_DEGREE);
	} else {
		setMode(state, MODE_ROTATE);
	}
}
