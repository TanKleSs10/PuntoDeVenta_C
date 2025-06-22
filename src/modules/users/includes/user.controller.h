#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "../../authentication/includes/auth.model.h"
#include "../../authorization/includes/authz.h"

int create_user_controller();
int update_user_controller();
int find_user_by_id_controller();
int find_user_by_username_controller();
int list_users_controller();
int delete_user_controller();
void menu_user_controller();

#endif
