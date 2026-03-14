#include <Arduino.h>
#include "monitor.h"
#include "swerve.h"

/**
 * @brief 检查是否脱轨
*/
bool isLost()
{
    
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

    if(isLost()){
        Serial.println("小车已脱轨");

        SwerveReverse(150);
        delay(100);

        int searchTime = 0;
        bool foundLine = false;

        while(searchTime < 600){
            MonitorSensor();

            if(!isLost()){
                foundLine = true;
                Serial.println("小车回到轨道");
                break;
            }
            SwerveLeftTurn(150);
            delay(5);
            searchTime += 5;
        }
        
        if(!foundLine){
            SwerveForward(0);
            delay(100);
            return;
        }
    }

    if(MonitorValue[0] > 0.5){
        SwerveLeftTurn(150);
    }else if(MonitorValue[3] > 0.5){
        SwerveRightTurn(150);
    }else{
        SwerveForward(200);
    }

    delay(50);
}