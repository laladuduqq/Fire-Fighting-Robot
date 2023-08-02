#include "stm32f10x.h"
#include "linewalk.h"
#include "motor.h"
#include "delay.h"

void linewalk(u16 adcx1,u16 adcx2,u16 adcx3){
    u16 right,middle,left;
    u8 status; // 0,1 表示middle 2,3 表示left 4,5 表示right
    right=adcx3;
    middle=adcx2;
    left=adcx1;
    if(right>1000){status=5;}
    else if(200<right && right<1000){status=4;}
    if(middle>1000){status=1;}
    else {status=0;}
    if(left>1000){status=3;}
    else if(200<left && left<1000){status=2;}

    if(status==1){MOTOR_Forward(70);}
    else{
        switch (status)
        {
        case 5:
            MOTOR_Left(80);
            delay_ms(5);
            break;
        case 4:
            MOTOR_Left(70);
            delay_ms(5);
            break;
        case 3:
            MOTOR_Right(80);
            delay_ms(5);
            break;
        case 2:
            MOTOR_Right(70);
            delay_ms(5);
            break;
        default:
            MOTOR_Stop();
            break;
        }
        
    }
}
