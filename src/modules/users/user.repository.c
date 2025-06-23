#include "includes/user.repository.h"
#include "../../components/file.component.h"
#include "../../utils/logger.h"
#include "../../utils/utils.h"
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define USER_FILE "data/users.dat"
#define TEMP_FILE "data/users_tmp.dat"

int save_user(User user) {
  FILE *f = open_file(USER_FILE, "ab");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para guardar el usuario.",
              USER_FILE);
    return -1;
  }

  int r = write_record(f, &user, sizeof(User));
  fclose(f);

  if (r != 0) {
    LOG_ERROR("Fallo al escribir el usuario en %s", USER_FILE);
    return -1;
  }

  LOG_INFO("Usuario con ID %d guardado correctamente.", user.id);
  return 0;
}

User *get_user_by_id(int id) {
  FILE *f = open_file(USER_FILE, "rb");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para obtener el usuario.",
              USER_FILE);
    return NULL;
  }

  User temp;
  while (read_record(f, &temp, sizeof(User)) == 0) {
    if (temp.id == id) {
      User *found_user = malloc(sizeof(User));
      if (!found_user) {
        fclose(f);
        LOG_CRITICAL("Fallo al reservar memoria para el usuario con ID %d.",
                     id);
        return NULL;
      }
      *found_user = temp;
      fclose(f);
      LOG_INFO("Usuario con ID %d encontrado en el repositorio.", id);
      return found_user;
    }
  }

  fclose(f);
  LOG_WARNING("No se encontró el usuario con ID %d.", id);
  return NULL;
}

User *get_user_by_username(char *username) {
  FILE *f = open_file(USER_FILE, "rb");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para buscar el usuario.",
              USER_FILE);
    return NULL;
  }

  User temp;
  while (read_record(f, &temp, sizeof(User)) == 0) {
    if (strcmp(temp.username, username) == 0) {
      User *found_user = malloc(sizeof(User));
      if (!found_user) {
        fclose(f);
        LOG_CRITICAL("Fallo al reservar memoria para el usuario '%s'.",
                     username);
        return NULL;
      }
      *found_user = temp;
      fclose(f);
      LOG_INFO("Usuario con nombre de usuario '%s' encontrado.", username);
      return found_user;
    }
  }

  fclose(f);
  LOG_WARNING("No se encontró el usuario con nombre de usuario '%s'.",
              username);
  return NULL;
}

int update_user(User user) {
  FILE *original = open_file(USER_FILE, "rb");
  FILE *temp = open_file(TEMP_FILE, "wb");
  if (!original || !temp) {
    LOG_ERROR("Error al abrir archivos para actualizar el usuario con ID %d.",
              user.id);
    return -1;
  }

  User current;
  int updated = 0;

  while (read_record(original, &current, sizeof(User)) == 0) {
    if (current.id == user.id) {
      write_record(temp, &user, sizeof(User));
      updated = 1;
    } else {
      write_record(temp, &current, sizeof(User));
    }
  }

  fclose(original);
  fclose(temp);

  if (remove(USER_FILE) != 0 || rename(TEMP_FILE, USER_FILE) != 0) {
    LOG_ERROR("Error al reemplazar el archivo original tras actualizar usuario "
              "con ID %d.",
              user.id);
    return -1;
  }

  if (updated) {
    LOG_INFO("Usuario con ID %d actualizado correctamente.", user.id);
    return 0;
  } else {
    LOG_WARNING("No se encontró el usuario con ID %d para actualizar.",
                user.id);
    return -1;
  }
}

User **list_users(int *count) {
  FILE *f = open_file(USER_FILE, "rb");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para listar usuarios.",
              USER_FILE);
    *count = 0; // Asegurarse de que el conteo sea 0 en caso de error
    return NULL;
  }

  // Inicialmente asignamos memoria para un número fijo de usuarios.
  // Considera usar realloc si el número de usuarios puede exceder MAX_USERS.
  User **list = (User **)malloc(sizeof(User *) * MAX_USERS);
  if (!list) {
    fclose(f);
    LOG_CRITICAL("Fallo al reservar memoria para la lista de usuarios.");
    *count = 0;
    return NULL;
  }

  *count = 0;
  User temp_user_read; // Buffer temporal para leer un registro del archivo

  // Bucle corregido: Leer un registro y verificar el éxito de la lectura.
  // read_record debe devolver 0 si lee sizeof(User) bytes, y un valor no 0 (ej.
  // -1) en EOF o error.
  while (read_record(f, &temp_user_read, sizeof(User)) == 0) {
    // Asignar memoria para el nuevo usuario solo si la lectura fue exitosa
    User *u = (User *)malloc(sizeof(User));
    if (!u) {
      LOG_CRITICAL("Fallo al reservar memoria para un usuario en el índice %d. "
                   "Deteniendo listado.",
                   *count);
      // Liberar la memoria ya asignada para evitar fugas
      for (int i = 0; i < *count; i++) {
        free(list[i]);
      }
      free(list); // Liberar el array de punteros
      fclose(f);
      *count = 0;
      return NULL;
    }

    // Copiar los datos leídos del archivo a la nueva memoria
    *u = temp_user_read;

    // **Validación de campos para evitar registros corruptos (sin strlen
    // directo)** Esto asume que role_to_string() devuelve NULL para roles
    // inválidos y que id <= 0 no es válido. Asegúrate de que los campos de
    // cadena (username, password) en 'u' ya están garantizados con terminadores
    // nulos por la lógica de escritura.
    if (u->id <= 0 || !role_to_string(u->role)) {
      LOG_WARNING("Usuario inválido encontrado (ID: %d, Rol: %d), descartado.",
                  u->id, u->role);
      free(u);  // Liberar la memoria del usuario inválido
      continue; // Ir a la siguiente iteración para intentar leer el próximo
    }

    // Verificar si la lista ha alcanzado su capacidad máxima
    if (*count >= MAX_USERS) {
      LOG_WARNING("Se alcanzó el límite de MAX_USERS (%d). Se ignorarán "
                  "usuarios adicionales.",
                  MAX_USERS);
      free(u); // Liberar el usuario que no podemos añadir
      break;   // Salir del bucle
    }

    list[*count] = u; // Añadir el puntero a la lista
    (*count)++;
  }

  fclose(f);

  LOG_INFO("Se listaron %d usuario(s) desde el repositorio.", *count);
  return list;
}

int delete_user(int id) {
  FILE *original = open_file(USER_FILE, "rb");
  FILE *temp = open_file(TEMP_FILE, "wb");
  if (!original || !temp) {
    LOG_ERROR("No se pudo abrir archivos para eliminar el usuario con ID %d.",
              id);
    return -1;
  }

  User current;
  int deleted = 0;

  while (read_record(original, &current, sizeof(User)) == 0) {
    if (current.id == id) {
      deleted = 1;
      continue;
    }
    write_record(temp, &current, sizeof(User));
  }

  fclose(original);
  fclose(temp);

  if (remove(USER_FILE) != 0 || rename(TEMP_FILE, USER_FILE) != 0) {
    LOG_ERROR("Error al reemplazar archivo tras eliminar usuario con ID %d.",
              id);
    return -1;
  }

  if (deleted) {
    LOG_INFO("Usuario con ID %d eliminado correctamente.", id);
    return 0;
  } else {
    LOG_WARNING("No se encontró el usuario con ID %d para eliminar.", id);
    return -1;
  }
}
