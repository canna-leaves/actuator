/**
 * @file  led.h
 * @brief led��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef LED_H_
#define LED_H_
#include "../kernel/kernel.h"

#if 1
#define LED_DIR         P7DIR  ///< ���е������������
#define LED_OUT         P7OUT  ///< ���е�����ߵ͵�ƽ����
#define LED_RUN_BIT     BIT5   ///< ���е�
#else
#define LED_DIR         P4DIR  //P7DIR   ///< ���е������������
#define LED_OUT         P4OUT  //P7OUT   ///< ���е�����ߵ͵�ƽ����
#define LED_RUN_BIT     BIT6   //BIT5    ///< ���е�
#endif

extern void led_init();

#endif