/************************************************************************************
 * configs/smind_cang474/include/board.h
 *
 *   Copyright (C) 2024 SMIND. All rights reserved.
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
 * 3. Neither the name NuttX nor the names of its contributors may be
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
 ************************************************************************************/

#ifndef __BOARDS_SMIND_CANG474_INCLUDE_BOARD_H
#define __BOARDS_SMIND_CANG474_INCLUDE_BOARD_H

#include <nuttx/config.h>
#ifndef __ASSEMBLY__
# include <stdint.h>
#endif

#include <stm32.h>

/* Clocking *****************************************************************/

/* HSI - 16 MHz RC factory-trimmed
 * LSI - 32 KHz RC
 * HSE - 8 MHz Crystal
 * LSE - not installed
 */
#define STM32_BOARD_XTAL        8000000
#define STM32_HSE_FREQUENCY     STM32_BOARD_XTAL
#define STM32_HSI_FREQUENCY     16000000ul
#define STM32_LSI_FREQUENCY     32000

/* Main PLL Configuration.
 *
 * PLL source is HSE = 8MHz
 * PLLM = 2, PLLN = 85, PLLP = 10, PLLQ = 2, PLLR = 2
 *
 * f(VCO Clock) = f(PLL Clock Input) x (PLLN / PLLM)
 *              = 8MHz x 85 / 2 = 340MHz
 *
 * PLLPCLK      = f(VCO Clock) / PLLP = 340MHz / 10 = 34MHz  (ADC)
 * PLLQCLK      = f(VCO Clock) / PLLQ = 340MHz / 2  = 170MHz (FDCAN, SAI1)
 * PLLRCLK      = f(VCO Clock) / PLLR = 340MHz / 2  = 170MHz (SYSCLK)
 */

#define STM32_PLLCFGR_PLLSRC           RCC_PLLCFGR_PLLSRC_HSE
#define STM32_PLLCFGR_PLLCFG           (RCC_PLLCFGR_PLLPEN | \
                                       RCC_PLLCFGR_PLLQEN | \
                                       RCC_PLLCFGR_PLLREN)

#define STM32_PLLCFGR_PLLN             RCC_PLLCFGR_PLLN(85)
#define STM32_PLLCFGR_PLLM             RCC_PLLCFGR_PLLM(2)
#define STM32_PLLCFGR_PLLP             RCC_PLLCFGR_PLLPDIV(10)
#define STM32_PLLCFGR_PLLQ             RCC_PLLCFGR_PLLQ_2
#define STM32_PLLCFGR_PLLR             RCC_PLLCFGR_PLLR_2

#define STM32_VCO_FREQUENCY            ((STM32_HSE_FREQUENCY / 2) * 85)
#define STM32_PLLP_FREQUENCY           (STM32_VCO_FREQUENCY / 10)
#define STM32_PLLQ_FREQUENCY           (STM32_VCO_FREQUENCY / 2)
#define STM32_PLLR_FREQUENCY           (STM32_VCO_FREQUENCY / 2)

/* Use the PLL and set the SYSCLK source to be PLLR (170MHz) */

#define STM32_SYSCLK_SW                RCC_CFGR_SW_PLL
#define STM32_SYSCLK_SWS               RCC_CFGR_SWS_PLL
#define STM32_SYSCLK_FREQUENCY         STM32_PLLR_FREQUENCY

/* AHB clock (HCLK) is SYSCLK (170MHz) */

#define STM32_RCC_CFGR_HPRE            RCC_CFGR_HPRE_SYSCLK
#define STM32_HCLK_FREQUENCY           STM32_SYSCLK_FREQUENCY
#define STM32_BOARD_HCLK               STM32_HCLK_FREQUENCY

/* APB1 clock (PCLK1) is HCLK (170MHz) */

#define STM32_RCC_CFGR_PPRE1           RCC_CFGR_PPRE1_HCLK
#define STM32_PCLK1_FREQUENCY          STM32_HCLK_FREQUENCY

/* APB2 clock (PCLK2) is HCLK (170MHz) */

#define STM32_RCC_CFGR_PPRE2           RCC_CFGR_PPRE2_HCLK
#define STM32_PCLK2_FREQUENCY          STM32_HCLK_FREQUENCY

/* Timers driven from APB1/APB2 run at the bus clock since the APB prescalers
 * are 1 (see page 114 of the STM32G4 reference manual RM0440).
 */
#define STM32_APB1_TIM2_CLKIN          (STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM3_CLKIN          (STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM4_CLKIN          (STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM5_CLKIN          (STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM6_CLKIN          (STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM7_CLKIN          (STM32_PCLK1_FREQUENCY)

#define STM32_APB2_TIM1_CLKIN          (STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM8_CLKIN          (STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM15_CLKIN         (STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM16_CLKIN         (STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM17_CLKIN         (STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM20_CLKIN         (STM32_PCLK2_FREQUENCY)

/* Timer Frequencies */

#define BOARD_TIM2_FREQUENCY           (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM3_FREQUENCY           (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM4_FREQUENCY           (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM5_FREQUENCY           (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM6_FREQUENCY           (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM7_FREQUENCY           (STM32_PCLK1_FREQUENCY)
#define BOARD_TIM8_FREQUENCY           (STM32_PCLK2_FREQUENCY)
#define BOARD_TIM15_FREQUENCY          (STM32_PCLK2_FREQUENCY)
#define BOARD_TIM16_FREQUENCY          (STM32_PCLK2_FREQUENCY)
#define BOARD_TIM17_FREQUENCY          (STM32_PCLK2_FREQUENCY)
#define BOARD_TIM20_FREQUENCY          (STM32_PCLK2_FREQUENCY)

/* FDCAN clock source: PLLQ (170MHz) */

#ifdef CONFIG_STM32_FDCAN
#  define STM32_CCIPR_FDCANSRC         (RCC_CCIPR_FDCANSEL_PLLQ)
#  define STM32_FDCAN_FREQUENCY        (STM32_PLLQ_FREQUENCY)
#endif

/* Alternate function pin selections ****************************************/

/* UARTs */
#define GPIO_USART1_RX  GPIO_USART1_RX_1   /* PA10 */
#define GPIO_USART1_TX  GPIO_USART1_TX_1   /* PA9  */

#define GPIO_USART2_RX  GPIO_USART2_RX_3   /* PB4  */
#define GPIO_USART2_TX  GPIO_USART2_TX_3   /* PB3  */

#define GPIO_USART3_RX  GPIO_USART3_RX_2   /* PB11 */
#define GPIO_USART3_TX  GPIO_USART3_TX_2   /* PB10 */

/* UART4 (AF5 on PC10/PC11, not present in the 48-pin "C" pinmap) */
#define GPIO_UART4_RX   (GPIO_ALT | GPIO_AF5 | GPIO_PORTC | GPIO_PIN11)
#define GPIO_UART4_TX   (GPIO_ALT | GPIO_AF5 | GPIO_PORTC | GPIO_PIN10)

/* FDCAN */
#define GPIO_FDCAN1_RX  GPIO_FDCAN1_RX_1   /* PA11 */
#define GPIO_FDCAN1_TX  GPIO_FDCAN1_TX_1   /* PA12 */

#define GPIO_FDCAN2_RX  GPIO_FDCAN2_RX_1   /* PB5  */
#define GPIO_FDCAN2_TX  GPIO_FDCAN2_TX_1   /* PB6  */

/* SPI2 (RM3100 magnetometer) */
#define GPIO_SPI2_MISO  GPIO_SPI2_MISO_2   /* PB14 */
#define GPIO_SPI2_MOSI  GPIO_SPI2_MOSI_2   /* PB15 */
#define GPIO_SPI2_SCK   GPIO_SPI2_SCK_1    /* PB13 */

/* I2C1 (shared with SWD: PA13/PA14) */
#define GPIO_I2C1_SCL   GPIO_I2C1_SCL_1    /* PA13 */
#define GPIO_I2C1_SDA   GPIO_I2C1_SDA_1    /* PA14 */

#define GPIO_I2C1_SCL_GPIO  (GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_SPEED_50MHz | GPIO_OUTPUT_SET | GPIO_PORTA | GPIO_PIN13)
#define GPIO_I2C1_SDA_GPIO  (GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_SPEED_50MHz | GPIO_OUTPUT_SET | GPIO_PORTA | GPIO_PIN14)

/* I2C2 */
#define GPIO_I2C2_SCL   GPIO_I2C2_SCL_2    /* PC4  */
#define GPIO_I2C2_SDA   GPIO_I2C2_SDA_1    /* PA8  */

#define GPIO_I2C2_SCL_GPIO  (GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_SPEED_50MHz | GPIO_OUTPUT_SET | GPIO_PORTC | GPIO_PIN4)
#define GPIO_I2C2_SDA_GPIO  (GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_SPEED_50MHz | GPIO_OUTPUT_SET | GPIO_PORTA | GPIO_PIN8)

/* LED (blue "ACT", active high) */
#define GPIO_LED_ACT    (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_2MHz | GPIO_OUTPUT_CLEAR | GPIO_PORTC | GPIO_PIN13)

#endif /* __BOARDS_SMIND_CANG474_INCLUDE_BOARD_H */
