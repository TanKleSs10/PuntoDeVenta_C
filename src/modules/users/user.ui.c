#include "../../utils/utils.h"
#include <stdbool.h> // Para bool
#include <string.h>  // Para strlen

#define MAX_INPUT 100

void create_user_ui(User *user, int superadmin) {
  char input[MAX_INPUT];
  int role_input;
  bool valid_input;

  // Solicitar ID con validación
  do {
    printf("Ingresa el ID de usuario: ");
    get_line_input(input, MAX_INPUT);
    valid_input = (sscanf(input, "%d", &user->id) == 1);
    if (!valid_input) {
      printf("Entrada inválida. Por favor, ingresa un número.\n");
    }
  } while (!valid_input);

  // Solicitar nombre de usuario con validación (longitud mínima/máxima)
  do {
    printf("Ingresa el nombre de usuario (entre 3 y 20 caracteres): ");
    get_line_input(user->username, sizeof(user->username));
    valid_input = (strlen(user->username) >= 3 && strlen(user->username) <= 20);
    if (!valid_input) {
      printf("El nombre de usuario debe tener entre 3 y 20 caracteres.\n");
    }
  } while (!valid_input);

  // Solicitar contraseña con validación (longitud mínima/máxima)
  do {
    printf("Ingresa la contraseña (entre 8 y 20 caracteres): ");
    get_line_input(user->password, sizeof(user->password));
    valid_input = (strlen(user->password) >= 8 && strlen(user->password) <= 20);
    if (!valid_input) {
      printf("La contraseña debe tener entre 8 y 20 caracteres.\n");
    }
  } while (!valid_input);

  // Solicitar rol con validación
  if (superadmin) {
    user->role = SUPERADMIN;
  } else {
    do {
      printf("Selecciona el rol:\n 1: ADMIN\n 2: CAJERO\n");
      printf("Ingresa el número correspondiente al rol: ");
      get_line_input(input, MAX_INPUT);

      valid_input = (sscanf(input, "%d", &role_input) == 1 &&
                     (role_input == ADMIN || role_input == CASHIER));

      if (valid_input) {
        user->role = (UserRole)role_input;
      } else {
        printf("Rol inválido. Por favor, ingresa 1 (ADMIN) o 2 (CAJERO).\n");
      }
    } while (!valid_input);
  }
}

void update_user_ui(User *user) { create_user_ui(user, 0); }

void find_user_by_id_ui(User *user) {
  char input[MAX_INPUT];
  bool valid_input;
  do {
    printf("Ingresa el ID de usuario: ");
    get_line_input(input, MAX_INPUT);
    valid_input = (sscanf(input, "%d", &user->id) == 1);
    if (!valid_input) {
      printf("Entrada inválida. Por favor, ingresa un número.\n");
    }
  } while (!valid_input);
}

void find_user_by_username_ui(User *user) {
  bool valid_input;
  do {
    printf("Ingresa el nombre de usuario (entre 3 y 20 caracteres): ");
    get_line_input(user->username, sizeof(user->username));
    valid_input = (strlen(user->username) >= 3 && strlen(user->username) <= 20);
    if (!valid_input) {
      printf("El nombre de usuario debe tener entre 3 y 20 caracteres.\n");
    }
  } while (!valid_input);
}

void delete_user_ui(User *user) { find_user_by_id_ui(user); }

void menu_users_ui() {
  printf("==== Menu de usuarios ====\n");
  printf("1. Crear usuario\n");
  printf("2. Ver usuarios\n");
  printf("3. Buscar usuario por ID\n");
  printf("4. Buscar usuario por nombre de usuario\n");
  printf("5. Actualizar usuario\n");
  printf("6. Eliminar usuario\n");
  printf("0. Salir\n");
}

// Output
void show_user_ui(User *user) {
  printf("ID: %d\n", user->id);
  printf("Nombre de usuario: %s\n", user->username);
  // printf("Contraseña: %s\n", user->password);
  printf("Rol: %s\n", role_to_string(user->role));
}

void list_users_ui(User *users[], int count) {
  printf("=== Listado de usuarios (%d encontrados) ===\n\n", count);
  for (int i = 0; i < count; i++) {
    // printf("Usuario #%d\n", i + 1);
    show_user_ui(users[i]);
    printf("----------------------------\n");
  }
}
