#include "stdlib.h"
#include "stdbool.h"
#include "esc_dshot.h"

#define BIT_DURATION_US_DSHOT150  		6.67f
#define BIT_DURATION_US_DSHOT300  		3.33f
#define BIT_DURATION_US_DSHOT600  		1.67f
#define BIT_DURATION_US_DSHOT1200 		0.83f

#define BIT1_HIGH_DUTY  				0.74f
#define BIT0_HIGH_DUTY  				0.37f

typedef struct esc_dshot {
	uint32_t 				tim_freq;			/*!< Timer clock frequency in Hz */
	esc_dshot_type_t 		dshot_type;			/*!< Dshot type */
	uint32_t 				tick_bit;			/*!< Number of tick for 1 bit data */
	uint32_t  				tick_bit1_high;		/*!< Number of tick for bit 1 in high level */
	uint32_t  				tick_bit0_high;		/*!< Number of tick for bit 0 in high level */
} esc_dshot_t;

esc_dshot_handle_t esc_dshot_init(void)
{
	esc_dshot_handle_t handle = calloc(1, sizeof(esc_dshot_t));
	if (handle == NULL)
	{
		return NULL;
	}

	return handle;
}

err_code_t esc_dshot_set_config(esc_dshot_handle_t handle, esc_dshot_cfg_t config)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	uint32_t timer_tick_bit;

	switch (handle->dshot_type)
	{
	case ESC_DSHOT_TYPE_150:
		timer_tick_bit = BIT_DURATION_US_DSHOT150 * config.tim_freq / 1000000;
		break;

	case ESC_DSHOT_TYPE_300:
		timer_tick_bit = BIT_DURATION_US_DSHOT300 * config.tim_freq / 1000000;
		break;

	case ESC_DSHOT_TYPE_600:
		timer_tick_bit = BIT_DURATION_US_DSHOT600 * config.tim_freq / 1000000;
		break;

	case ESC_DSHOT_TYPE_1200:
		timer_tick_bit = BIT_DURATION_US_DSHOT1200 * config.tim_freq / 1000000;
		break;

	default:
		timer_tick_bit = BIT_DURATION_US_DSHOT150 * config.tim_freq / 1000000;
		break;
	}

	handle->tim_freq = config.tim_freq;
	handle->dshot_type = config.dshot_type;
	handle->tick_bit = timer_tick_bit;
	handle->tick_bit1_high = BIT1_HIGH_DUTY * timer_tick_bit;
	handle->tick_bit0_high = BIT0_HIGH_DUTY * timer_tick_bit;

	return ERR_CODE_SUCCESS;
}

err_code_t esc_dshot_config(esc_dshot_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t esc_dshot_get_timer_config(esc_dshot_handle_t handle, uint32_t *tick_bit, uint32_t *tick_bit1_high, uint32_t *tick_bit0_high)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	*tick_bit = handle->tick_bit;
	*tick_bit1_high = handle->tick_bit1_high;
	*tick_bit0_high = handle->tick_bit0_high;

	return ERR_CODE_SUCCESS;
}

err_code_t esc_dshot_prepare_packet(esc_dshot_handle_t handle, uint16_t throttle, uint16_t *packet)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
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

	return ERR_CODE_SUCCESS;
}