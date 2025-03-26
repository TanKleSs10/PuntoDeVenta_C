#include "UserView.h"
#include <stdio.h>

// Implementaciones para UserView (view)

void inputSuperUserData(User *user)
{
    user->id = 1;
    user->role = 1; // Superadmin

    printf("\n--- Creacion del Superusuario ---\n");
    printf("Ingrese el nombre del Superusuario: ");
    scanf(" %49[^\n]", user->name);

    printf("Ingrese la password del Superusuario: ");
    scanf(" %19s", user->pass);
}

void inputUserData(User *user)
{
    // Validación del ID
    do
    {
        printf("Ingrese el ID del usuario: ");
        scanf("%d", &user->id);
        if (user->id <= 0)
        {
            printf("Error: El ID debe ser un numero positivo.\n");
        }
    } while (user->id <= 0);

    // Validación del nombre
    do
    {
        printf("Ingrese el nombre del usuario: ");
        scanf(" %49[^\n]", user->name);
        if (strlen(user->name) == 0)
        {
            printf("Error: El nombre no puede estar vacio.\n");
        }
    } while (strlen(user->name) == 0);

    // Validación del rol
    do
    {
        printf("Ingrese el rol del usuario (2: Administrador, 3: Cajero): ");
        scanf("%d", &user->role);
        if (user->role != 2 && user->role != 3)
        {
            printf("Error: Rol inválido. Debe ser 2 (Administrador) o 3 (Cajero).\n");
        }
    } while (user->role != 2 && user->role != 3);

    // Validación de la contraseña
    do
    {
        printf("Ingrese la password del usuario (maximo 19 caracteres): ");
        scanf(" %19s", user->pass);
        if (strlen(user->pass) == 0)
        {
            printf("Error: La password no puede estar vacia.\n");
        }
    } while (strlen(user->pass) == 0);
}

void inputUserDataForUpdate(User *user)
{
    // Validación del nombre
    do
    {
        printf("Ingrese el nombre del usuario: ");
        scanf(" %49[^\n]", user->name);
        if (strlen(user->name) == 0)
        {
            printf("Error: El nombre no puede estar vacio.\n");
        }
    } while (strlen(user->name) == 0);

    // Validación del rol
    do
    {
        printf("Ingrese el rol del usuario (2: Administrador, 3: Cajero): ");
        scanf("%d", &user->role);
        if (user->role != 2 && user->role != 3)
        {
            printf("Error: Rol invalido. Debe ser 2 (Administrador) o 3 (Cajero).\n");
        }
    } while (user->role != 2 && user->role != 3);

    // Validación de la contraseña
    do
    {
        printf("Ingrese la password del usuario (maximo 19 caracteres): ");
        scanf(" %19s", user->pass);
        if (strlen(user->pass) == 0)
        {
            printf("Error: La password no puede estar vacia.\n");
        }
    } while (strlen(user->pass) == 0);
}

void showUserData(const User *users, int size)
{
    if (size == 0)
    {
        printf("No hay usuarios registrados.\n");
        return;
    }

    printf("\n--- Lista de Usuarios ---\n");
    for (int i = 0; i < size; i++)
    {
        printf("ID: %d | Nombre del usuario: %s | Rol: %d\n | Password: %s\n",
               users[i].id, users[i].name, users[i].role, users[i].pass);
    }
}

int inputSearchUserDataByid()
{
    int id;
    printf("Ingrese el ID del usuario a buscar: ");
    scanf("%d", &id);
    return id; // Devuelve el ID ingresado
}

char *inputSearchUserDataByName()
{
    static char name[50]; // Variable estática para conservar el valor después de la función
    printf("Ingrese el nombre del usuario a buscar: ");
    scanf(" %49[^\n]", name);
    return name; // Devuelve el nombre ingresado
}

int inputSelectSearchUserData()
{
    printf("\n--- Seleccione una opcion ---\n");
    printf("1. Buscar usuario por ID\n");
    printf("2. Buscar usuario por nombre\n");
    printf("3. Salir\n");

    int option;
    scanf("%d", &option);
    getchar();

    return option;
}

void showNoUserMessage()
{
    printf("No hay usuarios registrados.\n");
}

// menu para superusuario y admin
void showMenuUser()
{
    printf("\n--- Menu del Superusuario ---\n");
    printf("1. Crear usuario\n");
    printf("2. Listar usuarios\n");
    printf("3. Buscar usuario\n");
    printf("4. Modificar usuario\n");
    printf("5. Eliminar usuario\n");
    printf("0. Salir\n");
}

void showMenuSearchUser()
{
    printf("\nOpciones de busqueda de usuarios:\n");
    printf("Buscar usuario por ID\n");
    printf("Buscar usuario por nombre\n");
    printf("Salir\n");
}