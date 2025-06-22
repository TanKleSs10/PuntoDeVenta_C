#ifndef USER_UI_H
#define USER_UI_H

#include "user.model.h"

void create_user_ui(User *user, int superadmin);
void update_user_ui(User *user);
void find_user_by_id_ui(User *user);
void find_user_by_username_ui(User *user);
void delete_user_ui(User *user);
void show_user_ui(User *user);
void list_users_ui(User *users[], int count);
void menu_users_ui();

#endif
