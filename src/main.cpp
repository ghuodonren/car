#include <Arduino.h>
#include "monitor.h"
#include "swerve.h"

bool isLost()
{
    for(int i = 0; i < 4; i++){
        if(MonitorValue[i] > 0.5){
            return false;
        }
    }
    return true;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("the car is begining");

    MonitorPinInit();
    SwervePinInit();

    Serial.println("the initialization is over");
    delay(500); 
}

void loop()
{
    MonitorSensor();

    if(isLost()){
        Serial.println("the car is lost");

        SwerveReverse(100);
        delay(300);

        int searchTime = 0;
        bool foundLine = false;

        while(searchTime < 2000){
            MonitorSensor();

            if(!isLost()){
                foundLine = true;
                Serial.println("the car is coming back");
                break;
            }
            SwerveLeftTurn(150);
            delay(20);
            searchTime += 20;
        }
        
        if(foundLine){
            SwerveForward(0);
            delay(200);
            return;
        }else{
            Serial.println("the car has not yet found the black line");
            SwerveForward(0);
            delay(2000);
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