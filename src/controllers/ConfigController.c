#include "ConfigController.h"
#include <stdio.h>
#include <string.h>

// Configurar el sistema
void configSystem()
{
    ConfigPOS config;
    User superUser;

    // Obtener datos de configuración y superusuario desde las vistas
    inputConfigData(&config);
    inputSuperUserData(&superUser);

    // Asignar el nombre del superusuario como administrador en la configuración
    strncpy(config.admin, superUser.name, sizeof(config.admin) - 1);
    config.admin[sizeof(config.admin) - 1] = '\0'; // Asegurar terminación nula

    // Guardar configuración y superusuario en archivos
    if (!saveConfig(&config))
    {
        printf("Error al guardar la configuracion.\n");
        return;
    }

    if (!saveUser(&superUser))
    {
        printf("Error al guardar el superusuario.\n");
        return;
    }

    ShowMessageCleanScreen("Configuracion guardada exitosamente.", 2);
}

// Mostrar la configuración actual
void showConfig()
{
    ConfigPOS config;
    if (readConfig(&config))
    {
        showConfigData(&config); // Mostrar datos de configuración
    }
    else
    {
        showNoConfigMessage(); // Mostrar mensaje si no hay configuración
    }
}

// Eliminar la configuración
void deleteConfig()
{
    if (!confirmDeleteConfig())
    {
        printf("Operacion cancelada.\n");
        return;
    }

    if (removeFileConfig() && removeFileUsers())
    {
        printf("Configuracion eliminada correctamente.\n");
    }
    else
    {
        printf("Error al eliminar la configuracion.\n");
    }
}

// Validar si el sistema está configurado
void validateConfig()
{
    ConfigPOS config;
    if (readConfig(&config))
    {
        ShowMessageCleanScreen("Sistema configurado. Iniciando menu...", 2);
    }
    else
    {
        ShowMessageCleanScreen("El sistema NO esta configurado. Iniciando configuracion...", 2);
        configSystem();
    }
}

// Actualizar la configuración
void updateConfig()
{
    ConfigPOS newConfig;
    User currentAdmin;

    // Cargar configuración actual
    if (!readConfig(&newConfig))
    {
        showNoConfigMessage();
        return;
    }

    // Obtener datos actualizados desde las vistas
    inputConfigData(&newConfig);
    inputSuperUserData(&currentAdmin);

    // Actualizar el nombre del administrador en la configuración
    strncpy(newConfig.admin, currentAdmin.name, sizeof(newConfig.admin) - 1);
    newConfig.admin[sizeof(newConfig.admin) - 1] = '\0'; // Asegurar terminación nula

    // Validar coherencia de datos
    if (strcmp(newConfig.admin, currentAdmin.name) != 0)
    {
        printf("Error: El nombre del administrador no coincide.\n");
        return;
    }

    // Persistir cambios
    int configSaved = saveConfig(&newConfig);
    int userUpdated = modifyUser(currentAdmin.id, &currentAdmin);

    // Feedback al usuario
    if (configSaved && userUpdated)
    {
        printf("Configuracion y usuario admin actualizados correctamente.\n");
    }
    else
    {
        printf("Error al guardar cambios. Verifique los archivos.\n");
    }
}

void handleMenuConfig()
{
    int option;
    do
    {
        showMenuConfig();
        scanf("%d", &option);
        getchar(); // Consumir salto de línea

        switch (option)
        {
        case 1:
            updateConfig();
            break;
        case 2:
            showConfig();
            break;
        case 3:
            deleteConfig();
            break;
        default:
            printf("Opcion no valida");
            break;
        }
    } while (option != 0);
}