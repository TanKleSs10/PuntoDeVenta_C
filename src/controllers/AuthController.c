#include "AuthController.h"

// Implementaciones para AuthController (controller)

void login()
{
    // Crear un objeto User
    User user;
    inputLoginData(&user);

    // Validar que el usuario exista
    User *userByName = getUserByName(user.name);
    if (!userByName)
    {
        printf("Usuario no encontrado.\n");
        return;
    }

    // Validar que la contraseña sea correcta
    if (strcmp(userByName->pass, user.pass) != 0)
    {
        printf("Contraseña incorrecta.\n");
        return;
    }

    // Crear un objeto Session
    Session session;
    session.user = *userByName;
    session.CreatedAt = time(NULL);

    // Guardar la sesión en el archivo
    if (saveSession(&session))
    {
        ShowMessageCleanScreen("Sesion iniciada correctamente.", 2);
    }
}

int isLoggedIn()
{
    Session *session = getSession();
    if (!session)
    {
        printf("Sesion no iniciada.\n");
        return 0;
    }

    printf("Sesion iniciada correctamente.\n");
    free(session); // ✅ Liberamos la memoria después de verificar
    return 1;
}

void logout()
{
    removeSession();
    ShowMessageCleanScreen("Sesion cerrada correctamente.", 2);
}

void welcome()
{
    Session *session = getSession();
    ConfigPOS *config = getConfig();
    if (!session)
    {
        printf("No hay sesion activa.\n");
        return;
    }

    printf("Hola %s, bienvenido a la terminal punto de venta de %s.", session->user.name, config->bussinesName);
    free(session); // ✅ Liberamos la memoria después de usarla
    free(config);  // ✅ Liberamos la memoria después de usarla
}

void showMenu()
{
    Session *session = getSession();
    int option;

    do
    {
        printf("\n=== Menu Principal ===\n");

        // Mostrar opciones según el rol
        if (session->user.role == 1) // SuperAdmin
        {
            printf("1. Menu de Configuracion\n");
            printf("2. Menu de Usuarios\n");
            printf("3. Menu de Productos\n");
        }
        else if (session->user.role == 2) // Admin
        {
            printf("1. Menu de Usuarios\n");
            printf("2. Menu de Productos\n");
        }
        else if (session->user.role == 3) // Cajero
        {
            printf("1. Menu de Productos\n");
        }

        printf("0. Cerrar sesion\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &option);
        getchar(); // Consumir salto de línea

        switch (option)
        {
        case 1:
            if (session->user.role == 1)
            {
                // Mostrar Menu de configuración - SuperAdmin
                handleMenuConfig();
            }
            else if (session->user.role == 2)
            {
                // Mostrar Menu de administración de usuarios - Admin
                handleMenuUser();
            }
            else if (session->user.role == 3)
            {
                // Mostrar Menu de administración de productos - Cajero
                handleMenuProduct(session->user.role);
            }
            else
            {
                printf("Opcion no valida.\n");
            }
            break;

        case 2:
            if (session->user.role == 1)
            {
                // Mostrar Menu de administración de usuarios - SuperAdmin
                handleMenuUser();
            }
            else if (session->user.role == 2)
            {
                // Mostrar Menu de administración de productos - Admin
                handleMenuProduct(session->user.role);
            }
            else
            {
                printf("Opcion no vásida.\n");
            }
            break;

        case 3:
            if (session->user.role == 1)
            {
                // Mostrar Menu de administración de productos - SuperAdmin
                handleMenuProduct(session->user.role);
            }
            else
            {
                printf("Opcion no valida.\n");
            }
            break;

        case 0:
            printf("Cerrando sesion...\n");
            logout();
            return;

        default:
            printf("Opcion no valida. Intente nuevamente.\n");
        }

    } while (option != 0);
    free(session);
}