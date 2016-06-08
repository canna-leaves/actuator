/**
 * @file  upgrade_task.h
 * @brief ������������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef UPGRADE_TASK_H_
#define UPGRADE_TASK_H_
#include "../kernel/kernel.h"
#include "../drivers/drivers.h"
#include <string.h>

/**
 * @brief ��������ṹ
 */
typedef struct UpgradeInfo {
  u8 slave;          ///< �ӻ���
  u16 pack_index;    ///< ��ǰ����������
  u32 file_size;     ///< �����ļ���С
  u32 file_sum;      ///< �����ļ�У���
}UpgradeInfo;

extern UpgradeInfo upgrade_info;
extern void upgrade_task();
extern void upgrade_action();
extern u8 upgrade_map_write_registers(u8 slave, u8 *in_buf, u16 in_len);
extern u8 is_upgrade_pack(u8 *in_buf, u16 in_len);

#endif