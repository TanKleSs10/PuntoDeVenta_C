#include "ProductController.h"
#include <stdio.h>
#include <stdlib.h>

void addProduct()
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

void showProducts()
{
    Product products[100];
    int size = getAllProducts(products, 100);

    if (size == 0)
    {
        printf("No hay productos registrados.\n");
    }
    else
    {
        showAllProducts(products, size);
    }
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