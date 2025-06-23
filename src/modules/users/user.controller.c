#include "includes/user.controller.h"
#include "../../utils/utils.h"
#include "includes/user.service.h"
#include "includes/user.ui.h"
#include <stdio.h>
#include <stdlib.h> // Para free()

int create_user_controller() {
  User user;

  create_user_ui(&user, 0);
  if (create_user_service(user) != 0) {
    printf("Error: No se pudo crear el usuario.\n");
    return -1;
  }

  printf("Usuario creado exitosamente.\n");
  return 0;
}

int update_user_controller() {
  User user;
  int id;

  find_user_by_id_ui(&user);

  id = user.id;

  update_user_ui(&user);
  if (update_user_service(&user, id) != 0) {
    printf("No se pudo actualizar el usuario.\n");
    return -1;
  }

  printf("Usuario actualizado exitosamente.\n");

  return 0;
}

int find_user_by_id_controller() {
  User user_to_find;
  find_user_by_id_ui(&user_to_find);
  User *found_user = find_user_by_id_service(user_to_find.id);

  if (found_user == NULL) {
    printf("Error: No se pudo encontrar el usuario.\n");
    return -1;
  }

  printf("Usuario encontrado exitosamente.\n");
  show_user_ui(found_user);
  free(found_user); // ¡Liberar la memoria devuelta por el Service!

  return 0;
}

int find_user_by_username_controller() {
  User user_to_find;
  find_user_by_username_ui(&user_to_find);
  User *found_user = find_user_by_username_service(user_to_find.username);

  if (found_user == NULL) {
    printf("Error: No se pudo encontrar el usuario.\n");
    return -1;
  }

  printf("Usuario encontrado exitosamente.\n");
  show_user_ui(found_user);
  free(found_user); // ¡Liberar la memoria devuelta por el Service!

  return 0;
}

int list_users_controller() {
  int count = 0;
  User **users = list_users_service(&count); // Pasar la dirección de count

  if (!users || count < 1) {
    printf("Hubo un error al obtener el listado de usuarios.\n");
    return -1;
  }

  list_users_ui(users, count);

  // Liberar memoria
  for (int i = 0; i < count; i++) {
    free(users[i]);
    users[i] = NULL;
  }
  free(users);

  return 0;
}

int delete_user_controller() {
  User user_to_delete;
  delete_user_ui(&user_to_delete);
  if (delete_user_service(user_to_delete.id) != 0) {
    printf("No se pudo eliminar el usuario.\n");
    return -1;
  }

  printf("Usuario eliminado exitosamente.\n");

  return 0;
}

void menu_user_controller(Auth *session) {
  int option = 0;
  char input[MAX_INPUT];

  do {
    clear_screen();
    menu_users_ui();

    get_line_input(input, MAX_INPUT);

    // Intentar leer el entero de la cadena
    if (sscanf(input, "%d", &option) != 1) {
      // Si sscanf no pudo leer un entero, la entrada no es válida
      option = -1; // Valor para activar el 'default' en el switch
    }

    switch (option) {
    case 1:
      if (has_permission(session, PERM_USER_MANAGE)) {
        create_user_controller();
      } else {
        printf("No tienes permiso para crear usuarios.\n");
      }
      break;
    case 2:
      if (has_permission(session, PERM_USER_MANAGE)) {
        list_users_controller();
      } else {
        printf("No tienes permiso para ver usuarios.\n");
      }
      break;
    case 3:
      if (has_permission(session, PERM_USER_MANAGE)) {
        find_user_by_id_controller();
      } else {
        printf("No tienes permiso para buscar por ID.\n");
      }
      break;
    case 4:
      if (has_permission(session, PERM_USER_MANAGE)) {
        find_user_by_username_controller();
      } else {
        printf("No tienes permiso para buscar por nombre de usuario.\n");
      }
      break;
    case 5:
      if (has_permission(session, PERM_USER_MANAGE)) {
        update_user_controller();
      } else {
        printf("No tienes permiso para actualizar usuarios.\n");
      }
      break;
    case 6:
      if (has_permission(session, PERM_USER_MANAGE)) {
        delete_user_controller();
      } else {
        printf("No tienes permiso para eliminar usuarios.\n");
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
