/**
 * @file  lcd.c
 * @brief lcd����ʵ��(����΢lm6029)
 * @version 1.0
 * @author ygz <yangguozheng@tjwzkj.com>
 * @date   2015.7.1
 */
#include "lcd.h"
#define	_CS1_BIT
#define	_RES_BIT          BIT2    ///< ��عܽŶ��� P11.2
#define	RS_BIT            BIT1    //P11.1
#define	_WR_BIT           BIT0    //P11.0
#define	_RD_BIT           BIT7    //P9.7

#define LCD_DB_OUT        P10OUT
#define	_CS1_OUT
#define	_RES_OUT          P11OUT
#define	RS_OUT            P11OUT
#define	_WR_OUT           P11OUT
#define	_RD_OUT           P9OUT

#define LCD_DB_DIR        P10DIR
#define _RES_DIR          P11DIR
#define	RS_DIR            P11DIR
#define _WR_DIR           P11DIR
#define _RD_DIR           P9DIR

#define LCD_DB_SEL        P10SEL
#define _RES_SEL          P11SEL
#define	RS_SEL            P11SEL
#define _WR_SEL           P11SEL
#define _RD_SEL           P9SEL

#define LCD_DB_REN        P10REN
#define _RES_REN          P11REN
#define	RS_REN            P11REN
#define _WR_REN           P11REN
#define _RD_REN           P9REN


u8 contrast_level; ///< ���ȵȼ�
u8 lcd_screen_data[128*64/8]; ///< lcd��Ļ������
Lcd lcd;

/**
 * @brief ����ָ��
 * @param[in] cmd ָ��
 * @return �޷���ֵ
 * @note RS(0)->_WR(1)->_RD(1)->cmd->_WR(0)->_WR(1)
 */
void lcd_snd_cmd(u8 cmd)             //send command
{
  RS_OUT        &= ~RS_BIT;      //0
  _WR_OUT       |= _WR_BIT;      //1
  _RD_OUT       |= _RD_BIT;      //1
  LCD_DB_OUT     = cmd;
  //_CS1_OUT      &= ~_CS1_BIT;  //0;
  _WR_OUT       &= ~_WR_BIT;     //0;
  _WR_OUT     |= _WR_BIT;        //1;
  //_CS1_OUT    |= _CS1_BIT;     //1;
}

/**
 * @brief ������ʾ����
 * @param[in] data ����
 * @return �޷���ֵ
 * @note RS(1)->_WR(1)->_RD(1)->data->_WR(0)->_WR(1)
 */
void lcd_snd_data(u8 data)          //send data
{
  RS_OUT      |= RS_BIT;        //1;
  _WR_OUT     |= _WR_BIT;       //1;
  _RD_OUT     |= _RD_BIT;       //1;
  LCD_DB_OUT  = data;
  //_CS1_OUT    &= ~_CS1_BIT;   //0;
  _WR_OUT     &= ~_WR_BIT;      //0;
  _WR_OUT     |= _WR_BIT;       //1;
  //_CS1_OUT    |= _CS1_BIT;    //1;
}

/**
 * @brief �����ʾ����
 * @return �޷���ֵ
 */
void lcd_clear_data() {
  memset(lcd_screen_data, 0, sizeof(lcd_screen_data));
}

/**
 * @brief ����������
 * @param[in] opt TRUEʱ����,FALSEʱϨ��
 * @return �޷���ֵ
 */
void lcd_light_on(u8 opt) {
  if(TRUE == opt) {
    LCD_BLK_SWITCH_OUT &= ~LCD_BLK_SWITCH_BIT;
  } else {
    LCD_BLK_SWITCH_OUT |= LCD_BLK_SWITCH_BIT;
  }
  lcd.light_on = opt;
}

/**
 * @brief ��Ļ��ʾ(8 page,128 column)
 * @return �޷���ֵ
 */
void lcd_display_screen() {
	u8 i, j;
	for(i=0;i<8;i++)
  {
    lcd_snd_cmd(0xb0 | i);	// select page 0~7
    lcd_snd_cmd(0x10);	    // start form column 4
    lcd_snd_cmd(0x00);	    // (2byte command)
    for(j=0;j<128;j++)
    {
      lcd_snd_data((*(lcd_screen_data+(i*128)+j))); //Logo//lcd_screen_data
    }
  }
}

/**
 * @brief �ύ��ʾ���嵽��ʾ������
 * @param[in] x ˮƽ��ʼ��
 * @param[in] y ��ֱ��ʼ��
 * @param[in] w ������
 * @param[in] h ����߶�
 * @param[in] word ��������
 * @param[in] r �Ƿ񷴰���ʾ
 * @return �޷���ֵ
 * @note �Ƚϸ���
 */
void lcd_post_word(u8 x, u8 y, u8 w, u8 h, const u8 *word, u8 r) {
  if(y > 63 || x + w > 128) {
    return;
  }
  if(h < 8) {
    return;
  }
  u8 i0 = y/8, i1 = (y + h - 1)/8;
  u8 i, j, tmp, tmp1;
  u8 y_8 = y%8;
  u8 y_8_8 = (8 - y_8);
  u8 h_8 = h%8;
  u8 h_y_8 = (h_8 + y_8);
  u8 h_y_8_8 = 8 - (h_8 + y_8);
  u8 h_8__8 = (8 - h_8);
  u8 h_8__h_y_8 = h_8 - (h+y)%8;
  if(y%8) {
    for(i = i0;i <= i1;++i) {
      for(j = 0;j < w;++j) {
        if(i == i0) {                 //��һ��
          if(TRUE == r) {
            tmp = ~(word[w*(i-i0)+j]);//(*word++);//word[8*(i-i0)+j];
          } else {
            tmp = word[w*(i-i0)+j];   //*word++;
          }
          tmp <<= y_8;//y%8;                                            //��λ����
          lcd_screen_data[128*i + x + j] &= 0xFF>>y_8_8;//(8-y%8);      //ȡ��λ
          lcd_screen_data[128*i + x + j] |= tmp;
        }else if(i == i1 && h_y_8 <=8) {                               //(h%8 + y%8)���һ��
          if(TRUE == r) {
            tmp = ~(word[w*(i-i0-1)+j]);//(*word++);//word[8*(i-i0)+j];
          } else {
            tmp = word[w*(i-i0-1)+j];   //*word++;
          }
          //tmp &= 0xFF>>(8 - h%8);                                //ȡ����Чλ
          tmp >>= y_8_8;                                           //��λ����
          
          if(TRUE == r) {
            tmp1 = ~(word[w*(i-i0)+j]);//(*word++);//word[8*(i-i0)+j];
          } else {
            tmp1 = word[w*(i-i0)+j];   //*word++;
          }
          //tmp &= 0xFF>>(8 - h%8);                                //ȡ����Чλ
          tmp1 <<= y_8;//y%8;                                      //��λ����
          tmp |= tmp1;
          tmp &= 0xFF>>h_y_8_8;//(8 - (h%8 + y%8));
          
          lcd_screen_data[128*i + x + j] &= 0xFF<<h_y_8;//((h%8 + y%8));     //ɾ����λ
          lcd_screen_data[128*i + x + j] |= tmp;
        } else if(i == i1 && h_y_8 > 8) {                                   //(h%8 + y%8)���һ��
          if(TRUE == r) {
            tmp = ~(word[w*(i-i0-1)+j]);//(*word++);//word[8*(i-i0)+j];
          } else {
            tmp = word[w*(i-i0-1)+j];   //*word++;
          }
          tmp &= 0xFF>>h_8__8;//(8 - h%8);                                  //ȡ����Чλ
          tmp >>= h_8__h_y_8;//h%8-(h+y)%8;                                 //��λ����
          
          lcd_screen_data[128*i + x + j] &= 0xFF<<(((h+y)%8));              //ɾ����λ
          lcd_screen_data[128*i + x + j] |= tmp;
        } else {                                                           //�м���
          if(TRUE == r) {
            tmp = ~(word[w*(i-i0-1)+j]);//(*word++);//word[8*(i-i0)+j];
          } else {
            tmp = word[w*(i-i0-1)+j];   //*word++;
          }
          //tmp &= 0xFF>>(8 - h%8);                                        //ȡ����Чλ
          tmp >>= y_8_8;//8-y%8;                                           //��λ����
          
          if(TRUE == r) {
            tmp1 = ~(word[w*(i-i0)+j]);//(*word++);//word[8*(i-i0)+j];
          } else {
            tmp1 = word[w*(i-i0)+j];   //*word++;
          }
          //tmp &= 0xFF>>(8 - h%8);                                       //ȡ����Чλ
          tmp1 <<= y_8;//y%8;                                             //��λ����
          tmp |= tmp1;
          lcd_screen_data[128*i + x + j] = tmp;
        }
      }
    }
  } else {
    for(i = i0;i <= i1;++i) {
      for(j = 0;j < w;++j) {
        if(TRUE == r) {
          tmp = ~(word[w*(i-i0)+j]);//(*word++);//word[8*(i-i0)+j];
        } else {
          tmp = word[w*(i-i0)+j];   //*word++;
        }
        if(i0 !=i1 && i == i1) {                                   //���һ��
          tmp &= 0xFF>>h_8__8;//(8 - h%8);                         //ȡ��λ
          lcd_screen_data[128*i + x + j] &= 0xFF<<h_8;//(h%8);     //ɾ����λ
          lcd_screen_data[128*i + x + j] |= tmp;
        } else {
          lcd_screen_data[128*i + x + j] = tmp;
        }
      }
    }
  }
}

/**
 * @brief ����-����
 * @return �޷���ֵ
 */
void darker(void)
{
	if (contrast_level<0x3f)
    contrast_level++;
	lcd_snd_cmd(0x81);     		     // E-Vol setting
	lcd_snd_cmd(contrast_level);   // (2byte command)
}

/**
 * @brief ����-����
 * @return �޷���ֵ
 */
void lighter(void)
{
	if (contrast_level>0x00)
    contrast_level--;
	lcd_snd_cmd(0x81);             // E-Vol setting
	lcd_snd_cmd(contrast_level);   // (2byte command)	
  
}

/**
 * @brief lcd������ʼ��
 * @return �޷���ֵ
 */
void lcd_init() {
  //////////////////////////
  LCD_DB_SEL  = 0;
  _RES_SEL   &= ~_RES_BIT;
  RS_SEL     &= ~RS_BIT;
  _WR_SEL    &= ~_WR_BIT;
  _RD_SEL    &= ~_RD_BIT;
  
  LCD_DB_DIR  = 0xFF;
  _RES_DIR   |= _RES_BIT;
  RS_DIR     |= RS_BIT;
  _WR_DIR    |= _WR_BIT;
  _RD_DIR    |= _RD_BIT;
  
  LCD_DB_REN  = 0xFF;
  _RES_REN   |= _RES_BIT;
  RS_REN     |= RS_BIT;
  _WR_REN    |= _WR_BIT;
  _RD_REN    |= _RD_BIT;
  //////////////////////////
  
  LCD_BLK_SWITCH_DIR |= LCD_BLK_SWITCH_BIT;
  //LCD_BLK_SWITCH_OUT &= ~LCD_BLK_SWITCH_BIT;
  LCD_BLK_SWITCH_OUT |= LCD_BLK_SWITCH_BIT;
#if 1
  //_CS1_OUT    |= _CS1_BIT;  //1;
  _RES_OUT    |= _RES_BIT;    //1;
  RS_OUT      |= RS_BIT;      //1;
  _WR_OUT     |= _WR_BIT;     //1;
  _RD_OUT     |= _RD_BIT;     //1;
  
  _RES_OUT    |= _RES_BIT;    //1;hardware reset LCD module
	_RES_OUT    &= ~_RES_BIT;   //0;
	delayms(1);
	_RES_OUT    |= _RES_BIT;    //1;
	delayms(1);
  
  contrast_level = 0x1c;        //Update 0x1b -> 0x1c (V0=9.1V)
	lcd_snd_cmd(0xaf);            // display on
	lcd_snd_cmd(0x40);            // display start line=0
  lcd_snd_cmd(0xa0);            // ADC=0
  lcd_snd_cmd(0xa6);            // normal display
  lcd_snd_cmd(0xa4);            // Duisplay all point = off
  lcd_snd_cmd(0xa3);            // Update LCD bias 0xa2->0xa3 (1/9->1/7)
  lcd_snd_cmd(0xc8);            // Common output mode select= reverse
  lcd_snd_cmd(0x2f);            // Power control = all on
	lcd_snd_cmd(0x25);			      // Update 0x27->0x25 (Ra/Rb = 5.5 )
  
	lcd_snd_cmd(0x81);            // E-Vol setting
  lcd_snd_cmd(contrast_level);  // (2byte command)
#else
  lcd_snd_cmd(0xa0);            // ADC=0
  lcd_snd_cmd(0xc8);            // SHL=1
  lcd_snd_cmd(0xa3);            // LCD bias 1/7
  lcd_snd_cmd(0x40);            // display start line=0
  lcd_snd_cmd(0xa4);            // Entire Display OFF
  lcd_snd_cmd(0xa6);            // Reverse Display OFF
  lcd_snd_cmd(0x2f);            // Power control = all on
  lcd_snd_cmd(0xaf);            // display on
#endif
}