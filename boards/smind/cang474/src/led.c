/****************************************************************************
 *
 *   Copyright (c) 2024 SMIND. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 ****************************************************************************/

/**
 * @file led.c
 *
 * LED backend. The CAN-G474 has a single blue "ACT" LED on PC13 (active high).
 */

#include <px4_platform_common/px4_config.h>

#include <stdbool.h>

#include "chip.h"
#include "stm32_gpio.h"
#include "board_config.h"

#include "led.h"

void rgb_led(int r, int g, int b, int freqs)
{
	(void)freqs;
	static bool once = false;

	if (!once) {
		stm32_configgpio(GPIO_LED_ACT);
		once = true;
	}

	stm32_gpiowrite(GPIO_LED_ACT, (r > 0) || (g > 0) || (b > 0));
}
