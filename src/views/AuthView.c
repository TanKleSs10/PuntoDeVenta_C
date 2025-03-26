
#include "AuthView.h"
#include <stdio.h>

// Implementaciones para AuthView (view)

void inputLoginData(User *user)
{
    printf("\nIngrese los datos para iniciar sesion\n");
    printf("Ingrese el nombre del usuario: ");
    scanf(" %49[^\n]", user->name);
    printf("Ingrese la password del usuario: ");
    scanf(" %19s", user->pass);
}

void showMenuSuperAdmin()
{
    printf("\n Menu del Superadministrator:\n");
    printf("1. Configuracion del sistema\n");
    printf("2. Administracion de usuarios\n");
    printf("3. Administracion de productos\n");
    printf("0. Salir\n");
}

void showMenuAdmin()
{
    printf("\n Menu del Administrador:\n");
    printf("1. Administracion de usuarios\n");
    printf("2. Administracion de productos\n");
    printf("0. Salir\n");
}

void showMenuCashier()
{
    printf("\n Menu del Cajero:\n");
    printf("1. Administracion de productos\n");
    printf("2. Caja registradora\n");
    printf("0. Salir\n");
}