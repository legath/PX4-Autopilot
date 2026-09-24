############################################################################
#
#   Copyright (c) 2024 PX4 Development Team. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
############################################################################


add_subdirectory(../stm32_common/adc adc)
add_subdirectory(../stm32_common/board_critmon board_critmon)
add_subdirectory(../stm32_common/board_hw_info board_hw_info)
add_subdirectory(../stm32_common/board_reset board_reset)
add_subdirectory(../stm32_common/dshot dshot)
add_subdirectory(../stm32_common/hrt hrt)
add_subdirectory(../stm32_common/led_pwm led_pwm)
add_subdirectory(../stm32_common/srgbled_dma srgbled_dma)
add_subdirectory(../stm32_common/io_pins io_pins)
add_subdirectory(../stm32_common/spi spi)
add_subdirectory(../stm32_common/tone_alarm tone_alarm)
add_subdirectory(../stm32_common/version version)

add_subdirectory(watchdog)
