/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：main
*
* 文件标识：
* 摘    要：单片机STM8S207R8T6
*
*
* 当前版本：
* 作    者：lhb Steven
* 完成日期：2016/8/23
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Type.h"
#include "Sys.h"
#include "Fan.h"
#include "Ntc.h"
#include "Tm1650.h"
#include "Delay.h"
#include "Elecur.h"
#include "Time.h"
#include "Menu.h"
#include "Com.h"
#include "Eeprom.h"
/**********************************************函数定义***************************************************** 
* 函数名称: int main( void ) 
* 输入参数:  void  
* 返回参数: int  
* 功    能: zhu  
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
int main( void ) {
    SysInit();
    EeepromInit();
    FanInit();
    ElecurInit();
    NtcInit();
    TM1650_Init();
    Tm1650Show(10,0,0);
    //TimerInit();
    ComInit();
    INTEN
    MenuInit();
    while(1) {
        static u16 count_time = 0;
        if(count_time < 10000) {
            count_time++;
        } else {
            count_time = 0;
            //处理函数
            MenuTempSer();
        }
        MenuComSer();
    }
}

