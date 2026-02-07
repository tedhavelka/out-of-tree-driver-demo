/*
 *  Project:  Kionix Driver Demo (Zephyr RTOS based app)
 *  Copyright (c) 2021 - 2026 Neela Nurseries
 *  SPDX-License-Identifier: Apache-2.0 and MIT licenses
 */

//----------------------------------------------------------------------
// - SECTION - includes
//----------------------------------------------------------------------

// newlib C includes:
#include <stdio.h>

// Zephyr RTOS includes:
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/uart.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(demo);

#include <kx132-1211.h>

#include "development-flags.h"

//----------------------------------------------------------------------
// - SECTION - symbol defines
//----------------------------------------------------------------------

#define KX132_NODE DT_NODELABEL(kionix_sensor)

#define SLEEP_TIME_MS 2000

//----------------------------------------------------------------------
// - SECTION - file scoped
//----------------------------------------------------------------------

#define MY_KX132 DT_NODELABEL(kionix_sensor)

#if DT_NODE_HAS_STATUS(MY_KX132, okay)
const struct device *const kx132_dev = DEVICE_DT_GET(MY_KX132);
#else
// #error "Node for KX132 is disabled"
#endif

union generic_data_four_bytes_union_t {
    char as_string[sizeof(int)];
    uint8_t as_bytes[sizeof(int)];
    uint32_t as_32_bit_integer;
};

//----------------------------------------------------------------------
// - SECTION - routines
//----------------------------------------------------------------------

int main(void)
{
	// sensor related variables
	struct sensor_value requested_config;
	// const struct device *const dev_accel0 = DEVICE_DT_GET_ANY(kionix_kx132);
	const struct device *const dev_accel0 = DEVICE_DT_GET(DT_NODELABEL(kionix_sensor));

	struct sensor_value value;
	union generic_data_four_bytes_union_t data_from_sensor;

	// heartbeat and housekeeping
	int main_loop_count = 0;
	uint32_t rc = 0;

	if (dev_accel0 == NULL)
	{
        	LOG_ERR("DEVICE_DT_GET_ANY(kionix_kx132) expands to null");
		// Would return -ENODEV but Zephyr requires int main() to return zero.
		// So too for other error points which exit main().
		goto done;
	}
	else
	{
		if (!device_is_ready(dev_accel0))
		{
			LOG_ERR("Device '%s' is not ready\n", dev_accel0->name);
			goto done;
		}
	}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 2026-01-23
// When we need to change sensor attributes or refer to channels not in
// Zephyr's enumerations for these things, here is where we may implement
// extending APIs for our sensor.
//
// ~2021:
//
// In following sensor configuration tests first three parameters
//  1 device pointer, 2 sensor channel, 3 sensor attribute stay the same
//  to honor two sensor API enumerations in Zephyr v2.6.0.  These enums
//  do not in any obvious way support arbitrary sensor channels and
//  attributes.  Thus to stay with Zephyr's API way, and pass custom
//  settings to configuring routines of our out-of-tree driver those
//  values we pass in the final parameter.
//
//  Zephyr 2.6.0 project header of interest in this matter is:
//  zephyr/include/drivers/sensor.h.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	if ( DEV_TEST__ENABLE_KX132_1211_ASYNCHRONOUS_READINGS == 1 )
	{
		requested_config.val1 = KX132_ENABLE_ASYNC_READINGS;

		rc = sensor_attr_set(
		  dev_accel0,
		  SENSOR_CHAN_ALL,
		  SENSOR_ATTR_PRIV_START,		  
		  &requested_config
		);
	}

	if ( DEV_TEST__SET_KX132_1211_OUTPUT_DATA_RATE == 1 )
	{
		requested_config.val1 = KX132_ENABLE_ASYNC_READINGS;
		requested_config.val2 = KX132_ODR_3200_HZ;

		rc = sensor_attr_set(
		  dev_accel0,
		  SENSOR_CHAN_ALL,
		  SENSOR_ATTR_PRIV_START,		  
		  &requested_config
		);
	}

	while (1)
	{
		if ( DEV_TEST__FETCH_AND_GET_MANUFACTURER_ID )
		{
			sensor_sample_fetch_chan(dev_accel0,
						 SENSOR_CHAN_KIONIX_MANUFACTURER_ID);
			sensor_channel_get(dev_accel0, SENSOR_CHAN_KIONIX_MANUFACTURER_ID,
						 &value);

			LOG_INF("KX132 manufacturer ID as 32-bit integer %d", value.val1);
			LOG_INF("sensor_value.val2 holds %d", value.val2);
			data_from_sensor.as_32_bit_integer = value.val1;

			LOG_INF("value.val1 as bytes:  ");
			LOG_INF("  0x%2X 0x%2X 0x%2X 0x%2X",
				 data_from_sensor.as_bytes[0],
				 data_from_sensor.as_bytes[1],
				 data_from_sensor.as_bytes[2],
				 data_from_sensor.as_bytes[3]
			);
			LOG_INF("value.val1 as characters:  '%c %c %c %c'",
				 data_from_sensor.as_bytes[0],
				 data_from_sensor.as_bytes[1],
				 data_from_sensor.as_bytes[2],
				 data_from_sensor.as_bytes[3]
			);
		}

		if ( DEV_TEST__FETCH_AND_GET_PART_ID )
		{
			sensor_sample_fetch_chan(dev_accel0, SENSOR_CHAN_KIONIX_PART_ID);
			sensor_channel_get(dev_accel0, SENSOR_CHAN_KIONIX_PART_ID, &value);
			LOG_INF("Kionix sensor reports part ID of %d", value.val1);
		}

		if ( DEV_TEST__FETCH_ACCELEROMETER_READINGS_XYZ )
		{
			rc = sensor_sample_fetch_chan(dev_accel0,
							SENSOR_CHAN_ACCEL_XYZ);
		}

		if ((main_loop_count % 10) == 0)
		{
			LOG_INF("- MARK - ");
		}

		k_msleep(SLEEP_TIME_MS);
		++main_loop_count;
	}

done:
	LOG_INF("Kionix driver demo done . . . exiting.");
	return 0;
}
