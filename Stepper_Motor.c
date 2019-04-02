#include "lib.h"

int substep_num = 0;
int time_steps[] = {STEP_1, STEP_2, STEP_3, STEP_4};
GPIO_TypeDef* gpio_port_steps[] = {STEP_1_GPIO, STEP_2_GPIO, STEP_3_GPIO, STEP_4_GPIO};

void iterate(void);


int main(void){
	init();
	while(1){
		iterate();
		wait(DELAY);
    }
}

void iterate(void){
	reset();
	GPIO_SetBits(gpio_port_steps[substep_num], time_steps[substep_num]);
	if (++substep_num == 4){
			substep_num = 0;
	} 
}