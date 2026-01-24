/*
 * mpu6050.c
 *
 *  Created on: Dec 29, 2025
 *      Author: jake_
 */

#include <mpu6050.h>
#include <stdint.h>
#include <math.h>


#define MPU_ADDR 0x68
#define MPU_WHO_AM_I 0x75
#define MPU_PWR_MGMT_1 0x6B
#define MPU_SMPLRT_DIV 0x19
#define MPU_CONFIG 0x1A
#define MPU_GYRO_CONFIG 0x1B
#define MPU_ACCEL_CONFIG 0x1C
#define MPU_GYRO_XH 0x43
#define MPU_GYRO_XL 0x44
#define MPU_GYRO_YH 0x45
#define MPU_GYRO_YL 0x46
#define MPU_GYRO_ZH 0x47
#define MPU_GYRO_ZL 0x48
#define MPU_ACCEL_XH 0x3B
#define MPU_ACCEL_XL 0x3C
#define MPU_ACCEL_YH 0x3D
#define MPU_ACCEL_YL 0x3E
#define MPU_ACCEL_ZH 0x3F
#define MPU_ACCEL_ZL 0x40

uint8_t accel_scale = 2; // +/- 2g by default

void mpu_gyro_read(I2C_HandleTypeDef* hi2c)
{
	uint8_t data[2];
	int16_t x, y, z;
	HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_GYRO_XH, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
	x = (int16_t)(data[0] << 8) + data[1];
	HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_GYRO_YH, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
	y = (int16_t)(data[0] << 8) + data[1];
	HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_GYRO_ZH, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
	z = (int16_t)(data[0] << 8) + data[1];
	printf("x: %d, y: %d, z: %d \n", x, y, z);

}
void mpu_accel_read(I2C_HandleTypeDef* hi2c)
{
	uint8_t data[2];
	int16_t x, y, z;
	HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_ACCEL_XH, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
	x = (int16_t)(data[0] << 8) + data[1];
	HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_ACCEL_YH, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
	y = (int16_t)(data[0] << 8) + data[1];
	HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_ACCEL_ZH, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
	z = (int16_t)(data[0] << 8) + data[1];
	printf("x: %d, y: %d, z: %d \n", x, y, z);

}

int16_t mpu_get_accel_x(I2C_HandleTypeDef* hi2c)
{
	uint8_t d[2];
	int16_t X = 0;
	HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_ACCEL_XH, I2C_MEMADD_SIZE_8BIT, d, 2, 10);
	X = (int16_t)(d[0] << 8) + d[1];
	return X;
}

int16_t mpu_get_accel_y(I2C_HandleTypeDef* hi2c)
{
	uint8_t data[2];
	int16_t Y;
	HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_ACCEL_YH, I2C_MEMADD_SIZE_8BIT, data, 2, 10);
	Y = (int16_t)(data[0] << 8) + data[1];
	return Y;
}

int16_t mpu_get_accel_z(I2C_HandleTypeDef* hi2c)
{
	uint8_t d[2];
	int16_t Z;
	HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_ACCEL_ZH, I2C_MEMADD_SIZE_8BIT, d, 2, 10);
	Z = (int16_t)(d[0] << 8) + d[1];
	return Z;
}

void mpu_init(I2C_HandleTypeDef* hi2c, uint8_t scale)
{
	if (HAL_I2C_IsDeviceReady(hi2c, MPU_ADDR << 1, 3, 5) != HAL_OK)
	  {
		  printf("Device is unavailable!\n");
	  }

	  uint8_t recieved_data;
	  if (HAL_I2C_Mem_Read(hi2c, MPU_ADDR << 1, MPU_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &recieved_data, 1, HAL_MAX_DELAY) == HAL_OK)
	  {
		  if (recieved_data == MPU_ADDR)
		  {
				printf("MPU Identified!\n");
				printf("Configuring registers\n");
				recieved_data = 0b00001000;
				HAL_I2C_Mem_Write(hi2c, MPU_ADDR << 1, MPU_GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &recieved_data, 1, HAL_MAX_DELAY);
				recieved_data = 0b00001000;
				HAL_I2C_Mem_Write(hi2c, MPU_ADDR << 1, MPU_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &recieved_data, 1, HAL_MAX_DELAY);
				accel_scale = pow(2, ((recieved_data & 0b00011000) >> 3) + 1);
				recieved_data = 0b00001000;
				HAL_I2C_Mem_Write(hi2c, MPU_ADDR << 1, MPU_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &recieved_data, 1, HAL_MAX_DELAY);
		  }

		  else
		  {
			  printf("MPU Not Identified!\n");
		  }
	  }
}
