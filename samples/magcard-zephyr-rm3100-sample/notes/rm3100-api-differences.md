
2026-03-14 sabado

Comment in 2025 code that API will be implemented later:

https://github.com/zephyrproject-rtos/zephyr/blob/main/drivers/sensor/pni/rm3100/rm3100.c#L136

```
/* This will be implemented later */
static DEVICE_API(sensor, rm3100_driver_api) = {
	/* API functions will be added here */
	.submit = rm3100_submit,
	.get_decoder = rm3100_get_decoder,
};
```
