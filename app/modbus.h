/**
 * @file  modbus.h
 * @brief modbusЭ������(modbus-rtu)
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef MODBUS_H_
#define MODBUS_H_
#include "../kernel/kernel.h"
#include "../drivers/drivers.h"

/**
 * @brief modbus����״̬
 */
enum {
  RTU_ERR,     ///< Э���������
  RTU_REQ,     ///< ����
  RTU_REP,     ///< ��Ӧ
  RTU_REQ_NR,  ///< �����޻�Ӧ
  RTU_SLAVE_ERR,
};

#define WRITE_REGISTERS_POS    7   ///< ���Ĵ�������ʱ,�Ĵ�������ƫ��

extern u8 modbus_handler(u8 slave, u8 master, u8 *in_buf, u16 in_len, u8 *out_buf, u16 *out_len);
extern u8 modbus_rep_handler(u8 *in_buf, u16 in_len, u8 *req_buf, 
                      u8 **out_buf, u16 *out_len);
extern u8 modbus_read_registers_pack(u8 slave, u16 addr, u16 len, 
                              u8 *out_buf, u16 *out_len);
extern u8 modbus_write_register_pack(u8 slave, u16 addr, u16 value, 
                              u8 *out_buf, u16 *out_len);

extern u8 modbus_write_registers_pack(u8 slave, u16 addr, u16 v_len,
                               u8 *out_buf, u16 *out_len);

extern u8 modbus_read_input_registers_pack(u8 slave, u16 addr, u16 len, 
                              u8 *out_buf, u16 *out_len);

#endif