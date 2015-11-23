#include "mbed.h"
#include "28BYJ48.h"
#include "Dht21.h"
#include "ESP8266_Usart.h"
#include "GP2Y1010au.h"


Serial pc1(PA_9,PA_10);
Ticker hello;
Ticker motor;
Ticker Update;
void PPP(void)
{
	pc1.printf("Hello,Ticker motor\r\n");
}
int main() {
	uint16_t PM25Val;
	short temperature;
	float Temperature,humidity;
	wait(5);
	pc1.baud(115200);
	pc1.printf("Serial 1 Init successful!\r\n");
 	ESP8266_Init();
 	Init28BYJ48();
	while(DHT21_Init())	{
		pc1.printf("DHT21 initing\r\n");
	}
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
// 		ESP8266_Ds18b20UpdateLeWei50(PM25Val,Temperature,humidity);
	}
}

