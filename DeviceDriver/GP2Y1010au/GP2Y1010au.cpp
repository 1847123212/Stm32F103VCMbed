#include "mbed.h"
#include "GP2Y1010au.h"

AnalogIn	DustIn(PA_0);
DigitalOut IRLED(PD_14);
#define BASE_VOL 0.15

extern Serial pc1;
void GP2Y1010auInit(void)
{
	
}

uint16_t GP2Y1010auGetPM25()
{
		float DustVal=0;
		float DustVol;
		uint16_t PM25Val;
		IRLED.write(0);
		wait_us(280);
		DustVal=DustIn.read();
		wait_us(40);
		IRLED.write(1);
		wait_us(9680);
		wait_ms(1000);
		//pc1.printf("DustVal Vol is %f \r\n",DustVal);
		DustVol=DustVal*3.3*2;
	
		//pc1.printf("DustIn Vol is %0.3f V\r\n",DustVol);
	
		if(DustVol>BASE_VOL){
			PM25Val=(uint16_t)((DustVol-BASE_VOL)*1000/6.1);
		}
		else{
			PM25Val=0;
		}
		return PM25Val;
}



