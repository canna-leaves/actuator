/**
 * @file  led.c
 * @brief led����ʵ��
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#include "led.h"

/**
 * @brief led������ʼ��
 * @return �޷���ֵ
 */
void led_init() {
  LED_DIR |= LED_RUN_BIT;
  LED_OUT |= LED_RUN_BIT;
}