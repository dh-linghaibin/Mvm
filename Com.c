/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�
*
* �ļ���ʶ��
* ժ    Ҫ��
*
*
* ��ǰ�汾��
* ��    �ߣ�lhb Steven
* ������ڣ�2016/7/11
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/

#include "Com.h"
#include "Delay.h"
#include "Time.h"

/*��������*/
static com_data com_data_one;

void ComInit(void) {
//    PA_DDR &= ~BIT(5);//TX
//    PA_CR1 |= BIT(5); 
//    PA_CR2 &= ~BIT(5);
//
//    PA_DDR |= BIT(4);//RX
//    PA_CR1 |= BIT(4); 
//    PA_CR2 |= BIT(4);

    UART1_CR1=0x00;
    UART1_CR2=0x00;
    UART1_CR3=0x00; 
    UART1_BRR2=0x02;//02 0a
    UART1_BRR1=0x68;//68 08
    UART1_CR2=0x2c;//������գ����ͣ��������ж�
}
/**********************************************��������***************************************************** 
* ��������: void ComSend(u8 cmd, u8 dat1,u8 dat2,u8 dat3) 
* �������: u8 cmd, u8 dat1,u8 dat2,u8 dat3 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
void ComSend(u8 cmd, u8 dat1,u8 dat2,u8 dat3,u8 dat4,u8 dat5) { 
    u8 i = 0;
    u16 cheek = 0; 
    u8 data[10];
    /**/
    data[0] = com_head_frame;
    data[1] = cmd;
    data[2] = dat1;
    data[3] = dat2;
    data[4] = dat3;
    data[5] = dat4;
    data[6] = dat5;
    data[9] = com_tail_frame;
    /*�ۼ�У��*/
    for(i = 1;i < 6;i++) {
       cheek += data[i];
    }
    data[7] = (u8)cheek;
    data[8] = (u8)(cheek>>8);
    DelayMs(20);
    for(i = 0;i < 10;i++) {
        while((UART1_SR & 0x80) == 0x00);
        UART1_DR = data[i];
        DelayMs(1);
    }
}
/**********************************************��������***************************************************** 
* ��������: u8 ComGetFlag(void) 
* �������: void 
* ���ز���: u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
u8 ComGetFlag(void) { 
    return com_data_one.rs_ok;
}

/**********************************************��������***************************************************** 
* ��������: u8 ComGetDate(u8 cmd) 
* �������: u8 cmd 
* ���ز���: u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
u8 ComGetDate(u8 cmd) { 
    return com_data_one.data[cmd];
}
/**********************************************��������***************************************************** 
* ��������: void ComSetFlag(u8 cmd) 
* �������: u8 cmd 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/23
************************************************************************************************************/ 
void ComSetFlag(u8 cmd) { 
    com_data_one.rs_ok = 0x00;
}
/**********************************************��������***************************************************** 
* ��������: u8 ComCheck(void) 
* �������: void 
* ���ز���: u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/23
************************************************************************************************************/ 
u8 ComCheck(void) { 
    u16 num = 0;
    for(u8 i = 1;i < 6;i++) {
        num += com_data_one.data[i];
    }
    if(com_data_one.data[7] == (u8)num) {
        if(com_data_one.data[8] == (u8)(num>>8)) {
            return 0x01;
        } else {
            return 0x00;
        }
    } else {
        return 0x00;
    }
}


#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)
{
    u8 data;
    data = UART1_DR;
    /*�ȴ����ݽ������*/
    while((UART1_SR & 0x80) == 0x00);
    /*��ֹ������ͷ֡��ͻ*/
    if(com_data_one.rs_flag == 0x00) {
        if(data == com_head_frame) {
            com_data_one.rs_flag = 0x01;
        }    
    }
    /*��ʼ��������*/
    if(com_data_one.rs_flag > 0x00) {
        com_data_one.data[com_data_one.rs_flag-1] = data;
        com_data_one.rs_flag++;
        if(com_data_one.rs_flag == com_size+1) {
            if(data == com_tail_frame) {
                com_data_one.rs_ok = 0x01;
                com_data_one.rs_flag = 0x00;
            } else {
                com_data_one.rs_flag = 0x00;
            }
        }
    }
    return;
}




