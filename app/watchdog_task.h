/**
 * @file  watchdog_task.h
 * @brief ���Ź�����
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef WATCH_DOG_TASK_H_
#define WATCH_DOG_TASK_H_
#include "../kernel/kernel.h"

/**
 * @brief ���Ź�����ṹ
 */
typedef struct WatchDog {
  u16 itv_time;  ///< ʱ����
  u64 time_a;    ///< ��ʱ��
}WatchDog;

#define WATCH_DOG_FEED_CYCLE_TIME     500 ///< ι������500ms

extern WatchDog watchdog;
extern void watchdog_task();

#endif