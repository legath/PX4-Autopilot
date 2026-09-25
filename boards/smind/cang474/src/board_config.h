/****************************************************************************
 *
 *   Copyright (c) 2024 SMIND. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file board_config.h
 *
 * board internal definitions for the SMIND / Matek CAN-G474 profile
 */

#pragma once

#include <px4_platform_common/px4_config.h>
#include <nuttx/compiler.h>
#include <stdint.h>

/* LED (blue "ACT", active high) */
#define GPIO_LED_ACT    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_2MHz | GPIO_OUTPUT_CLEAR | GPIO_PORTC | GPIO_PIN13)

/* I2C bus recovery (bit-bang) pins */
#define GPIO_I2C1_SCL_RESET   /* PA13 */  (GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_SPEED_2MHz | GPIO_OUTPUT_SET | GPIO_PORTA | GPIO_PIN13)
#define GPIO_I2C1_SDA_RESET   /* PA14 */  (GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_SPEED_2MHz | GPIO_OUTPUT_SET | GPIO_PORTA | GPIO_PIN14)
#define GPIO_I2C2_SCL_RESET   /* PC4  */  (GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_SPEED_2MHz | GPIO_OUTPUT_SET | GPIO_PORTC | GPIO_PIN4)
#define GPIO_I2C2_SDA_RESET   /* PA8  */  (GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_SPEED_2MHz | GPIO_OUTPUT_SET | GPIO_PORTA | GPIO_PIN8)

/* PWM outputs (11 channels) */
#define BOARD_NUM_IO_TIMERS         4
#define DIRECT_PWM_OUTPUT_CHANNELS  11

#define FLASH_BASED_PARAMS

/* High-resolution timer: TIM4, capture/compare channel 1 */
#define HRT_TIMER                    4
#define HRT_TIMER_CHANNEL            1

#define PX4_GPIO_INIT_LIST { \
		GPIO_LED_ACT,                     \
		GPIO_I2C1_SCL_RESET,              \
		GPIO_I2C1_SDA_RESET,              \
		GPIO_I2C2_SCL_RESET,              \
		GPIO_I2C2_SDA_RESET,              \
	}

__BEGIN_DECLS

/* Single blue "ACT" LED on PC13 (ArduPilot hwdef: "PC13 LED OUTPUT HIGH",
 * "define HAL_LED_ON 1"), i.e. a plain active-high GPIO, not an RGB LED.
 */
#define BOARD_MAX_LEDS              1

#ifndef __ASSEMBLY__

extern void stm32_spiinitialize(void);

#include <px4_platform_common/board_common.h>

#endif /* __ASSEMBLY__ */

__END_DECLS
