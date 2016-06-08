/**
 * @file  lcd_task.h
 * @brief lcd��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef LCD_TASK_H_
#define LCD_TASK_H_
#include "../kernel/kernel.h"
#include "../drivers/drivers.h"
#include "lcd_font.h"
/**
 * @brief ��ǰ��ʾ��(����)״̬
 */
enum {
  ITEM_HOVER,         ///< ��ͣ״̬(��ʼ״̬)
  ITEM_FOCUS_ALL,     ///< ȫ����״̬
  ITEM_FOCUS_FIRST,   ///< ��һ����
  ITEM_FOCUS_SECOND,  ///< �ڶ�����
  ITEM_FOCUS_THIRD,   ///< ��������
  ITEM_FOCUS_FOURTH,  ///< ���Ľ���
  ITEM_FOCUS_FIFTH,   ///< ���役��
  ITEM_FOCUS_SIXTH,   ///< ��������
};

/**
 * @brief ѡ�����(����)
 */
enum {
  //ITEM_PASSWD,                     ///< ������
  ITEM_ADDR,                       ///< ��ַ�� //////////��һҳ
  ITEM_BACK_LIGHT,                 ///< ������
  //ITEM_OPEN_ANGLE,                 ///< ������
  ITEM_PRECISION,                  ///< ������
  ITEM_INJECTION,                  ///< ��ע��
  //ITEM_FLIP_PAGE,                ///< ��ҳ��
  ITEM_H_VERSION,                  ///< Ӳ���汾��
  ITEM_ACTUATOR_VERSION,           ///< ����汾��
  ITEM_SAVE_CONF,                  ///< ��������
  ITEM_REBOOT,                     ///< ����
  ITEM_FLOW_UART,                  ///< �����ƴ����� ////�ڶ�ҳ
  ITEM_RTU_UART,                   ///< RTU������
  ITEM_FLOW_TYPE,                  ///< ����������
  ITEM_FLOW_ADDR,                  ///< �����Ƶ�ַ
  ITEM_MOTOR_REMOTE_CTL,           ///< ���ң��    /////����ҳ
  ITEM_MOTOR_MANUAL_ADJ,           ///< �Զ�/�ֶ�
  ITEM_MOTOR_ADJ,                  ///< ����Ƕ�У׼/////����ҳ
  ITEM_MOTOR_TEST,                 ///< �������
  ITEM_MOTOR_ANGLE_AD_MIN,         ///< �Ƕȵ���AD��Сֵ
  ITEM_MOTOR_ANGLE_AD_MID,         ///< �Ƕȵ���AD�м�ֵ
  ITEM_MOTOR_ANGLE_AD_MAX,         ///< �Ƕȵ���AD���ֵ
  ITEM_MOTOR_RATIO,                ///< �������ռ�ձ�
  ITEM_MOTOR_TIME,                 ///< �������ʱ��
  ITEM_LPM_SWITCH,                 ///< �͹���
  ITEM_MOTOR_REVERSE,              ///< ����
  ITEM_PRECISION_RATIO,            ///< �����ƾ���Ȩֵ
  ITEM_FLOW_MOTOR_WEIGHT_EDGE,     ///< Ȩֵ
  ITEM_FLOW_REQ_TIME0,             ///< �޵���������///����ҳ
  ITEM_FLOW_REQ_TIME1,             ///< �е���������
  //ITEM_SUN_RISE_HOUR,
  ITEM_MAX_NUM,                    ///< ѡ�����
};

/**
 * @brief ҳ������
 */
enum {
  PAGE_MAIN,    ///< ��ҳ��
  PAGE_SUB0,    ///< ��0ҳ��
  PAGE_SUB1,    ///< ��1ҳ��
  PAGE_LOGIN,   ///< ��½ҳ��
  PAGE_SETTING, ///< ����ҳ��
  PAGE_MAX_NUM, ///< ҳ������
};

/**
 * @brief lcdҳ�ṹ
 */
typedef struct LcdPage {
  u8 page;            ///< ��ǰҳ
  u8 hover_item;      ///< ����ͣ��
  u8 status;          ///< lcd��ǰ����״̬
  u64 frame_time_a;   ///< ˢ����ʱ��
  u64 frame_time_b;   ///< ���ݸ��¼�ʱ��
  u16 frame_itv_time; ///< ˢ�����
  u8 flip_page_time;  ///< �Զ��������
  u8 x;               ///< ����ƫ��
  u8 y;               ///< ��ֱƫ��
  u8 light_time;      ///< ��Ļ��ʱ��
  u64 light_time_a;   ///< ��ʱ��
  u8 max_item;
}LcdPage;
extern LcdPage lcd_page;

#define LCD_FRAME_INT_TIME     100   ///< ��Ļˢ��Ƶ��100ms
#define LCD_PAGE_OFFSET_X      0     ///< ����ƫ��Ĭ��ֵ
#define LCD_PAGE_OFFSET_Y      0     ///< ��ֱƫ��Ĭ��ֵ

extern void lcd_task();

#endif