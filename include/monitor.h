#ifndef MONITOR_H
#define MONITOR_H

// 声明监控模块获取的值
extern float MonitorValue[4]={0,0,0,0};

// 引脚初始化
void MonitorPinInit();
// 声明监控模块函数
void MonitorSensor();

#endif