#include "UserModel.h"
#include <time.h>
#include <stdlib.h>

int saveUser(const User *user)
{
    FILE *file = openFile(USERS_FILE, "ab", "Error al abrir el archivo de usuarios");
    if (!file)
        return 0;

    User newUser = *user;
    time_t now = time(NULL);
    newUser.created_at = now;
    newUser.updated_at = now;

    int result = fwrite(&newUser, sizeof(User), 1, file) == 1;
    fclose(file);
    return result;
}

int getAllUsers(User *users, int maxSize)
{
    FILE *file = openFile(USERS_FILE, "rb", "Error al abrir el archivo de usuarios");
    if (!file)
        return 0;

    int count = fread(users, sizeof(User), maxSize, file);
    fclose(file);
    return count;
}

// Función para obtener un usuario dinámicamente por ID
User *getUserById(int id)
{
    FILE *file = openFile(USERS_FILE, "rb", "Error al abrir el archivo de usuarios");
    if (!file)
        return NULL;

    User *user = malloc(sizeof(User));
    if (!user)
    {
        fclose(file);
        return NULL;
    }

    while (fread(user, sizeof(User), 1, file))
    {
        if (user->id == id)
        {
            fclose(file);
            return user;
        }
    }

    fclose(file);
    free(user);
    return NULL;
}

User *getUserByName(const char *name)
{
    FILE *file = openFile(USERS_FILE, "rb", "Error al abrir el archivo de usuarios");
    if (!file)
        return NULL;

    User *user = malloc(sizeof(User));
    if (!user)
    {
        fclose(file);
        return NULL;
    }

    while (fread(user, sizeof(User), 1, file))
    {
        if (strcmp(user->name, name) == 0)
        {
            fclose(file);
            return user;
        }
    }

    fclose(file);
    free(user);
    return NULL;
}

int modifyUser(int id, const User *newUser)
{
    FILE *file = openFile(USERS_FILE, "rb+", "Error al abrir el archivo de usuarios");
    if (!file)
        return 0;

    User user;
    while (fread(&user, sizeof(User), 1, file))
    {
        if (user.id == id)
        {
            // Convertir sizeof(User) a long int antes de aplicar el negativo
            fseek(file, -(long int)sizeof(User), SEEK_CUR);

            User updatedUser = *newUser;
            updatedUser.updated_at = time(NULL); // Actualiza la fecha de modificación
            int result = fwrite(&updatedUser, sizeof(User), 1, file) == 1;
            fclose(file);
            return result;
        }
    }

    fclose(file);
    return 0;
}

int removeUser(int id)
{
    FILE *file = openFile(USERS_FILE, "rb", "Error al abrir el archivo de usuarios");
    FILE *tempFile = openFile(TEMP_FILE, "wb", "Error al abrir el archivo temporal");
    if (!file || !tempFile)
        return 0;

    User user;
    int deleted = 0;

    // Leer el archivo de usuarios y copiar todos los usuarios excepto el que se desea eliminar
    while (fread(&user, sizeof(User), 1, file))
    {
        if (user.id != id)
        {
            fwrite(&user, sizeof(User), 1, tempFile);
        }
        else
        {
            deleted = 1; // Marcar que se encontró y eliminó el usuario
        }
    }

    fclose(file);
    fclose(tempFile);

    // Reemplazar el archivo original con el archivo temporal
    if (deleted)
    {
        return replaceFile(USERS_FILE, TEMP_FILE);
    }
    else
    {
        remove(TEMP_FILE); // Eliminar el archivo temporal si no se eliminó ningún usuario
        return 0;
    }
}

// Función para verificar si un usuario necesita cambiar su contraseña
int needsPasswordChange(const User *user)
{
    time_t now = time(NULL);
    double daysPassed = difftime(now, user->updated_at) / (60 * 60 * 24);
    return daysPassed >= 30;
}

int removeFileUsers()
{
    if (!openFile(USERS_FILE, "rb", "Error al abrir el archivo de usuarios"))
        return 0;

    remove(USERS_FILE);
    return 1;
}