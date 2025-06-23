#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "user.model.h"

int save_user(User user);
User *get_user_by_id(int id);
User *get_user_by_username(char *username);
User **list_users(int *count);
int update_user(User *user);
int delete_user(int id);

#endif
