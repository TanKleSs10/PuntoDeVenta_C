#include "modules/authentication/includes/auth.controller.h"
#include "modules/authentication/includes/auth.model.h"
#include "modules/configSystem/includes/config.controller.h"
#include "modules/configSystem/includes/config.model.h"
#include "modules/menu/includes/menu.ui.h"
// #include "modules/users/includes/user.controller.h"
// #include "modules/products/includes/product.controller.h"
// #include "modules/pos/includes/pos.controller.h"
// #include "modules/menu/includes/menu.ui.h"
//
// #include "utils/logger.h"
#include "utils/utils.h"

int main() {
  Auth *SESSION;

  int is_session_exist = 0;
  clear_screen();
  // Configuración inicial del sistema
  create_config_controller();

  // Iniciar sesión
  is_session_exist = login_controller();

  art_adminCore();

  if (is_session_exist == 1) {
    main_menu(SESSION);
  }
  return 0;
}
