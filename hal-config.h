  /***************************************************************************//**
 * @file
 * @brief hal-config.h
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef HAL_CONFIG_H
#define HAL_CONFIG_H

#include "board_features.h"
#include "hal-config-board.h"
#include "hal-config-app-common.h"
//#include "bspconfig.h"


#define PWM_PIN                               (3U)
#define PWM_PORT                              (gpioPortC)
#define PWM2_PIN                               (5U)
#define PWM2_PORT                              (gpioPortC)

#if 0
#define HAL_SERIAL_PORT_USART1			BSP_BCC_USART
#define BSP_SERIAL_APP_PORT				HAL_SERIAL_PORT_USART1
#endif

#ifndef HAL_VCOM_ENABLE
#define HAL_VCOM_ENABLE                   (1)
#endif
#ifndef HAL_I2CSENSOR_ENABLE
#define HAL_I2CSENSOR_ENABLE              (0)
#endif
#ifndef HAL_SPIDISPLAY_ENABLE
#define HAL_SPIDISPLAY_ENABLE             (0)
#endif

#endif
