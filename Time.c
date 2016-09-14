/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：time,c
*
* 文件标识：ds
* 摘    要：定时器，用于休眠
*
*
* 当前版本：v1.0
* 作    者：lhb Steven
* 完成日期：2016/3/18
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Time.h"
#include "Fan.h"

void TimerInit(void) {
    TIM4_IER = 0x00;//       
    TIM4_EGR = 0x01;// 
    TIM4_PSCR = 0x04;// 计数器时钟=主时钟/128=16MHZ/128
    TIM4_ARR = 0x90;// 设定重装载时的寄存器值，255是最大值
    //TIM4_CNTR = 0x00;// 设定计数器的初值
    // 定时周期=(ARR+1)*64=16320uS
    TIM4_IER = 0x01;//   
    TIM4_CR1 = 0x01;  
}

static u16 sec_flag = 0;

u16 TimerGetSec(void) {
    return sec_flag;
}

void TimerSetSec(u8 data) {
    sec_flag = data;
}

#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
    static u8 dr = 0;
    TIM4_SR = 0x00;
    //FanSetSer();
    if(dr == 0) {
        dr = 1;
        FAN_0 = 0;
        FAN_1 = 0;
        FAN_2 = 0;
        FAN_3 = 0;
        FAN_4 = 0;
        FAN_5 = 0;
        FAN_6 = 0;
        FAN_7 = 0;
        FAN_8 = 0;
        FAN_9 = 0;
        FAN_10 = 0;
        FAN_11 = 0;
        FAN_12 = 0;
        FAN_13 = 0;
        FAN_14 = 0;
        FAN_15 = 0;
        FAN_16 = 0;
        FAN_17 = 0;
        FAN_18 = 0;
        FAN_19 = 0;
        FAN_20 = 0;
        FAN_21 = 0;
        FAN_22 = 0;
        FAN_23 = 0;
        FAN_24 = 0;
        FAN_25 = 0;
        FAN_26 = 0;
        FAN_27 = 0;
        
    } else {
        dr = 0;
        FAN_0 = 1;
        FAN_1 = 1;
        FAN_2 = 1;
        FAN_3 = 1;
        FAN_4 = 1;
        FAN_5 = 1;
        FAN_6 = 1;
        FAN_7 = 1;
        FAN_8 = 1;
        FAN_9 = 1;
        FAN_10 = 1;
        FAN_11 = 1;
        FAN_12 = 1;
        FAN_13 = 1;
        FAN_14 = 1;
        FAN_15 = 1;
        FAN_16 = 1;
        FAN_17 = 1;
        FAN_18 = 1;
        FAN_19 = 1;
        FAN_20 = 1;
        FAN_21 = 1;
        FAN_22 = 1;
        FAN_23 = 1;
        FAN_24 = 1;
        FAN_25 = 1;
        FAN_26 = 1;
        FAN_27 = 1;
    }
    
    return;
}



