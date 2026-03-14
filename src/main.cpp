#include <Arduino.h>
#include "monitor.h"
#include "swerve.h"

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

    if(MonitorValue[0] > 0.5){
        SwerveLeftTurn(150);
    }else if(MonitorValue[3] > 0.5){
        SwerveRightTurn(150);
    }else{
        SwerveForward(200);
    }
    
    delay(50);
}