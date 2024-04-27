#include "esc_dshot.h"

typedef struct esc_dshot {
	esc_dshot_type_t 		dshot_type;			/*!< Dshot type */
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

	handle->dshot_type = config.dshot_type;

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