#include "includes/auth.controller.h"
#include "../../utils/utils.h"
#include "../users/includes/user.service.h"
#include "includes/auth.service.h"
#include "includes/auth.ui.h"
#include <stdio.h>
#include <stdlib.h> // Para free()
#include <string.h>
#include <time.h>

int login_controller() {
  Auth session;
  User *foundUser = NULL;
  int attempt = 0;
  int login_successful = 0;

  // Validar si existe sesión
  if (get_session_service() != NULL) {
    printf("Sesión iniciada.\nAccediendo... \n");
    delay_ms(2000);
    clear_screen();
    return 1;
  }

  // Intentar 3 veces
  while (attempt < 3 && !login_successful) {
    login_ui(&session); // Obtener datos de usuario
    foundUser = find_user_by_username_service(session.user.username);

    // Validar si el usuario existe
    if (foundUser == NULL) {
      printf("Usuario no encontrado.\n");
      attempt++;
      continue;
    }

    if (strcmp(foundUser->password, session.user.password) != 0) {
      printf("Contraseña incorrecta.\n");
      attempt++;
      continue;
    }

    login_successful = 1;
    break;
  }

  if (!login_successful) {
    printf("Se han realizado 3 intentos fallidos, valida tus credenciales.\n");
    if (foundUser != NULL) {
      free(foundUser);
    }
    return 0; // Indica fallo en el inicio de sesión
  }

  // Crear sesión
  session.user = *foundUser;
  session.CreatedAt = time(NULL);

  if (create_session_service(session) != 0) {
    printf("Error al crear la sesión.\n");
    if (foundUser != NULL) {
      free(foundUser);
    }
    return 0; // Indica fallo al crear la sesión
  }

  if (foundUser != NULL) {
    free(foundUser);
  }

  printf("Sesión creada con éxito.\nAccediendo...\n");
  delay_ms(2000);
  clear_screen();
  return 1; // Indica inicio de sesión exitoso
}

Auth *get_session_controller() {
  Auth *session = get_session_service();
  if (session == NULL) {
    printf("No existe una sesión iniciada.\n");
    return NULL;
  }

  // Opcional: Mostrar información de la sesión en UI
  // show_session_ui(session);

  return session;
}

void logout_controller() {
  printf("Cerrando sesión...\n");
  if (delete_session_service() != 0) {
    printf("Error al eliminar la sesión.\n");
    return;
  }
}
