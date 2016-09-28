#include "auth.h"
#include "delay.h"
#include "led.h"
#include "wg.h"

u8 dat[26]; //ˢ����Ϣ
u8 count = 0;
u8 firstbit;   //ǰ2-13λ��żУ��λ
u8 lastbit;    //��14��25λ����У��λ
u8 r_done = 0; //���ݻ�ȡ��ɱ�־λ

//�� D0 ���ϵ�����
void WGR_D0(void) //��ɫ C2
{
  if (count == 0) //��ȡżУ����
  {
    firstbit = 0;
    dat[count] = 0;
    r_done = 0;
  } else if (count < 25) {
    dat[count] = 0;
  } else if (count == 25) {
    lastbit = 0;
    dat[count] = 0;
  } //��ȡ��У����
  count++;
  if (count == 26) {
    count = 0;
//		delay_ms(10);
	  r_done = 1;
  }
}

//�� D1 ���ϵ�����
void WGR_D1(void) //��ɫ C3
{
  if (count == 0) {
    firstbit = 1;
    dat[count] = 1;
  } else if (count < 25) {
    dat[count] = 1;
  } else if (count == 25) {
    lastbit = 1;
    dat[count] = 1;
  }
  count++;
  if (count == 26) {
    count = 0;
//		delay_ms(10);
		r_done = 1;
  }
}

//���У������

u8 dat_check(void) {
  int f, l, n=0, m=0, p=0;
  u8 one_num=0;
  for (f = 1; f <= 12; f++) {
    if (dat[f] & 0x01)
      one_num++;
  }
  n = (one_num + firstbit) % 2; // 0Ϊͨ��
  one_num = 0;
  if (!n) {
    for (l = 13; l <= 24; l++) {
      if (dat[l] & 0x01)
        one_num++;
    }
    m = (one_num + lastbit) % 2;
    one_num = 0;
    if (m)
       p=1;
  }
	return p;
}


void send_wg_dat(void) {
  // if (r_done == 1) //������ݻ�ȡ��ɱ�־λ��Ч��˵�����ݻ�ȡ���
  // {
  int p;
  //  delay_ms(200);
  //  r_done = 0;
  for (p = 0; p <= 25; p++) {
    if (dat[p] == 0) {
      LED0 = 0;
      delay_ms(200);
      LED0 = 1;
      delay_ms(200);
    } else {
      LED1 = 0;
      delay_ms(200);
      LED1 = 1;
      delay_ms(200);
    }
  }
  //}
  //	return 0;
}
