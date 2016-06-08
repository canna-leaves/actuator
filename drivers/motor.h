/**
 * @file  motor.h
 * @brief �����������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef MOTOR_H_
#define MOTOR_H_
#include "../kernel/kernel.h"
#include "adc.h"
#define ANGLE_INT_SEL              P1SEL  ///< ��λ���ؼĴ���
#define ANGLE_INT_DIR              P1DIR
#define ANGLE_INT_REN              P1REN
#define ANGLE_INT_OUT              P1OUT
#define ANGLE_INT_IN               P1IN
#define ANGLE_INT_IES              P1IES
#define ANGLE_INT_IE               P1IE
#define ANGLE_INT_IFG              P1IFG
#define ANGLE_INT_BIT              BIT7

#define ANGLE_DIR_SEL              P1SEL  ///< ���ת��������ƼĴ���
#define ANGLE_DIR_DIR              P1DIR
#define ANGLE_DIR_REN              P1REN
#define ANGLE_DIR_OUT              P1OUT
#define ANGLE_DIR_BIT              BIT7

#define ANGLE_PWR_SWITCH_SEL       P6SEL ///< ��λ���ص�Դ���ƼĴ���
#define ANGLE_PWR_SWITCH_DIR       P6DIR
#define ANGLE_PWR_SWITCH_REN       P6REN
#define ANGLE_PWR_SWITCH_OUT       P6OUT
#define ANGLE_PWR_SWITCH_BIT       BIT4
#define ANGLE_PWR_SWITCH_ON()      ANGLE_PWR_SWITCH_OUT |= ANGLE_PWR_SWITCH_BIT   //����
#define ANGLE_PWR_SWITCH_OFF()     ANGLE_PWR_SWITCH_OUT &= ~ANGLE_PWR_SWITCH_BIT

#define BTN_IN1_SEL                P2SEL  ///< �����������Ĵ���
#define BTN_IN1_DIR                P2DIR
#define BTN_IN1_REN                P2REN
#define BTN_IN1_OUT                P2OUT
#define BTN_IN1_BIT                BIT3

#define BTN_IN2_SEL                P2SEL  ///< �����������Ĵ���
#define BTN_IN2_DIR                P2DIR
#define BTN_IN2_REN                P2REN
#define BTN_IN2_OUT                P2OUT
#define BTN_IN2_BIT                BIT4

#define BTN_INH_SEL                P2SEL  ///< �����Դ�Ĵ���
#define BTN_INH_DIR                P2DIR
#define BTN_INH_REN                P2REN
#define BTN_INH_OUT                P2OUT
#define BTN_INH_BIT                BIT5

#define MOTOR_EDGE_MID             (ANGLE_INT_IN & ANGLE_INT_BIT) ///< δ������λ����

/**
 * @brief ������Խṹ
 */
typedef struct Motor {
  u32 run_duration;  ///< �������ʱ��
  u64 time_a;        ///< ��ʱ��
  u64 stop_time;     ///< ���ֹͣ����ʱ��
  u8 duty_ratio;     ///< ռ�ձ�
  u8 duty_ratio_tmp; ///< ��ʱֵ
  u8 dir;            ///< ת������
  u8 switch_dir;     ///< ��λ����λ��
  u8 status;         ///< �������״̬
  u8 edge_switch;    ///< ��λ����״̬
  u8 mode;           ///< �������ģʽ
  u8 adj_count_left; ///< ����λ��ײ����
  u8 adj_count_right;///< ����λ��ײ����
  u16 ad_tmp;        ///< adֵ
  u8 reverse;        ///< ����
}Motor;

enum {
  MOTOR_DIR_SHUT,
  MOTOR_DIR_OPEN,
};

enum {
  MOTOR_STOP,
  MOTOR_RUN,
};

enum {
  MOTOR_ANGLE_MAN,
  MOTOR_ANGLE_MAN_BACK,
  MOTOR_ANGLE_POWER,
  MOTOR_ANGLE_POWER_BACK,
  MOTOR_ANGLE_ADJ,
  MOTOR_ANGLE_ADJ_BACK,
  MOTOR_TEST,
  MOTOR_TEST_BACK,
};

enum {
  EDGE_SWITCH_UP,
  EDGE_SWITCH_DOWN,
};

#define MOTOR_ANGLE_AD_MIN_OFFSET   30
#define MOTOR_ANGLE_AD_MAX_OFFSET   10
#define MOTOR_ADJ_COUNT_MAX         100
#define MOTOR_ADJ_COUNT_MIN         2
#define MOTOR_ADJ_COUNT_DEF         2
#define MOTOR_RUN_DURATION_TIME_MIN 300
#define MOTOR_RUN_DURATION_TIME_MAX 300000                       ///< ���Ĭ������ʱ��2s
#define MOTOR_WAVE_TICK_TIME        TASK_TIMER_CLOCK/10000       ///< PWMʱ��,����ʲô��˼��,һ���ٿ�
#define MOTOR_WAVE_DUTY_RATIO       (100 * MOTOR_WAVE_TICK_TIME-1)  ///< ���Ĭ��ռ�ձ�50%
#define MOTOR_WAVE_CYCLE_TIME       (100 * MOTOR_WAVE_TICK_TIME-1) ///< PWM����
#define MOTOR_WAVE_DUTY_RATIO_MIN   20   ///< 10%
#define MOTOR_WAVE_DUTY_RATIO_MAX   80   ///< 80%
#define MOTOR_WAVE_DUTY_RATIO_DEF   60   ///< 50%
#define MOTOR_STOP_DELAY            200  ///< 200ms
#define MOTOR_ADJ_STOP_DELAY        3000 ///< 3000ms
#define MOTOR_ADJ_DELAY             1000 ///< 100ms

extern Motor motor;
extern void motor_init();
extern u8 motor_ctl(u8 run, u8 dir, u8 ratio, u32 duration, u8 mode);
extern void motor_edge_ctl();
extern void motor_timer_start();
extern void motor_stop();

#endif