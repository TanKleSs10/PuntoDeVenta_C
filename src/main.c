#include "modules/authentication/includes/auth.controller.h"
#include "modules/authentication/includes/auth.model.h"
#include "modules/configSystem/includes/config.controller.h"
#include "modules/menu/includes/menu.ui.h"
// #include "modules/users/includes/user.controller.h"
// #include "modules/products/includes/product.controller.h"
// #include "modules/pos/includes/pos.controller.h"
// #include "modules/menu/includes/menu.ui.h"
//
// #include "utils/logger.h"
// #include "utils/utils.h"
// #include <stdio.h>

int main() {
  Auth *SESSION;
  int is_session_exist = 0;

  // Configuración inicial del sistema
  create_config_controller();

  // Iniciar sesión
  is_session_exist = login_controller();

  if (is_session_exist)
    SESSION = get_session_controller(); // <-- Esto recupera la sesión real

  main_menu(SESSION);
  return 0;
}
