/**
 * @file  register_map.h
 * @brief �Ĵ���ӳ������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef REGISTER_MAP_H_
#define REGISTER_MAP_H_
#include "../kernel/kernel.h"
#include <string.h>

/**
 * @brief �Ĵ�����ַ����
 */
enum {
  /** ��ʯ��Э��ӳ��� */
  MAP_PEC_DEVICE_CODE                  = 0,      ///< �豸����
  MAP_PEC_VENDOR_CODE                  = 1,      ///< ���̴���
  MAP_PEC_PRODUCTION_YEAR              = 2,      ///< ������
  MAP_PEC_PRODUCTION_MONTH             = 3,      ///< ������
  MAP_PEC_PRODUCTION_DAY               = 4,      ///< ������
  MAP_PEC_MODEL_H                      = 5,      ///< �ͺ�0
  MAP_PEC_MODEL_M                      = 6,      ///< �ͺ�1
  MAP_PEC_MODEL_L                      = 7,      ///< �ͺ�2
  MAP_PEC_TUNING_RANGE                 = 8,      ///< ��������
  MAP_PEC_SERIAL_NUMBER_H              = 9,      ///< ���
  MAP_PEC_SERIAL_NUMBER_L              = 0xA,    ///< ���
  MAP_PEC_PROTOCOL                     = 0xC,    ///< ͨѶЭ�飬"0"ΪMODBUS RTU
  MAP_PEC_DEVICE_ADDR                  = 0xD,    ///< Դ��ַ���豸��ַ���Ǳ�ͨѶ��ַ��
  MAP_PEC_RTU_ADDR                     = 0xE,    ///< Ŀ��վ��ַ��RTU��ַ
  MAP_PEC_BAUD_RATE                    = 0xF,    ///< ͨ�Ų�����
  MAP_PEC_CEILING_ALARM_ENABLE         = 0x10,   ///< ���ޱ���ʹ��
  MAP_PEC_LOWER_ALARM_ENABLE           = 0x11,   ///< ���ޱ���ʹ��
  MAP_PEC_INJECTION                    = 0x12,   ///< עˮ�����趨ֵ
  MAP_PEC_INJECTION_DIGIT              = 0x13,   ///< עˮ����С��λ
  MAP_PEC_INJECTION_MAX                = 0x14,   ///< עˮ��������ֵ
  MAP_PEC_INJECTION_UP_DELAY           = 0x15,   ///< עˮ����Խ������ʱ
  MAP_PEC_INJECTION_MIN                = 0x16,   ///< עˮ��������ֵ
  MAP_PEC_INJECTION_DOWN_DELAY         = 0x17,   ///< עˮ����Խ������ʱ
  MAP_PEC_INJ_PRESSURE_RANGE_MAX       = 0x18,   ///< עˮѹ���������
  MAP_PEC_INJ_PRESSURE_RANGE_MIN       = 0x19,   ///< עˮѹ����С����
  MAP_PEC_INJ_PRESSURE_RANGE_DIGIT     = 0x1A,   ///< עˮѹ��С��λ
  MAP_PEC_INJ_PRESSURE_MAX             = 0x1B,   ///< עˮѹ��������ֵ
  MAP_PEC_INJ_PRESSURE_UP_DELAY        = 0x1C,   ///< עˮѹ��Խ������ʱ
  MAP_PEC_INJ_PRESSURE_MIN             = 0x1D,   ///< עˮѹ��������ֵ
  MAP_PEC_INJ_PRESSURE_DOWN_DELAY      = 0x1E,   ///< עˮѹ��Խ������ʱ
  MAP_PEC_INJECTION_LESS_DIGIT         = 0x1F,   ///< Ƿע��С��λ
  MAP_PEC_OPEN_ANGLE_DIGIT             = 0x20,   ///< ������С��λ
  /** ��ʯ��Э����Ϣ���� */
  MAP_PEC_INJECTION_UP_ALARM           = 0xFE,   ///< ���ޱ���״̬
  MAP_PEC_INJECTION_DOWN_ALARM         = 0xFF,   ///< ���ޱ���״̬
  MAP_PEC_RUN_STATE                    = 0x100,  ///< ����״̬
  MAP_PEC_RUN_TIME_H                   = 0x101,  ///< �豸����ʱ�䣨�ߣ�
  MAP_PEC_RUN_TIME_L                   = 0x102,  ///< �豸����ʱ�䣨�ͣ�
  MAP_PEC_INJECTION_LESS               = 0x103,  ///< Ƿע��
  MAP_PEC_INJ_PRESSURE                 = 0x104,  ///< עˮѹ��
  MAP_PEC_OPEN_ANGLE                   = 0x105,  ///< ���ſ���
  MAP_PEC_INSTANT_FLOW                 = 0x106,  ///< עˮ����˲ʱ��
  MAP_PEC_CUMULA_FLOW_H                = 0x107,  ///< עˮ�����ۼ������ߣ�
  MAP_PEC_CUMULA_FLOW_L                = 0x108,  ///< עˮ�����ۼ������ͣ�
  /** �Զ���ӳ��� */
  MAP_BATTERY_VOLTAGE                  = 300,    ///< 40001 ��ص�ѹ
  MAP_AUTO_ADJ_NO                      = 301,    ///< 40002 �Զ����ڴ���
  MAP_RTU_COM_STATE                    = 302,    ///< 40003 RTUͨ��״̬
  MAP_FLOW_METER_COM_STATE             = 303,    ///< 40004 ������ͨ��״̬
  MAP_HOUR                             = 304,    ///< 40005 ʱ
  MAP_MINUTE                           = 305,    ///< 40006 ��
  MAP_SECOND                           = 306,    ///< 40007 ��
  MAP_ANGLE                            = 307,    ///< 40008 �Ƕ�
  MAP_INSTANT_FLOW_H                   = 308,    ///< 40009 ˲ʱ����H
  MAP_INSTANT_FLOW_L                   = 309,    ///< 40010 ˲ʱ����L
  MAP_DAILY_INJECTION_H                = 310,    ///< 40011 ����עH
  MAP_DAILY_INJECTION_L                = 311,    ///< 40012 ����עL
  MAP_ACTUATOR_SLAVE                   = 312,    ///< 40013 ִ������ַ
  MAP_LCD_LIGHT_TIME                   = 313,    ///< 40014 ����ʱ��
  MAP_OPENING_VALUE                    = 314,    ///< 40015 ����ֵ
  MAP_PRECISION                        = 315,    ///< 40016 ���ھ���
  MAP_COM_QUALITY                      = 316,    ///< 40017 ͨ������
  MAP_CUMULA_FLOW_H                    = 317,    ///< 40018 �ۼ�ע����(Float Inverse)H
  MAP_CUMULA_FLOW_L                    = 318,    ///< 40019 �ۼ�ע����(Float Inverse)L
  MAP_FLOW_METER_TYPE                  = 319,    ///< 40020 ����������
  MAP_FLOW_METER_VER                   = 320,    ///< 40021 �����ư汾
  MAP_FLOW_METER_SLAVE                 = 321,    ///< 40022 �����ƴӻ���
  MAP_FLOW_METER_UART_BAUD_H           = 322,    ///< 40023 �����ƴ��ڲ�����H
  MAP_FLOW_METER_UART_BAUD_L           = 323,    ///< 40024 �����ƴ��ڲ�����L
  MAP_FLOW_METER_UART_BYTE             = 324,    ///< 40025 �����ƴ�������λ
  MAP_FLOW_METER_UART_PARITY           = 325,    ///< 40026 �����ƴ���У��λ
  MAP_FLOW_METER_UART_STOP_BITS        = 326,    ///< 40027 �����ƴ���ֹͣλ
  MAP_RTU_SLAVE                        = 327,    ///< 40028 RTU�ӻ���ַ
  MAP_RTU_UART_BAUD_H                  = 328,    ///< 40029 RTU���ڲ�����H
  MAP_RTU_UART_BAUD_L                  = 329,    ///< 40030 RTU���ڲ�����L
  MAP_RTU_UART_BYTE                    = 330,    ///< 40031 RTU��������λ
  MAP_RTU_UART_PARITY                  = 331,    ///< 40032 RTU����У��λ
  MAP_RTU_UART_STOP_BITS               = 332,    ///< 40033 RTU����ֹͣλ
  MAP_AUTO_ADJ                         = 333,    ///< 40034 �Զ����ڱ�־λ
  MAP_SINGLE_ADJ_NO                    = 334,    ///< 40035 �����������ڴ���
  MAP_SCREEN_FLIP_TIME                 = 335,    ///< 40036 ��Ļ����ʱ��
  MAP_USR_NORMAL_PWD                   = 336,    ///< 40037 ��ͨ�û�����
  MAP_USR_TEST_PWD                     = 337,    ///< 40038 �����û�����
  MAP_USR_SUP_PWD                      = 338,    ///< 40039 �����û�����
  MAP_SAVE_CONF                        = 339,    ///< 40040 д�����
  MAP_REBOOT                           = 340,    ///< 40041 ����
  MAP_MOTOR_REMOTE_CTL                 = 400,    ///< 40101 ���ң��
  MAP_MOTOR_ADJ                        = 401,    ///< 40102 ����Ƕ�У׼
  MAP_MOTOR_TEST                       = 402,    ///< 40103 �������
  MAP_MOTOR_RATIO                      = 403,    ///< 40104 �������ռ�ձ�
  MAP_MOTOR_TIME                       = 404,    ///< 40105 �������ʱ��
  MAP_LPM_SWITCH                       = 405,    ///< 40106 �������
  MAP_MOTOR_REVERSE                    = 406,    ///< 40107 ����
  MAP_FLOW_POWER                       = 407,    ///< 40108 �����Ƶ�Դ
  MAP_FLOW_REQ_TIME0                   = 408,    ///< 40109 �޵���������
  MAP_FLOW_REQ_TIME1                   = 409,    ///< 40110 �е���������
  MAP_FLOW_MOTOR_WEIGHT_EDGE           = 410,    ///< 40111 �����Ƶ���Ȩֵ
  MAP_PRECISION_RATIO                  = 411,    ///< 40112 �����ƾ���Ȩֵ
  MAP_H_VERSION                        = 412,    ///< 40113 Ӳ���汾
  MAP_S_VERSION                        = 413,    ///< 40114 ����汾
  MAP_FLOW_COMPRO                      = 414,    ///< 40115 ������ͨ��Э��
  MAP_FLOW_COMMODE                     = 415,    ///< 40116 ������ͨ�ŷ�ʽ
  MAP_RTU_COMPRO                       = 416,    ///< 40117 RTUͨ��Э��
  MAP_RTU_COMMODE                      = 417,    ///< 40118 RTUͨ�ŷ�ʽ
  MAP_UPGRADE_ADDR                     = 1000,   ///< 41001 ����
};

extern u8 read_registers(u8 slave, u16 addr, u16 len, u8 *out_buf);
extern u8 write_registers(u8 slave, u16 addr, u16 len, u8 *in_buf);

#endif