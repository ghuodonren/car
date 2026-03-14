#include "config.h"
#include "monitor.h"
#include <esp32-hal-gpio.h>

float MonitorValue[4] = {0, 0, 0, 0};
/**
 * @brief 监控模块引脚初始化
*/
void MonitorPinInit()
{
    for(int i = 0; i < 4; i++){
        pinMode(MonitorPin[i], INPUT_PULLUP);
    }
}

/**
 * @brief 监控模块函数
*/
void MonitorSensor()
{
    for(int i = 0; i < 4; i++){
        int raw = digitalRead(MonitorPin[i]);
        MonitorValue[i] = (raw == LOW)?(1.0):(0.0);
    }
}