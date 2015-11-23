#ifndef __DHT21_H
#define __DHT21_H 

#ifdef __cplusplus
extern "C" {
#endif

//IO方向设置
#define DHT21_IO_IN()  DHT21IO.input(); //{GPIOD->CRH&=0XFFFF0FFF;GPIOD->CRH|=8<<12;}
#define DHT21_IO_OUT() DHT21IO.output();//{GPIOD->CRH&=0XFFFF0FFF;GPIOD->CRH|=3<<12;}
////IO操作函数											   
#define	DHT21_DQ_OUT PDout(11) //数据端口	PA0 
#define	DHT21_DQ_IN  PDin(11)  //数据端口	PA0 


uint8_t DHT21_Init(void);//初始化DHT21
uint8_t DHT21_Read_Data(float *temp,float *humi);//读取温湿度
uint8_t DHT21_Read_Byte(void);//读出一个字节
uint8_t DHT21_Read_Bit(void);//读出一个位
uint8_t DHT21_Check(void);//检测是否存在DHT21
void DHT21_Rst(void);//复位DHT21    


#ifdef __cplusplus
}
#endif 
#endif















