#include "ProductView.h"

void showProduct(Product p)
{
    printf("\nProducto ID: %d\n", p.id);
    printf("Nombre: %s\n", p.name);
    printf("Descripcion: %s\n", p.desc);
    printf("Código de Barras: ");
    for (int i = 0; i < 13; i++)
    {
        printf("%d", p.bar_code[i]); // Mostrar el código de barras como números
    }
    printf("\nPrecio: %.2f\n", p.price);
    printf("--------------------------\n");
}

void inputProductData(Product *p)
{
    printf("\nAgregar nuevo producto\n");

    // Validación del ID
    do
    {
        printf("ID: ");
        scanf("%d", &p->id);
        if (p->id <= 0)
        {
            printf("Error: El ID debe ser un numero positivo.\n");
        }
    } while (p->id <= 0);

    // Validación del nombre
    do
    {
        printf("Nombre: ");
        scanf(" %49[^\n]", p->name);
        if (strlen(p->name) == 0)
        {
            printf("Error: El nombre no puede estar vacio.\n");
        }
    } while (strlen(p->name) == 0);

    // Validación de la descripción
    do
    {
        printf("Descripcion: ");
        scanf(" %99[^\n]", p->desc);
        if (strlen(p->desc) == 0)
        {
            printf("Error: La descripcion no puede estar vacia.\n");
        }
    } while (strlen(p->desc) == 0);

    // Validación del código de barras
    do
    {
        printf("Codigo de Barras (13 dígitos): ");
        for (int i = 0; i < 13; i++)
        {
            scanf("%1d", &p->bar_code[i]); // Leer cada dígito del código de barras
        }
        if (p->bar_code[0] == 0) // Validar que el código no esté vacío
        {
            printf("Error: El codigo de barras no puede estar vacio.\n");
        }
    } while (p->bar_code[0] == 0);

    // Validación del precio
    do
    {
        printf("Precio: ");
        scanf("%f", &p->price);
        if (p->price <= 0)
        {
            printf("Error: El precio debe ser un numero positivo.\n");
        }
    } while (p->price <= 0);
}

void inputUpdateProductData(Product *p)
{
    // Validación del nombre
    do
    {
        printf("Nuevo Nombre: ");
        scanf(" %49[^\n]", p->name);
        if (strlen(p->name) == 0)
        {
            printf("Error: El nombre no puede estar vacio.\n");
        }
    } while (strlen(p->name) == 0);

    // Validación de la descripción
    do
    {
        printf("Nueva Descripcion: ");
        scanf(" %99[^\n]", p->desc);
        if (strlen(p->desc) == 0)
        {
            printf("Error: La descripcion no puede estar vacia.\n");
        }
    } while (strlen(p->desc) == 0);

    // Validación del código de barras
    do
    {
        printf("Nuevo Codigo de Barras (13 dígitos): ");
        for (int i = 0; i < 13; i++)
        {
            scanf("%1d", &p->bar_code[i]); // Leer cada dígito del código de barras
        }
        if (p->bar_code[0] == 0) // Validar que el código no esté vacío
        {
            printf("Error: El codigo de barras no puede estar vacio.\n");
        }
    } while (p->bar_code[0] == 0);

    // Validación del precio
    do
    {
        printf("Nuevo Precio: ");
        scanf("%f", &p->price);
        if (p->price <= 0)
        {
            printf("Error: El precio debe ser un numero positivo.\n");
        }
    } while (p->price <= 0);
}

void inputSearchProductUpdateData(int *id, const char *action)
{
    printf("\n%s producto\n", action);
    do
    {
        printf("Ingrese el ID del producto a %s: ", action);
        scanf("%d", id);
        if (*id <= 0)
        {
            printf("Error: El ID debe ser un numero positivo.\n");
        }
    } while (*id <= 0);
}

void showAllProducts(Product products[], int count)
{
    if (count == 0)
    {
        printf("No hay productos registrados.\n");
        return;
    }

    printf("\nLista de Productos:\n");
    for (int i = 0; i < count; i++)
    {
        showProduct(products[i]);
    }
}