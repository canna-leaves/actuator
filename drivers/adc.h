/**
 * @file  adc.h
 * @brief adc��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef ADC_H_
#define ADC_H_
#include "../kernel/kernel.h"

#define ANGLE_R_AD_SEL      P6SEL   ///< adc�ܽŶ���
#define AD_24V_SEL          P7SEL

#define ANGLE_R_AD_BIT      BIT7
#define AD_24V_BIT          BIT7

#define ANGLE_R_AD_VALUE    ADC12MEM7
#define AD_24V_VALUE        ADC12MEM15

/**
 * @brief ͨ������
 */
enum {
  AD_CHANNEL_ANGLE_R,  ///< �Ƕ�AD
  AD_CHANNEL_24V,      ///< ��ѹAD
  AD_CHANNEL_MAX_NUM,  ///< ���ͨ����
};

extern u16 ad_channels[AD_CHANNEL_MAX_NUM];
extern void adc12_init();
extern void adc12_start();

#endif