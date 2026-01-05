/*
 * mpu6050.h
 *
 *  Created on: Dec 29, 2025
 *      Author: jake_
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
#include <main.h>
#include <stdio.h>

void mpu_gyro_read(I2C_HandleTypeDef* hi2c);
void mpu_accel_read(I2C_HandleTypeDef* hi2c);
void mpu_init(I2C_HandleTypeDef* hi2c);
int16_t mpu_get_accel_y(I2C_HandleTypeDef* hi2c);
int16_t mpu_get_accel_x(I2C_HandleTypeDef* hi2c);

#endif /* INC_MPU6050_H_ */
