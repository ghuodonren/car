#include <Arduino.h>
#include "monitor.h"
#include "swerve.h"

int lastState = 6; //保存上一次小车的状态

void handleLostState()  //调整小车偏离轨道的补救函数
{
    int prev_s0 = (lastState >> 3) & 1; //提取上次状态的第一个模块的状态
    int prev_s1 = (lastState >> 2) & 1; //提取上次状态的第二个模块的状态
    int prev_s2 = (lastState >> 1) & 1; //提取上次状态的第三个模块的状态
    int prev_s3 = lastState & 1;        //提取上次状态的第四个模块的状态

    int leftSum = prev_s0 + prev_s1;    //左边总计
    int rightSum = prev_s2 + prev_s3;   //右边总计

    if(leftSum > rightSum){
        SwerveLeftTurn(255);
    }else if(leftSum < rightSum){
        SwerveRightTurn(255);
    }else{
        SwerveLeftTurn(150);
    }
}


void setup()
{
    Serial.begin(115200);

    MonitorPinInit();
    SwervePinInit();

    Serial.println("初始化完成");
    delay(500); 
}

void loop()
{
    MonitorSensor();

    int s0 = MonitorValue[0]; //记录第一个模块
    int s1 = MonitorValue[1]; //记录第二个模块
    int s2 = MonitorValue[2]; //记录第三个模块
    int s3 = MonitorValue[3]; //记录第四个模块
    int state = (s0 << 3) + (s1 << 2) + (s2 << 1) + s3; //记忆四个红外模块状态值

    if(state == 6){
        SwerveForward(255); //0110,小车保持直行
    }else if(state == 2 || state == 3){
        SwerveRightTurn(200); //0010、0011，小车小幅度右转
    }else if(state == 4 || state == 12){
        SwerveLeftTurn(200); //0100、1100，小车小幅度左转
    }else if(state == 1){
        SwerveRightTurn(255); //0001，小车严重偏右，大幅度右转
    }else if(state == 8){
        SwerveLeftTurn(255); //1000，小车严重偏左，大幅度左转
    }else if(state == 0){
        handleLostState(); //0000，小车偏移轨道，使用补救函数
    }else if(state == 15){
        SwerveForward(200); //1111，小车可能遇到十字路口，保持直行
    }else{
        //额外情况所作出的调整
        int leftSum = s0 + s1;
        int rightSum = s2 + s3;

        if(leftSum > rightSum){ //小车偏左
            SwerveLeftTurn(180);
        }else if(rightSum > leftSum){ //小车偏右
            SwerveRightTurn(180);
        }else{ 
            //小车遇到复杂情况的调整
            int prevLeft = ((lastState >> 3) & 1) + ((lastState >> 2) & 1); //左边总计
            int prevRight = ((lastState >> 1) & 1) + (lastState & 1); //右边总计

            if(prevLeft > prevRight){
                SwerveLeftTurn(180);
            }else if(prevRight > prevLeft){
                SwerveRightTurn(180);
            }else{
                SwerveForward(200);
            }
        }
    }

    lastState = state;

    delay(50);
}