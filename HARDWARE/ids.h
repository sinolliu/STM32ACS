#include "sys.h"

#define ids_on	1		//���⴫������⵽�ź�

//�����߶˿ڶ���
#define ids  PCin(4)  	//PC4


void IDS_Init(void);		//IO��ʼ��
u8 IDS_Scan(void);		     //���⴫����ɨ�躯��
void IDS_Alarm(void);				//���ⱨ��������
