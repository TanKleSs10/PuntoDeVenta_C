#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "user.model.h"

int create_user_service(User user);
int update_user_service(User *user, int id);
User *find_user_by_id_service(int id);
User *find_user_by_username_service(char *username);
User **list_users_service(int *count);
int delete_user_service(int id);

#endif
