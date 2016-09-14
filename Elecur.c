/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：
*
* 文件标识：
* 摘    要：
*
*
* 当前版本：
* 作    者：lhb Steven
* 完成日期：2016/8/24
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Elecur.h"
#include "Ntc.h"
/**********************************************函数定义***************************************************** 
* 函数名称: void ElecurInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
void ElecurInit(void) { 
    PB_DDR_DDR0 = 0;
    PB_CR1_C10 = 0;
    PB_CR2_C20 = 0;
    
    PB_DDR_DDR1 = 0;
    PB_CR1_C11 = 0;
    PB_CR2_C21 = 0;
    
    PB_DDR_DDR2 = 0;
    PB_CR1_C12 = 0;
    PB_CR2_C22 = 0;
    
    PB_DDR_DDR3 = 0;
    PB_CR1_C13 = 0;
    PB_CR2_C23 = 0;
    
    PB_DDR_DDR4 = 0;
    PB_CR1_C14 = 0;
    PB_CR2_C24 = 0;
    
    PB_DDR_DDR5 = 0;
    PB_CR1_C15 = 0;
    PB_CR2_C25 = 0;

    //v2版本 PE7
    PE_DDR_DDR7 = 0;
    PE_CR1_C17 = 0;
    PE_CR2_C27 = 0;
}
/**********************************************函数定义***************************************************** 
* 函数名称: u16 ElecurGet(u8 chx) 
* 输入参数: u8 chx 
* 返回参数: u16  
* 功    能: 获取电流  
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
u16 ElecurGet(u8 chx) { 
    u8 ch = 0;
    switch( chx ) {
    case 0:
        ch = 1;
        break;
    case 1:
        ch = 8;
        break;
    case 2:
        ch = 0;
        break;
    case 3:
        ch = 2;
        break;
    case 4:
        ch = 6;
        break;
    case 5:
        ch = 5;
        break;
    case 6:
        ch = 4;
        break;
    case 7://计划
        ch = 3;
        break;
    default:
        break;
    }
    return NtcGet(ch);
}





