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
#include "./UserController.h"
#include "./ConfigController.h"
#include "./ProductController.h"
// Declaraciones para AuthController (controller)

void login();
void logout();
int isLoggedIn();
void welcome();

#endif
