#ifndef CONFIG_UI_H
#define CONFIG_UI_H

#include "config.model.h"

int create_config_ui(ConfigSystem *config, int isUpdate);
void update_config_ui(ConfigSystem *config);
void get_config_ui(ConfigSystem *config);
int delete_config_ui();
void menu_config_ui();

#endif
