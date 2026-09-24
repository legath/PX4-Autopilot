/****************************************************************************
 *
 *   Copyright (c) 2024 PX4 Development Team. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 ****************************************************************************/

#include <nuttx/config.h>
#include "chip.h"
#include "stm32.h"
#include <hardware/stm32_wdg.h>
#include "nvic.h"

void watchdog_pet(void)
{
	putreg32(IWDG_KR_KEY_RELOAD, STM32_IWDG_KR);
}

void watchdog_init(void)
{
	/* unlock */
	putreg32(IWDG_KR_KEY_ENABLE, STM32_IWDG_KR);

	/* Set the prescale value */
	putreg32(IWDG_PR_DIV16, STM32_IWDG_PR);

	/* Set the reload value */
	putreg32(IWDG_RLR_MAX, STM32_IWDG_RLR);

	/* Start the watch dog */
	putreg32(IWDG_KR_KEY_START, STM32_IWDG_KR);

	watchdog_pet();
}
