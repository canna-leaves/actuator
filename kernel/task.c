/**
 * @file  task.c
 * @brief ϵͳ����ģ��ʵ��
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#include "task.h"

//u64 task_timer_tick = 0; //������ȵ�ǰʱ��ms
//u64 sys_timer_tick = 0;  //ϵͳ��ǰʱ��ms
Task task_list[TASK_MAX_NUM];

TaskTimer task_timer;

/**
 * @brief �������
 * @return �޷���ֵ
 */
void task_scheduling(void)
{
  while(1) {
    u8 i;
    for (i=0; i < TASK_MAX_NUM; ++i)       // �������ʱ�䴦��
    {
      if (task_list[i].run && NULL != task_list[i].task_hook)  // �������б�־
      {
        task_list[i].task_hook();          // ��������
        task_list[i].run = TASK_STOP;      // ��־��0
      }
    }
    //P7OUT ^= BIT5;//����
  }
}

/**
 * @brief ����ʱ�ӳ�ʼ��
 * @return �޷���ֵ
 */
void task_timer_init( void )
{
  task_timer.status = TIMER_STATE_TASK_HANDLER;
  TB0CCR0 = TASK_TIMER_CYCLE_TIME;
  TB0CTL  |= MC__UP | TASSEL__ACLK | TACLR;
  TB0CCTL0 |= CCIE;
}

/**
 * @brief ����ʱ���ж�
 * @return �޷���ֵ
 */
#pragma vector = TIMER0_B0_VECTOR
__interrupt void task_timer_isr(void) 
{
  u8 i;
  for (i=0; i < TASK_MAX_NUM; ++i)                       // �������ʱ�䴦��
  {
    if (task_list[i].timer > 0)                      // ʱ�䲻Ϊ0
    {
      task_list[i].timer--;                          // ��ȥһ������
    } else {
      task_list[i].timer = task_list[i].itv_time;    // �ָ���ʱ��ֵ��������һ��
      task_list[i].run = TASK_RUN;                   // �����������
    }
  }
  switch(task_timer.status) {
    case TIMER_STATE_EMPTY:
      TB0CCR0 = TASK_TIMER_EMPTY_CYCLE_TIME;
      task_timer.status = TIMER_STATE_EMPTY_HANDLER;
    case TIMER_STATE_TASK_HANDLER:
      task_timer.sys_tick += 5;
      task_timer.tick += 5;
      break;
    case TIMER_STATE_TASK:
      TB0CCR0 = TASK_TIMER_CYCLE_TIME;
      task_timer.status = TIMER_STATE_TASK_HANDLER;
    case TIMER_STATE_EMPTY_HANDLER:
      task_timer.tick += 1000;
      task_timer.sys_tick += 1000;
      P7OUT ^= BIT5;
      if(task_timer.tick - task_timer.time_a > task_timer.itv_time) {
        LOW_POWER_MODE_OFF();
      }
      break;
  }
}

/**
 * @brief �ύ��ʱ�¼�
 * @param[in] task ��������
 * @param[in] event �¼�����
 * @param[in] delay �¼���ʱ(����)
 * @retval TRUE �ɹ�
 * @retval FALSE ʧ��
 */
u8 task_event_post(u8 task, u16 event, u64 delay) {
  task_list[task].evt_on = TRUE;
  task_list[task].evt = event;
  task_list[task].evt_time_a = task_timer.tick;
  task_list[task].evt_time_b = delay;
  return TRUE;
}

/**
 * @brief ��ȡ��ǰ�¼�
 * @param[in] task ��������
 * @param[out] event ��ǰ�¼�
 * @retval TRUE �ɹ�
 * @retval FALSE ʧ��
 */
u8 task_event_get(u8 task, u16 *event) {
  if(TRUE == task_list[task].evt_on 
     && task_timer.tick - task_list[task].evt_time_a >= task_list[task].evt_time_b)
  {
    *event = task_list[task].evt;
    task_list[task].evt_on = FALSE;
    return TRUE;
  } else {
    return FALSE;
  }
}
    
void task_setsystime(u64 tm, u8 opt) {
  u8 tmp0, tmp1;
  switch(opt) {
    case TIME_TIME:
      task_timer.sys_tick = tm;
      break;
    case TIME_DAY:
      break;
    case TIME_HOUR:
      tmp0 = task_timer.sys_tick/1000/3600%24;
      tmp1 = tm%24;
      task_timer.sys_tick += (tmp1 - tmp0)*1000L*3600;
      break;
    case TIME_MINUTE:
      tmp0 = task_timer.sys_tick/1000/60%60;
      tmp1 = tm%60;
      task_timer.sys_tick += (tmp1 - tmp0)*1000L*60;
      break;
    case TIME_SECOND:
      tmp0 = task_timer.sys_tick/1000%60;
      tmp1 = tm%60;
      task_timer.sys_tick += (tmp1 - tmp0)*1000L;
      break;
  }
}
