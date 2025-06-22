#ifndef CONFIG_CONTROLLER_H
#define CONFIG_CONTROLLER_H

#include "../../authentication/includes/auth.model.h"
#include "../../authorization/includes/authz.h"
#include "config.model.h"

void create_config_controller();
void update_config_controller();
void get_config_controller();
void delete_config_controller();
void menu_config_controller(Auth *session);

#endif
