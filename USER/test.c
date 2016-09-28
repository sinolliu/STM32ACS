#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "flash.h"
#include "key.h"
#include "led.h"
#include "exti.h"
#include "auth.h"
#include "wg.h"

extern int r_done;	//��ȡ�ɹ���־
u8 datatemp[26];

int main(void)
{
	
	u32 FLASH_SIZE;
	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);	    //��ʱ��ʼ��
	uart_init(72,9600); //���ڳ�ʼ��
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	EXTI_Init();		//�ⲿ�жϳ�ʼ��
	SPI_Flash_Init();
	FLASH_SIZE = 2 * 1024 * 1024;

	while(1)
	{
		if (r_done == 1) {
			r_done = 0;
			if(dat_check()){
			SPI_Flash_Read(datatemp, FLASH_SIZE - 100,26);
			auth();
			}
		}
	}
	}

