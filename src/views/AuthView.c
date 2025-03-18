
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