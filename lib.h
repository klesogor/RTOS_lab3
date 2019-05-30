#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "GPIO_STM32F10x.h"             // Keil::Device:GPIO
#include <cmsis_os.h>

#define STEP_1 GPIO_Pin_0
#define STEP_2 GPIO_Pin_2
#define STEP_3 GPIO_Pin_5
#define STEP_4 GPIO_Pin_7
#define DIR_PIN GPIO_Pin_10
#define MODE_PIN GPIO_Pin_12
#define GPIO GPIOA

#define DIR_FORWARD 0
#define DIR_BACKWARD 1

#define MODE_ROTATE 0
#define MODE_DEGREE 1

#define INIT_MASK STEP_1 | STEP_2 | STEP_3 | STEP_4 | DIR_PIN | MODE_PIN

void init(void);

//ACESSING PROPS DIRECTLY IS THREAD UNSAFE!
struct State{
	int* steps;
	int currentStepIndex;
	int dir;
	int mode;
	bool isLocked;
	int rotationDegree;
	int degreePerStep;
};

//THREAD SAFE
bool setMode(struct State* state,int mode);
bool setDirection(struct State* state,int dir);
bool isLocked(struct State* state);
void doWork(struct State* state, GPIO_TypeDef* gpio);


