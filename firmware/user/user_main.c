#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"

#include "spibang.h"
#include "color.h"


uint16_t foo = 0;
uint8_t bar = 0;

os_timer_t led_timer;

void ICACHE_FLASH_ATTR led_timer_task(void)
{

	struct color_hsv hsv;
	struct color_rgb rgb;

	hsv.h = foo;
	hsv.s = 255;
	hsv.v = 255;

	color_hsv2rgb(&hsv, &rgb);

	spibang_send_byte(rgb.r);
	spibang_send_byte(rgb.g);
	spibang_send_byte(rgb.b);

	bar = ~bar & 0x0F;


	foo += 32;
	if(foo > 1535) {
		foo = 0;
	}
}

//Init function 
void ICACHE_FLASH_ATTR user_init()
{
    // Initialize the GPIO subsystem.
    gpio_init();

	spibang_init();

	os_timer_disarm(&led_timer);
	os_timer_setfn(&led_timer, (os_timer_func_t *)led_timer_task, (void *)0);
	os_timer_arm(&led_timer, 100, 1);

}
