#include "ConfigView.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Implementaciones para ConfigView (view)
void inputConfigData(ConfigPOS *c)
{
    printf("\n--- Configuracion del sistema ---\n");
    do
    {
        printf("Ingresa el nombre de la empresa: ");
        scanf(" %49[^\n]", c->bussinesName);
        if (strlen(c->bussinesName) == 0)
        {
            printf("El nombre no puede estar vacio.\n");
        }
    } while (strlen(c->bussinesName) == 0);

    do
    {
        printf("Ingresa el porcentaje de impuestos (ej. 16.0 para 16%%): ");
        scanf("%f", &c->taxes);
        if (c->taxes <= 0)
        {
            printf("El Impuesto debe ser un numero positivo mayor a 0.\n");
        }
    } while (c->taxes <= 0);

    do
    {
        printf("Ingresa el tipo de moneda (MXN o USD): ");
        scanf(" %9s", c->currency);
        for (int i = 0; c->currency[i]; i++)
        {
            c->currency[i] = toupper(c->currency[i]);
        }
    } while (strcmp(c->currency, "MXN") != 0 &&
             strcmp(c->currency, "USD") != 0);
}

void showConfigData(const ConfigPOS *c)
{
    printf("\n--- Configuracion del sistema ---\n");
    printf("Nombre de la empresa: %s\n", c->bussinesName);
    printf("Impuestos(IVA): %.2f\n", c->taxes);
    printf("Tipo de Moneda: %s\n", c->currency);
    printf("Administrador: %s\n", c->admin);
}

void showMenuConfig() // solo superadmin
{
    printf("\nOpciones de configuracion:\n");
    printf("1. Editar configuracion del sitema\n");
    printf("2. Mostrar configuracion actual\n");
    printf("3. Eliminar configuracion\n");
    printf("0. Salir\n");
}

int confirmDeleteConfig()
{
    char option[10];
    printf("\nSe eliminaran la configuracion y los usuarios de forma permanente.\n");
    printf("Estas seguro? (si / no): \n");
    scanf(" %9s", option);

    // Convertir a minúsculas
    for (int i = 0; option[i]; i++)
    {
        option[i] = tolower(option[i]);
    }

    if (strcmp(option, "si") == 0)
    {
        return 1;
    }
    return 0;
}

void showNoConfigMessage()
{
    printf("No hay configuracion.\n");
}
