#include "UserController.h"
#include <stdio.h>

// Implementaciones para UserController (controller)

// Función para agregar un usuario - CREATE (CRUD)
void createUser()
{
    User user;
    inputUserData(&user);

    // validar que no exista el usuario
    if (getUserByName(user.name) || getUserById(user.id))
    {
        printf("El usuario ya existe.\n");
        return;
    }

    if (saveUser(&user))
    {
        printf("Usuario agregado correctamente.\n");
    }
    else
    {
        printf("Error al agregar usuario.\n");
    }
}

// Función para mostrar usuarios - READ (CRUD)
void showUsers()
{
    User users[100];
    int size = getAllUsers(users, 100);
    showUsersData(users, size);
}

void searchUser()
{
    User *user = NULL;
    int option;
    do
    {
        showMenuSearchUser();
        printf("Seleccione una opcion: ");
        if (scanf("%d", &option) != 1)
        {
            printf("Error: Entrada no valida. Intente nuevamente.\n");
            while (getchar() != '\n')
                ; // Limpiar buffer
            continue;
        }
        switch (option)
        {
        case 1:
            int id;
            printf("ingresa el ID del usuario: ");
            if (scanf("%d", &id) != 1)
            {
                printf("Error: ID no valido.\n");
                while (getchar() != '\n')
                    ; // Limpiar buffer
                break;
            }
            user = getUserById(id);
            if (!user)
            {
                printf("Usuario no encontrado.\n");
            }
            else
            {
                showUser(user);
            }
            break;
        case 2:
            char name[50];
            printf("ingresa el ID del usuario: ");
            scanf("%49s", name); // Limitar a 49 caracteres
            user = getUserByName(name);
            if (!user)
            {
                printf("Usuario no encontrado.\n");
            }
            else
            {
                showUser(user);
            }
            break;
        default:
            break;
        }
    } while (option != 0);
}

void updateUser()
{
    int id;
    char name[50];

    switch (inputSelectSearchUserData())
    {
    case 1:
        id = inputSearchUserDataByid();
        User *userById = getUserById(id);
        if (userById)
        {
            printf("\n--- Modificando usuario (ID: %d) ---\n", userById->id);

            // Solicitar nuevos datos (sin ID)
            inputUserDataForUpdate(userById);

            // Actualizar la fecha de modificación
            userById->updated_at = time(NULL);

            // Intentar actualizar el usuario en el archivo
            if (modifyUser(userById->id, userById))
            {
                printf("Usuario actualizado correctamente.\n");
            }
            else
            {
                printf("Error: No se pudo actualizar el usuario.\n");
            }

            // Liberar la memoria asignada en getUserById
            free(userById);
        }
        else
        {
            printf("Error: Usuario no encontrado.\n");
        }
        break;

    case 2:
        inputSearchUserDataByName(name);
        User *userByName = getUserByName(name);
        if (userByName)
        {
            printf("\n--- Modificando usuario (Nombre: %s) ---\n", userByName->name);

            // Solicitar nuevos datos (sin ID)
            inputUserDataForUpdate(userByName);

            // Actualizar la fecha de modificación
            userByName->updated_at = time(NULL);

            // Intentar actualizar el usuario en el archivo
            if (modifyUser(userByName->id, userByName))
            {
                printf("Usuario actualizado correctamente.\n");
            }
            else
            {
                printf("Error: No se pudo actualizar el usuario.\n");
            }

            // Liberar la memoria asignada en getUserByName
            free(userByName);
        }
        else
        {
            printf("Error: Usuario no encontrado.\n");
        }
        break;

    default:
        printf("Opcion invalida.\n");
        break;
    }
}

void deleteUser()
{
    if (removeUser(inputSearchUserDataByid()))
    {
        printf("Usuario eliminado correctamente.\n");
    }
    else
    {
        printf("Error al eliminar usuario.\n");
    }
}

void handleMenuUser()
{
    int option;
    do
    {
        showMenuUser();
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            createUser();
            break;
        case 2:
            showUsers();
            break;
        case 3:
            searchUser();
            break;
        case 4:
            updateUser();
            break;
        case 5:
            deleteUser();
            break;
        case 0:
            printf("Regresando al menu principal...\n");
            break;
        default:
            printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while (option != 0);
}