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
#ifndef __ELECUR_H
#define __ELECUR_H

#include "Type.h"

/**********************************************函数定义***************************************************** 
* 函数名称: void ElecurInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
void ElecurInit(void);
/**********************************************函数定义***************************************************** 
* 函数名称: u16 ElecurGet(u8 chx) 
* 输入参数: u8 chx 
* 返回参数: u16  
* 功    能: 获取电流  
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
u16 ElecurGet(u8 chx);

#endif


