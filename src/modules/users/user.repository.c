#include "includes/user.repository.h"
#include "../../components/file.component.h"
#include "../../utils/logger.h"
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
    return NULL;
  }

  User **list = malloc(sizeof(User *) * MAX_USERS);
  if (!list) {
    fclose(f);
    LOG_CRITICAL("Fallo al reservar memoria para la lista de usuarios.");
    return NULL;
  }

  *count = 0;
  int read_result;
  while (*count < MAX_USERS) {
    User *u = malloc(sizeof(User));
    if (!u) {
      LOG_CRITICAL("Fallo al reservar memoria para el usuario en índice %d.",
                   *count);
      break;
    }

    read_result = read_record(f, u, sizeof(User));
    if (read_result != 0) {
      free(u);
      if (read_result == -1) {
        LOG_ERROR("Error al leer un registro de usuario desde el archivo.");
      }
      break;
    }

    list[*count] = u;
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
