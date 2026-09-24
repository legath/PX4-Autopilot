/****************************************************************************
 *
 *   Copyright (c) 2024 PX4 Development Team. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 ****************************************************************************/
#pragma once


#include "../../../stm32_common/include/px4_arch/io_timer_hw_description.h"

static inline constexpr timer_io_channels_t initIOTimerGPIOInOut(Timer::TimerChannel timer, GPIO::GPIOPin pin)
{
	timer_io_channels_t ret{};
	uint32_t gpio_af = 0;

	switch (timer.timer) {
	case Timer::Timer1:
	case Timer::Timer2:
		gpio_af = GPIO_AF1;
		break;

	case Timer::Timer3:
	case Timer::Timer4:
	case Timer::Timer5:
		gpio_af = GPIO_AF2;
		break;

	case Timer::Timer8:
		/* STM32G4 advanced timer: AF varies per channel */
		switch (timer.channel) {
		case Timer::Channel1:
			gpio_af = GPIO_AF4;
			break;

		case Timer::Channel2:
			gpio_af = GPIO_AF5;
			break;

		case Timer::Channel3:
			gpio_af = GPIO_AF10;
			break;

		case Timer::Channel4:
			gpio_af = GPIO_AF6;
			break;
		}

		break;

	default:
		break;
	}

	uint32_t pin_port = getGPIOPort(pin.port) | getGPIOPin(pin.pin);
	ret.gpio_in = gpio_af | (GPIO_ALT | GPIO_SPEED_50MHz | GPIO_FLOAT) | pin_port;
	ret.gpio_out = gpio_af | (GPIO_ALT | GPIO_SPEED_50MHz | GPIO_PUSHPULL) | pin_port;
	return ret;
}
