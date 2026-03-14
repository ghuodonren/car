#ifndef SWERVE_H
#define SWERVE_H

// 声明转向模块引脚初始化函数
void SwervePinInit();
// 声明转向函数
void SwerveRightTurn(int speed);
void SwerveLeftTurn(int speed);
void SwerveForward(int speed);
void SwerveReverse(int speed);

#endif
