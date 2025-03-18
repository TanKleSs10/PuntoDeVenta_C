#ifndef USERMODEL_H
#define USERMODEL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../helpers/helpers.h"

// Declaraciones para UserModel (model)
#define USERS_FILE "../data/users.dat"
#define TEMP_FILE "../data/temp.dat"

typedef struct
{
    int id;
    int role; // 1: Superadmin, 2: Administrador, 3: Cajero, etc.
    char name[50];
    char pass[20]; // En un sistema real, se debería cifrar
    time_t created_at;
    time_t updated_at;
} User; // Estructura de usuario

// Funciones CRUD
int saveUser(const User *user);
int getAllUsers(User *users, int maxSize);
User *getUserById(int id);
User *getUserByName(const char *name);
int modifyUser(int id, const User *newUser);
int removeUser(int id);
int removeFileUsers();

#endif
