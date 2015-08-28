#include "color.h" 
#include "mqtt.h"
#include "osapi.h"
#include "string_utils.h"

#include "channels.h"

struct color_rgb channel_colors[CHANNEL_COUNT];

void channels_init() {
	os_memset(channel_colors, 0, sizeof(struct color_rgb) * CHANNEL_COUNT);
}

void channels_subscribe(MQTT_Client *client) {
	int i;
	for(i = 0; i < CHANNEL_COUNT; i++) {
		MQTT_Subscribe(client, channel_infos[i].topic, 0);
	}
}


void channels_update(char *topic, char *data) {
	int i;

	for(i = 0; i < CHANNEL_COUNT; i++) {
		if(strcmp(channel_infos[i].topic, topic) == 0) {
			char *lines[3];
			int count = parse_lines(data, lines, 3);
			if(count == 3) {
				channels_set(i, atoi(lines[0]), atoi(lines[1]), atoi(lines[2]));
			}
		}
	}
}


void channels_set(uint8_t channel, uint16_t h, uint8_t v, uint8_t s) {
	if(channel >= CHANNEL_COUNT) {
		return;
	}

	struct color_hsv hsv;

	hsv.h = h;
	hsv.v = v;
	hsv.s = s;

	color_hsv2rgb(&hsv, &channel_colors[channel]);	
}
