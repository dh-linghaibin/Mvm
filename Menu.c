/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：Menu.c
*
* 文件标识：V
* 摘    要：菜单内核
*
*
* 当前版本：V1.0
* 作    者：lhb Steven
* 完成日期：2016/3/17
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Menu.h"
#include "Ntc.h"
#include "Tm1650.h"
#include "Delay.h"
#include "Elecur.h"
#include "Fan.h"
#include "Com.h"
#include "Eeprom.h"
/***********************************************变量声明*****************************************************
* 功    能: 菜单  
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
menu menu_n;
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
void MenuInit(void) { 
    if(EepromRead(10) != 0x55) {
        EepromWrite(10,0x55);
        EepromWrite(11,0x01);//工作模式
        EepromWrite(12,0);//选用温度计
        EepromWrite(13,45);//温度点
    }
    menu_n.mode = EepromRead(11);
    menu_n.temp_arr = EepromRead(12);
    for(u8 i = 0;i < 6;i++) {
        menu_n.tempSet[i] = EepromRead(13);
    }
    
    Tm1650Show(10,0,0);
    menu_n.fan_error = FanSelfInspection();//自检
    Tm1650Show(menu_n.fan_error%100/10,menu_n.fan_error%10,0);
}
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuTempSer(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 温度处理函数  
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
void MenuTempSer(void) { 
    //获取温度
    if(menu_n.mode == 1) {
        if(menu_n.temp_arr < 6) {
            menu_n.temp[menu_n.temp_arr] = NtcGetTemp(menu_n.temp_arr);
            if(menu_n.temp[menu_n.temp_arr] > menu_n.tempSet[menu_n.temp_arr]) {
                //打开风扇
               // if((menu_n.temp[menu_n.temp_arr] - menu_n.tempSet[menu_n.temp_arr]) > 10) {
                FanAllSet(1);//全速
                if(menu_n.cur_time < 50) {
                    menu_n.cur_time++;
                } else {
                    u16 cur_all_l[3][9];//dianliu //增加一组
                    //menu_n.cur_time = 0;
                    DelayMs(80);//150
                    for(u8 nj = 0;nj < 8;nj++) {//增加一组
                        cur_all_l[0][nj] = ElecurGet(nj);
                    }
                    DelayMs(80);//150
                    for(u8 nj = 0;nj < 8;nj++) {//增加一组
                        cur_all_l[1][nj] = ElecurGet(nj);
                    }
                    DelayMs(80);//150
                    for(u8 nj = 0;nj < 8;nj++) {//增加一组
                        cur_all_l[2][nj] = ElecurGet(nj);
                    }
                    for(u8 hh = 0;hh < 8;hh++) {//增加一组
                        for(u8 ii = 0; ii < 3; ii++) {
                            for(u8 jj = 0; ii + jj < 2; jj++) {
                                if(cur_all_l[jj][hh] > cur_all_l[jj + 1][hh]) {
                                    u16 temp = cur_all_l[jj][hh];
                                    cur_all_l[jj][hh] = cur_all_l[jj + 1][hh];
                                    cur_all_l[jj + 1][hh] = temp;
                                }
                            }
                        }
                    }
                    for(u8 hh = 0;hh < 8;hh++) {//增加一组
                        menu_n.cur_get[hh] = cur_all_l[1][hh];
                    }
                    //检测
                    for(u8 nj = 0;nj < 8;nj++) {//增加一组
                        //menu_n.cur_get[nj] = ElecurGet(nj);
                        if(FanGetAllcur(nj) > menu_n.cur_get[nj]) {
                            if((FanGetAllcur(nj) - menu_n.cur_get[nj]) > 750) {
                                if(menu_n.error_num[nj] < 4) {
                                    menu_n.error_num[nj]++;
                                } else {
                                    menu_n.error_num[nj] = 0;
                                    Tm1650Show(10,1,0);
                                    //menu_n.fan_error = FanSelfInspection();//自检
                                    menu_n.fan_error = FanFandError(nj);
                                    Tm1650Show(menu_n.fan_error%100/10,menu_n.fan_error%10,0);
                                    FanAllSet(1);//全速
                                    DelayMs(1000);
                                    menu_n.cur_time = 0;
                                    break;
                                }
                            } else {
                                //正常
                                menu_n.error_num[nj] = 0;
                            }
                        } else {
                            if((menu_n.cur_get[nj] - FanGetAllcur(nj)) > 750) {
                                if(menu_n.error_num[nj] < 4) {
                                    menu_n.error_num[nj]++;
                                } else {
                                    menu_n.error_num[nj] = 0;
                                    Tm1650Show(10,1,0);
                                    //menu_n.fan_error = FanSelfInspection();//自检
                                     menu_n.fan_error =  FanFandError(nj);
                                    Tm1650Show(menu_n.fan_error%100/10,menu_n.fan_error%10,0);
                                    FanAllSet(1);//全速
                                    DelayMs(1000);
                                    menu_n.cur_time = 0;
                                    break;
                                }
                            } else {
                                //正常
                                menu_n.error_num[nj] = 0;
                            }
                        }
                    }
                }
//                } else {
//                    FanAllSet(2);//半流
//                    menu_n.cur_time = 0;
//                }
            } else {
                //关闭风扇
                FanAllSet(0);
                menu_n.cur_time = 0;
            }
        }
    }
    //有故障发送
    if(menu_n.fan_error > 0) {
        static u16 error_time = 0;
        if(error_time < 60) {
            error_time++;
        } else {
            error_time = 0;
            ComSend(0x08,menu_n.fan_error,0x00,0x00,0x00,0x00);
        }
    }
    //数码管动态显示
    if(menu_n.show_time < 5) {
        menu_n.show_time++;
    } else {
        menu_n.show_time = 0;
        switch( menu_n.show_bit ) {
        case 0:
            Tm1650Show(menu_n.temp[menu_n.temp_arr]/10,menu_n.temp[menu_n.temp_arr]%10,1);
            menu_n.show_bit = 1;
            break;
        case 1:
            Tm1650Show(menu_n.fan_error%100/10,menu_n.fan_error%10,0);
            menu_n.show_bit = 2;
            break;
        case 2:
            Tm1650Show(11,menu_n.temp_arr%10,0);
            menu_n.show_bit = 0;
            break;
        case 3:
            break;
        default:
            break;
        }
        

    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuComSer(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
void MenuComSer(void) { 
    if(ComGetFlag() == 0x01) {
        ComSetFlag(0x00);
        if(ComCheck() == 0x01) {
            switch( ComGetDate(1) ) {
            case 0X01://开关风扇
                if( ComGetDate(2) == 0x00 ) {
                    FanSpeedSet(ComGetDate(3) - 1,0x00);
                } else if( ComGetDate(2) == 0x01 ) {
                    FanSpeedSet(ComGetDate(3) - 1,0xFF);
                } else {
                    FanSpeedSet(ComGetDate(3) - 1,0x7F);
                }
                ComSend(0x01,ComGetDate(2),ComGetDate(3),0x00,0x00,0x00);
                break;
            case 0x02://工作状态
                menu_n.mode = ComGetDate(2);
                ComSend(0x02,ComGetDate(2),0x00,0x00,0x00,0x00);
                EepromWrite(11,menu_n.mode);//工作模式
                break;
            case 0x03://设置温度点
                for(u8 i = 0;i < 6;i++) {
                    menu_n.tempSet[i] = ComGetDate(2);
                }
                ComSend(0x03,ComGetDate(2),0x00,0x00,0x00,0x00);
                EepromWrite(13,ComGetDate(2));//温度点
                break;
            case 0x04://查询温度
                ComSend(0x04,NtcGetTemp(menu_n.temp_arr),0x00,0x00,0x00,0x00);
                break;
            case 0x05://设置温度计
                menu_n.temp_arr = ComGetDate(2);
                ComSend(0x05,ComGetDate(2),0x00,0x00,0x00,0x00);
                EepromWrite(12,menu_n.temp_arr);//选用温度计
                break;
            case 0x06://查询故障
                Tm1650Show(10,0,0);
                menu_n.fan_error = FanSelfInspection();//自检
                Tm1650Show(menu_n.fan_error%100/10,menu_n.fan_error%10,0);
                ComSend(0x06,menu_n.fan_error,0x00,0x00,0x00,0x00);
                break;
            case 0x07://查询故障电机               
                ComSend(0x07,ComGetDate(2),FanErrorNum(ComGetDate(2)*4),
                                           FanErrorNum((ComGetDate(2)*4)+1),
                                           FanErrorNum((ComGetDate(2)*4)+2),
                                           FanErrorNum((ComGetDate(2)*4))+2);
                break;
            case 0x08:
                break;
            default:
                break;
            }
        } else {
            //校验错误
            ComSend(0x44,0x00,0x00,0x00,0x00,0x00);
        }
    }
}






