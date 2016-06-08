/**
 * @file  kernel.c
 * @brief �ں���غ���
 * @version 1.0
 * @author ygz
 * @date   2015.7.1
 */
#include "kernel.h"

/**
 * @brief �����ں˳�ʼ������
 * @return �޷���ֵ
 */
void kernel_init() {
  cpu_init();
  task_timer_init();
#if 1
  WATCH_DOG_ENABLE();
#else
  WATCH_DOG_DISABLE();
#endif
}

/**
 * @brief �����ʼ��ǰ���ڲ����Ź��ر�,��ֹ�������ʼ��ʱ���Ź���λ
 * @retval 1 �ɹ�
 */
int __low_level_init(void)
{
  /* Insert your low-level initializations here */
  //stop WDT
  WDTCTL = WDTPW + WDTHOLD;
  /*
  *Return value:
  *
  * 1 - Perform data segment initialization.
  * 0 - Skip data segment initialization.
  */
  return 1;
}