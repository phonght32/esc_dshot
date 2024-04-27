// MIT License

// Copyright (c) 2024 phonght32

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __ESC_DSHOT_H__
#define __ESC_DSHOT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"

#define DSHOT_FRAME_SZIE 	16

/**
 * @brief   Handle structure.
 */
typedef struct esc_dshot *esc_dshot_handle_t;

/**
 * @brief   Dshot type.
 */
typedef enum {
	ESC_DSHOT_TYPE_150 = 0,
	ESC_DSHOT_TYPE_300,
	ESC_DSHOT_TYPE_600,
	ESC_DSHOT_TYPE_1200
} esc_dshot_type_t;

/**
 * @brief   Configuration structure.
 */
typedef struct {
	uint32_t 				tim_freq;			/*!< Timer clock frequency in Hz */
	esc_dshot_type_t 		dshot_type;			/*!< Dshot type */
} esc_dshot_cfg_t;

/*
 * @brief   Initialize ESC_DSHOT with default parameters.
 *
 * @note    This function must be called first.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
esc_dshot_handle_t esc_dshot_init(void);

/*
 * @brief   Set configuration parameters.
 *
 * @param 	handle Handle structure.
 * @param   config Configuration structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t esc_dshot_set_config(esc_dshot_handle_t handle, esc_dshot_cfg_t config);

/*
 * @brief   Configure Dshot to run.
 *
 * @param 	handle Handle structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t esc_dshot_config(esc_dshot_handle_t handle);

/*
 * @brief   Get configuration parameter for timer.
 *
 * @param 	handle Handle structure.
 * @param 	tick_bit Number of tick for 1 bit data.
 * @param 	tick_bit1_high Number of tick for bit 1 in high level.
 * @param 	tick_bit0_high Number of tick for bit 0 in high level.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t esc_dshot_get_timer_config(esc_dshot_handle_t handle, uint32_t *tick_bit, uint32_t *tick_bit1_high, uint32_t *tick_bit0_high);

/*
 * @brief   Prepare packet.
 *
 * @param 	handle Handle structure.
 * @param 	throttle Throttle value.
 * @param 	packet Output packet.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t esc_dshot_prepare_packet(esc_dshot_handle_t handle, uint16_t throttle, uint16_t *packet);

#ifdef __cplusplus
}
#endif

#endif /* __ESC_DSHOT_H__ */