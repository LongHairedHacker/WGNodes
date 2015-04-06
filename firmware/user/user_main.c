#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"

#include "spibang.h"
#include "color.h"

#define user_procTaskPrio 0
#define user_procTaskQueueLen 1
os_event_t user_procTaskQueue[user_procTaskQueueLen];

int foo = 0;

//Do nothing function
void ICACHE_FLASH_ATTR user_procTask(os_event_t *events)
{

	struct color_hsv hsv;
	struct color_rgb rgb;

	hsv.h = foo / 10;
	hsv.s = 255;
	hsv.v = 255;

	color_hsv2rgb(&hsv, &rgb);

	spibang_send_byte(rgb.r);
	spibang_send_byte(rgb.g);
	spibang_send_byte(rgb.b);
	os_delay_us(600);

	foo++;
	if(foo / 10 > 1536) {
		foo = 0;
	}
	system_os_post(user_procTaskPrio, 0, 0 );
}

//Init function 
void ICACHE_FLASH_ATTR user_init()
{
    // Initialize the GPIO subsystem.
    gpio_init();

	spibang_init();

	system_os_task(user_procTask, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
	system_os_post(user_procTaskPrio, 0, 0 );
}
