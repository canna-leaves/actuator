/**
 * @file  uart.h
 * @brief �����������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef UART_H_
#define UART_H_

#include "../kernel/kernel.h"

#define UART_FBRCLK        CRY_FREQ          ///< 32768
#define MAX_BUF_SIZE       300               ///< ���ڻ�������С

/**
 * @brief ����״̬����
 */
enum UART_STATE
{
    //STATE_RX_INIT,              ///< Receiver is in initial state.
    STATE_RX_IDLE,              ///< Receiver is in idle state.
    STATE_RX_RCV,               ///< Frame is beeing received.
    //STATE_RX_ERROR,             ///< If the frame is invalid.
    //STATE_TX_IDLE,              ///< Transmitter is in idle state.
    STATE_TX_XMIT,              ///< Transmitter is in transfer state.
};

#define UART_0              0  ///< ����0
#define UART_1              1  ///< ����1
#define UART_2              2  ///< ����2
#define UART_3              3  ///< ����3
#define UART_MAX_NUM        4  ///< ��������

#define RTU_UART            UART_1  ///< RTU����
#define FLOW_METER_UART     UART_2  ///< �����ƴ���

#define UART_DEFAULT_BAUD           9600  ///< ������Ĭ��ֵ
#define UART_DEFAULT_BYTE           8     ///< ����λĬ��ֵ
#define UART_DEFAULT_PARITY         'N'   ///< У�鷽ʽĬ��ֵ
#define UART_DEFAULT_STOP_BITS      1     ///< ֹͣλĬ��ֵ

#define RTU_UART_DELAY              10    ///< RTU���ڽ��շ�����ʱ
#define FLOW_METER_UART_DELAY       10    ///< �����ƴ��ڽ��շ�����ʱ

#define UART1_DIR_SEL               P7SEL ///< RTU���ڷ��ͽ��տ���
#define UART1_DIR_DIR               P7DIR ///< RTU
#define UART1_DIR_OUT               P7OUT ///< RTU
#define UART1_DIR_BIT               BIT2  ///< RTU

#define UART2_DIR_SEL               P9SEL ///< FLOW���ڷ��ͽ��տ���
#define UART2_DIR_DIR               P9DIR ///< FLOW
#define UART2_DIR_OUT               P9OUT ///< FLOW
#define UART2_DIR_BIT               BIT6  ///< FLOW

#define RS485_PWR_SWITCH_SEL        P5SEL ///< RTU���ڵ�Դ
#define RS485_PWR_SWITCH_DIR        P5DIR ///< RTU
#define RS485_PWR_SWITCH_OUT        P5OUT ///< RTU
#define RS485_PWR_SWITCH_BIT        BIT5  ///< RTU
#define RS485_PWR_SWITCH_ON()       RS485_PWR_SWITCH_OUT &= ~RS485_PWR_SWITCH_BIT
#define RS485_PWR_SWITCH_OFF()      RS485_PWR_SWITCH_OUT |= RS485_PWR_SWITCH_BIT

#define FLOW_PWR_SWITCH_SEL         P5SEL ///< FLOW���ڵ�Դ
#define FLOW_PWR_SWITCH_DIR         P5DIR ///< FLOW
#define FLOW_PWR_SWITCH_OUT         P5OUT ///< FLOW
#define FLOW_PWR_SWITCH_BIT         BIT4  ///< FLOW

#define FLOW_PWR_SWITCH_ON()        FLOW_PWR_SWITCH_OUT &= ~FLOW_PWR_SWITCH_BIT
#define FLOW_PWR_SWITCH_OFF()       FLOW_PWR_SWITCH_OUT |= FLOW_PWR_SWITCH_BIT
#define FLOW_PWR_SWITCH_IS_ON       (!(FLOW_PWR_SWITCH_OUT & FLOW_PWR_SWITCH_BIT))

#pragma pack(1)
typedef struct UartInfo {
  u32 baudrate;         ///< ������
  u8 bytesize;          ///< ����λ
  u8 parity;            ///< У��λ
  u8 stopbits;          ///< ֹͣλ
}UartInfo;
#pragma pack()

/**
 * @brief ���ڽṹ������
 */
typedef struct Uart {
  UartInfo info;               ///< ������Ϣ
  u16 rcv_pos;                 ///< ��������ǰλ��
  u16 snd_pos;                 ///< ����ȥ��ǰλ��
  u16 snd_len;                 ///< ��������Ч�ֽ���
  u16 state;                   ///< ����״̬
//  volatile u8 *txbuf;         ///< 
//  volatile u8 *ie;            ///<
//  volatile u8 *ifg;           ///<
  u8 rcv_buf[MAX_BUF_SIZE];    ///< ���ջ�����
  u8 snd_buf[MAX_BUF_SIZE];    ///< ���ͻ�����
}Uart;

extern Uart uart_list[];      ///< �����б�
extern u32 uart_get_baud(u32 baud);
extern u8 uart_get_parity(u8 parity);
extern void uart_init();
extern void uart_rcv(u8 no, u8 data);
//extern void uart_snd(u8 no);
//extern void uart_enable(u8 no, u8 rx, u8 tx);

/**
 * @brief ���ڽ��շ���ʹ��
 * @param[in] NO ���ں�
 * @param[in] RX TRUEʱ�򿪽����ж�,FALSE�رս����ж�
 * @param[in] TX TRUEʱ�򿪷����ж�,FALSE�رշ����ж�
 * @return �޷���ֵ
 */
#define __UART_ENABLE(NO, RX, TX)\
  if(TRUE == RX) {\
    if(UART_1 == NO){\
      UART1_DIR_OUT &= ~UART1_DIR_BIT;\
    } else if(UART_2 == NO){\
      UART2_DIR_OUT &= ~UART2_DIR_BIT;\
    }\
    UCA##NO##IE |= UCRXIE;\
  } else {\
    UCA##NO##IE &= ~UCRXIE;\
  }\
  if(TRUE == TX) {\
    if(UART_1 == NO){\
      UART1_DIR_OUT |= UART1_DIR_BIT;\
    }else if(UART_2 == NO){\
      UART2_DIR_OUT |= UART2_DIR_BIT;\
    }\
    UCA##NO##IE |= UCTXIE;\
    UCA##NO##IFG = UCTXIFG;\
  } else {\
    UCA##NO##IE &= ~UCTXIE;\
  }
/**
 * @brief ���ڽ��շ���ʹ��,�ض���,��ֹ����չ���쳣
 */
#define UART_ENABLE(NO, RX, TX) __UART_ENABLE(NO, RX, TX)
//#define UART_ENABLE   uart_enable
  
/**
 * @brief ���ڳ�ʼ��
 * @param[in] NO ���ں�
 * @param[in] LCK ʱ��Դ
 * @param[in] BAUD ������
 * @param[in] BYTE ����λ
 * @param[in] PART У��λ
 * @param[in] STOP ֹͣλ
 * @return �޷���ֵ
 */
#define __UART_INIT(NO, LCK, BAUD, BYTE, PART, STOP){\
  UART_ENABLE(NO, FALSE, FALSE);\
  Uart *uart = uart_list + NO;\
  if(UART_0 == NO){\
    P3SEL |= (BIT5 | BIT4);\
    P3DIR |= BIT4;\
    P3DIR &= ~BIT5;\
  } else if(UART_1 == NO) {\
    UART1_DIR_SEL &= ~UART1_DIR_BIT;\
    UART1_DIR_DIR |= UART1_DIR_BIT;\
    P5SEL |= (BIT7 | BIT6);\
    P5DIR |= BIT6;\
    P5DIR &= ~BIT7;\
  } else if(UART_2 == NO) {\
    UART2_DIR_SEL &= ~UART2_DIR_BIT;\
    UART2_DIR_DIR |= UART2_DIR_BIT;\
    P9SEL |= (BIT5 | BIT4);\
    P9DIR |= BIT4;\
    P9DIR &= ~BIT5;\
  } else if(UART_3 == NO) {\
    P10SEL |= (BIT5 | BIT4);\
    P10DIR |= BIT4;\
    P10DIR &= ~BIT5;\
  }\
  fp32 baud_f;\
  fp32 baud_N;\
  u16  baud_BR0;\
  u16  baud_BR1;\
  u8  baud_UCBRSx=0;\
  u8  baud_UCBRFx=0;\
  u8  baud_UCOS16=0;\
  u8 tmp = 0;\
  if(7 == BYTE){\
    tmp |= UC7BIT;\
  } else {\
    tmp &= ~UC7BIT;\
  }\
  if('O' == PART){\
    tmp |= UCPEN;\
    tmp &= ~UCPAR;\
  } else if('E' == PART){\
    tmp |= UCPEN;\
    tmp |= UCPAR;\
  } else {\
    tmp &= ~UCPEN;\
  }\
  if(2 == STOP){\
    tmp |= UCSPB;\
  } else {\
    tmp &= ~UCSPB;\
  }\
  baud_f = (fp32)UART_FBRCLK/BAUD;\
  if(baud_f >= 16) {\
    baud_UCOS16=1;\
    baud_N=baud_f/16;\
    baud_BR0=(u16)baud_N&0xFF;\
    baud_BR1=(u16)baud_N>>8;\
    baud_UCBRSx=(u8)(0.5+((baud_N-baud_BR0)*16));\
  } else {\
    baud_BR0=(u16)baud_f&0xFF;\
    baud_BR1=(u16)baud_f>>8;\
    baud_UCBRSx=(u8)(0.5+((baud_f - baud_BR0)*8));\
  }\
  UCA##NO##CTL0 = tmp;\
  UCA##NO##CTL1 |= LCK;\
  UCA##NO##BR0 = baud_BR0;\
  UCA##NO##BR1 = baud_BR1;\
  UCA##NO##MCTL = (baud_UCBRFx<<4)|(baud_UCBRSx<<1)|baud_UCOS16;\
  UCA##NO##CTL1 &= ~UCBRKIE;\
  UCA##NO##CTL1 &= ~UCSWRST;\
  uart->rcv_pos=0;\
  uart->snd_pos=0;\
  uart->state=STATE_RX_IDLE;\
  UART_ENABLE(NO, TRUE, FALSE);\
}

#if 1
/**
 * @brief �������ݽ���
 * @param[in] NO ���ں�
 * @param[in] DATA ���յ�������
 * @return �޷���ֵ
 */
#define UART_RCV(NO, DATA)\
  Uart *uart = uart_list + NO;\
  switch (uart->state)\
  {\
    case STATE_RX_IDLE:\
        uart->rcv_pos = 0;\
        uart->rcv_buf[uart->rcv_pos++] = DATA;\
        uart->state = STATE_RX_RCV;\
        if(RTU_UART == NO) {\
          task_event_post(TASK_RTU, EV_FRAME_RECEIVED, RTU_UART_DELAY);\
        } else if(FLOW_METER_UART == NO) {\
          task_event_post(TASK_FLOW_METER, EV_FRAME_RECEIVED, FLOW_METER_UART_DELAY);\
        }\
        break;\
    case STATE_RX_RCV:\
        if(uart->rcv_pos < MAX_BUF_SIZE) {\
          uart->rcv_buf[uart->rcv_pos++] = DATA;\
        }\
        if(RTU_UART == NO) {\
          task_event_post(TASK_RTU, EV_FRAME_RECEIVED, RTU_UART_DELAY);\
        } else if(FLOW_METER_UART == NO) {\
          task_event_post(TASK_FLOW_METER, EV_FRAME_RECEIVED, FLOW_METER_UART_DELAY);\
        }\
        break;\
    }
#else
#define UART_RCV uart_rcv
#endif

/**
 * @brief �������ݷ���
 * @param[in] NO ���ں�
 * @return �޷���ֵ
 */
#define UART_SND(NO) {\
  Uart *uart = uart_list + NO;\
  switch (uart->state)\
  {\
    case STATE_TX_XMIT:\
      if(uart->snd_pos < uart->snd_len) {\
        UCA##NO##TXBUF = uart->snd_buf[uart->snd_pos];\
        ++uart->snd_pos;\
      } else {\
        uart->snd_pos = 0;\
        uart->snd_len = 0;\
        if(RTU_UART == NO) {\
          if(uart->info.baudrate >= 9600) {\
            DELAY_US(1000);\
          } else if(uart->info.baudrate >= 4800){\
            DELAY_US(2000);\
          } else if(uart->info.baudrate >= 2400){\
            DELAY_US(4000);\
          }\
          UART_ENABLE(NO, TRUE, FALSE);\
          uart->state = STATE_RX_IDLE;\
        } else if(FLOW_METER_UART == NO) {\
          if(uart->info.baudrate >= 9600) {\
            DELAY_US(1000);\
          } else if(uart->info.baudrate >= 4800){\
            DELAY_US(2000);\
          } else if(uart->info.baudrate >= 2400){\
            DELAY_US(4000);\
          }\
          UART_ENABLE(NO, TRUE, FALSE);\
          uart->state = STATE_RX_IDLE;\
        }\
      }\
      break;\
  }\
}

/**
 * @brief �����жϺ�������
 * @param[in] NO ���ں�
 * @return �޷���ֵ
 */
#define UART_ISR_CREATE(NO)\
__interrupt void uart##NO##_isr(void)\
{\
  switch(__even_in_range(UCA##NO##IV, 4))\
  {\
    case 0:\
    break;\
    case 2:\
    {\
      LOW_POWER_MODE_OFF();\
      u8 tmp = UCA##NO##RXBUF;\
      UART_RCV(NO, tmp);\
      break;\
    }\
    case 4:\
      UART_SND(NO);\
      break;\
    default:\
      break;\
  }\
}

/**
 * @brief ���ڳ�ʼ��,�ض���,��ֹ����չ���쳣
 * @return �޷���ֵ
 */
#define UART_INIT(NO, BAUD, BYTE, PART, STOP)\
  __UART_INIT(NO, UCSSEL__ACLK, BAUD, BYTE, PART, STOP)

/**
 * @brief �������³�ʼ��,����һ��,ûɶ��һ��
 * @return �޷���ֵ
 */
#define UART_RE_INIT(NO) {\
  UartInfo *info = &uart_list[NO].info;\
  UART_INIT(NO, info->baudrate, info->bytesize, info->parity, info->stopbits);\
}
#endif