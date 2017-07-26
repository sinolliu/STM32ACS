#include "ids.h"
#include "led.h"
#include "delay.h"

//������ʼ������
//PA0.15��PC5 ���ó�����
void IDS_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��

  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
  
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PA15
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������  //todo
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA15
}



//���⴫����ɨ�账����
u8 IDS_Scan(void)
{
	if(ids == 0)return ids_on;
	return 0;
}


void IDS_Alarm(void)
{
	LED0=!LED0;
	delay_ms(300);
	LED0=!LED0;
	delay_ms(300);
	LED0=!LED0;
	delay_ms(300);
	LED0=!LED0;


}
