/**
 * @file  button.h
 * @brief ������������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef BUTTON_H_
#define BUTTON_H_
#include "../kernel/kernel.h"
#if 1
#define BUTTON_SEL          P2SEL   ///< �����ܽŶ���
#define BUTTON_DIR          P2DIR
#define BUTTON_OUT          P2OUT
#define BUTTON_REN          P2REN
#define BUTTON_IN           P2IN
#define BUTTON_IES          P2IES
#define BUTTON_IE           P2IE
#define BUTTON_IFG          P2IFG
#define BUTTON_MAIN_BIT     BIT2
#define BUTTON_LEFT_BIT     BIT1
#define BUTTON_RIGHT_BIT    BIT0
#else
#define BUTTON_SEL          P4SEL
#define BUTTON_DIR          P4DIR
#define BUTTON_OUT          P4OUT
#define BUTTON_REN          P4REN
#define BUTTON_IN           P4IN
#define BUTTON_MAIN_BIT     BIT7
#define BUTTON_LEFT_BIT     BIT7
#define BUTTON_RIGHT_BIT    BIT7
#endif

/**
 * @brief �����ṹ
 */
typedef struct Button {
  u8 state;    ///< ����״̬
  u8 bit;      ///< ��������
  u64 time_a;  ///< ��ʱ��
}Button;

/**
 * @brief ���ⰴ���ṹ
 */
typedef struct IRButton {
  u8 state;   ///< ����״̬
  u8 bit;     ///< ��������
  u64 time_a; ///< ��ʱ��
}IRButton;

#define BUTTON_PRESS_TIME            10   //�̰���ʱms
#define BUTTON_LONG_PRESS_TIME       800  //������ʱms

/**
 * @brief ��ť��������״̬
 */
enum {
  STATE_BUTTONN_UP,         ///< ����̧��
  STATE_BUTTONN_DOWN,       ///< ����
  STATE_BUTTONN_PRESS,      ///< �̰�
  STATE_BUTTONN_LONG_PRESS, ///< ����
};

/**
 * @brief ��ť����
 */
enum {
  BUTTON_MAIN,    ///< ����
  BUTTON_LEFT,    ///< ���
  BUTTON_RIGHT,   ///< �Ҽ�
  BUTTON_MAX_NUM, ///< ��������
};

/**
 * @brief ������ʼ��
 * @param[in] NO ������
 * @param[in] BIT ��������
 * @return �޷���ֵ
 */
#define BUTTON_CREATE(NO, BIT)\
  button_list[NO].state = STATE_BUTTONN_UP;\
  button_list[NO].bit = BIT;

extern void button_init();
#endif