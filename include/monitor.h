#ifndef MONITOR_H
#define MONITOR_H

// 监控模块获取的值
extern int MonitorValue[4];

// 引脚初始化
void MonitorPinInit();
// 监控模块函数
void MonitorSensor();

#endif