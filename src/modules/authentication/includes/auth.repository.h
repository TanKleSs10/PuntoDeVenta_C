#ifndef AUTH_REPOSITORY_H
#define AUTH_REPOSITORY_H

#include "auth.model.h"

int save_session_repository(Auth auth);
Auth* get_session_repository();
int delete_session_repository();

#endif