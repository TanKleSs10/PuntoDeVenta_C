#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

#include "auth.model.h"

int login_controller();
void logout_controller();
Auth* get_session_controller();

#endif