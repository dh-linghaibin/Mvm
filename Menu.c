/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�Menu.c
*
* �ļ���ʶ��V
* ժ    Ҫ���˵��ں�
*
*
* ��ǰ�汾��V1.0
* ��    �ߣ�lhb Steven
* ������ڣ�2016/3/17
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "Menu.h"
#include "Ntc.h"
#include "Tm1650.h"
#include "Delay.h"
#include "Elecur.h"
#include "Fan.h"
#include "Com.h"
#include "Eeprom.h"
/***********************************************��������*****************************************************
* ��    ��: �˵�  
* ��    ��: by lhb_steven
* ��    ��: 2016/8/25
************************************************************************************************************/ 
menu menu_n;
/**********************************************��������***************************************************** 
* ��������: void MenuInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/25
************************************************************************************************************/ 
void MenuInit(void) { 
    if(EepromRead(10) != 0x55) {
        EepromWrite(10,0x55);
        EepromWrite(11,0x01);//����ģʽ
        EepromWrite(12,0);//ѡ���¶ȼ�
        EepromWrite(13,45);//�¶ȵ�
    }
    menu_n.mode = EepromRead(11);
    menu_n.temp_arr = EepromRead(12);
    for(u8 i = 0;i < 6;i++) {
        menu_n.tempSet[i] = EepromRead(13);
    }
    
    Tm1650Show(10,0,0);
    menu_n.fan_error = FanSelfInspection();//�Լ�
    Tm1650Show(menu_n.fan_error%100/10,menu_n.fan_error%10,0);
}
/**********************************************��������***************************************************** 
* ��������: void MenuTempSer(void) 
* �������: void 
* ���ز���: void  
* ��    ��: �¶ȴ�����  
* ��    ��: by lhb_steven
* ��    ��: 2016/8/25
************************************************************************************************************/ 
void MenuTempSer(void) { 
    //��ȡ�¶�
    if(menu_n.mode == 1) {
        if(menu_n.temp_arr < 6) {
            menu_n.temp[menu_n.temp_arr] = NtcGetTemp(menu_n.temp_arr);
            if(menu_n.temp[menu_n.temp_arr] > menu_n.tempSet[menu_n.temp_arr]) {
                //�򿪷���
               // if((menu_n.temp[menu_n.temp_arr] - menu_n.tempSet[menu_n.temp_arr]) > 10) {
                FanAllSet(1);//ȫ��
                if(menu_n.cur_time < 50) {
                    menu_n.cur_time++;
                } else {
                    u16 cur_all_l[3][9];//dianliu //����һ��
                    //menu_n.cur_time = 0;
                    DelayMs(80);//150
                    for(u8 nj = 0;nj < 8;nj++) {//����һ��
                        cur_all_l[0][nj] = ElecurGet(nj);
                    }
                    DelayMs(80);//150
                    for(u8 nj = 0;nj < 8;nj++) {//����һ��
                        cur_all_l[1][nj] = ElecurGet(nj);
                    }
                    DelayMs(80);//150
                    for(u8 nj = 0;nj < 8;nj++) {//����һ��
                        cur_all_l[2][nj] = ElecurGet(nj);
                    }
                    for(u8 hh = 0;hh < 8;hh++) {//����һ��
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
                    for(u8 hh = 0;hh < 8;hh++) {//����һ��
                        menu_n.cur_get[hh] = cur_all_l[1][hh];
                    }
                    //���
                    for(u8 nj = 0;nj < 8;nj++) {//����һ��
                        //menu_n.cur_get[nj] = ElecurGet(nj);
                        if(FanGetAllcur(nj) > menu_n.cur_get[nj]) {
                            if((FanGetAllcur(nj) - menu_n.cur_get[nj]) > 750) {
                                if(menu_n.error_num[nj] < 4) {
                                    menu_n.error_num[nj]++;
                                } else {
                                    menu_n.error_num[nj] = 0;
                                    Tm1650Show(10,1,0);
                                    //menu_n.fan_error = FanSelfInspection();//�Լ�
                                    menu_n.fan_error = FanFandError(nj);
                                    Tm1650Show(menu_n.fan_error%100/10,menu_n.fan_error%10,0);
                                    FanAllSet(1);//ȫ��
                                    DelayMs(1000);
                                    menu_n.cur_time = 0;
                                    break;
                                }
                            } else {
                                //����
                                menu_n.error_num[nj] = 0;
                            }
                        } else {
                            if((menu_n.cur_get[nj] - FanGetAllcur(nj)) > 750) {
                                if(menu_n.error_num[nj] < 4) {
                                    menu_n.error_num[nj]++;
                                } else {
                                    menu_n.error_num[nj] = 0;
                                    Tm1650Show(10,1,0);
                                    //menu_n.fan_error = FanSelfInspection();//�Լ�
                                     menu_n.fan_error =  FanFandError(nj);
                                    Tm1650Show(menu_n.fan_error%100/10,menu_n.fan_error%10,0);
                                    FanAllSet(1);//ȫ��
                                    DelayMs(1000);
                                    menu_n.cur_time = 0;
                                    break;
                                }
                            } else {
                                //����
                                menu_n.error_num[nj] = 0;
                            }
                        }
                    }
                }
//                } else {
//                    FanAllSet(2);//����
//                    menu_n.cur_time = 0;
//                }
            } else {
                //�رշ���
                FanAllSet(0);
                menu_n.cur_time = 0;
            }
        }
    }
    //�й��Ϸ���
    if(menu_n.fan_error > 0) {
        static u16 error_time = 0;
        if(error_time < 60) {
            error_time++;
        } else {
            error_time = 0;
            ComSend(0x08,menu_n.fan_error,0x00,0x00,0x00,0x00);
        }
    }
    //����ܶ�̬��ʾ
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
/**********************************************��������***************************************************** 
* ��������: void MenuComSer(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/25
************************************************************************************************************/ 
void MenuComSer(void) { 
    if(ComGetFlag() == 0x01) {
        ComSetFlag(0x00);
        if(ComCheck() == 0x01) {
            switch( ComGetDate(1) ) {
            case 0X01://���ط���
                if( ComGetDate(2) == 0x00 ) {
                    FanSpeedSet(ComGetDate(3) - 1,0x00);
                } else if( ComGetDate(2) == 0x01 ) {
                    FanSpeedSet(ComGetDate(3) - 1,0xFF);
                } else {
                    FanSpeedSet(ComGetDate(3) - 1,0x7F);
                }
                ComSend(0x01,ComGetDate(2),ComGetDate(3),0x00,0x00,0x00);
                break;
            case 0x02://����״̬
                menu_n.mode = ComGetDate(2);
                ComSend(0x02,ComGetDate(2),0x00,0x00,0x00,0x00);
                EepromWrite(11,menu_n.mode);//����ģʽ
                break;
            case 0x03://�����¶ȵ�
                for(u8 i = 0;i < 6;i++) {
                    menu_n.tempSet[i] = ComGetDate(2);
                }
                ComSend(0x03,ComGetDate(2),0x00,0x00,0x00,0x00);
                EepromWrite(13,ComGetDate(2));//�¶ȵ�
                break;
            case 0x04://��ѯ�¶�
                ComSend(0x04,NtcGetTemp(menu_n.temp_arr),0x00,0x00,0x00,0x00);
                break;
            case 0x05://�����¶ȼ�
                menu_n.temp_arr = ComGetDate(2);
                ComSend(0x05,ComGetDate(2),0x00,0x00,0x00,0x00);
                EepromWrite(12,menu_n.temp_arr);//ѡ���¶ȼ�
                break;
            case 0x06://��ѯ����
                Tm1650Show(10,0,0);
                menu_n.fan_error = FanSelfInspection();//�Լ�
                Tm1650Show(menu_n.fan_error%100/10,menu_n.fan_error%10,0);
                ComSend(0x06,menu_n.fan_error,0x00,0x00,0x00,0x00);
                break;
            case 0x07://��ѯ���ϵ��               
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
            //У�����
            ComSend(0x44,0x00,0x00,0x00,0x00,0x00);
        }
    }
}






