/**
 * @file  watchdog.h
 * @brief ���Ź��������
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#ifndef WATCH_DOG_H_
#define WATCH_DOG_H_
#include "cpu.h"
#include "stdint.h"

#define WATCH_DOG_DIR        P6DIR  ///< ���Ź������������
#define WATCH_DOG_OUT        P6OUT  ///< ���Ź������ƽ�ߵ�
#define WATCH_DOG_BIT        BIT0   ///< ���Ź��ܽ�

/**
 * @brief ���Ź�ʹ��
 * @param[in] ON ����TRUEʱ�������Ź�,FALSEʱ�رտ��Ź�
 * @return �޷���ֵ
 */
#define WATCH_DOG_ENABLE()    WATCH_DOG_DIR |= WATCH_DOG_BIT
#define WATCH_DOG_DISABLE()   WATCH_DOG_DIR &= ~WATCH_DOG_BIT

/**
 * @brief ι������,�����Ź�����,1s֮����Ҫιһ��
 * @return �޷���ֵ
 */
#define WATCH_DOG_FEED()      WATCH_DOG_OUT ^= WATCH_DOG_BIT

#endif