/****************************************************************************
 *
 *   Copyright (c) 2024 PX4 Development Team. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 ****************************************************************************/
#pragma once


#include "../../../stm32_common/include/px4_arch/hw_description.h"

/* STM32G4 uses DMA_V1 + DMAMUX1 (full crossbar: any request on any channel of
 * DMA1 or DMA2). The DMAMAP_DMA12_TIMxCHy_{0,1} / DMAMAP_DMA12_TIMxUP_{0,1}
 * macros are provided by hardware/stm32g4xxxx_dmamux.h, where the _0 suffix
 * selects DMA1 and _1 selects DMA2.
 */

static inline constexpr void getTimerChannelDMAMap(Timer::Timer timer, const DMA &dma, uint32_t *dma_map_ch)
{
	switch (timer) {
	case Timer::Timer1:
		if (dma.index == DMA::Index1) {
			dma_map_ch[0] = DMAMAP_DMA12_TIM1CH1_0;
			dma_map_ch[1] = DMAMAP_DMA12_TIM1CH2_0;
			dma_map_ch[2] = DMAMAP_DMA12_TIM1CH3_0;
			dma_map_ch[3] = DMAMAP_DMA12_TIM1CH4_0;

		} else {
			dma_map_ch[0] = DMAMAP_DMA12_TIM1CH1_1;
			dma_map_ch[1] = DMAMAP_DMA12_TIM1CH2_1;
			dma_map_ch[2] = DMAMAP_DMA12_TIM1CH3_1;
			dma_map_ch[3] = DMAMAP_DMA12_TIM1CH4_1;
		}

		break;

	case Timer::Timer2:
		if (dma.index == DMA::Index1) {
			dma_map_ch[0] = DMAMAP_DMA12_TIM2CH1_0;
			dma_map_ch[1] = DMAMAP_DMA12_TIM2CH2_0;
			dma_map_ch[2] = DMAMAP_DMA12_TIM2CH3_0;
			dma_map_ch[3] = DMAMAP_DMA12_TIM2CH4_0;

		} else {
			dma_map_ch[0] = DMAMAP_DMA12_TIM2CH1_1;
			dma_map_ch[1] = DMAMAP_DMA12_TIM2CH2_1;
			dma_map_ch[2] = DMAMAP_DMA12_TIM2CH3_1;
			dma_map_ch[3] = DMAMAP_DMA12_TIM2CH4_1;
		}

		break;

	case Timer::Timer3:
		if (dma.index == DMA::Index1) {
			dma_map_ch[0] = DMAMAP_DMA12_TIM3CH1_0;
			dma_map_ch[1] = DMAMAP_DMA12_TIM3CH2_0;
			dma_map_ch[2] = DMAMAP_DMA12_TIM3CH3_0;
			dma_map_ch[3] = DMAMAP_DMA12_TIM3CH4_0;

		} else {
			dma_map_ch[0] = DMAMAP_DMA12_TIM3CH1_1;
			dma_map_ch[1] = DMAMAP_DMA12_TIM3CH2_1;
			dma_map_ch[2] = DMAMAP_DMA12_TIM3CH3_1;
			dma_map_ch[3] = DMAMAP_DMA12_TIM3CH4_1;
		}

		break;

	case Timer::Timer4:
		if (dma.index == DMA::Index1) {
			dma_map_ch[0] = DMAMAP_DMA12_TIM4CH1_0;
			dma_map_ch[1] = DMAMAP_DMA12_TIM4CH2_0;
			dma_map_ch[2] = DMAMAP_DMA12_TIM4CH3_0;
			dma_map_ch[3] = DMAMAP_DMA12_TIM4CH4_0;

		} else {
			dma_map_ch[0] = DMAMAP_DMA12_TIM4CH1_1;
			dma_map_ch[1] = DMAMAP_DMA12_TIM4CH2_1;
			dma_map_ch[2] = DMAMAP_DMA12_TIM4CH3_1;
			dma_map_ch[3] = DMAMAP_DMA12_TIM4CH4_1;
		}

		break;

	case Timer::Timer5:
		if (dma.index == DMA::Index1) {
			dma_map_ch[0] = DMAMAP_DMA12_TIM5CH1_0;
			dma_map_ch[1] = DMAMAP_DMA12_TIM5CH2_0;
			dma_map_ch[2] = DMAMAP_DMA12_TIM5CH3_0;
			dma_map_ch[3] = DMAMAP_DMA12_TIM5CH4_0;

		} else {
			dma_map_ch[0] = DMAMAP_DMA12_TIM5CH1_1;
			dma_map_ch[1] = DMAMAP_DMA12_TIM5CH2_1;
			dma_map_ch[2] = DMAMAP_DMA12_TIM5CH3_1;
			dma_map_ch[3] = DMAMAP_DMA12_TIM5CH4_1;
		}

		break;

	case Timer::Timer6:
		/* Basic timer: no channels */
		break;

	case Timer::Timer7:
		/* Basic timer: no channels */
		break;

	case Timer::Timer8:
		if (dma.index == DMA::Index1) {
			dma_map_ch[0] = DMAMAP_DMA12_TIM8CH1_0;
			dma_map_ch[1] = DMAMAP_DMA12_TIM8CH2_0;
			dma_map_ch[2] = DMAMAP_DMA12_TIM8CH3_0;
			dma_map_ch[3] = DMAMAP_DMA12_TIM8CH4_0;

		} else {
			dma_map_ch[0] = DMAMAP_DMA12_TIM8CH1_1;
			dma_map_ch[1] = DMAMAP_DMA12_TIM8CH2_1;
			dma_map_ch[2] = DMAMAP_DMA12_TIM8CH3_1;
			dma_map_ch[3] = DMAMAP_DMA12_TIM8CH4_1;
		}

		break;

	default:
		break;
	}
}

static inline constexpr uint32_t getTimerUpdateDMAMap(Timer::Timer timer, const DMA &dma)
{
	uint32_t dma_map_up = 0;

	switch (timer) {
	case Timer::Timer1:
		dma_map_up = (dma.index == DMA::Index1) ? DMAMAP_DMA12_TIM1UP_0 : DMAMAP_DMA12_TIM1UP_1;
		break;

	case Timer::Timer2:
		dma_map_up = (dma.index == DMA::Index1) ? DMAMAP_DMA12_TIM2UP_0 : DMAMAP_DMA12_TIM2UP_1;
		break;

	case Timer::Timer3:
		dma_map_up = (dma.index == DMA::Index1) ? DMAMAP_DMA12_TIM3UP_0 : DMAMAP_DMA12_TIM3UP_1;
		break;

	case Timer::Timer4:
		dma_map_up = (dma.index == DMA::Index1) ? DMAMAP_DMA12_TIM4UP_0 : DMAMAP_DMA12_TIM4UP_1;
		break;

	case Timer::Timer5:
		dma_map_up = (dma.index == DMA::Index1) ? DMAMAP_DMA12_TIM5UP_0 : DMAMAP_DMA12_TIM5UP_1;
		break;

	case Timer::Timer6:
		dma_map_up = (dma.index == DMA::Index1) ? DMAMAP_DMA12_TIM6UP_0 : DMAMAP_DMA12_TIM6UP_1;
		break;

	case Timer::Timer7:
		dma_map_up = (dma.index == DMA::Index1) ? DMAMAP_DMA12_TIM7UP_0 : DMAMAP_DMA12_TIM7UP_1;
		break;

	case Timer::Timer8:
		dma_map_up = (dma.index == DMA::Index1) ? DMAMAP_DMA12_TIM8UP_0 : DMAMAP_DMA12_TIM8UP_1;
		break;

	default:
		break;
	}

	constexpr_assert(dma_map_up != 0, "Invalid DMA config for given timer");
	return dma_map_up;
}
