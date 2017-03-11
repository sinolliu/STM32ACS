#include "delay.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "usart.h"
#include "wg.h"

//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void) {
  delay_ms(10);   //����
  if (WK_UP == 1) // WK_UP����
  {
    LED0 = !LED0;
    LED1 = !LED1;
  }
  EXTI->PR = 1 << 0; //���LINE0�ϵ��жϱ�־λ
}
//�ⲿ�ж�1�������
void EXTI1_IRQHandler(void) {
  delay_ms(10);  //����
  if (KEY0 == 0) //����0
  {
    LED0 = !LED0;
  }
  EXTI->PR = 1 << 1; //���LINE1�ϵ��жϱ�־λ
}
//�ⲿ�ж�15~10�������
void EXTI15_10_IRQHandler(void) {
  delay_ms(10);  //����
  if (KEY1 == 0) //����1
  {
    LED1 = !LED1;
  }
  EXTI->PR = 1 << 13; //���LINE13�ϵ��жϱ�־λ
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void) {
  WGR_D1();
  EXTI->PR = 1 << 3; //���LINE1�ϵ��жϱ�־λ
}

void EXTI2_IRQHandler(void) {
  WGR_D0();
  EXTI->PR = 1 << 2; //���LINE1�ϵ��жϱ�־λ
}
//�ⲿ�жϳ�ʼ������
//��ʼ��PA0,PC5,PA15Ϊ�ж�����.
void EXTI_Init(void) {
  KEY_Init();
  Ex_NVIC_Config(GPIO_A, 0, RTIR);  //�����ش���
  Ex_NVIC_Config(GPIO_C, 1, FTIR);  //�½��ش���
  Ex_NVIC_Config(GPIO_C, 13, FTIR); //�½��ش���

  Ex_NVIC_Config(GPIO_C, 2, FTIR); //�½��ش���	D0 //Τ���ж�
  Ex_NVIC_Config(GPIO_C, 3, FTIR); //�½��ش���	D1

  MY_NVIC_Init(1, 1, EXTI0_IRQn, 3);     //��ռ2�������ȼ�2?z��3
  MY_NVIC_Init(1, 1, EXTI1_IRQn, 3);     //��ռ2�������ȼ�1����3
  MY_NVIC_Init(1, 1, EXTI15_10_IRQn, 3); //��ռ2�������ȼ�0����3

  MY_NVIC_Init(0, 1, EXTI3_IRQn, 3);
  MY_NVIC_Init(0, 1, EXTI2_IRQn, 3);
}
