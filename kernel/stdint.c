/**
 * @file  stdint.c
 * @brief ��������ת������ʵ��
 * @version 1.0
 * @author ygz
 * @date   2015.7.1
 */
#include "stdint.h"
#include <string.h>

/**
 * @brief ����������ת��Ϊ16λBCD��ʽ
 * @param[in] n ��Ҫת��������
 * @retval ת�����BCD��
 */
u16 u16_to_bcd(u16 n) {
  if (n > 9999) {
    return 0;
  }
  return ((n/1000)<<12)|((n/100%10)<<8)|((n%100/10)<<4)|(n%10);
}

/**
 * @brief ����������ת��Ϊ8λBCD��ʽ
 * @param[in] n ��Ҫת��������
 * @retval ת�����BCD��
 */
u8 u8_to_bcd(u8 n) {
  if (n > 99) {
    return 0;
  }
  return (((n%100/10)<<4)|(n%10));
}

/**
 * @brief ��BCD��ת��Ϊ8λ��������
 * @param[in] bcd ��Ҫת����BCD��
 * @retval ת�������������
 */
u8 bcd_to_u8(u8 bcd)
{
  return (bcd>>4)*10+(bcd&0x0F);
}

/**
 * @brief ��BCD��ת��Ϊ16λ��������
 * @param[in] bcd ��Ҫת����BCD��
 * @retval ת�������������
 */
u16 bcd_to_u16(u16 bcd)
{
  return ((u16)bcd_to_u8(bcd>>8))*100+bcd_to_u8(bcd&0xFF);
}

/**
 * @brief ��u8����ת��Ϊu64����,�������
 * @param[in] value ��Ҫת����u8����
 * @retval ת�����u64����
 */
u64 u8_to_u64_big(u8 *value) {
  return value[7] | ((u16)value[6]<<8) | ((u32)value[5]<<16) | ((u32)value[4]<<24) | ((u64)value[3]<<32) | ((u64)value[2]<<40) | ((u64)value[1]<<48) | ((u64)value[0]<<56);
}

/**
 * @brief ��u8����ת��Ϊu32����,�������
 * @param[in] value ��Ҫת����u8����
 * @retval ת�����u32����
 */
u32 u8_to_u32_big(u8 *value) {
  return value[3] | ((u16)value[2]<<8) | ((u32)value[1]<<16) | ((u32)value[0]<<24);
}

/**
 * @brief ��u8����ת��Ϊu16����,�������
 * @param[in] value ��Ҫת����u8����
 * @retval ת�����u16����
 */
u16 u8_to_u16_big(u8 *value) {
  return value[1] | (u16)(value[0]<<8);
}

/**
 * @brief ��u64����ת��Ϊu8����,�������
 * @param[in] value ��Ҫת����u64����
 * @param[out] out_buf ת�����u8����
 * @return �޷���ֵ
 */
void u64_to_u8_big(u64 value, u8 *out_buf) {
  out_buf[0] = (value>>56)&0xFF;
  out_buf[1] = (value>>48)&0xFF;
  out_buf[2] = (value>>40)&0xFF;
  out_buf[3] = (value>>32)&0xFF;
  out_buf[4] = (value>>24)&0xFF;
  out_buf[5] = (value>>16)&0xFF;
  out_buf[6] = (value>>8)&0xFF;
  out_buf[7] = (value)&0xFF;
}

/**
 * @brief ��u32����ת��Ϊu8����,�������
 * @param[in] value ��Ҫת����u32����
 * @param[out] out_buf ת�����u8����
 * @return �޷���ֵ
 */
void u32_to_u8_big(u32 value, u8 *out_buf) {
  out_buf[0] = (value>>24)&0xFF;
  out_buf[1] = (value>>16)&0xFF;
  out_buf[2] = (value>>8)&0xFF;
  out_buf[3] = (value)&0xFF;
}

/**
 * @brief ��u16����ת��Ϊu8����,�������
 * @param[in] value ��Ҫת����u16����
 * @param[out] out_buf ת�����u8����
 * @return �޷���ֵ
 */
void u16_to_u8_big(u16 value, u8 *out_buf) {
  out_buf[0] = (value>>8)&0xFF;
  out_buf[1] = (value)&0xFF;
}

void fp32_to_u8_h_big(fp32 value, u8 *out_buf) {
  u8 tmp[4];
  memcpy(tmp, &value, sizeof(tmp));
  out_buf[0] = tmp[3];
  out_buf[1] = tmp[2];
}

void fp32_to_u8_l_big(fp32 value, u8 *out_buf) {
  u8 tmp[4];
  memcpy(tmp, &value, sizeof(tmp));
  out_buf[0] = tmp[1];
  out_buf[1] = tmp[0];
}

void fp32_to_u8_big(fp32 value, u8 *out_buf) {
  u8 tmp[4];
  memcpy(tmp, &value, sizeof(tmp));
  out_buf[0] = tmp[3];
  out_buf[1] = tmp[2];
  out_buf[2] = tmp[1];
  out_buf[3] = tmp[0];
}

fp32 u8_to_fp32_big(u8 *value) {
  u8 tmp[4];
  tmp[0] = value[3];
  tmp[1] = value[2];
  tmp[2] = value[1];
  tmp[3] = value[0];
  fp32 rc = 0.0f;
  memcpy(tmp, &rc, sizeof(fp32));
  return rc;
}

u32 fp32_2_u32(fp32 value, u8 digit) {
  u8 i;
  if(digit > 5) {
    return 0;
  }
  for(i=0;i < digit;++i) {
    value *= 10;
  }
  return (u32)value;
}

u16 fp32_2_u16_h(fp32 value, u8 digit) {
  u8 i;
  if(digit > 5) {
    return 0;
  }
  for(i=0;i < digit;++i) {
    value *= 10;
  }
  return ((u32)value)>>16;
}

u16 fp32_2_u16_l(fp32 value, u8 digit) {
  u8 i;
  if(digit > 5) {
    return 0;
  }
  for(i=0;i < digit;++i) {
    value *= 10;
  }
  return (u16)value;
}

u8 fp32_2_u8(fp32 value, u8 digit) {
  u8 i;
  if(digit > 5) {
    return 0;
  }
  for(i=0;i < digit;++i) {
    value *= 10;
  }
  return (u8)value;
}

fp32 u16_2_fp32(u16 value, u8 digit) {
  u8 i;
  if(digit > 5) {
    return 0;
  }
  fp32 v = (fp32)value;
  for(i=0;i < digit;++i) {
    v /= 10;
  }
  return v;
}