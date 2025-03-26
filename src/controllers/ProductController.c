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
            (rol != 3) ? readProducts() : printf("No implementado.\n");
            break;
        case 3:
            (rol != 3) ? updateProduct() : printf("Opcion no valida.\n");
            break;
        case 4:
            (rol != 3) ? printf("No implementado.\n") : printf("Opcion no valida.\n");
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