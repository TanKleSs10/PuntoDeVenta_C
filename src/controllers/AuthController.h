#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../models/UserModel.h"
#include "../models/AuthModel.h"
#include "../models/ConfigModel.h"
#include "../views/AuthView.h"
// Declaraciones para AuthController (controller)

void login();
int isLoggedIn();
void welcome();

#endif
