#include "ProductView.h"

void showProduct(Product *p)
{
    printf("\nProducto ID: %d\n", p->id);
    printf("Nombre: %s\n", p->name);
    printf("Descripcion: %s\n", p->desc);
    printf("Codigo de Barras: ");
    for (int i = 0; i < 13; i++)
    {
        printf("%d", p->bar_code[i]);
    }
    printf("\nPrecio: %.2f\n", p->price);
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
        scanf(" %49[^\n]", p->name); // Lee el nombre sin problemas
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
    char temp[14];
    do
    {
        printf("Codigo de Barras (13 digitos): ");
        scanf("%13s", temp);

        if (strlen(temp) != 13)
        {
            printf("Error: El codigo de barras debe tener exactamente 13 digitos.\n");
            continue;
        }

        int valid = 1;
        for (int i = 0; i < 13; i++)
        {
            if (!isdigit(temp[i]))
            {
                valid = 0;
                break;
            }
            p->bar_code[i] = temp[i] - '0';
        }

        if (!valid)
        {
            printf("Error: El codigo de barras debe contener solo numeros.\n");
        }
    } while (strlen(temp) != 13);

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
        printf("Nuevo Codigo de Barras (13 digitos): ");
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

// Muestra todos los productos
void showAllProducts(Product *products, int count)
{
    if (count <= 0)
    {
        printf("No hay productos registrados.\n");
        return;
    }

    printf("\nLista de Productos:\n");
    for (int i = 0; i < count; i++)
    {
        showProduct(&products[i]); // Suponiendo que showProduct recibe un puntero
    }
}

void showMenuProduct()
{
    printf("\nOpciones de productos:\n");
    printf("1. Agregar producto\n");
    printf("2. Listar productos\n");
    printf("3. Modificar producto\n");
    printf("4. Buscar producto\n");
    printf("5. Eliminar producto\n");
    printf("0. Salir\n");
}

void showMenuCashierProduct()
{
    printf("\nOpciones de productos:\n");
    printf("1. Listar productos\n");
    printf("2. Buscar producto\n");
    printf("0. Salir\n");
}

void showMenuSearchProduct()
{
    printf("\nOpciones de busqueda de productos:\n");
    printf("1. Buscar producto por ID\n");
    printf("2. Buscar producto por nombre\n");
    printf("3. Buscar producto por codigo de barras\n");
    printf("Salir\n");
}