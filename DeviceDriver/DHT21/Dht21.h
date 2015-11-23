#ifndef __DHT21_H
#define __DHT21_H 

#ifdef __cplusplus
extern "C" {
#endif

//IO��������
#define DHT21_IO_IN()  DHT21IO.input(); //{GPIOD->CRH&=0XFFFF0FFF;GPIOD->CRH|=8<<12;}
#define DHT21_IO_OUT() DHT21IO.output();//{GPIOD->CRH&=0XFFFF0FFF;GPIOD->CRH|=3<<12;}
////IO��������											   
#define	DHT21_DQ_OUT PDout(11) //���ݶ˿�	PA0 
#define	DHT21_DQ_IN  PDin(11)  //���ݶ˿�	PA0 


uint8_t DHT21_Init(void);//��ʼ��DHT21
uint8_t DHT21_Read_Data(float *temp,float *humi);//��ȡ��ʪ��
uint8_t DHT21_Read_Byte(void);//����һ���ֽ�
uint8_t DHT21_Read_Bit(void);//����һ��λ
uint8_t DHT21_Check(void);//����Ƿ����DHT21
void DHT21_Rst(void);//��λDHT21    


#ifdef __cplusplus
}
#endif 
#endif















