/****************************************************************************
 *
 *   Copyright (c) 2024 PX4 Development Team. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 ****************************************************************************/
#pragma once


#include "../../../stm32_common/include/px4_arch/spi_hw_description.h"

#if defined(CONFIG_SPI)
constexpr bool validateSPIConfig(const px4_spi_bus_t spi_busses_conf[SPI_BUS_MAX_BUS_ITEMS])
{
	const bool nuttx_enabled_spi_buses[] = {
#ifdef CONFIG_STM32_SPI1
		true,
#else
		false,
#endif
#ifdef CONFIG_STM32_SPI2
		true,
#else
		false,
#endif
#ifdef CONFIG_STM32_SPI3
		true,
#else
		false,
#endif
	};
	for (unsigned i = 0; i < sizeof(nuttx_enabled_spi_buses) / sizeof(nuttx_enabled_spi_buses[0]); ++i) {
		bool found_bus = false;

		for (int j = 0; j < SPI_BUS_MAX_BUS_ITEMS; ++j) {
			if (spi_busses_conf[j].bus == (int)i + 1) {
				found_bus = true;
			}
		}

		constexpr_assert(found_bus == nuttx_enabled_spi_buses[i], "SPI bus config mismatch (CONFIG_STM32_SPIx)");
	}

	return false;
}
#endif // CONFIG_SPI
