#ifndef CONFIG_SERVICE_H
#define CONFIG_SERVICE_H

#include "config.model.h"

int create_config_service(ConfigSystem config);
ConfigSystem* get_config_service();
int update_config_service(ConfigSystem config);
int delete_config_service();

#endif