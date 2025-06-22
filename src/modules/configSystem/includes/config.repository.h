#ifndef CONFIG_REPOSITORY_H
#define CONFIG_REPOSITORY_H

#include "config.model.h"

int save_config_repository(ConfigSystem config);
ConfigSystem* get_config_repository();
int update_config_repository(ConfigSystem config);
int delete_config_repository();

#endif