/**
 * @file  adc_task.h
 * @brief adc��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef ADC_TASK_H_
#define ADC_TASK_H_

#include "../kernel/kernel.h"
#include "../drivers/drivers.h"
#include "flowmeter_task.h"
#include "actuator.h"

#define AD_DETECT_INT_TIME    10///< ADC�ɼ����10ms
#define AD_ANGLE_SAMPLE_SIZE  20///< �Ƕ�AD������С

enum {
  AD_ANGLE_STOP,  ///< ֹͣ�Ƕȸ���
  AD_ANGLE_RUN,   ///< �����Ƕȸ���
};

typedef struct Adc {
  u64 scan_itv_time; ///< adc�ɼ����
  u8 status;
  u16 angle_ad_sample[AD_ANGLE_SAMPLE_SIZE];
  u8 angle_ad_index;
}Adc;

extern Adc adc;
extern void adc_task();

#endif