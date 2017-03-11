#include "delay.h"
#include "key.h"

//������ʼ������
// PA0.15��PC5 ���ó�����
void KEY_Init(void) {
  RCC->APB2ENR |= 1 << 2; //ʹ��PORTAʱ��
  RCC->APB2ENR |= 1 << 4; //ʹ��PORTCʱ��
  // JTAG_Set(SWD_ENABLE);	//�ر�JTAG,����SWD	//�ƺ�û���ظ�
  GPIOA->CRL &= 0XFFFFFFF0; // PA0���ó�����
  GPIOA->CRL |= 0X00000008;
  GPIOC->CRL &= 0XFFFF000F; // PC1��2��3���ó�����
  GPIOC->CRL |= 0X00008880;
  GPIOC->ODR |= 1 << 1;     // PC1����,PA0Ĭ������
	GPIOC->ODR |= 1 << 2;
	GPIOC->ODR |= 1 << 3;
  GPIOC->CRH &= 0XFF0FFFFF; // PC13���ó�����
  GPIOC->CRH |= 0X00800000;
  GPIOC->ODR |= 1 << 13; // PC13����
}
//����������
//���ذ���ֵ
// mode:0,��֧��������;1,֧��������;
//����ֵ��
// 0��û���κΰ�������
// KEY0_PRES��KEY0����
// KEY1_PRES��KEY1����
// WKUP_PRES��WK_UP����
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode) {
  static u8 key_up = 1; //�������ɿ���־
  if (mode)
    key_up = 1; //֧������
  if (key_up && (KEY0 == 0 || KEY1 == 0 || WK_UP == 1)) {
    delay_ms(10); //ȥ����
    key_up = 0;
    if (KEY0 == 0)
      return KEY0_PRES;
    else if (KEY1 == 0)
      return KEY1_PRES;
    else if (WK_UP == 1)
      return WKUP_PRES;
  } else if (KEY0 == 1 && KEY1 == 1 && WK_UP == 0)
    key_up = 1;
  return 0; // �ް�������
}
