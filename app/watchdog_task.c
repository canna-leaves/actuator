/**
 * @file  watchdog_task.c
 * @brief ���Ź�����ģ��ʵ��
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#include "watchdog_task.h"

WatchDog watchdog;  ///< ���Ź���������

/**
 * @brief ���Ź�������
 * @return �޷���ֵ
 */
void watchdog_task() {
  if(task_timer.tick - watchdog.time_a > watchdog.itv_time) {
    WATCH_DOG_FEED();
    watchdog.time_a = task_timer.tick;
  }
  u16 event;
  if(TRUE == task_event_get(TASK_WATCH_DOG, &event))
  {}
}