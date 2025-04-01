#include "ProductController.h"
#include <stdio.h>
#include <stdlib.h>

void createProduct()
{
    Product p;
    inputProductData(&p);

    // Verificar si el producto ya existe (por ID o nombre)
    if (getProductById(p.id) || getProductByName(p.name))
    {
        printf("Error: El producto ya existe (ID o nombre duplicado).\n");
        return;
    }

    // Guardar el producto en el archivo
    if (saveProduct(&p))
    {
        printf("Producto agregado con exito.\n");
    }
    else
    {
        printf("Error al agregar el producto.\n");
    }
}

// Lee los productos desde el archivo y los muestra
void readProducts()
{
    Product products[100];
    int size = getAllProducts(products, 100);

    if (size <= 0)
    {
        printf("No hay productos registrados.\n");
        return;
    }

    showAllProducts(products, size);
}

// Función para buscar productos
void searchProduct()
{
    Product *product = NULL;
    int option;

    do
    {
        showMenuSearchProduct();
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
        {
            int id;
            printf("Ingrese el ID del producto: ");
            if (scanf("%d", &id) != 1)
            {
                printf("Error: ID no válido.\n");
                while (getchar() != '\n')
                    ; // Limpiar buffer
                break;
            }
            product = getProductById(id);
            if (!product)
            {
                printf("Producto no encontrado.\n");
            }
            else
            {
                showProduct(product);
            }
            break;
        }
        case 2:
        {
            char name[50];
            printf("Ingrese el nombre del producto: ");
            scanf("%49s", name); // Limitar a 49 caracteres
            product = getProductByName(name);
            if (!product)
            {
                printf("Producto no encontrado.\n");
            }
            else
            {
                showProduct(product);
            }
            break;
        }
        case 3:
        {
            int barCode[13];
            printf("Ingrese el codigo de barras (13 dígitos): ");

            for (int i = 0; i < 13; i++)
            {
                if (scanf("%1d", &barCode[i]) != 1)
                {
                    printf("Error: Codigo de barras no valido.\n");
                    while (getchar() != '\n')
                        ; // Limpiar buffer
                    break;
                }
            }

            product = getProductByBarCode(barCode);
            if (!product)
            {
                printf("Producto no encontrado.\n");
            }
            else
            {
                showProduct(product);
            }
            break;
        }
        case 0:
            printf("Saliendo del sistema de busqueda...\n");
            break;
        default:
            printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while (option != 0);
}

void updateProduct()
{
    int id;
    inputSearchProductUpdateData(&id, "actualizar");

    // Buscar el producto por ID
    Product *product = getProductById(id);
    if (product)
    {
        printf("\n--- Modificando producto (ID: %d) ---\n", product->id);

        // Solicitar los nuevos datos del producto
        inputUpdateProductData(product);

        // Actualizar el producto en el archivo
        if (modifyProduct(id, product))
        {
            printf("Producto actualizado con exito.\n");
        }
        else
        {
            printf("Error al actualizar el producto.\n");
        }

        // Liberar la memoria asignada en getProductById
        free(product);
    }
    else
    {
        printf("Producto no encontrado.\n");
    }
}

void deleteProduct()
{
    int id;
    inputSearchProductUpdateData(&id, "eliminar");

    // Eliminar el producto del archivo
    if (removeProduct(id))
    {
        printf("Producto eliminado con exito.\n");
    }
    else
    {
        printf("Producto no encontrado.\n");
    }
}

void handleMenuProduct(int rol)
{
    int option;
    printf("%d", rol);
    do
    {
        if (rol == 3)
        {
            showMenuCashierProduct();
        }
        else
        {
            showMenuProduct();
        }

        scanf("%d", &option);

        switch (option)
        {
        case 1:
            (rol != 3) ? createProduct() : readProducts();
            break;
        case 2:
            (rol != 3) ? readProducts() : searchProduct();
            break;
        case 3:
            (rol != 3) ? updateProduct() : printf("Opcion no valida.\n");
            break;
        case 4:
            (rol != 3) ? searchProduct() : printf("Opcion no valida.\n");
            break;
        case 5:
            (rol != 3) ? deleteProduct() : printf("Opcion no valida.\n");
            break;
        case 0:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opcion invalida.\n");
            break;
        }
    } while (option != 0);
}

// 3x2, 2x1, sin iva, si la compra llega a x cantidad se aplica descuento, ciertos productos aplicar x monto de descuento