#ifndef CONFIG_H
#define CONFIG_H

// monitor
/**
 * @brief 监控模块引脚定义
*/
const int MonitorPin[4] = {3, 6, 7, 12};

// swerve
/**
 * @brief 转向模块引脚定义
*/
const int SwervePin[6] = {
    18, //PWMA
    19, //PWMB
    4,  //AIN1
    5,  //AIN2
    11, //BIN1
    13  //BIN2
};

#endif
