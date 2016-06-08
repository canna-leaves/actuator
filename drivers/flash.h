/**
 * @file  flash.h
 * @brief flash��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef FLASH_H_
#define FLASH_H_
#include "../kernel/kernel.h"
#include <string.h>

#define FLASH_INFO_ADDR               0x1880   ///< ��Ϣ����ʼ��ַ
#define FLASH_RUN_ADDR                0x5c00   ///< ��������ʼ��ַ
#define FLASH_BACKUP_ADDR             0x25c00  ///< ��������ʼ��ַ
#define FLASH_INFO_SEGMENT_SIZE       128      ///< ��Ϣ��������С
#define FLASH_CODE_SEGMENT_SIZE       512      ///< ��flash������С

extern u8 flash_tmp[FLASH_CODE_SEGMENT_SIZE];
extern u8 flash_write(u8 *addr, u32 offset, u8 *value, u32 len, u16 seg_szie);
extern void flash_write_one_seg(u8 *addr, u8 *value, u16 seg_szie);

/**
 * @brief дflash(����ֹ�ж�)
 * @param[in] ADDR ������ʼ��ַ
 * @param[in] OFFSET ��ַƫ��
 * @param[in] VALUE ����
 * @param[in] LEN ����
 * @param[in] SEG_SIZE ������С
 * @return �޷���ֵ
 */
#define FLASH_WRITE(ADDR, OFFSET, VALUE, LEN, SEG_SIZE)\
  __disable_interrupt();\
  flash_write(ADDR, OFFSET, VALUE, LEN, SEG_SIZE);\
  __enable_interrupt();

#endif