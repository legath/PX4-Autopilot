#pragma once

/* STM32G4 uses DMA_V1 + DMAMUX1. DMA channels are allocated dynamically from
 * the DMAMUX request number encoded as (controller << 8) | request.
 * Request numbers are defined in hardware/stm32g4xxxx_dmamux.h.
 *
 * NOTE: DMA is currently not used for SPI/UART/DShot on this port. The entries
 * below are provided for reference and can be enabled once the corresponding
 * drivers are wired up.
 */

#define DMAMAP_SPI2_RX    ((0 << 8) | DMAMUX1_SPI2_RX)    /* DMA1, req 12 */
#define DMAMAP_SPI2_TX    ((0 << 8) | DMAMUX1_SPI2_TX)    /* DMA1, req 13 */
#define DMAMAP_USART2_RX  ((0 << 8) | DMAMUX1_USART2_RX)  /* DMA1, req 26 */
#define DMAMAP_USART2_TX  ((0 << 8) | DMAMUX1_USART2_TX)  /* DMA1, req 27 */
#define DMAMAP_USART3_RX  ((0 << 8) | DMAMUX1_USART3_RX)  /* DMA1, req 28 */
#define DMAMAP_USART3_TX  ((0 << 8) | DMAMUX1_USART3_TX)  /* DMA1, req 29 */
