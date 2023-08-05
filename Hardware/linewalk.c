#include "stm32f10x.h"
#include "linewalk.h"
#include "motor.h"
#include "delay.h"

void linewalk(u16 adcx1,u16 adcx2,u16 adcx3){
    u16 right,middle,left;
    u8 left_status,middle_status,right_status; 
    right=adcx3;
    middle=adcx2;
    left=adcx1;
    if(right>1000){right_status=1;}
    else if(right<1000){right_status=0;}
    if(middle>1000){middle_status=1;}
    else {middle_status=0;}
    if(left>1000){right_status=1;}
    else if(left<1000){right_status=0;}

    if(middle_status==1 && right_status==0 && left_status==0 ){MOTOR_Forward(70);}
    else if(middle_status==0 && right_status==1 && left_status==0 ){MOTOR_Left(70);}
    else if(middle_status==0 && right_status==0 && left_status==1 ){MOTOR_Right(70);}
    else if(middle_status==0 && right_status==0 && left_status==0 ){MOTOR_Stop();}
    
}
