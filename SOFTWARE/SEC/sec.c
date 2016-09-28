#include "auth.h"
#include "delay.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "usart.h"
#include "wg.h"

int fault_count = 0;
int lock_counter=0;
int delay_start_flag = 0; //��ʱ��ʼ��־
int valid_time_flag = 0; //��Чʱ���־,0������Ч
void init_delay(void);
void start_valid_time_counter(void);
void setlock(void);
void lock_exit(void);
void unlock_exit(void);
void start_lock_delay(void);

void sec(void) { //��ʾˢ����֤ʧ��һ��
  // fault_count++;
  // if (delay_start_flag == 0) {
  //   start_valid_time_counter();
  // } else if (delay_start_flag == 1) {
  //   if (valid_time_up();) {           //�������Чʱ����
  //     if (fault_count > 5) {          //���������󳬹�5��
  //       setlock();                    //��������
  //     } else if (unlock_time_up();) { //����������ʱ�䵽
  //       unlock();
  //       init_delay;
  //     }
  //   }
  // }
  fault_count++;
  if (fault_count == 1) {
    start_valid_time_counter();
  }
  if (fault_count == 5) { //����������С��5����Чʱ�����
    if (valid_time_flag == 0) {
      setlock();
    } else if (valid_time_flag == 1) {
      init_delay();
      start_valid_time_counter();
    }
  }
}

void start_valid_time_counter(void) //��ʼ������ʱ
{
  init_delay();
  delay_start_flag = 1;
}

void init_delay(void) //��ʼ����ʱ,�൱�����ü�ʱ
{
  delay_start_flag = 0;
  fault_count = 0; //���ô��������
  valid_time_flag = 0;
}

// void atom_delay(void) //һ����ʱ��λ 30��
// {
//   get_atom_time(); //���һ������30���ʱ�Ĳ���
//}

void valid_time_up(void) //�����жϵ�ǰ�Ƿ�Ϊ��Чʱ��
{
  if (delay_start_flag == 1) {
    int t;
    t++;
    if (t < 30) {
      valid_time_flag = 0;
    } else if (t == 30) {
      valid_time_flag = 1;
    }
  }
}

// void unlock_time_up(void) //���ص�ǰ�Ƿ�������ʱ����
// {
//
// }

void setlock(void) {  //�ú���Ϊִ����ʱ���٣�����ʱ��Ƭ��
  lock_exit();        //�ر��ж�
  start_lock_delay(); //ִֻ�и���ʱ����
  unlock_exit();      //���ж�
  init_delay();       //ִ������ʼ����ʱ����
}

void lock_exit(void)
{

}

void unlock_exit()
{

}

void start_lock_delay()
{
  int p=0,i=2;
  lock_counter++;
  p=i*lock_counter;
  delay_ms(p);
  if (lock_counter>5) {
    lock_counter=0;
  }
}
