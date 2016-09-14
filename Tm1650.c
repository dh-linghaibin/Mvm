/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�Tm1650.c
*
* �ļ���ʶ��
* ժ    Ҫ��
*
*
* ��ǰ�汾��
* ��    �ߣ�lhb Steven
* ������ڣ�2016/8/24
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "Tm1650.h"
#include "Delay.h"

#define TM_SCL  PE_ODR_ODR1
#define TM_SDA  PE_ODR_ODR2
#define TM_TIME 100
// ------ Public variable definitions ---------------------
const u8 Digital_tube_coding[12] = {
0x6f, 0x21, 0xe6, 0xe5, 
0xa9, 0xcd, 0xcf, 0x61, 
0xef, 0xed, 0xeb, 0x4e,
};

/**********************************************��������***************************************************** 
* ��������: void Tm1650Init(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/24
************************************************************************************************************/ 
void Tm1650Init(void) { 
    PE_DDR_DDR1 = 1;
    PE_CR1_C11 = 1;
    PE_CR2_C21 = 1;
    
    PE_DDR_DDR2 = 1;
    PE_CR1_C12 = 1;
    PE_CR2_C22 = 1;
}
/*---------------------------------------------------------------*-
 * TM1650_Start()
 * 
 * Send start condition 
-*---------------------------------------------------------------*/
void TM1650_Start(void)
{
	TM_SCL = 1;
	TM_SDA = 1;
	DelayUs(TM_TIME);
	TM_SDA = 0;
	DelayUs(TM_TIME);
	TM_SCL = 0;
	DelayUs(TM_TIME);
}
/*---------------------------------------------------------------*-
 * TM1650_Stop();
 * 
 * Send stop condition
-*---------------------------------------------------------------*/
void TM1650_Stop(void)
{
	TM_SCL = 0;
	TM_SDA = 0;
	DelayUs(TM_TIME);
	TM_SCL = 1;
	DelayUs(TM_TIME);
	TM_SDA = 1;
	DelayUs(TM_TIME);
}
/*---------------------------------------------------------------*-
 * TM1650_ACK()
 * 
 * Make sure the slave has received the data
-*---------------------------------------------------------------*/
void TM1650_ACK()
{
	TM_SDA = 0;
	TM_SCL = 1;
	DelayUs(TM_TIME);
	TM_SCL = 0;
	TM_SDA = 1;
}
/*---------------------------------------------------------------*-
 * TM1650_Write_Byte()
 * 
 * Send one byte data to slave
-*---------------------------------------------------------------*/
void TM1650_Write_Byte(unsigned char DATA)
{
	unsigned char i;
	for (i = 0; i < 8; i++) {
		if ((DATA & 0x80) == 0)
			TM_SDA = 0;
		else
			TM_SDA = 1;
		DATA <<= 1;
		TM_SCL = 0;
		DelayUs(TM_TIME);
		TM_SCL = 1;
		DelayUs(TM_TIME);
		TM_SCL = 0;
		DelayUs(TM_TIME);
	}
}
/**********************************************��������***************************************************** 
* ��������:  Tm165() 
* �������:  
* ���ز���:   
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/24
************************************************************************************************************/ 
void TM1650_Init(void) {
    DelayMs(30);
    PE_DDR_DDR1 = 1;
    PE_CR1_C11 = 1;
    PE_CR2_C21 = 1;
    
    PE_DDR_DDR2 = 1;
    PE_CR1_C12 = 1;
    PE_CR2_C22 = 1;
    DelayMs(30);
	TM1650_Send(DEFAULT_SETTING, NORMAL_DISPLAY);
    //TM1650_Send(DEFAULT_SETTING, 0x00);
    //TM1650_Send(DEFAULT_SETTING, 0x70);
}
/*---------------------------------------------------------------*-
 * TM1650_Display()
 * 
 * Display the number on the specified postion or Send
 * initialization commands.
-*---------------------------------------------------------------*/
void TM1650_Send(u8 CMD, u8 DATA)
{
	TM1650_Start();
	TM1650_Write_Byte(CMD);	
	TM1650_ACK();
	TM1650_Write_Byte(DATA);
	TM1650_ACK();
	TM1650_Stop();
}
/**********************************************��������***************************************************** 
* ��������: void Tm1650(u8 num1, u8 num2,u8 pos) 
* �������: u8 num1, u8 num2,u8 pos 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/24
************************************************************************************************************/ 
void Tm1650Show(u8 num1, u8 num2,u8 pos) { 
    u8 data = 0;
    TM1650_Send(FIRST_POSITON, Digital_tube_coding[num1]);
    data = Digital_tube_coding[num2];
    if(pos > 0) {
        data = (Digital_tube_coding[num2] | 0x10 );
    }
    TM1650_Send(SECOND_POSITION, data);
}




