/**
 * @file  button.c
 * @brief ��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#include "button.h"
#define BUTTON_EABLDE  TRUE

/**
 * @brief ����������ʼ��
 * @return �޷���ֵ
 */
void button_init() {
  /* ����IO��ʼ�� */
  BUTTON_SEL &= ~(BUTTON_MAIN_BIT | BUTTON_LEFT_BIT | BUTTON_RIGHT_BIT);
  BUTTON_DIR &= ~(BUTTON_MAIN_BIT | BUTTON_LEFT_BIT | BUTTON_RIGHT_BIT);
  BUTTON_REN |= (BUTTON_MAIN_BIT | BUTTON_LEFT_BIT | BUTTON_RIGHT_BIT);
  BUTTON_OUT |= (BUTTON_MAIN_BIT | BUTTON_LEFT_BIT | BUTTON_RIGHT_BIT);
#if TRUE == BUTTON_EABLDE
  BUTTON_IES |= (BUTTON_MAIN_BIT | BUTTON_LEFT_BIT | BUTTON_RIGHT_BIT);
  BUTTON_IE |= (BUTTON_MAIN_BIT | BUTTON_LEFT_BIT | BUTTON_RIGHT_BIT);
  BUTTON_IFG &= ~(BUTTON_MAIN_BIT | BUTTON_LEFT_BIT | BUTTON_RIGHT_BIT);
#endif
}

/**
 * @brief �����ж�
 * @return �޷���ֵ
 */
#if TRUE == BUTTON_EABLDE
#pragma vector=PORT2_VECTOR
__interrupt void button_isr(void) {
  switch(__even_in_range(P2IV, 16))
  {
    case 0:
      break;
    case 2:
      BUTTON_IFG &= ~BUTTON_RIGHT_BIT;
      //BUTTON_IES ^= BUTTON_RIGHT_BIT;�����½����л�
      LOW_POWER_MODE_OFF();
      break;
    case 4:
      BUTTON_IFG &= ~BUTTON_MAIN_BIT;
      //BUTTON_IES ^= BUTTON_MAIN_BIT;
      LOW_POWER_MODE_OFF();
      break;
    case 6:
      BUTTON_IFG &= ~BUTTON_LEFT_BIT;
      //BUTTON_IES ^= BUTTON_LEFT_BIT;
      LOW_POWER_MODE_OFF();
      break;
    case 8:
      break;
    case 10:
      break;
    case 12:
      break;
    case 14:
      break;
    case 16:
      break;
  }
}
#endif