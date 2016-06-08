/**
 * @file  upgrade_task.c
 * @brief ��������ģ��ʵ��
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#include "upgrade_task.h"
#include "register_map.h"

#pragma segment="ROMCODE"                            
#pragma segment="RAMCODE"

/**
 * @brief ����copy
 * @param[out] dst Ŀ�ĵ�ַ
 * @param[in] src Դ��ַ
 * @param[in] len ����
 * @return �޷���ֵ
 * @note �洢��RAMCODE��
 */
#pragma location="RAMCODE"
void ramcpy(u8 *dst, u8 *src, u32 len) {
  if(0 == len) {
    return;
  }
  u32 i;
  for(i = 0;i < len;++i) {
    *dst++ = *src++;
  }
}
  
UpgradeInfo upgrade_info;  ///< ������������
void upgrade_action();

/**
 * @brief дflash
 * @param[in] addr ������ʼ��ַ
 * @param[in] offset ��ַƫ��
 * @param[in] value ����
 * @param[in] len ���ݳ���
 * @param[in] seg_size ������С
 * @return �޷���ֵ
 * @note �洢��RAMCODE��
 */
u8 upgrade_flash_write(u8 *addr, u32 offset, u8 *value, u32 len, u16 seg_size);

/**
 * @brief �����������
 * @return �޷���ֵ
 * @note �洢��RAMCODE��
 */
#pragma location="RAMCODE"
void upgrade_task() {
  int i;
  for(i = 0;i < 30;++i) {
    LED_OUT ^= LED_RUN_BIT;
    DELAY_MS(100);
  }
  LED_OUT &= ~LED_RUN_BIT;
  upgrade_flash_write((u8 *)FLASH_RUN_ADDR, 0, (u8 *)FLASH_BACKUP_ADDR, upgrade_info.file_size, FLASH_CODE_SEGMENT_SIZE);
  for(i = 0;i < 30;++i) {
    LED_OUT ^= LED_RUN_BIT;
    DELAY_MS(100);
  }
  PMMCTL0 = PMMPW + PMMSWBOR;//��Դ���Ƹ�λ
  WATCH_DOG_ENABLE();
  WDTCTL =WDT_ARST_1000;
  while(1) {
    LED_OUT ^= LED_RUN_BIT;
    DELAY_MS(100);
  }
  //__enable_interrupt();
}

/**
 * @brief д��������
 * @param[in] addr ������ʼ��ַ
 * @param[in] value ����
 * @param[in] seg_szie ������С
 * @return �޷���ֵ
 * @note �洢��RAMCODE��
 */
#pragma location="RAMCODE"
void upgrade_flash_write_one_seg(u8 *addr, u8 *value, u16 seg_szie) {
  u16 i;
  while(BUSY == (FCTL3&BUSY));
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY+ERASE;                      // Set Erase bit
  *(u16 *)addr = 0;                         // Dummy write to erase Flash seg
  while(BUSY == (FCTL3&BUSY));
  FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

  for (i = 0; i < seg_szie; i++)
  {
    *(addr++) = *(value++);                 // Write value to flash
    while(!(WAIT & FCTL3));                 // Test wait until ready for next byte
  }
  FCTL1 = FWKEY;                            // Clear WRT bit
  while(BUSY == (FCTL3&BUSY));
  FCTL3 = FWKEY+LOCK;                       // Set LOCK bit
}

#pragma location="RAMCODE"
u8 upgrade_flash_write(u8 *addr, u32 offset, u8 *value, u32 len, u16 seg_size) {
  if(0 == len) {
    return FALSE;
  }
  u16 i;
  //__disable_interrupt();                    // 5xx Workaround: Disable global
                                            // interrupt while erasing. Re-Enable
                                            // GIE if needed
  //u8 tmp[FLASH_SEGMENT_SIZE];
  u8 *flash_addr = addr + (offset/seg_size*seg_size);
  u32 count_left = offset%seg_size;
  u32 count_right = (offset + len)%seg_size;
  
  u32 seg_num = ((offset + len)/seg_size - offset/seg_size);
  
  ramcpy(flash_tmp, flash_addr, seg_size);
  if(seg_size - count_left > len) {
    ramcpy(flash_tmp + count_left, value, len);
    value += len;
  } else {
    ramcpy(flash_tmp + count_left, value, seg_size - count_left);
    value += seg_size - count_left;
  }
  upgrade_flash_write_one_seg(flash_addr, flash_tmp, seg_size);
  flash_addr += seg_size;
  
  for(i = 1;i < seg_num;++i) {
    upgrade_flash_write_one_seg(flash_addr, value, seg_size);
    flash_addr += seg_size;
    value += seg_size;
  }
  
  if(0 != count_right && seg_size - count_left < len) {
    ramcpy(flash_tmp, flash_addr, seg_size);
    ramcpy(flash_tmp, value, count_right);
    upgrade_flash_write_one_seg(flash_addr, flash_tmp, seg_size);
    flash_addr += seg_size;
    value += count_right;
  }
  //__enable_interrupt();
  return TRUE;
}
           
#define MAX_IMAGE_SZIE            0x14000                    ///< ���֧��80k��������
#define REGISTER_LEN              125                        ///< �Ĵ�������
#define PACK_SIZE                 (2*(REGISTER_LEN - 1))     ///< ��Ч���ݰ���С
#define MAX_PACK_INDEX            (MAX_IMAGE_SZIE/PACK_SIZE) ///< ��������

/**
 * @brief �����������أ���������code����
 * @param[in] slave �ӻ���ַ
 * @param[in] in_buf ����
 * @param[in] in_len ����
 * @retval TRUE �ɹ�
 * @retval FALSE ʧ��
 * @note ����modbus-rtuЭ�飬��ʼӳ���ַΪ40001(1000) �Ĵ�����СΪREGISTER_LEN
 */
u8 upgrade_map_write_registers(u8 slave, u8 *in_buf, u16 in_len) {
  if(REGISTER_LEN != in_len) {
    return FALSE;
  }
  u16 pack_index = in_buf[0]<<8 | in_buf[1];
  if(0 == pack_index) {
    upgrade_info.pack_index = 0;
    upgrade_info.slave = slave;
    in_buf += sizeof(u16);
    upgrade_info.file_size = u8_to_u32_big(in_buf);
    in_buf += sizeof(u32);
    upgrade_info.file_sum = u8_to_u32_big(in_buf);
    if(upgrade_info.file_size > MAX_IMAGE_SZIE) {
      return FALSE;
    }
  } else if(pack_index <= MAX_PACK_INDEX) {
    if(upgrade_info.slave != slave || pack_index != upgrade_info.pack_index + 1) {
      return FALSE;
    }
    __disable_interrupt();
    flash_write((u8 *)FLASH_BACKUP_ADDR, PACK_SIZE * (pack_index - 1), in_buf + sizeof(u16), PACK_SIZE, FLASH_CODE_SEGMENT_SIZE);
    __enable_interrupt();
    upgrade_info.pack_index = pack_index;
    if((u32)pack_index * PACK_SIZE >= upgrade_info.file_size) {
      __disable_interrupt();
      WATCH_DOG_DISABLE();
      u32 sum0 = 0;
      u8 *addr0 = (u8 *)FLASH_BACKUP_ADDR;
      while((u32)addr0 < FLASH_BACKUP_ADDR + upgrade_info.file_size) {
        sum0 += *addr0++;
      }
      WATCH_DOG_ENABLE();
      __enable_interrupt();
      if(sum0 != upgrade_info.file_sum) {
        return FALSE;
      }
      upgrade_info.pack_index = 0xFFFF;
      task_event_post(TASK_FLASH, EV_UPGRADE, 1000);
    }
  } else {
    return FALSE;
  }
  return TRUE;
}

/**
 * @brief ������������flash copy���Ĵ���copy��ram�в�����
 * @return �޷���ֵ
 * @note upgrade_task��ʼǰ�����ֹ���Ź�
 */
void upgrade_action() {
  u8 *rom_start = (u8 *)__segment_begin("ROMCODE");
  u8 *ram_start = (u8 *)__segment_begin("RAMCODE");
  u8 *ram_end = (u8 *)__segment_end("RAMCODE");
  u32 ram_len =  (u32)(ram_end) - (u32)(ram_start);
  __disable_interrupt();
  WATCH_DOG_DISABLE();  //��������code���򲿷�ֹͣ���Ź�
  memcpy(ram_start, rom_start, ram_len);
  upgrade_task();
}

u8 is_upgrade_pack(u8 *in_buf, u16 in_len) {
  u16 addr = ((in_buf[2] << 8) | in_buf[3]);
  if(0x03 == in_buf[1] && MAP_H_VERSION == addr) {
    
  } else if(0x10 == in_buf[1] && MAP_UPGRADE_ADDR == addr) {
    
  } else {
    return FALSE;
  }
  return TRUE;
}