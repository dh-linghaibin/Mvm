/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：Fan.h
*
* 文件标识：
* 摘    要：
*
*
* 当前版本：
* 作    者：lhb Steven
* 完成日期：2016/8/23
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#ifndef __FAN_H
#define __FAN_H

#include "Type.h"

#define FAN_0   PF_ODR_ODR0 /*风扇1*/
#define FAN_1   PB_ODR_ODR7 
#define FAN_2   PE_ODR_ODR6
#define FAN_3   PC_ODR_ODR4
#define FAN_4   PC_ODR_ODR3
#define FAN_5   PC_ODR_ODR2
#define FAN_6   PC_ODR_ODR1
#define FAN_7   PE_ODR_ODR5
#define FAN_8   PC_ODR_ODR5
#define FAN_9   PC_ODR_ODR6
#define FAN_10   PC_ODR_ODR7
#define FAN_11   PG_ODR_ODR0
#define FAN_12   PG_ODR_ODR1
#define FAN_13   PG_ODR_ODR2
#define FAN_14   PG_ODR_ODR3
#define FAN_15   PG_ODR_ODR4
#define FAN_16   PI_ODR_ODR0
#define FAN_17   PG_ODR_ODR5
#define FAN_18   PG_ODR_ODR6
#define FAN_19   PG_ODR_ODR7
#define FAN_20   PE_ODR_ODR4
#define FAN_21   PE_ODR_ODR3
#define FAN_22   PE_ODR_ODR0
#define FAN_23   PD_ODR_ODR0
#define FAN_24   PD_ODR_ODR2
#define FAN_25   PD_ODR_ODR3
#define FAN_26   PD_ODR_ODR4
#define FAN_27   PD_ODR_ODR5
#define FAN_28   PD_ODR_ODR6
#define FAN_29   PD_ODR_ODR7
#define FAN_30   PA_ODR_ODR2
#define FAN_31   PA_ODR_ODR1

typedef struct fan{
    u8 speed;//保存风扇速度
    u8 dr;//io口方向
}fan;
/**********************************************函数定义***************************************************** 
* 函数名称: void FanInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void FanInit(void);
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSelect(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 测试  
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void FanSelect(u8 cmd ,u8 dr);
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSetSer(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 风扇控制服务函数  
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void FanSetSer(void);
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSpeedSet(u8 chx, u8 speed) 
* 输入参数: u8 chx, u8 speed 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
void FanSpeedSet(u8 chx, u8 speed);
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSelfInspection(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 风扇自检  
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
u8 FanSelfInspection(void);
/**********************************************函数定义***************************************************** 
* 函数名称: void FanAllSet(u8 mode) 
* 输入参数: u8 mode 
* 返回参数: void  
* 功    能: mode 0:全部关闭 1：全部打开 2：半流  
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
void FanAllSet(u8 mode);
/**********************************************函数定义***************************************************** 
* 函数名称: u8 FanErrorNum(u8 num) 
* 输入参数: u8 num 
* 返回参数: u8  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
u8 FanErrorNum(u8 num);
/**********************************************函数定义***************************************************** 
* 函数名称: u16 FanGetAllcur(u8 num) 
* 输入参数: u8 num 
* 返回参数: u16  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
u16 FanGetAllcur(u8 num);

#endif


