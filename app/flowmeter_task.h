/**
 * @file  flowmeter_task.h
 * @brief ��������������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef FLOWMETER_TASK_H_
#define FLOWMETER_TASK_H_

#include "../kernel/kernel.h"
#include "../drivers/drivers.h"
#include "modbus.h"
#include "actuator.h"
#include "protocol.h"

#define FLOW_METER_REQ_TIME0      5000  ///< Ĭ������ʱ5s
#define FLOW_METER_REQ_TIME1      20000 ///< ���������ʱ20s
#define FLOW_METER_REQ_TIME_MIN   2000  ///< ����ʱ��Сֵ2s
#define FLOW_METER_REQ_TIME_MAX   60000 ///< ����ʱ���ֵ60s
#define FlOW_METER_SLAVE          1     ///< ������Ĭ�ϵ�ַ

/**
 * @brief ������������
 */
enum {
  FLOW_METER_INSTANT_FLOW_REQ,  ///< ˲ʱ��������
  FLOW_METER_PRESSURE_REQ,      ///< ѹ����������
};

enum {
  FLOW_PROTOCOL_AUTO,
  FLOW_PROTOCOL_MODBUS,
  FLOW_PROTOCOL_FUMA,
  FLOW_PROTOCOL_GANGYI,
  FLOW_PROTOCOL_JINDA,
  FLOW_PROTOCOL_MAX,
};

enum {
  FLOW_METER_TYPE_FUMA   = 2,
  FLOW_METER_TYPE_GANGYI = 3,
};

/**
 * @brief �����ַ����
 */
enum {
  FLOW_METER_INSTANT_FLOW_ADDR = 2006,   ///< ˲ʱ���������ַ
  FLOW_METER_PRESSURE_ADDR,              ///< ѹ�����������ַ
};

#define FLOW_METER_INSTANT_FLOW_REG_LEN    6  ///< ˲ʱ�����������ݳ���

#define FLOW_JINDA_REG_ADDR                0
#define FLOW_JINDA_REG_LEN                 4

#define FLOW_METER_DAILY_INJECTION_MAX     9999000
#define FLOW_METER_CUMULA_ADJ_NO_MAX       9999
#define FLOW_METER_WEIGHT_EDGE_MIN         2
#define FLOW_METER_WEIGHT_EDGE_MAX         10
#define FLOW_METER_PRECISION_RATIO         15

/**
 * @brief ����ģʽ
 */
enum {
  FLOW_METER_ADJ_AUTO,     ///< �Զ�
  FLOW_METER_ADJ_MANUAL,   ///< �ֶ�
  FLOW_METER_ONLY_MANUAL,  ///< ֻ���ֶ�
};

#define INSTANT_FLOW_TMP_NUM_MAX           FLOW_METER_WEIGHT_EDGE_MAX
#define USE_MEAN_VALUE                     TRUE
#define FLOW_COM_TIME_OUT                  300000L ///< RTUͨ�ų�ʱ5����
#define DAY_TIME                           (1000L*3600*24)
/**
 * @brief �����ƽṹ
 */
typedef struct FlowMeter {
  u8 slave;                ///< ��ַ
  u8 protocol;             ///< Э������
  u8 req_type;             ///< ��������
  u16 itv_time;            ///< ʱ����
  u64 time_a;              ///< ʱ�����
  u16 req_time_0;          ///< �޵���������
  u16 req_time_1;          ///< �е���������
  fp32 cumula_flow;         ///< �ۼ�����
  //u16 cumula_flow_dec_no; ///< �ۼ�����С��λ��
  u32 instant_flow;        ///< ˲ʱ����
  //u16 instant_flow_dec_no; ///< �ۼ�����С��λ��
#if TRUE==USE_MEAN_VALUE
  u32 instant_flow_tmp[INSTANT_FLOW_TMP_NUM_MAX];
  u32 mean_flow;
#endif
  u32 daily_injection;     ///< ����ע
  u8 precision;            ///< ���ھ���
  u8 precision_ratio;      ///< ���ھ���
  u8 auto_adj;             ///< �Զ�����
  u8 sun_rise_hour;        ///< ����������ʼ����ʱ��
  signed char weight;     ///< Ȩֵ
  u8 weight_edge;          ///< Ȩֵ��ֵ
  u16 version;             ///< �汾��
  u8 type;                 ///< ����
  fp32 com_quality;        ///< ͨ������
  u8 status;               ///< ͨ��״̬
  u64 s_time_a;            ///< ͨ��״̬������
  u8 timeout_cnt;          ///< 
  u8 com_count;
  u8 compro;               ///< ͨ��Э��
  u8 commode;              ///< ͨ��ģʽ
  /** ��ʯ��Э����� */
  u16 injection_up_alarm;
  u16 injection_down_alarm;
  u16 injection_less;
  u16 inj_pressure;
  //u16 inj_up_alarm_count;
  //u16 inj_down_alarm_count;
}FlowMeter;
extern FlowMeter flow_meter;
extern void flowmeter_task();

#endif