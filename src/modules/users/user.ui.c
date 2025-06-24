#include "../../utils/utils.h"
#include <stdbool.h> // Para bool
#include <string.h>  // Para strlen
#define MIN_USERNAME_LEN 3
#define MAX_USERNAME_LEN                                                       \
  19 // Asume username[20] en User struct (19 chars + '\0')
#define MIN_PASSWORD_LEN 8
#define MAX_PASSWORD_LEN                                                       \
  19 // Asume password[20] en User struct (19 chars + '\0')

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
    printf("Ingresa el nombre de usuario (entre %d y %d caracteres): ",
           MIN_USERNAME_LEN, MAX_USERNAME_LEN);
    get_line_input(user->username, sizeof(user->username));
    valid_input = (strlen(user->username) >= 3 && strlen(user->username) <= 20);
    if (!valid_input) {
      printf("El nombre de usuario debe tener entre %d y %d caracteres.\n",
             MIN_USERNAME_LEN, MAX_USERNAME_LEN);
    }
  } while (!valid_input);

  // Solicitar contraseña con validación (longitud mínima/máxima)
  do {
    printf("Ingresa la contraseña (entre %d y %d caracteres): ",
           MIN_PASSWORD_LEN, MAX_PASSWORD_LEN);
    get_line_input(user->password, sizeof(user->password));
    valid_input = (strlen(user->password) >= 8 && strlen(user->password) <= 20);
    if (!valid_input) {
      printf("La contraseña debe tener entre %d y %d caracteres.\n",
             MIN_PASSWORD_LEN, MAX_PASSWORD_LEN);
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

      int sscanf_result = sscanf(input, "%d", &role_input);
      printf("DEBUG: sscanf_result=%d, role_input=%d\n", sscanf_result,
             role_input);

      valid_input = (sscanf_result == 1 &&
                     (role_input == ADMIN || role_input == CASHIER));
      printf("DEBUG: valid_input=%d\n", valid_input);

      if (valid_input) {
        user->role = (UserRole)role_input;
        printf("DEBUG: Rol asignado correctamente: %d\n", user->role);
      } else {
        printf("Rol inválido. Por favor, ingresa 1 (ADMIN) o 2 (CAJERO).\n");
      }
    } while (!valid_input);
  }
}

void update_user_ui(User *update_data) {
  char input[MAX_INPUT]; // Buffer genérico para capturar S/N o entradas
                         // temporales
  bool valid_input;
  int sscanf_result;

  printf("\n=== Actualización de Usuario ===\n");
  printf(
      "Deja los campos en blanco o presiona 'N' si no deseas actualizarlos.\n");

  // Inicializar los campos de update_data para indicar "sin cambios"
  // Para ID: Usaremos -1 o algún valor que indique "no actualizar ID"
  update_data->id = -1; // -1 indica que el ID no se actualizará a sí mismo,
                        // sino que se usará para buscar

  // Para cadenas: Usaremos cadena vacía "" para indicar "no actualizar"
  strcpy(update_data->username, "");
  strcpy(update_data->password, "");

  update_data->role = -1; // Asume que -1 no es un valor válido de UserRole

  // --- Nombre de usuario ---
  printf("\n¿Deseas actualizar el nombre de usuario? (S/N): ");
  get_line_input(input, MAX_INPUT);
  if (input[0] == 'S' || input[0] == 's') {
    do {
      printf("Ingresa el nuevo nombre de usuario (%d a %d caracteres): ",
             MIN_USERNAME_LEN, MAX_USERNAME_LEN);
      // IMPORTANTE: Asegurarse de que el buffer en update_data->username
      // tenga espacio para MAX_USERNAME_LEN + 1 (para el '\0')
      get_line_input(update_data->username, sizeof(update_data->username));
      size_t len = strlen(update_data->username);
      valid_input = (len >= MIN_USERNAME_LEN && len <= MAX_USERNAME_LEN);
      if (!valid_input) {
        printf("Error: El nombre de usuario debe tener entre %d y %d "
               "caracteres.\n",
               MIN_USERNAME_LEN, MAX_USERNAME_LEN);
      }
    } while (!valid_input);
  }

  // --- Contraseña ---
  printf("\n¿Deseas actualizar la contraseña? (S/N): ");
  get_line_input(input, MAX_INPUT);
  if (input[0] == 'S' || input[0] == 's') {
    do {
      printf("Ingresa la nueva contraseña (%d a %d caracteres): ",
             MIN_PASSWORD_LEN, MAX_PASSWORD_LEN);
      // IMPORTANTE: Asegurarse de que el buffer en update_data->password
      // tenga espacio para MAX_PASSWORD_LEN + 1 (para el '\0')
      get_line_input(update_data->password, sizeof(update_data->password));
      size_t len = strlen(update_data->password);
      valid_input = (len >= MIN_PASSWORD_LEN && len <= MAX_PASSWORD_LEN);
      if (!valid_input) {
        printf("Error: La contraseña debe tener entre %d y %d caracteres.\n",
               MIN_PASSWORD_LEN, MAX_PASSWORD_LEN);
      }
    } while (!valid_input);
  }

  // --- Rol de Usuario ---
  printf("\n¿Deseas actualizar el rol de usuario? (S/N): ");
  get_line_input(input, MAX_INPUT);
  if (input[0] == 'S' || input[0] == 's') {
    int role_option;
    do {
      valid_input = true; // Reiniciar para cada intento de entrada
      printf("Selecciona el nuevo rol:\n");
      printf("  1: ADMIN\n");
      printf("  2: CAJERO\n");
      printf("Ingresa el número correspondiente al rol: ");

      get_line_input(input, MAX_INPUT); // Leer la entrada como string
      sscanf_result = sscanf(input, "%d", &role_option);

      if (sscanf_result != 1) {
        printf("Entrada inválida. Por favor, ingresa un número.\n");
        valid_input = false;
      } else {
        if (role_option >= 1 && role_option <= 2) {
          update_data->role = (UserRole)role_option; // Castear al tipo de enum
        } else {
          valid_input = false;
          printf("Opción de rol inválida. Por favor, elige 1 o 2.\n");
        }
      }
    } while (!valid_input);
  }
}

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
