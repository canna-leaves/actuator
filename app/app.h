/**
 * @file  app.h
 * @brief Ӧ�ò�ӿ����
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef APP_H_
#define APP_H_

#include "led_task.h"
#include "debug_uart_task.h"
#include "lcd_task.h"
#include "rtu_task.h"
#include "flowmeter_task.h"
#include "button_task.h"
#include "adc_task.h"
#include "actuator.h"
#include "flash_task.h"
#include "flash_task.h"
#include "register_map.h"
#include "modbus.h"
#include "watchdog_task.h"
#include "upgrade_task.h"
#include "motor_task.h"
#include "protocol.h"
#include <string.h>

/**
 * @brief ������Ϣ�ṹ
 */
#pragma pack(1)
typedef struct Config {
  u64 sys_timer_tick;                 ///< ϵͳʱ��
  u8 actuator_slave;                  ///< ִ�������ڴӻ���
  UartInfo rtu_uart;                  ///< RTU����
  u8 flow_meter_slave;                ///< �����ƴӻ���
  UartInfo flow_meter_uart;           ///< �����ƴ���
  u32 flow_meter_version;             ///< �����ư汾��
  u32 daily_injection;                ///< ����ע
  u8 precision;                       ///< ���ھ���
  u8 auto_adj;                        ///< �Զ�����
  u8 sun_rise_hour;                   ///< ����������ʼ����ʱ��
  u8 light_time;                      ///< ����ʱ��
  u8 open_angle;                      ///< ����
  u8 flip_page_time;                  ///< ����ʱ��
  u8 flow_meter_type;                 ///< ����������
  u16 angle_ad_max;                   ///< ���Ƕ�ADֵ
  u16 angle_ad_min;                   ///< ��С�Ƕ�ADֵ
  u8 lpm_switch;                      ///< �͹���ģʽ����
  u16 motor_time;                     ///< 
  u8 motor_ratio;                     ///< 
  u8 motor_reverse;                   ///<
  u16 flow_meter_req_time_0;
  u16 flow_meter_req_time_1;
  u8 weight_edge;
  u8 precision_ratio;
  u8 flow_compro;                     ///< 
  u8 flow_commode;                    ///< 
  u8 rtu_compro;                      ///< 
  u8 rtu_commode;                     ///< 
  /** ��ʯ��Э����� */
  u16 device_code;
  u16 vendor_code;
  u16 production_year;
  u16 production_month;
  u16 production_day;
  u16 model_h;
  u16 model_m;
  u16 model_l;
  u16 tuning_range;
  u16 serial_number_h;
  u16 serial_number_l;
  u16 protocol;
  u16 device_addr;
  u16 rtu_addr;
  u16 baud_rate;
  u16 ceiling_alarm_enable;
  u16 lower_alarm_enable;
  u16 injection;
  u16 injection_digit;
  u16 injection_max;
  u16 injection_up_delay;
  u16 injection_min;
  u16 injection_down_delay;
  u16 inj_pressure_range_max;
  u16 inj_pressure_range_min;
  u16 inj_pressure_range_digit;
  u16 inj_pressure_max;
  u16 inj_pressure_up_delay;
  u16 inj_pressure_min;
  u16 inj_pressure_down_delay;
  u16 injection_less_digit;
  u16 open_angle_digit;
}Config;
#pragma pack()

#define APP_VERSION                  0x0091L ///< Ӧ�ó���(���)�汾��
#define H_VERSION                    0x0011L ///< Ӳ���汾��
extern Config config;

extern void app_init();
#endif