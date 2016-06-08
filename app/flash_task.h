/**
 * @file  flash_task.h
 * @brief flash��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef FLASH_TASK_H_
#define FLASH_TASK_H_
#include "../kernel/kernel.h"
#include "../drivers/drivers.h"

/**
 * @brief flash״̬
 */
enum {
  FLASH_NO_CHANGE,   ///<  ����δ�ı�
  FLASH_CHANGED,     ///<  ���ݸı�,��Ҫͬ��
};

#define FLASH_SYN_INT_TIME          5000 ///< flash ͬ����� 5s

/**
 * @brief flash�ṹ
 */
typedef struct Flash {
  u8 action;    ///< ����
  u64 time_a;   ///< ʱ���ʱ��
  u16 itv_time; ///< ʱ����
  u8 saved;
}Flash;

extern Flash flash;

extern void flash_task();
extern void flash_load_config();

#endif