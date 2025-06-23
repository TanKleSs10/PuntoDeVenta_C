#include "includes/config.controller.h"
#include "../../utils/utils.h"
#include "../users/includes/user.service.h"
#include "../users/includes/user.ui.h"
#include "includes/config.service.h"
#include "includes/config.ui.h"

#include <stdio.h>
#include <stdlib.h>

void create_config_controller() {
  ConfigSystem config;
  User u;
  if (get_config_service() != NULL) {
    printf("El Sistema ya está configurado.\nIniciando sistema... \n");
    delay_ms(2000);
    clear_screen();
    return;
  }

  create_config_ui(&config);
  create_user_ui(&u, 1);

  if (create_user_service(u) == -1) {
    printf("Error al crear el usuario administrador.\n");
    exit(EXIT_FAILURE);
  }

  config.admin_id = u.id;

  if (create_config_service(config) == -1) {
    printf("Error al crear la configuración del sistema.\n");
    exit(EXIT_FAILURE);
  }

  printf("Configuración creada con éxito.\n");
  return;
}

void update_config_controller() {
  ConfigSystem config;

  update_config_ui(&config);
  if (update_config_service(config) == -1) {
    printf("Error al actualizar la configuración del sistema.\n");
    return;
  }

  printf("Configuración actualizada con éxito.\n");
}

void get_config_controller() {
  ConfigSystem *config = get_config_service();
  User *u = find_user_by_id_service(config->admin_id);

  if (!config) {
    printf("Error al obtener la configuración del sistema.\n");
    return;
  }

  get_config_ui(config, u->username);
}

void delete_config_controller() {

  int confirm = delete_config_ui(); // ← obtiene la decisión del usuario

  if (confirm) {
    if (delete_config_service() == 0) {
      printf("Configuración eliminada correctamente.\n");
    } else {
      printf("Hubo un error al eliminar la configuración.\n");
    }
  } else {
    printf("Eliminación cancelada por el usuario.\n");
  }
}

void menu_config_controller(Auth *session) {
  int option = 0;
  do {
    clear_screen();
    menu_config_ui();
    scanf("%d", &option);
    getchar(); // Limpiar newline

    switch (option) {
    case 1:
      if (has_permission(session, PERM_CONFIG_VIEW)) {
        get_config_controller();
      } else {
        printf("No tienes permiso para ver la configuración.\n");
      }
      break;
    case 2:
      if (session->user.role == 3) {
        update_config_controller();
      } else {
        printf("Solo el Superadmin puede actualizar la configuración.\n");
      }
      break;
    case 3:
      if (session->user.role == 3) {
        delete_config_controller();
      } else {
        printf("Solo el Superadmin puede eliminar la configuración.\n");
      }
      break;
    case 0:
      printf("Volviendo al menú anterior...\n");
      break;
    default:
      printf("Opción inválida.\n");
      break;
    }
  } while (option != 0);
}
