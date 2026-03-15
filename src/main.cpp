#include <Arduino.h>
#include "monitor.h"
#include "swerve.h"

int lastState = 6;


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

    int s0 = (MonitorValue[0] > 2000)? 1:0;
    int s1 = (MonitorValue[1] > 2000)? 1:0;
    int s2 = (MonitorValue[2] > 2000)? 1:0;
    int s3 = (MonitorValue[3] > 2000)? 1:0;
    int state = (s0 << 3) + (s1 << 2) + (s2 << 1) + s3; //记忆四个value值

    if(state == 6){
        SwerveForward(255);
    }else if(state == 2 || state == 3){
        SwerveRightTurn(200);
    }else if(state == 4 || state == 12){
        SwerveLeftTurn(200);
    }else if(state == 1){
        SwerveRightTurn(255);
    }else if(state == 8){
        SwerveLeftTurn(255);
    }else if(state == 0){
        handleLostState();
    }else if(state == 15){
        SwerveForward(200);
    }else{
        int leftSum = s0 + s1;
        int rightSum = s2 + s3;

        if(leftSum > rightSum){
            SwerveLeftTurn(180);
        }else if(rightSum > leftSum){
            SwerveRightTurn(180);
        }else{
            int prevLeft = ((lastState >> 3) & 1) + ((lastState >> 2) & 1);
            int prevRight = ((lastState >> 1) & 1) + (lastState & 1);

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