/**
 * @file  cpu.h
 * @brief cpuʱ����ض���
 * @version 1.0
 * @author ygz
 * @date   2015.7.1
 */
#ifndef CPU_H_
#define CPU_H_
#include "stdint.h"
#include "msp430x54xA.h"

#define CPU_DCO_3MHZ            99                        ///< 3,276,800
#define CPU_DCO_12MHZ           374                       ///< 12,288,000

#define FLLN_A                  CPU_DCO_3MHZ              ///< N
#define CRY_FREQ                32768                     ///< ����Ƶ��
#define CPU_CLOCK               ((FLLN_A + 1) * CRY_FREQ) ///< CPU��ʱ��
#define DELAY_AFTER_FLL_CTL     375000

#define DELAY_US(x) __delay_cycles((long)(CPU_CLOCK*(double)x/1000000.0)) ///< ��ʱ��us
#define DELAY_MS(x) __delay_cycles((long)(CPU_CLOCK*(double)x/1000.0))    ///< ��ʱ��ms

extern void delayms(u64 m);
extern void cpu_init(void);

#endif