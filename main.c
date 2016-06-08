/**
 * @file  main.c
 * @brief ����������
 * @version 1.0
 * @author ygz
 * @date   2015.7.1
 */
#include "kernel/kernel.h"
#include "drivers/drivers.h"
#include "app/app.h"
#include "app/test.h"
/**
 * @brief ������ڣ���������������
 */
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD; /// �����ڲ����Ź�
  __disable_interrupt();    /// ��ֹȫ���ж�
  kernel_init();            /// �ں˳�ʼ��
  drivers_init();           /// ������ʼ��
  /** �������� */
  TASK_CREATE(TASK_RTU        ,1 , rtu_task);         /// 1 ����TASK_RTU����
  TASK_CREATE(TASK_FLOW_METER ,1 , flowmeter_task);   /// 2 ����TASK_FLOW_METER����
  TASK_CREATE(TASK_LCD        ,5 , lcd_task);         /// 3 ����TASK_LCD����
  TASK_CREATE(TASK_BUTTON     ,3 , button_task);      /// 4 ����TASK_BUTTON����
  TASK_CREATE(TASK_LED        ,20, led_task);         /// 5 ����TASK_LED����
  TASK_CREATE(TASK_ADC        ,3 , adc_task);         /// 6 ����TASK_ADC����
  TASK_CREATE(TASK_FLASH      ,30, flash_task);       /// 7 ����TASK_FLASH����
  TASK_CREATE(TASK_WATCH_DOG  ,30, watchdog_task);    /// 8 ����TASK_WATCH_DOG����
  TASK_CREATE(TASK_MOTOR      ,10, motor_task);       /// 9
  app_init();               /// Ӧ�ó�ʼ��
  //test();
  __enable_interrupt();     /// ����ȫ���ж�
  task_scheduling();        /// �������
  return 0;                /// �������е�����
}
