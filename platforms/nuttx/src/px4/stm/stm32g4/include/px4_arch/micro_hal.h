/****************************************************************************
 *
 *   Copyright (c) 2024 PX4 Development Team. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 ****************************************************************************/
#pragma once


#include "../../../stm32_common/include/px4_arch/micro_hal.h"

__BEGIN_DECLS

#include <stm32.h>
#define PX4_SOC_ARCH_ID             PX4_SOC_ARCH_ID_STM32G4
#define PX4_FLASH_BASE              STM32_FLASH_BASE
#define PX4_NUMBER_I2C_BUSES        STM32_NI2C

/* STM32G4 has no bxCAN filter registers (STM32_CAN1_FIR), so the bootloader
 * shared signature locations are mapped to the (otherwise unused) CCM SRAM.
 * This port has no CAN bootloader, so reset persistence is not required.
 */
#undef crc_HiLOC
#undef crc_LoLOC
#undef signature_LOC
#undef bus_speed_LOC
#undef node_id_LOC
#define crc_HiLOC                   (STM32_CCMRAM_BASE + 0x00)
#define crc_LoLOC                   (STM32_CCMRAM_BASE + 0x04)
#define signature_LOC               (STM32_CCMRAM_BASE + 0x08)
#define bus_speed_LOC               (STM32_CCMRAM_BASE + 0x0C)
#define node_id_LOC                 (STM32_CCMRAM_BASE + 0x10)

/* G4 has TAMP backup registers instead of the F4 BKP registers. */
#define STM32_RTC_BK0R              (STM32_TAMP_BASE + 0x100)
__END_DECLS
