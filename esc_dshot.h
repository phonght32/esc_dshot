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

#define DSHOT_FRAME_SIZE 	16

typedef err_code_t (*esc_dshot_func_send_dma)(uint32_t *buf_send);

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
	esc_dshot_type_t 			dshot_type;			/*!< Dshot type */
	uint32_t 					tick_bit;			/*!< Number of timer ticks to present a data bit */
	esc_dshot_func_send_dma 	send_dma;			/*!< Function send DMA */
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
 * @brief   Prepare packet DMA.
 *
 * @param 	handle Handle structure.
 * @param 	throttle Throttle value.
 * @param 	packet_dma Output packet.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t esc_dshot_prepare_packet(esc_dshot_handle_t handle, uint16_t throttle, uint32_t *packet);

/*
 * @brief   Send packet DMA.
 *
 * @param 	handle Handle structure.
 * @param 	packet_dma Packet DMA.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t esc_dshot_send_packet(esc_dshot_handle_t handle, uint32_t *packet);

#ifdef __cplusplus
}
#endif

#endif /* __ESC_DSHOT_H__ */