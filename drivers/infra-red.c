/**
 * @file  infra-red.c
 * @brief ��������ʵ��
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#include "infra-red.h"

#define RED_R        (IRDA_BIT&IRDA_IN)     ///< �ܽ�״̬

#define KEY_MAIN       0x05                 ///< ��������ң���� ��F(����)
#define KEY_LEFT       0x0D                 ///< ����
#define KEY_RIGHT      0x11                 ///< ����

#define KEY_MAIN1      0x00                 ///< ��������ң���� ��F(����)
#define KEY_LEFT1      0x02                 ///< ����
#define KEY_RIGHT1     0x04                 ///< ����
#define KEY_M1         0x01                 ///< ��M
#define KEY_S1         0x03                 ///< ��S
#define KEY_PLUSH_ONE1 0x05                 ///< ��+1

IRButton ir_button; ///< ���ⰴť

/**
 * @brief ����������ʼ��
 * @return �޷���ֵ
 */
void infra_red_init() {
  IRDA_SEL &= ~IRDA_BIT;
  IRDA_DIR &= ~IRDA_BIT;
  IRDA_REN |= IRDA_BIT;
  IRDA_OUT |= IRDA_BIT;
  IRDA_IES |= IRDA_BIT;
  IRDA_IE |= IRDA_BIT;
  IRDA_IFG &= ~IRDA_BIT;
  
  ir_button.state = STATE_BUTTONN_UP;
  ir_button.bit = 0;
}

/**
 * @brief ��������
 * @param[in] code ����
 * @param[in] repeat �ط����
 * @return �޷���ֵ
 */
void key_icode(u8 code, u8 repeat)
{
  ir_button.bit = code;
  u8 i = 0;
  if(KEY_MAIN == code || KEY_MAIN1 == code) {
    i = BUTTON_MAIN;
  } else if(KEY_LEFT == code || KEY_LEFT1 == code) {
    i = BUTTON_LEFT;
  } else if(KEY_RIGHT == code || KEY_RIGHT1 == code) {
    i = BUTTON_RIGHT;
  } else {
    return;
  }
  if(STATE_BUTTONN_UP == ir_button.state) {
    if(FALSE == repeat) {
      task_event_post(TASK_BUTTON, EV_BUTTON_MAIN_PRESS + i, IRDA_BUTTON_DELAY);
      ir_button.state = STATE_BUTTONN_PRESS;
      ir_button.time_a = task_timer.tick;
    }
  } else if(STATE_BUTTONN_PRESS == ir_button.state) {
    if(task_timer.tick - ir_button.time_a > BUTTON_LONG_PRESS_TIME) {
      task_event_post(TASK_BUTTON, EV_BUTTON_MAIN_LONG_PRESS + i, 0);
      ir_button.state = STATE_BUTTONN_LONG_PRESS;
    } else {
      task_event_post(TASK_BUTTON, EV_BUTTON_MAIN_PRESS + i, IRDA_BUTTON_DELAY);
    }
  }
}

/**
 * @brief ���⴦��
 * @return �޷���ֵ
 */
u8 irda_isr_handler() {
  IRDA_IFG &= ~IRDA_BIT;
  u8 i, j, k = 0;
  u8 code_value=0;
  u8 key_code[4];
  for(i = 0;i < 19;++i)
  {
    DELAY_US(400);              //��ʱ400us
    if(RED_R)                   //9ms���иߵ�ƽ�����ж�Ϊ���ţ��˳��������
    {
      return FALSE;
    }
  }
  while(!RED_R);
  for(i=0;i<5;++i)              //�Ƿ�������
  {
    DELAY_US(500);
    if(!RED_R)
    {
      key_icode(ir_button.bit, TRUE);
      return TRUE;
    }
  }
  while(RED_R);                //�ȴ�4.5ms�ߵ�ƽ��ȥ
  for(i = 0;i < 4;++i)         //����4���ֽڵ�����
  {
    for(j = 0;j < 8;++j)       //ÿ���ֽڵ�����8λ
    {
      
      while(!RED_R);           //�ȴ���ߵ�ƽ
      while(RED_R)             //����ߵ�ƽʱ��
      {
        DELAY_US(100);
        k++;
        if(k > 22)              //�ߵ�ƽʱ����������˳��������
        {
          return FALSE;        
        }
        
      }
      code_value>>=1;          //����һλ����
      if(k >= 7)
      {
        code_value|=0x80;      //�ߵ�ƽʱ�����0.56����Ϊ����1
      }
      k = 0;                   //��ʱ����
    }
    key_code[i]=code_value;    //�ĸ��ֽڵ�����
  }
  if((u8)key_code[2] != (u8)~key_code[3]) {
    return FALSE;
  }
  key_icode(key_code[2], FALSE);      //���ø�ֵ����
  return TRUE;
}

/**
 * @brief �����ж�
 * @return �޷���ֵ
 */
#pragma vector=PORT1_VECTOR
__interrupt void irda_isr(void) {
switch(__even_in_range(P1IV, 16))
  {
    case 0:
      break;
    case 2:
      break;
    case 4:
      if(TRUE == irda_isr_handler()) { //P1.1
        LOW_POWER_MODE_OFF();
      }
      break;
    case 6:
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
      motor_edge_ctl();
      break;
  }
}