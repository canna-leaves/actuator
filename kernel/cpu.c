/**
 * @file  cpu.c
 * @brief ϵͳcpu��ʼ������Ҫ����ϵͳʱ�ӳ�ʼ��
 * @version 1.0
 * @author ygz
 * @date   2015.7.1
 */
#include "cpu.h"

/**
 * @brief 430��Ƶʱ��(32768hzʱ��)�ĳ�ʼ��
 * @return �޷���ֵ
 */
void cpu_clock_low_init(void)
{    
  //��ʼ��Ϊ32768����
  P7SEL |= (BIT0 | BIT1);                   //0x03; // Port7 select XT1
  //XT1����,�͹���ģʽ,��С��������
  UCSCTL6 &= ~(XT1OFF + XTS + XT1DRIVE_0);  //XT1 On, XTS����Ϊ��Ƶ����XT1DRIVE_3����Ƶ�ʵ�������ģʽ                                        
  UCSCTL6 |= XCAP_3 ;                       //xt1��Ƶģʽ�µ��ڲ����� Internal load cap
}

/**
 * @brief 30�ڲ�ʱ��Dco�ĳ�ʼ��(Ҳ����fll���໷�ĳ�ʼ��)
 * @return �޷���ֵ
 */
void cpu_clock_dco_init(void )
{
  
  UCSCTL3 |= SELREF__REFOCLK + FLLREFDIV_0; //  ѡ��FLL�ο�Դ���ڲ���32768hz��REFO  Set DCO FLL reference = REFO 32768Hz
  __bis_SR_register(SCG0);                  //��ֹ���໷ System clock generator 0. This bit, when set, turns off the FLL+ loop control
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 32MHz operation
  UCSCTL2 = FLLD_1 + FLLN_A; //374          //(FLLN_A + 1) * 32768 = 12.288MHz
  // UCSCTL2 = FLLD_1 + 0xb5;         // ���໷�ķ�ƵΪ1  Set DCO Multiplier for 12MHz 
  // (N + 1) * FLLRef = Fdco
  // (0xb5(181) + 1) * 32768 = 5.963776MHz
  //(374 + 1) * 32768 = 12.288MHz
  
  __bic_SR_register(SCG0);          // Enable the FLL control loop
  
  __delay_cycles(DELAY_AFTER_FLL_CTL);
}

/**
 * @brief �ȴ�430ʱ�Ӳ��ֵ��ȶ�
 * @return �޷���ֵ
 */
void cpu_waitclock_stabilize(void)
{
  int i = 0;
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);//���ܳ�ʼ�����־������еĴ����־����Ҫ���
    SFRIFG1 &= ~OFIFG;                      // ���⹦�ܼĴ��� Clear fault flags
    for(i = 0;i< 0xFFFF;i ++);              // Delay for Osc to stabilize
    
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag 
}

/**
 * @brief 430�ڲ�ʱ��Դ��ѡ�񣬰���aclk mclk smclkʱ��Դ��ѡ��
 * @return �޷���ֵ
 */
void cpu_clock_select(void)
{
  
  UCSCTL4 = SELA__XT1CLK | SELM__DCOCLKDIV;/* | SELS__DCOCLKDIV;*/  // Set ACLK
  //UCSCTL5 |= DIVA__2;                                        //2��Ƶ    ����ACLKʱ��Ϊ6144000
}

/**
 * @brief CPU��ʼ��
 * @return �޷���ֵ
 */
void cpu_init(void)
{
  cpu_clock_low_init();
  cpu_clock_dco_init();      //��Ƶ��NMhz
  cpu_waitclock_stabilize(); //���������е�ʱ��������Ϻ��ٽ��еȴ���ѯ�����ܵ����Ķ�xt1����dco���еȴ���ѯ
  cpu_clock_select();        //ACLKd��ʱ��ԴΪXT1CLK��Selects the SMCLK source ΪDCOCLKDIV��Selects the MCLK source ΪDCOCLKDIV
}

/**
 * @brief Ӳ����ʱ
 * @param[in] m ����
 * @return �޷���ֵ
 */
void delayms(u64 m)         // 12MHz Xtal, close to ms value
{
  u64 i;
  for(i=0; i<m; i++) {
    DELAY_MS(1);
  }
}