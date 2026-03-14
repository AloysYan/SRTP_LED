/*
 * ky040.c
 *
 *  Created on: Mar 14, 2026
 *      Author: Lenovo
 */

#include "tim.h"
#include "ky040.h"

int count = 0;
int light_on = 0;

// 初始化编码器
void KY040_Init() {
	// ky040编码器初始化
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	// 初始化计数值和LED状态
	count = 0;
	light_on = 0;
}

// 更新编码器状态并调整LED亮度
void KY040_Update() {
	// 读取编码器计数值，并进行处理
	count = __HAL_TIM_GET_COUNTER(&htim1);

	// 根据计数值调整LED亮度并防止溢出
	if (count > 6000) {
	    count = 0;
	    __HAL_TIM_SET_COUNTER(&htim1, 0);
	} else if (count > 100) {
	    count = 100;
	    __HAL_TIM_SET_COUNTER(&htim1, 100);
	}
}

// 按键处理函数
void KY040_Key() {
	// 按键按下
	if (HAL_GPIO_ReadPin(Key_GPIO_Port, Key_Pin) == GPIO_PIN_RESET) {
		// 防抖处理
	    HAL_Delay(10);
	    if (HAL_GPIO_ReadPin(Key_GPIO_Port, Key_Pin) == GPIO_PIN_RESET) {
	        // 切换LED状态
			light_on = !light_on;
	    }
		// 等待按键释放
	    while (HAL_GPIO_ReadPin(Key_GPIO_Port, Key_Pin) == GPIO_PIN_RESET);
	}
}
