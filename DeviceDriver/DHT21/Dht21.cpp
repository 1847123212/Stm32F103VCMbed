#include "mbed.h"
#include "pinbitband.h"   
#include "DHT21.h"

#include "stdio.h"
DigitalInOut DHT21IO(PD_11,PIN_OUTPUT,PullNone,1);
void DHT21_Rst(void)	   
{                 
		DHT21_IO_OUT(); 	//SET OUTPUT
		DHT21_DQ_OUT=0; 	//����DQ
		wait_ms(20);    	//��������18ms
		DHT21_DQ_OUT=1; 	//DQ=1 
		wait_us(30);     	//��������20~40us
}
//�ȴ�DHT21�Ļ�Ӧ
//����1:δ��⵽DHT21�Ĵ���
//����0:����
uint8_t DHT21_Check(void) 	   
{   
	uint8_t retry=0;
	DHT21_IO_IN();//SET INPUT	 
    while (DHT21_DQ_IN&&retry<100)//DHT21������40~80us
	{
		retry++;
		wait_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT21_DQ_IN&&retry<100)//DHT21���ͺ���ٴ�����40~80us
	{
		retry++;
		wait_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//��DHT21��ȡһ��λ
//����ֵ��1/0
uint8_t DHT21_Read_Bit(void) 			 
{
 	uint8_t retry=0;
	while(DHT21_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		wait_us(1);
	}
	retry=0;
	while(!DHT21_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ
	{
		retry++;
		wait_us(1);
	}
	wait_us(40);//�ȴ�40us
	if(DHT21_DQ_IN)return 1;
	else return 0;		   
}
//��DHT21��ȡһ���ֽ�
//����ֵ������������
uint8_t DHT21_Read_Byte(void)    
{        
    uint8_t i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT21_Read_Bit();
    }						    
    return dat;
}
//��DHT21��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
uint8_t DHT21_Read_Data(float *temp,float *humi)    
{        
 	uint8_t buf[5];
	uint8_t i;
	DHT21_Rst();
	if(DHT21_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
		{
			buf[i]=DHT21_Read_Byte();
		}
			//printf(" buf0-4: %x %x %x %x %x\r\n",buf[0],buf[1],buf[2],buf[3],buf[4]);
		if(((buf[0]+buf[1]+buf[2]+buf[3])&0xff)==buf[4])
		{
		
			//printf("T:%d H:%d\r\n",buf[0]*256+buf[1],buf[2]*256+buf[3]);
		
			*humi=((buf[0]<<8) + buf[1])*0.1;
			if(buf[2]&0x80){
				*temp=(((buf[2]&0x7f)<<8) + buf[3])*(-1)*(0.1);
			}
			else{
				*temp=((buf[2]<<8)+buf[3])*(0.1);
			}
			
		}
	}else return 1;
	return 0;	    
}
//��ʼ��DHT21��IO�� DQ ͬʱ���DHT21�Ĵ���
//����1:������
//����0:����    	 
uint8_t DHT21_Init(void)
{	 
//  	GPIO_InitTypeDef  GPIO_InitStructure;
//  	
//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PG�˿�ʱ��
// 	
//  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //PG11�˿�����
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(GPIOD, &GPIO_InitStructure);				 //��ʼ��IO��
//  	GPIO_SetBits(GPIOD,GPIO_Pin_11);						 //PG11 �����
			    
	DHT21_Rst();  //��λDHT21
	return DHT21_Check();//�ȴ�DHT21�Ļ�Ӧ
} 







