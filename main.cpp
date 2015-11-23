#include "mbed.h"
#include "28BYJ48.h"
#include "Dht21.h"
#include "ESP8266_Usart.h"
#include "GP2Y1010au.h"
#include "SDFileSystem.h"

Serial pc1(PA_9,PA_10);
Ticker hello;
Ticker motor;
Ticker Update;
SDFileSystem sd(PB_15, PB_14, PB_13, PB_12, "sd");
void PPP(void)
{
	pc1.printf("Hello,Ticker motor\r\n");
}
int main() {
	uint16_t PM25Val;
	short i=0,temperature=0;
	float Temperature,humidity;
	wait(5);
	pc1.baud(115200);
	pc1.printf("Serial 1 Init successful!\r\n");
 	ESP8266_Init();
 	Init28BYJ48();
	while(DHT21_Init())	{
		pc1.printf("DHT21 initing\r\n");
	}
	
	pc1.printf("mkdir\r\n");
	mkdir("/sd/mydir", 0777);
	pc1.printf("fopen file sdtest.txt\r\n");
	FILE *fp = fopen("/sd/mydir/sdtest.txt", "w");
	if(fp == NULL) {
			error("Could not open file for write\n");
	}
	fprintf(fp, "Hello fun SD Card World!");
	i=3000;
	while(i--){
		fprintf(fp,"%d",i);
	}
	fclose(fp); 
	pc1.printf("create file sdtest\r\n");
	
	
	//hello.attach(&PPP,1);
	motor.attach_us(&StepD4_28BYJ48,5000);
	Update.attach(&ESP8266_UpLoadData,6);
	
	
	while(1) {   
		wait_ms(100);

		DHT21_Read_Data(&Temperature,&humidity);		//¶ÁÈ¡ÎÂÊª¶ÈÖµ		
		//pc1.printf("Temp: %0.1f,Humi: %0.1f\r\n",Temperature,humidity);
		PM25Val=GP2Y1010auGetPM25();		
		//pc1.printf("Dust Value is: %d ug/m3\r\n",PM25Val);
		ESP8266_UpdateData(PM25Val,Temperature,humidity);
	}
}

