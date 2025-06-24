#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include "auth.repository.h"

int create_session_service(Auth auth);
Auth* get_session_service();
int delete_session_service();

#endif