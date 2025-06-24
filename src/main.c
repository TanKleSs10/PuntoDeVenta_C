#include "modules/authentication/includes/auth.controller.h"
#include "modules/authentication/includes/auth.model.h"
#include "modules/configSystem/includes/config.controller.h"
// #include "modules/configSystem/includes/config.model.h"
#include "modules/menu/includes/menu.ui.h"
// #include "modules/users/includes/user.controller.h"
// #include "modules/products/includes/product.controller.h"
// #include "modules/pos/includes/pos.controller.h"
// #include "modules/menu/includes/menu.ui.h"
//
// #include "utils/logger.h"
#include "utils/utils.h"

int main() {
  // declaraciones necesarias para el inicio del programa
  Auth *SESSION;
  int is_session_exist = 0;

  // limpiar la pantalla
  clear_screen();

  // Configuración inicial del sistema
  create_config_controller();

  // Iniciar sesión
  is_session_exist = login_controller();

  // obtener detalles de la sesión
  SESSION = get_session_controller();

  // iniciar el menu solo si hay una sesión activa
  if (is_session_exist == 1) {
    main_menu(SESSION);
  }

  return 0;
}
