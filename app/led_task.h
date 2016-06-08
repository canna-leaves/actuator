/**
 * @file  led_task.h
 * @brief led����������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef LED_TASK_H_
#define LED_TASK_H_
#include "../kernel/kernel.h"
#include "../drivers/drivers.h"
#include "flowmeter_task.h"

/**
 * @brief led�ṹ
 */
typedef struct Led {
  u8 state;    ///< led��״̬
  u64 time_a;  ///< ��ʱ��
}Led;

/**
 * @brief led������
 */
enum {
  LED_RUN,      ///< ���е�
  LED_MAX_NUM,  ///< led������
};

/**
 * @brief led��״̬
 */
enum {
  STATE_LED_OFF,   ///< �ر�״̬
  STATE_LED_LIGHT, ///< ����״̬
  STATE_LED_BLINK, ///< ��˸״̬
};

extern Led leds[LED_MAX_NUM];

#define LED_RUN_INT_TIME      800 ///< ��˸���0.5s

extern void led_task();

#endif