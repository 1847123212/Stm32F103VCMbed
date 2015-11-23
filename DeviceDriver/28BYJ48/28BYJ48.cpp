#include "mbed.h"
#include "28BYJ48.h"

DigitalOut INA(PE_0);
DigitalOut INB(PE_1);
DigitalOut INC(PE_2);
DigitalOut IND(PE_3);
void Init28BYJ48(void)
{
	INA.write(1);
	INB.write(0);
	INC.write(0);
	IND.write(0);
}
#define STEP_TIME 5000
void StepSD8_28BYJ48(void)
{
	wait_us(STEP_TIME);
	INB.write(1);//AB
	wait_us(STEP_TIME);
	INA.write(0);//B
	wait_us(STEP_TIME);
	INC.write(1);//BC
	wait_us(STEP_TIME);
	INB.write(0);//C
	wait_us(STEP_TIME);
	IND.write(1);//CD
	wait_us(STEP_TIME);
	INC.write(0);//D
	wait_us(STEP_TIME);
	INA.write(1);//DA
	wait_us(STEP_TIME);
	IND.write(0);//A
}
void StepS4_28BYJ48(void)
{
	INA.write(0);//B
	INB.write(1);//AB
	wait_us(STEP_TIME);
	INB.write(0);//C
	INC.write(1);//BC
	wait_us(STEP_TIME);
	INC.write(0);//D
	IND.write(1);//CD
	wait_us(STEP_TIME);
	IND.write(0);//A
	INA.write(1);//DA
	wait_us(STEP_TIME);
	
}
extern Serial pc1;
void StepD4_28BYJ48(void)
{
	static int Step=0;
	switch(Step){
		case 0:
			IND.write(0);
			INB.write(1);//AB
			break;
		case 1:
			INA.write(0);
			INC.write(1);//BC
			break;
		case 2:
			INB.write(0);
			IND.write(1);//CD
			break;
		case 3:
			INC.write(0);
			INA.write(1);//DA
			break;
		default:
			break;
	}
	Step++;
	if(Step==4)Step=0;
// 	INB.write(1);//AB
// 	wait_us(STEP_TIME);
// 	INA.write(0);
// 	INC.write(1);//BC
// 	wait_us(STEP_TIME);
// 	INB.write(0);
// 	IND.write(1);//CD
// 	wait_us(STEP_TIME);
// 	INC.write(0);
// 	INA.write(1);//DA
// 	wait_us(STEP_TIME);
// 	IND.write(0);
	//pc1.printf("motor\r\n");
}
