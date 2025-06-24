#include "./includes/menu.ui.h"
#include "../../utils/utils.h"
#include "../authentication/includes/auth.controller.h"
#include "../authorization/includes/authz.h"
#include "../configSystem/includes/config.service.h"
#include <stdio.h>
#include <stdlib.h>

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

void inf_menu_ui(ConfigSystem c, Auth a) {
  printf("\n--- Info del Sistema ---\n");
  printf("Negocio: %s\n", c.bussinesName);
  printf("Usuario: %s\n", a.user.username);
  printf("Rol: %s\n", role_to_string(a.user.role));
  printf("------------------------\n");
}

void main_menu(Auth *session) {
  ConfigSystem *c = get_config_service();
  int option = 0;
  char input[MAX_INPUT];

  do {
    art_adminCore();

    printf("\n--- Info del Sistema ---\n");
    printf("Negocio: %s\n", c->bussinesName);
    printf("Usuario: %s\n", session->user.username);
    printf("Rol: %s\n", role_to_string(session->user.role));
    printf("------------------------\n");

    printf("\n=== Menú Principal ===\n");
    printf("1. Gestión de usuarios\n");
    printf("2. Gestión de productos\n");
    printf("3. Configuración del sistema\n");
    printf("4. Punto de venta (POS)\n");
    printf("5. Cerrar sesión\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");

    get_line_input(input, MAX_INPUT);

    if (sscanf(input, "%d", &option) != 1) {
      option = -1;
    }

    switch (option) {
    case 1:
      clear_screen();
      menu_user_controller(session);
      clear_screen();
      break;
    case 2:
      clear_screen();
      menu_products_controller(session);
      clear_screen();
      break;
    case 3:
      clear_screen();
      menu_config_controller(session);
      clear_screen();
      break;
    case 4:
      clear_screen();
      run_pos_controller();
      clear_screen(); // ← Solo aquí, después de POS
      break;
    case 5:
      logout_controller();
      printf("\nSesión cerrada exitosamente.\n");
      press_enter_to_continue();
      clear_screen();
      free(c);
      option = 0;
      break;
    case 0:
      printf("\nSaliendo del sistema...\n");
      press_enter_to_continue();
      free(c);
      break;
    default:
      printf("\nOpción inválida. Intenta de nuevo.\n");
      delay_ms(1000);
      break;
    }

  } while (option != 0);
}
