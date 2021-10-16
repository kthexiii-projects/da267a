/**
 * @file   main.c
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  DA267A Lab05
 * @date   2021-10-12
 *
 * @copyright Copyright (c) 2021
 */
#include <stdint.h>

#include "driver/gpio.h"
#include "esp_task_wdt.h"
#include "esp_pm.h"

#include "I2CUtil.h"
#include "MPU6050.h"

#define SDA_PIN 23
#define SCL_PIN 22

//void app_main() {
//	// Initialise I2C bus and the MPU6050
//	I2C_Init(SDA_PIN, SCL_PIN);
//	MPU6050 mpu;
//	MPU6050_Config(MPU6050_PWR_MGMT_1, 0x00);
//	MPU6050_Config(MPU6050_SMPLRT_DIV, 250);
//	MPU6050_AccConfig(0x00);
//
//	for (;;) {
//		MPU6050_Update(&mpu);
//		// Print Acceleration data
//		printf("%.2f, %.2f, %.2f\n", mpu.accx, mpu.accy, mpu.accz);
//		vTaskDelay(pdMS_TO_TICKS(10));
//	}
//}

void task(void* arg) {
	MPU6050 mpu;
	MPU6050_Config(MPU6050_PWR_MGMT_1, 0x00);
	MPU6050_Config(MPU6050_SMPLRT_DIV, 250);
	MPU6050_AccConfig(0x00);
	for(;;) {
		MPU6050_Update(&mpu);
		// Print Acceleration data
		printf("%.2f, %.2f, %.2f\n", mpu.accx, mpu.accy, mpu.accz);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void app_main() {
	// Configure light sleep mode with esp_pm_configure()
	esp_pm_config_esp32_t pconfig = {
		.max_freq_mhz = 80,
		.min_freq_mhz = 13,
		.light_sleep_enable = true
	};
	esp_pm_configure(&pconfig);

	// Initialise I2C bus and the MPU6050
	I2C_Init(SDA_PIN, SCL_PIN);
	xTaskCreate(task, "PrintTask", 2048, NULL, 10, NULL);
}
