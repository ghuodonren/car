#include "config.h"
#include "swerve.h"
#include <esp32-hal-gpio.h>
#include <Arduino.h>

const int PWM_CHANNEL_A = 0; //PWMA的通道
const int PWM_CHANNEL_B = 1; //PWMB的通道
const int PWM_FREQ = 5000;   //PWM的频率
const int PWM_RESOLUTION = 8;//PWM的8位分辨率


/**
 * @brief 转向模块引脚初始化
*/
void SwervePinInit()
{
    ledcSetup(PWM_CHANNEL_A, PWM_FREQ, PWM_RESOLUTION); //初始化PWMA
    ledcSetup(PWM_CHANNEL_B, PWM_FREQ, PWM_RESOLUTION); //初始化PWMB

    ledcAttachPin(SwervePin[0], PWM_CHANNEL_A); //绑定对应的PWMA引脚
    ledcAttachPin(SwervePin[1], PWM_CHANNEL_B); //绑定对应的PWMB引脚

    for(int i = 2; i <= 5; i++){
        if(SwervePin[i] != -1){
            pinMode(SwervePin[i], OUTPUT);
            digitalWrite(SwervePin[i], LOW);
        }
    }
}

/**
 * @brief 电机驱动辅助函数
*/
void setMotor(int pwmChannel, int dirPin1, int dirPin2, int speed)
{
    speed = constrain(speed, 0, 255); //限制speed的最大值

    if(speed == 0){
        //停车
        ledcWrite(pwmChannel, 0);
        digitalWrite(dirPin1, LOW);
        digitalWrite(dirPin2, LOW);
    }else{
        ledcWrite(pwmChannel, speed); //将对应的通道写入速度
        digitalWrite(dirPin1, HIGH);  //拉高PIN1
        digitalWrite(dirPin2, LOW);   //拉高PIN2
    }
}


void SwerveRightTurn(int speed)
{
    setMotor(PWM_CHANNEL_A, SwervePin[2], SwervePin[3], speed);
    setMotor(PWM_CHANNEL_B, SwervePin[5], SwervePin[4], speed);
}
void SwerveLeftTurn(int speed)
{
    setMotor(PWM_CHANNEL_A, SwervePin[3], SwervePin[2], speed);
    setMotor(PWM_CHANNEL_B, SwervePin[4], SwervePin[5], speed);
}
void SwerveForward(int speed)
{
    setMotor(PWM_CHANNEL_A, SwervePin[2], SwervePin[3], speed);
    setMotor(PWM_CHANNEL_A, SwervePin[4], SwervePin[5], speed);
}
void SwerveReverse(int speed)
{
    setMotor(PWM_CHANNEL_A, SwervePin[3], SwervePin[2], speed);
    setMotor(PWM_CHANNEL_A, SwervePin[5], SwervePin[4], speed);
}