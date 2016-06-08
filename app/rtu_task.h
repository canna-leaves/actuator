/**
 * @file  rtu_task.h
 * @brief rtu��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef RTU_TASK_H_
#define RTU_TASK_H_
#include "../kernel/kernel.h"
#include "../drivers/drivers.h"
#include "modbus.h"
#include "protocol.h"
#include <string.h>

#define RTU_COM_TIME_OUT        600000L ///< RTUͨ�ų�ʱ10����

typedef struct Rtu {
  u8 slave;
  u8 status;
  u64 s_time_a;
  u8 com_count;
  u8 compro;               ///< ͨ��Э��
  u8 commode;              ///< ͨ��ģʽ
}Rtu;

extern Rtu rtu;
extern void rtu_task();

#endif