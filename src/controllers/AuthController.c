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
