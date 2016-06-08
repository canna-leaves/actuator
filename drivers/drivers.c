/**
 * @file  drivers.c
 * @brief ������ʼ������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#include "drivers.h"

/**
 * @brief ������ʼ��
 * @return �޷���ֵ
 */
void drivers_init() {
  adc12_init();
  button_init();
  infra_red_init();
  lcd_init();
  led_init();
  motor_init();
  uart_init();
}
