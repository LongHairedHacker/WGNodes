#ifndef _CHANNELS_H_
#define _CHANNELS_H_

#include "color.h"

#define CHANNEL_COUNT 2

struct channel_info {
	char *topic;
};

static const struct channel_info channel_infos[] = {
	{"/light/lamp1"},
	{"/ligth/lamp2"},
};


extern struct color_rgb channel_colors[CHANNEL_COUNT];

void channels_init(void);
void channels_subscribe(MQTT_Client *client);
void channels_set(uint8_t channel, uint16_t h, uint8_t v, uint8_t s);
void channels_update(char *topic, char *data);

#endif
