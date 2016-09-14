/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�main
*
* �ļ���ʶ��
* ժ    Ҫ����Ƭ��STM8S207R8T6
*
*
* ��ǰ�汾��
* ��    �ߣ�lhb Steven
* ������ڣ�2016/8/23
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
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
/**********************************************��������***************************************************** 
* ��������: int main( void ) 
* �������:  void  
* ���ز���: int  
* ��    ��: zhu  
* ��    ��: by lhb_steven
* ��    ��: 2016/8/23
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
            //������
            MenuTempSer();
        }
        MenuComSer();
    }
}

