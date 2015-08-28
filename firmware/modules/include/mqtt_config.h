#ifndef _MQTT_CONFIG_H_
#define _MQTT_CONFIG_H_

#include "mqtt.h"

static const char topic_prefix[] = "";
static const char topic_config_suffix[] = "config";


void mqtt_config_init(void);
void mqtt_config_subscribe(MQTT_Client *client);
void mqtt_config_update(char *topic, char *data);

#endif

