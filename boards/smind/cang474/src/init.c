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
 * @file init.c
 *
 * board specific early startup code.
 */

#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/tasks.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <debug.h>
#include <errno.h>
#include <syslog.h>

#include <nuttx/board.h>

#include <stm32.h>
#include "board_config.h"
#include "led.h"
#include <stm32_uart.h>

#include <arch/board/board.h>

#include <drivers/drv_hrt.h>
#include <drivers/drv_board_led.h>
#include <drivers/drv_watchdog.h>

#include <systemlib/px4_macros.h>

#include <px4_platform_common/init.h>
#include <px4_platform/gpio.h>

#if defined(CONFIG_NETDEV_LATEINIT)
#  include <stm32_fdcan.h>
#endif

# if defined(FLASH_BASED_PARAMS)
#  include <parameters/flashparams/flashfs.h>
#endif

/************************************************************************************
 * Name: board_on_reset
 ************************************************************************************/
__EXPORT void board_on_reset(int status)
{
	/* No io_timer reset configured for this port yet */
	(void)status;
}

/************************************************************************************
 * Name: stm32_boardinitialize
 ************************************************************************************/
__EXPORT void stm32_boardinitialize(void)
{
	board_on_reset(-1);

	watchdog_init();

	/* configure pins */
	const uint32_t gpio[] = PX4_GPIO_INIT_LIST;
	px4_gpio_init(gpio, arraySize(gpio));

	/* Configure SPI all interfaces GPIO. */
	stm32_spiinitialize();
}

/****************************************************************************
 * Name: board_app_initialize
 ****************************************************************************/
__EXPORT int board_app_initialize(uintptr_t arg)
{
	px4_platform_init();

#if defined(CONFIG_NETDEV_LATEINIT)
	/* Bring up the FDCAN SocketCAN netdevs (network stack is already up). */
#  ifdef CONFIG_STM32_FDCAN1
	stm32_fdcansockinitialize(0);
#  endif
#  ifdef CONFIG_STM32_FDCAN2
	stm32_fdcansockinitialize(1);
#  endif
#endif

#if defined(FLASH_BASED_PARAMS)
	/* STM32G474 flash has 2KB sectors. Reserve the last 16KB (sectors
	 * 248-255, 0x0807C000-0x0807FFFF) for parameters.
	 */
	static sector_descriptor_t params_sector_map[] = {
		{248, 2 * 1024, 0x0807C000},
		{249, 2 * 1024, 0x0807C800},
		{250, 2 * 1024, 0x0807D000},
		{251, 2 * 1024, 0x0807D800},
		{252, 2 * 1024, 0x0807E000},
		{253, 2 * 1024, 0x0807E800},
		{254, 2 * 1024, 0x0807F000},
		{255, 2 * 1024, 0x0807F800},
		{0, 0, 0},
	};

	int result = parameter_flashfs_init(params_sector_map, NULL, 0);

	if (result != OK) {
		syslog(LOG_ERR, "[boot] FAILED to init params in FLASH %d\n", result);
	}

#endif // FLASH_BASED_PARAMS

	return OK;
}
