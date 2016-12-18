/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_DMAMUX_HAL_H__
#define __FSL_DMAMUX_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup dmamux_hal
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name DMAMUX HAL function
 * @{
 */

/*!
 * @brief Initializes the DMAMUX module to the reset state.
 *
 * Initializes the DMAMUX module to the reset state.
 *
 * @param base Register base address for DMAMUX module.
 */
void DMAMUX_HAL_Init(DMAMUX_Type * base);

/*!
 * @brief Enables/Disables the DMAMUX channel.
 *
 * Enables the hardware request. If enabled, the hardware request is  sent to
 * the corresponding DMA channel.
 *
 * @param base Register base address for DMAMUX module.
 * @param channel DMAMUX channel number.
 * @param enable Enables (true) or Disables (false) DMAMUX channel.
 */
static inline void DMAMUX_HAL_SetChannelCmd(DMAMUX_Type * base, uint32_t channel, bool enable)
{
#ifdef DEV_ERROR_DETECT
    DEV_ASSERT(channel < FSL_FEATURE_DMAMUX_MODULE_CHANNEL);
#endif
    BITBAND_ACCESS32(&(base->CHCFG[channel]), DMAMUX_CHCFG_ENBL_SHIFT) = ((uint32_t)enable);
}

#if (FSL_FEATURE_DMAMUX_HAS_TRIG == 1)
/*!
 * @brief Enables/Disables the period trigger.
 *
 * @param base Register base address for DMAMUX module.
 * @param channel DMAMUX channel number.
 * @param enable Enables (true) or Disables (false) period trigger.
 */
static inline void DMAMUX_HAL_SetPeriodTriggerCmd(DMAMUX_Type * base, uint32_t channel, bool enable)
{
#ifdef DEV_ERROR_DETECT
    DEV_ASSERT(channel < FSL_FEATURE_DMAMUX_MODULE_CHANNEL);
#endif
    BITBAND_ACCESS32(&(base->CHCFG[channel]), DMAMUX_CHCFG_TRIG_SHIFT) = ((uint32_t)enable);
}
#endif

/*!
 * @brief Configures the DMA request for the DMAMUX channel.
 *
 * Sets the trigger source for the DMA channel. The trigger source is in the file
 * fsl_dma_request.h.
 *
 * @param base Register base address for DMAMUX module.
 * @param channel DMAMUX channel number.
 * @param source DMA request source.
 */
static inline void DMAMUX_HAL_SetTriggerSource(DMAMUX_Type * base, uint32_t channel, uint8_t source)
{
#ifdef DEV_ERROR_DETECT
    DEV_ASSERT(channel < FSL_FEATURE_DMAMUX_MODULE_CHANNEL);
#endif
    uint8_t regValTemp;
    regValTemp = base->CHCFG[channel];
    regValTemp &= ~(DMAMUX_CHCFG_SOURCE_MASK);
    regValTemp |= DMAMUX_CHCFG_SOURCE(source);
    base->CHCFG[channel] = regValTemp;
}

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* __FSL_DMAMUX_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
