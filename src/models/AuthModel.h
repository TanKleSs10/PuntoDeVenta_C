#ifndef AUTHMODEL_H
#define AUTHMODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UserModel.h"
#include "../helpers/helpers.h"

#define SESSIONS_FILE "../data/sessions.dat"

// Implementaciones para AuthModel (model)
typedef struct
{
    int isActive;
    User user;
    time_t CreatedAt;
} Session;

typedef enum
{
    ROLE_SUPERADMIN,
    ROLE_ADMIN,
    ROLE_CAJERO
} RoleUser;

int saveSession(Session *session);
Session *getSession();
int removeSession();

#endif
