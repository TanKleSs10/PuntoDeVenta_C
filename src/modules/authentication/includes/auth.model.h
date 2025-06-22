#ifndef AUTH_MODEL_H
#define AUTH_MODEL_H

#include <stdbool.h>
#include <time.h>
#include "../../users/includes/user.model.h"


typedef struct {
    User user;
    time_t CreatedAt;
} Auth;

#endif