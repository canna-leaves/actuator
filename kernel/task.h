/**
 * @file  task.h
 * @brief ����ģ�����˵��
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef TASK_H_
#define TASK_H_
#include "cpu.h"
#include "stdint.h"
#include "watchdog.h"

enum {
  TASK_STOP, ///< ��������
  TASK_RUN,  ///< ����ֹͣ
};

/** 32768 */
#define TASK_TIMER_CLOCK              CRY_FREQ
/** ����ģʽ5ms */
#define TASK_TIMER_CYCLE_TIME         ((TASK_TIMER_CLOCK*5/(1000)) -1) ///<����ʱ��Ƭ5ms
/** ����ģʽģʽ1s */
#define TASK_TIMER_EMPTY_CYCLE_TIME   ((TASK_TIMER_CLOCK) -1)

#define TIME_ZONE                     8 //������

/**
 * @brief ����ṹ��
 */
typedef struct Task {
  u8 run;                    ///< �������б�ǣ�0-�����У�1����
  u16 timer;                 ///< ��ʱ��
  u16 itv_time;              ///< �������м��ʱ��
  void (*task_hook)(void);   ///< Ҫ���е�������
  u8 evt_on;                 ///< �¼�������־
  u16 evt;                   ///< �¼�����
  u64 evt_time_a;            ///< �¼���ʼʱ��
  u64 evt_time_b;            ///< �¼���ʱ
} Task;

typedef struct TaskTimer {
  u8 status;
  u64 time_a;                   ///< ��ʱ��
  u16 itv_time;                 ///< �������м��ʱ��
  u64 tick;                     ///< ����ʱ�ӵδ�
  u64 sys_tick;                 ///< ϵͳʱ��
  void (*task_sleep)(void);    ///< 
  void (*task_wakeup)(void);   ///<
}TaskTimer;

extern TaskTimer task_timer;

/**
 * @brief ������������,��Ҫ����µ�����������Ҫ�������������
 */
enum {
  TASK_RTU,                  ///< rtu����
  TASK_FLOW_METER,           ///< ����������
  TASK_LCD,                  ///< LCD����
  TASK_BUTTON,               ///< ��������
  TASK_LED,                  ///< LED����
  TASK_ADC,                  ///< AD�ɼ�����
  TASK_FLASH,                ///< FLASH����
  TASK_WATCH_DOG,            ///< ���Ź�����
  TASK_MOTOR,                ///< �������
  TASK_MAX_NUM,
};

/**
 * @brief �¼���������,��Ҫ����µ��¼�������Ҫ�������������
 */
enum {
  EV_NULL,                    ///< ���¼�
  EV_READY,                   ///< ��ʼ�����
  EV_FRAME_RECEIVED,          ///< ֡�������
  EV_EXECUTE,                 ///< ִ���¼�
  EV_FRAME_SENT,              ///< ��������
  EV_TIMEOUT,                 ///< ��ʱ�¼�
  EV_BUTTON_MAIN_PRESS,       ///< �����̰�
  EV_BUTTON_LEFT_PRESS,       ///< ����̰�
  EV_BUTTON_RIGHT_PRESS,      ///< �Ҽ��̰�
  EV_BUTTON_MAIN_LONG_PRESS,  ///< ��������
  EV_BUTTON_LEFT_LONG_PRESS,  ///< �������
  EV_BUTTON_RIGHT_LONG_PRESS, ///< �Ҽ�����
  EV_APPLY_CONFIG,            ///< Ӧ������
  EV_SAVE_CONFIG,             ///< ��������
  EV_MOTOR_START,             ///< �������
  EV_MOTOR_RUN,               ///< �������
  EV_MOTOR_ANGLE_AD_MIN,      ///< ����Ƕ�AD��Сֵ
  EV_MOTOR_ANGLE_AD_MAX,      ///< ����Ƕ�AD��Сֵ
  EV_MOTOR_STOP,              ///< �رյ��
  EV_ADC_ANGLE_RUN,           ///< �����Ƕȱ仯
  EV_ADC_ANGLE_STOP,          ///< �رսǶȱ仯
  EV_UPGRADE,                 ///< �������
};

enum {
  TIMER_STATE_TASK,
  TIMER_STATE_TASK_HANDLER,
  TIMER_STATE_EMPTY,
  TIMER_STATE_EMPTY_HANDLER,
};

enum {
  TIME_TIME,
  TIME_DAY,
  TIME_HOUR,
  TIME_MINUTE,
  TIME_SECOND,
};

extern Task task_list[];     ///< �����б�

//#define TASK_EVENT_POST_DELAY(TASK, EVENT, DELAY)\
//  LOW_POWER_MODE_OFF();\
//  task_event_post_delay(TASK, EVENT, DELAY);

/**
 * @brief ���񴴽�(������Ϣ��ʼ��)
 * @param[in] TASK ��������
 * @param[in] ITV ʱ��Ƭ��С
 * @param[in] TASK_HOOK ������
 * @return �޷���ֵ
 */
#define TASK_CREATE(TASK, ITV, TASK_HOOK)\
  task_list[TASK].timer = ITV;\
  task_list[TASK].itv_time = ITV;\
  task_list[TASK].task_hook = TASK_HOOK;\
  task_event_post(TASK, EV_READY, 0);\
  task_list[TASK].run = TASK_STOP;
  
#if 1
#define LOW_POWER_MODE_ON()\
  if(task_timer.status < TIMER_STATE_EMPTY) {\
    task_timer.status = TIMER_STATE_EMPTY;\
    task_timer.task_sleep();\
    WATCH_DOG_DISABLE();\
    LPM3;\
  }

#define LOW_POWER_MODE_OFF()\
  if(task_timer.status > TIMER_STATE_TASK_HANDLER) {\
    task_timer.status = TIMER_STATE_TASK;\
    task_timer.task_wakeup();\
    WATCH_DOG_ENABLE();\
    LPM3_EXIT;\
  }
#else
#define LOW_POWER_MODE_ON()
#define LOW_POWER_MODE_OFF()
#endif

extern void task_scheduling(void);
extern void task_timer_init(void);
extern u8 task_event_post(u8 task, u16 event, u64 delay);
extern u8 task_event_get(u8 task, u16 *event);
extern void task_setsystime(u64 tm, u8 opt);

#endif