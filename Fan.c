/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：Fan,c
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
#include "Fan.h"
#include "Delay.h"
#include "Elecur.h"

/*风扇结构体*/
static fan fan_Arr[32];
static u8 huai[32];
static u8 huai_arr[32];
static u16 cur_all[8];//七组电流值   增加一组
static u8 huai_jl[10];//每一组坏的电机记录
//#define GPBCON  (*(volatile unsigned int *)0x5029)
//
//const unsigned int fan_gpio_adr[28] = {
//0x5028,
//};
#define FAN_BEST    11
#define FAN_HALF    5    
/**********************************************函数定义***************************************************** 
* 函数名称: void FanInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void FanInit(void) { 
    PF_DDR_DDR0 = 1;
    PF_CR1_C10 = 1;
    PF_CR2_C20 = 1;
    
    PB_DDR_DDR7 = 1;
    PB_CR1_C17 = 1;
    PB_CR2_C27 = 1;
    
    PE_DDR_DDR6 = 1;
    PE_CR1_C16 = 1;
    PE_CR2_C26 = 1;
    
    PC_DDR_DDR4 = 1;
    PC_CR1_C14 = 1;
    PC_CR2_C24 = 1;
    
    PC_DDR_DDR2 = 1;
    PC_CR1_C12 = 1;
    PC_CR2_C22 = 1;
    
    PC_DDR_DDR3 = 1;
    PC_CR1_C13 = 1;
    PC_CR2_C23 = 1;
    
    PC_DDR_DDR1 = 1;
    PC_CR1_C11 = 1;
    PC_CR2_C21 = 1;
    
    PE_DDR_DDR5 = 1;
    PE_CR1_C15 = 1;
    PE_CR2_C25 = 1;
    
    PC_DDR_DDR5 = 1;
    PC_CR1_C15 = 1;
    PC_CR2_C25 = 1;
    
    PC_DDR_DDR6 = 1;
    PC_CR1_C16 = 1;
    PC_CR2_C26 = 1;
    
    PC_DDR_DDR7 = 1;
    PC_CR1_C17 = 1;
    PC_CR2_C27 = 1;
    
    PG_DDR_DDR0 = 1;
    PG_CR1_C10 = 1;
    PG_CR2_C20 = 1;
    
    PG_DDR_DDR1 = 1;
    PG_CR1_C11 = 1;
    PG_CR2_C21 = 1;
    
    PG_DDR_DDR2 = 1;
    PG_CR1_C12 = 1;
    PG_CR2_C22 = 1;
    
    PG_DDR_DDR3 = 1;
    PG_CR1_C13 = 1;
    PG_CR2_C23 = 1;
    
    PG_DDR_DDR4 = 1;
    PG_CR1_C14 = 1;
    PG_CR2_C24 = 1;
    
    PI_DDR_DDR0 = 1;
    PI_CR1_C10 = 1;
    PI_CR2_C20 = 1;
    
    PG_DDR_DDR5 = 1;
    PG_CR1_C15 = 1;
    PG_CR2_C25 = 1;
    
    PG_DDR_DDR6 = 1;
    PG_CR1_C16 = 1;
    PG_CR2_C26 = 1;
    
    PG_DDR_DDR7 = 1;
    PG_CR1_C17 = 1;
    PG_CR2_C27 = 1;
    
    PE_DDR_DDR4 = 1;
    PE_CR1_C14 = 1;
    PE_CR2_C24 = 1;
    
    PE_DDR_DDR3 = 1;
    PE_CR1_C13 = 1;
    PE_CR2_C23 = 1;
    
    PE_DDR_DDR0 = 1;
    PE_CR1_C10 = 1;
    PE_CR2_C20 = 1;
    
    PD_DDR_DDR0 = 1;
    PD_CR1_C10 = 1;
    PD_CR2_C20 = 1;
    
    PD_DDR_DDR2 = 1;
    PD_CR1_C12 = 1;
    PD_CR2_C22 = 1;
    
    PD_DDR_DDR3 = 1;
    PD_CR1_C13 = 1;
    PD_CR2_C23 = 1;
    
    PD_DDR_DDR4 = 1;
    PD_CR1_C14 = 1;
    PD_CR2_C24 = 1;
    
    PD_DDR_DDR5 = 1;
    PD_CR1_C15 = 1;
    PD_CR2_C25 = 1;
        
    PD_DDR_DDR6 = 1;
    PD_CR1_C16 = 1;
    PD_CR2_C26 = 1;
    
    PD_DDR_DDR7 = 1;
    PD_CR1_C17 = 1;
    PD_CR2_C27 = 1;
    
    PA_DDR_DDR2 = 1;
    PA_CR1_C12 = 1;
    PA_CR2_C22 = 1;
    
    PA_DDR_DDR1 = 1;
    PA_CR1_C11 = 1;
    PA_CR2_C21 = 1;
    for(u8 i = 0; i < 32;i++) {
        FanSelect(i,0);
    }
    
    for(u8 i = 0; i < 32;i++) {
        fan_Arr[i].speed = 0x00;
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSelect(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 测试  
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void FanSelect(u8 cmd ,u8 dr) {
    switch( cmd ) {
    case 0:
        FAN_0 = dr;
        break;
    case 1:
        FAN_1 = dr;
        break;
    case 2:
        FAN_2 = dr;
        break;
    case 3:
        FAN_3 = dr;
        break;
    case 4:
        FAN_4 = dr;
        break;
    case 5:
        FAN_5 = dr;
        break;
    case 6:
        FAN_6 = dr;
        break;
    case 7:
        FAN_7 = dr;
        break;
    case 8:
        FAN_8 = dr;
        break;
    case 9:
        FAN_9 = dr;
        break;
    case 10:
        FAN_10 = dr;
        break;
    case 11:
        FAN_11 = dr;
        break;
    case 12:
        FAN_12 = dr;
        break;
    case 13:
        FAN_13 = dr;
        break;
    case 14:
        FAN_14 = dr;
        break;
    case 15:
        FAN_15 = dr;
        break;
    case 16:
        FAN_16 = dr;
        break;
    case 17:
        FAN_17 = dr;
        break;
    case 18:
        FAN_18 = dr;
        break;
    case 19:
        FAN_19 = dr;
        break;
    case 20:
        FAN_20 = dr;
        break;
    case 21:
        FAN_21 = dr;
        break;
    case 22:
        FAN_22 = dr;
        break;
    case 23:
        FAN_23 = dr;
        break;
    case 24:
        FAN_24 = dr;
        break;
    case 25:
        FAN_25 = dr;
        break;
    case 26:
        FAN_26 = dr;
        break;
    case 27:
        FAN_27 = dr;
        break;
    case 28:
        FAN_28 = dr;
        break;
    case 29:
        FAN_29 = dr;
        break;
    case 30:
        FAN_30 = dr;
        break;
    case 31:
        FAN_31 = dr;
        break;
    default:
        break;
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSelectLock(u8 num) 
* 输入参数: u8 num 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/26
************************************************************************************************************/ 
void FanSelectLock(u8 cmd ,u8 dr) { 
    if(huai[cmd] == 1) {
        switch( cmd ) {
        case 0:
            FAN_0 = dr;
            break;
        case 1:
            FAN_1 = dr;
            break;
        case 2:
            FAN_2 = dr;
            break;
        case 3:
            FAN_3 = dr;
            break;
        case 4:
            FAN_4 = dr;
            break;
        case 5:
            FAN_5 = dr;
            break;
        case 6:
            FAN_6 = dr;
            break;
        case 7:
            FAN_7 = dr;
            break;
        case 8:
            FAN_8 = dr;
            break;
        case 9:
            FAN_9 = dr;
            break;
        case 10:
            FAN_10 = dr;
            break;
        case 11:
            FAN_11 = dr;
            break;
        case 12:
            FAN_12 = dr;
            break;
        case 13:
            FAN_13 = dr;
            break;
        case 14:
            FAN_14 = dr;
            break;
        case 15:
            FAN_15 = dr;
            break;
        case 16:
            FAN_16 = dr;
            break;
        case 17:
            FAN_17 = dr;
            break;
        case 18:
            FAN_18 = dr;
            break;
        case 19:
            FAN_19 = dr;
            break;
        case 20:
            FAN_20 = dr;
            break;
        case 21:
            FAN_21 = dr;
            break;
        case 22:
            FAN_22 = dr;
            break;
        case 23:
            FAN_23 = dr;
            break;
        case 24:
            FAN_24 = dr;
            break;
        case 25:
            FAN_25 = dr;
            break;
        case 26:
            FAN_26 = dr;
            break;
        case 27:
            FAN_27 = dr;
            break;
        case 28:
            FAN_28 = dr;
            break;
        case 29:
            FAN_29 = dr;
            break;
        case 30:
            FAN_30 = dr;
            break;
        case 31:
            FAN_31 = dr;
            break;
        default:
            break;
        }
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSetSer(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 风扇控制服务函数  
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void FanSetSer(void) { 
    static u8 fan_count = 0;
    /*总周期计数*/
    if(fan_count < 10) {
        fan_count++;
    } else {
        fan_count = 0;
    }
    /*风扇*/
    for(u8 i = 0;i < 32;i++) {
        if(fan_count < fan_Arr[i].speed) {
            if(fan_Arr[i].dr == 0) {
                fan_Arr[i].dr = 1;
                FanSelect(i,1);
            }
        } else {
            if(fan_Arr[i].dr == 1) {
                fan_Arr[i].dr = 0;
                FanSelect(i,0);
            }
        }
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSpeedSet(u8 chx, u8 speed) 
* 输入参数: u8 chx, u8 speed 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
void FanSpeedSet(u8 chx, u8 speed) { 
    if(huai[chx] == 1) {
        fan_Arr[chx].speed = speed;
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanAllSet(u8 mode) 
* 输入参数: u8 mode 
* 返回参数: void  
* 功    能: mode 0:全部关闭 1：全部打开 2：半流  
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
void FanAllSet(u8 mode) { 
    if(mode == 0) {
        for(u8 i = 0; i < 32;i++) {
            //fan_Arr[i].speed = 0x00;
            FanSelect(i,0);
        }
    } else if(mode == 1) {
        for(u8 i = 0; i < 32;i++) {
            if(huai[i] == 1) {
                //fan_Arr[i].speed = FAN_BEST;
                FanSelect(i,1);
            }
        }
    } else if(mode == 2) {
        for(u8 i = 0; i < 32;i++) {
            if(huai[i] == 1) {
                //fan_Arr[i].speed = FAN_HALF;
                FanSelect(i,1);
            }
        }
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSelfInspection(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 风扇自检  
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
u8 FanSelfInspection(void) { 
    u16 spec[7][8];
    u8 fazhi_num = 0;//故障数量
    u8 haha = 0;
    u16 cur_all_l[3][8];//dianliu
    
    for(u8 g = 0;g < 7;g++) {
        for(u8 s = 0;s < 8;s++) {//增加一路电流检测
            spec[g][s] = 0x00;
        }
    }
    for(u8 h = 0;h < 32;h++) {
        huai_arr[h] = 0x00;
    }
    for(u8 h = 0;h < 8;h++) {//增加一组
        cur_all[h] = 0x00;
    }
    for(u8 h = 0;h < 9;h++) {//增加一组
        huai_jl[h] = 0x00;
    }
    for(u8 i = 0; i < 32;i++) {
        //fan_Arr[i].speed = 0;
        FanSelect(i,0);
    }
    DelayMs(5000);//500
    for(u8 a_i = 0;a_i < 4;a_i++) {
        for(u8 i = 0; i < 32;i++) {
            //fan_Arr[i].speed = 0;
            FanSelect(i,0);
        }
        DelayMs(100);//100
        switch( a_i ) {
        case 0:
//            fan_Arr[0].speed = FAN_BEST;
//            fan_Arr[4].speed = FAN_BEST;
//            fan_Arr[8].speed = FAN_BEST;
//            fan_Arr[12].speed = FAN_BEST;
//            fan_Arr[16].speed = FAN_BEST;
//            fan_Arr[20].speed = FAN_BEST;
//            fan_Arr[24].speed = FAN_BEST;
            FAN_0 = 1;
            FAN_4 = 1;
            FAN_8 = 1;
            FAN_12 = 1;
            FAN_16 = 1;
            FAN_20 = 1;
            FAN_24 = 1;
            //增加一组
            FAN_28 = 1;
            //DelayMs(120);//10
            break;
        case 1:
//            fan_Arr[1].speed = FAN_BEST;
//            fan_Arr[5].speed = FAN_BEST;
//            fan_Arr[9].speed = FAN_BEST;
//            fan_Arr[13].speed = FAN_BEST;
//            fan_Arr[17].speed = FAN_BEST;
//            fan_Arr[21].speed = FAN_BEST;
//            fan_Arr[25].speed = FAN_BEST;
            FAN_1 = 1;
            FAN_5 = 1;
            FAN_9 = 1;
            FAN_13 = 1;
            FAN_17 = 1;
            FAN_21 = 1;
            FAN_25 = 1;
            //增加一组
            FAN_29 = 1;
            //DelayMs(120);
            break;
        case 2:
//            fan_Arr[2].speed = FAN_BEST;
//            fan_Arr[6].speed = FAN_BEST;
//            fan_Arr[10].speed = FAN_BEST;
//            fan_Arr[14].speed = FAN_BEST;
//            fan_Arr[18].speed = FAN_BEST;
//            fan_Arr[22].speed = FAN_BEST;
//            fan_Arr[26].speed = FAN_BEST;
            FAN_2 = 1;
            FAN_6 = 1;
            FAN_10 = 1;
            FAN_14 = 1;
            FAN_18 = 1;
            FAN_22 = 1;
            FAN_26 = 1;
            //增加一组
            FAN_30 = 1;
            //DelayMs(120);
            break;
        case 3:
//            fan_Arr[3].speed = FAN_BEST;
//            fan_Arr[7].speed = FAN_BEST;
//            fan_Arr[11].speed = FAN_BEST;
//            fan_Arr[15].speed = FAN_BEST;
//            fan_Arr[19].speed = FAN_BEST;
//            fan_Arr[23].speed = FAN_BEST;
//            fan_Arr[27].speed = FAN_BEST;
            FAN_3 = 1;
            FAN_7 = 1;
            FAN_11 = 1;
            FAN_15 = 1;
            FAN_19 = 1;
            FAN_23 = 1;
            FAN_27 = 1;
            //增加一组
            FAN_31 = 1;
            //DelayMs(120);
            break;
        default:
            break;
        }
        DelayMs(400);
        for(u8 j = 0;j < 6;j++) {
            DelayMs(200);//300
            for(u8 nj = 0;nj < 8;nj++) {//增加一路电流检测
                spec[nj][j] = ElecurGet(nj);
            }
        }
        //查询风扇情况
        for(u8 x = 0;x < 8;x++) {//增加一组
            u16 fazhi = 0;
            if(spec[x][0] > 8000) {
                fazhi = 2000;
            } else if(spec[x][0] > 7000) {
                fazhi = 2000;
            } else if(spec[x][0] > 5000) {
                fazhi = 200;
            } else if(spec[x][0] > 4000) { 
                fazhi = 200;
            } else if(spec[x][0] > 2200) { 
                fazhi = 200;
            } else {
                fazhi = 10000;
            }
            if( (spec[x][5] > 2200) && (spec[x][4] > 2200) ){ 
                if(spec[x][0] > spec[x][5]) {
                    if( (spec[x][0] - spec[x][5]) > fazhi) {
                        huai[a_i+(x*4)] = 1;
                        //cur_all[x] += spec[x][5];
                    } else {
                        //错误
                        huai[a_i+(x*4)] = 0;
                        //huai_arr[fazhi_num] = ((a_i+(x*4))+1);a_i
                        huai_arr[a_i*x] = ((a_i+(x*4))+1);
                        fazhi_num++;
                        huai_jl[x]++;
                    }
                } else {
                    //错误
                    huai[a_i+(x*4)] = 0;
                    //huai_arr[fazhi_num] = ((a_i+(x*4))+1);
                    huai_arr[a_i*x] = ((a_i+(x*4))+1);
                    fazhi_num++;
                    huai_jl[x]++;
                }
               
            } else {
                //错误
                huai[a_i+(x*4)] = 0;
                //huai_arr[fazhi_num] = ((a_i+(x*4))+1);
                huai_arr[a_i*x] = ((a_i+(x*4))+1);
                fazhi_num++;
                huai_jl[x]++;
            }
            haha++;
        }
    }
    //记录电流
    FanAllSet(0);
    FanAllSet(1);
    DelayMs(5000);//150
    DelayMs(5000);//150
    for(u8 nj = 0;nj < 8;nj++) {//增加一组
        cur_all_l[0][nj] = ElecurGet(nj);
    }
    DelayMs(200);//150
    for(u8 nj = 0;nj < 8;nj++) {//增加一组
        cur_all_l[1][nj] = ElecurGet(nj);
    }
    DelayMs(200);//150
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
        cur_all[hh] = cur_all_l[1][hh];
    }
    //关闭所有风扇
    for(u8 i = 0; i < 32;i++) {
        //fan_Arr[i].speed = 0;
        FanSelect(i,0);
    }
    DelayMs(1000);//150
    huai_jl[9] = fazhi_num;
    return fazhi_num;
}
/**********************************************函数定义***************************************************** 
* 函数名称: u8 FanFandError(u8 num) 
* 输入参数: u8 num 
* 返回参数: u8  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/26
************************************************************************************************************/ 
u8 FanFandError(u8 num) { 
    u16 spec[7][8];//增加一组
    u8 fazhi_num = 0;//故障数量
    u8 haha = 0;
    u16 cur_all_l[3][8];//dianliu
    u16 fazhi = 0;
    u8 fan_arr[4];//储存哪个四个风扇
    
    huai_jl[9] -= huai_jl[num];
    huai_jl[num] = 0;
    //寻找风扇
    for(u8 g = 0;g < 4;g++) {
        fan_arr[g] = ((num*4)+g);
    }
    
    for(u8 g = 0;g < 7;g++) {
        for(u8 s = 0;s < 8;s++) {//增加一组
            spec[g][s] = 0x00;
        }
    }
    
    //关闭风扇
    for(u8 i = 0; i < 4;i++) {
        FanSelect(fan_arr[i],0);
    }
    DelayMs(5000);//500
    DelayMs(5000);//500
    for(u8 a_i = 0;a_i < 4;a_i++) {
        for(u8 i = 0; i < 4;i++) {
            FanSelect(fan_arr[i],0);
        }
        DelayMs(1000);//100
        FanSelect(fan_arr[a_i],1);
        DelayMs(400);
        for(u8 j = 0;j < 6;j++) {
            DelayMs(200);//300
            spec[0][j] = ElecurGet(num);
        }
        //查询风扇情况
        if(spec[0][0] > 8000) {
            fazhi = 2000;
        } else if(spec[0][0] > 7000) {
            fazhi = 2000;
        } else if(spec[0][0] > 5000) {
            fazhi = 220;
        } else if(spec[0][0] > 4000) { 
            fazhi = 200;
        } else if(spec[0][0] > 2200) { 
            fazhi = 200;
        } else {
            fazhi = 10000;
        }
        if( (spec[0][5] > 2200) && (spec[0][4] > 2200) ){ 
            if(spec[0][0] > spec[0][5]) {
                if( (spec[0][0] - spec[0][5]) > fazhi) {
                    huai[a_i+(num*4)] = 1;
                    //cur_all[x] += spec[x][5];
                } else {
                    //错误
                    huai[a_i+(num*4)] = 0;
                    //huai_arr[fazhi_num] = ((a_i+(num*4))+1);
                    huai_arr[a_i*num] = ((a_i+(num*4))+1);
                    fazhi_num++;
                    huai_jl[num]++;
                }
            } else {
                //错误
                huai[a_i+(num*4)] = 0;
                //huai_arr[fazhi_num] = ((a_i+(num*4))+1);
                huai_arr[a_i*num] = ((a_i+(num*4))+1);
                fazhi_num++;
                huai_jl[num]++;
            }
           
        } else {
            //错误
            huai[a_i+(num*4)] = 0;
            //huai_arr[fazhi_num] = ((a_i+(num*4))+1);
            huai_arr[a_i*num] = ((a_i+(num*4))+1);
            fazhi_num++;
            huai_jl[num]++;
        }
        haha++;
    }
    //记录电流
    //关闭风扇
    //关闭风扇
    for(u8 i = 0; i < 4;i++) {
        FanSelect(fan_arr[i],0);
    }
    for(u8 i = 0; i < 4;i++) {
        FanSelectLock(fan_arr[i],1);
    }
    DelayMs(5000);//150
    DelayMs(5000);//150
    cur_all_l[0][0] = ElecurGet(num);
    DelayMs(200);//150
    cur_all_l[1][0] = ElecurGet(num);
    DelayMs(200);//150
    cur_all_l[1][0] = ElecurGet(num);
    for(u8 ii = 0; ii < 3; ii++) {
        for(u8 jj = 0; ii + jj < 2; jj++) {
            if(cur_all_l[jj][0] > cur_all_l[jj + 1][0]) {
                u16 temp = cur_all_l[jj][0];
                cur_all_l[jj][0] = cur_all_l[jj + 1][0];
                cur_all_l[jj + 1][0] = temp;
            }
        }
    }
    cur_all[num] = cur_all_l[1][0];
    //关闭所有风扇
    for(u8 i = 0; i < 4;i++) {
        FanSelect(fan_arr[i],0);
    }
    DelayMs(1000);//150
    huai_jl[9] += huai_jl[num];
    fazhi_num = huai_jl[9];
    return fazhi_num;
}
/**********************************************函数定义***************************************************** 
* 函数名称: u8 FanErrorNum(u8 num) 
* 输入参数: u8 num 
* 返回参数: u8  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
u8 FanErrorNum(u8 num) { 
    return huai_arr[num];
}
/**********************************************函数定义***************************************************** 
* 函数名称: u16 FanGetAllcur(u8 num) 
* 输入参数: u8 num 
* 返回参数: u16  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
u16 FanGetAllcur(u8 num) { 
    return cur_all[num];
}














