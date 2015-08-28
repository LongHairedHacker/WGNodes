#include <stdio.h>
#include <string.h>

#include "mem.h"
#include "osapi.h"
#include "config.h"
#include "debug.h"
#include "string_utils.h"

#include "mqtt_config.h"

char *config_topic;

void mqtt_config_init(void) {
	// Put together topic for config changes for this device
	size_t len = strlen(topic_prefix)
					+ strlen(sysCfg.device_id)
					+ strlen(topic_config_suffix) 
					+ 3; // Slashes + terminator
	config_topic = (char*) os_zalloc(len);
	os_sprintf(config_topic, "%s/%s/%s", topic_prefix, sysCfg.device_id, topic_config_suffix);
}


void mqtt_config_subscribe(MQTT_Client *client) {
	char *config = (char*) os_zalloc(256);
	os_sprintf(config, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n", 
				sysCfg.device_id,
				sysCfg.sta_ssid,
				sysCfg.sta_pwd,
				sysCfg.mqtt_host,
				sysCfg.mqtt_port,
				sysCfg.mqtt_user,
				sysCfg.mqtt_pass);
				
	size_t len = strlen(config);
	MQTT_Publish(client, config_topic, config, len, 0, 0);

	os_free(config);

	INFO("Use %s to change config\n", config_topic);
	MQTT_Subscribe(client, config_topic, 0);
}


void update_config_string(char *line, char *dest, size_t len, const char *name) {
	if(strcmp(line, "-") != 0) {
		INFO("Setting %s: %s\n", name, line);
		strncpy(dest, line, len);
	}
}

void update_config_integer(char *line, uint32_t *dest, const char *name) {
	if(strcmp(line, "-") != 0) {
		INFO("Setting %s: %s\n", name, line);
		*dest = atoi(line);
	}
}


void mqtt_config_update(char *topic, char *data) {
	if(strcmp(config_topic, topic) == 0) {	
		INFO("Got configuration update\r\n");
		
		char *lines[7];
		int result = parse_lines(data,lines,7);
		if(result != 7) {
			INFO("Not enough lines in new configuration. Only got %d.\n", result);
			return;
		}

		update_config_string(lines[0], sysCfg.device_id, 15, "device id");
		update_config_string(lines[1], sysCfg.sta_ssid, 63, "station ssid");
		update_config_string(lines[2], sysCfg.sta_pwd, 63, "station password");
		update_config_string(lines[3], sysCfg.mqtt_host, 63, "mqtt host");
		update_config_integer(lines[4], &sysCfg.mqtt_port, "mqtt port"); 
		update_config_string(lines[5], sysCfg.mqtt_user, 31, "mqtt user");
		update_config_string(lines[6], sysCfg.mqtt_pass, 31, "mqtt password");

		CFG_Save();
		system_restart();	
	}
}
