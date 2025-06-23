#include "./includes/menu.ui.h"
#include "../../utils/utils.h"
#include "../authorization/includes/authz.h"
#include <stdio.h>

// Acciones simples para test
void manage_users() { printf("-> Gestión de usuarios\n"); }
void edit_config() { printf("-> Editar configuración\n"); }
void create_product() { printf("-> Crear producto\n"); }
void access_pos() { printf("-> Accediendo al POS\n"); }

void show_menu_ui(const Auth *session) {
  typedef struct {
    const char *label;
    Permission perm;
    void (*action)();
  } MenuOption;

  MenuOption menu[] = {{"Gestión de usuarios", PERM_USER_MANAGE, manage_users},
                       {"Editar configuración", PERM_CONFIG_EDIT, edit_config},
                       {"Crear producto", PERM_PRODUCT_CREATE, create_product},
                       {"Acceso al POS", PERM_POS_ACCESS, access_pos}};

  size_t count = sizeof(menu) / sizeof(MenuOption);
  int visible[count];
  int visible_count = 0;

  printf("\n== Menú para el rol: %s ==\n", role_to_string(session->user.role));

  for (size_t i = 0; i < count; ++i) {
    if (has_permission(session, menu[i].perm)) {
      printf("%d. %s\n", visible_count + 1, menu[i].label);
      visible[visible_count++] = i;
    }
  }

  if (visible_count == 0) {
    printf("No tienes permisos para acceder a ninguna opción.\n");
    return;
  }

  printf("Seleccione una opción: ");
  int choice;
  scanf("%d", &choice);

  if (choice >= 1 && choice <= visible_count) {
    menu[visible[choice - 1]].action();
  } else {
    printf("Opción inválida.\n");
  }
}

void main_menu(Auth *session) {
  int option = 0;
  char input[MAX_INPUT];

  do {
    printf("\n=== Menú Principal ===\n");
    printf("1. Gestión de usuarios\n");
    printf("2. Gestión de productos\n");
    printf("3. Configuración del sistema\n");
    printf("4. Punto de venta (POS)\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");

    get_line_input(input, MAX_INPUT);

    if (sscanf(input, "%d", &option) != 1) {
      option = -1;
    }

    switch (option) {
    case 1:
      menu_user_controller(session);
      break;
    case 2:
      menu_products_controller(session);
      break;
    case 3:
      menu_config_controller(session);
      break;
    case 4:
      run_pos_controller(); // ← acceso libre
      break;
    case 0:
      printf("Saliendo del sistema...\n");
      break;
    default:
      printf("Opción inválida.\n");
    }

  } while (option != 0);
}
