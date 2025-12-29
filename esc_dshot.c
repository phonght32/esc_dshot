#include "stdlib.h"
#include "stdbool.h"
#include "esc_dshot.h"

#define BIT1_HIGH_DUTY  				0.74f
#define BIT0_HIGH_DUTY  				0.37f

typedef struct esc_dshot {
	esc_dshot_type_t 			dshot_type;			/*!< Dshot type */
	uint32_t 					tick_bit;			/*!< Number of timer ticks to present a data bit */
	esc_dshot_func_send_dma 	send_dma;			/*!< Function send DMA */
	uint32_t  					tick_bit1_high;		/*!< Number of tick for bit 1 in high level */
	uint32_t  					tick_bit0_high;		/*!< Number of tick for bit 0 in high level */
} esc_dshot_t;

static esc_dshot_status_t _prepare_packet(esc_dshot_handle_t handle, uint16_t throttle, uint16_t *packet)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ESC_DSHOT_STATUS_INVALID_ARG;
	}

	uint16_t packet_prepare;
	bool dshot_telemetry = false;

	packet_prepare = (throttle << 1) | (dshot_telemetry ? 1 : 0);

	/* Calculate CRC */
	unsigned csum = 0;
	unsigned csum_data = packet_prepare;

	for (int i = 0; i < 3; i++)
	{
		csum ^=  csum_data;
		csum_data >>= 4;
	}

	csum &= 0xf;
	packet_prepare = (packet_prepare << 4) | csum;

	*packet = packet_prepare;

	return ESC_DSHOT_STATUS_SUCCESS;
}

esc_dshot_handle_t esc_dshot_init(void)
{
	esc_dshot_handle_t handle = calloc(1, sizeof(esc_dshot_t));
	if (handle == NULL)
	{
		return NULL;
	}

	return handle;
}

esc_dshot_status_t esc_dshot_set_config(esc_dshot_handle_t handle, esc_dshot_cfg_t config)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ESC_DSHOT_STATUS_INVALID_ARG;
	}

	handle->dshot_type = config.dshot_type;
	handle->tick_bit = config.tick_bit;
	handle->send_dma = config.send_dma;
	handle->tick_bit1_high = BIT1_HIGH_DUTY * config.tick_bit;
	handle->tick_bit0_high = BIT0_HIGH_DUTY * config.tick_bit;

	return ESC_DSHOT_STATUS_SUCCESS;
}

esc_dshot_status_t esc_dshot_config(esc_dshot_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ESC_DSHOT_STATUS_INVALID_ARG;
	}

	return ESC_DSHOT_STATUS_SUCCESS;
}

esc_dshot_status_t esc_dshot_prepare_packet(esc_dshot_handle_t handle, uint16_t throttle, uint32_t *packet)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ESC_DSHOT_STATUS_INVALID_ARG;
	}

	uint16_t raw_packet;

	_prepare_packet(handle, throttle, &raw_packet);

	for (int i = 0; i < 16; i++)
	{
		packet[i] = (raw_packet & 0x8000) ? handle->tick_bit1_high : handle->tick_bit0_high;
		raw_packet <<= 1;
	}

	return ESC_DSHOT_STATUS_SUCCESS;
}

esc_dshot_status_t esc_dshot_send_packet(esc_dshot_handle_t handle, uint32_t *packet)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ESC_DSHOT_STATUS_INVALID_ARG;
	}

	if (handle->send_dma != NULL)
	{
		handle->send_dma(packet);
	}

	return ESC_DSHOT_STATUS_SUCCESS;
}
