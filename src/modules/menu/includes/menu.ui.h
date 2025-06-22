#ifndef MENU_UI_H
#define MENU_UI_H

#include "../../authentication/includes/auth.model.h"
#include "../../authorization/includes/authz.h"
#include "../../configSystem/includes/config.controller.h"
#include "../../pos/includes/pos.controller.h"
#include "../../products/includes/product.controller.h"
#include "../../users/includes/user.controller.h"
#include <stdio.h>

void show_menu_ui(const Auth *session);
void main_menu(Auth *session);

#endif
