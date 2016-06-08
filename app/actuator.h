/**
 * @file  actuator.h
 * @brief ִ��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef ACTUATOR_H_
#define ACTUATOR_H_
#include "../kernel/kernel.h"
#include "../drivers/drivers.h"

/**
 * @brief ִ�������Խṹ
 */
typedef struct Actuator {
  u8 slave;               ///< ִ������ַ
  u8 single_adj_no;       ///< ������ڴ���
  fp32 angle;             ///< ��ǰ�Ƕ�
  fp32 angle_tmp;         ///< 
  u16 angle_ad_max;       ///< ���Ƕ�ADֵ
  u16 angle_ad_min;       ///< ��С�Ƕ�ADֵ
  u16 angle_ad_mid;       ///< �м�ADֵ
  u8 open_angle;          ///< ����
  u16 cumula_adj_no;      ///< �ۼƵ��ڴ���
  u8 single_adj_angle;    ///< ������ڽǶ�
  fp32 voltage;           ///< ��ѹ
  u8 hour;                ///< 
  u8 minute;              ///< 
  u8 second;              ///< 
  u16 pwd_usr0;           ///< 
  u16 pwd_usr1;           ///< 
  u16 pwd_usr2;           ///< 
  u8 pwd_tmp[4];          ///< 
  u8 lpm_switch;          ///< TTREʱ�����͹���
  u16 motor_time;         ///< 
  u8 motor_ratio;         ///< 
  u64 day_time;           ///< 
  /** ��ʯ��Э����� */
  u16 run_state;
  u16 run_time_h;
  u16 run_time_l;
}Actuator;
#define PRODUCT_CODE                0x6002
#define USR0_PREFIX                 0
#define USR1_PREFIX                 1
#define USR2_PREFIX                 2
#define USR_PWD_ROOT                PRODUCT_CODE
extern Actuator actuator;
#define ACTUATOR_SLAVE_NO           1

#endif