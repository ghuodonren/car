#ifndef SWERVE_H
#define SWERVE_H

// 转向模块引脚初始化函数
void SwervePinInit();

void SwerveRightTurn(int speed); //右转函数
void SwerveLeftTurn(int speed); //左转函数
void SwerveForward(int speed); //前进函数
void SwerveReverse(int speed); //后退函数
void SwerveDifferential(int leftSpeed, int rightSpeed); //差速驱动函数

#endif
