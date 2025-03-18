#include "ProductModel.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

int saveProduct(const Product *product)
{
    FILE *file = openFile(PRODUCTS_FILE, "ab", "Error al abrir el archivo de productos");
    if (!file)
        return 0;

    int result = fwrite(product, sizeof(Product), 1, file) == 1;
    fclose(file);
    return result;
}

int getAllProducts(Product *products, int maxSize)
{
    FILE *file = openFile(PRODUCTS_FILE, "rb", "Error al abrir el archivo de productos");
    if (!file)
        return 0;

    int count = fread(products, sizeof(Product), maxSize, file);
    fclose(file);
    return count;
}

Product *getProductById(int id)
{
    FILE *file = openFile(PRODUCTS_FILE, "rb", "Error al abrir el archivo de productos");
    if (!file)
        return NULL;

    Product *product = malloc(sizeof(Product));
    if (!product)
    {
        fclose(file);
        return NULL;
    }

    while (fread(product, sizeof(Product), 1, file))
    {
        if (product->id == id)
        {
            fclose(file);
            return product;
        }
    }

    fclose(file);
    free(product);
    return NULL;
}

Product *getProductByName(const char *name)
{
    FILE *file = openFile(PRODUCTS_FILE, "rb", "Error al abrir el archivo de productos");
    if (!file)
        return NULL;

    Product *product = malloc(sizeof(Product));
    if (!product)
    {
        fclose(file);
        return NULL;
    }

    while (fread(product, sizeof(Product), 1, file))
    {
        if (strcmp(product->name, name) == 0)
        {
            fclose(file);
            return product;
        }
    }

    fclose(file);
    free(product);
    return NULL;
}

Product *getProductByBarCode(const int *barCode)
{
    FILE *file = openFile(PRODUCTS_FILE, "rb", "Error al abrir el archivo de productos");
    if (!file)
        return NULL;

    Product *product = malloc(sizeof(Product));
    if (!product)
    {
        fclose(file);
        return NULL;
    }

    while (fread(product, sizeof(Product), 1, file))
    {
        if (memcmp(product->bar_code, barCode, sizeof(product->bar_code)) == 0)
        {
            fclose(file);
            return product;
        }
    }

    fclose(file);
    free(product);
    return NULL;
}

int modifyProduct(int id, const Product *newProduct)
{
    FILE *file = openFile(PRODUCTS_FILE, "rb+", "Error al abrir el archivo de productos");
    if (!file)
        return 0;

    Product product;
    while (fread(&product, sizeof(Product), 1, file))
    {
        if (product.id == id)
        {
            // Convertir sizeof(Product) a long int antes de aplicar el negativo
            fseek(file, -(long int)sizeof(Product), SEEK_CUR);

            Product updatedProduct = *newProduct;
            int result = fwrite(&updatedProduct, sizeof(Product), 1, file) == 1;
            fclose(file);
            return result;
        }
    }

    fclose(file);
    return 0;
}

int removeProduct(int id)
{
    FILE *file = openFile(PRODUCTS_FILE, "rb", "Error al abrir el archivo de productos");
    FILE *tempFile = openFile(TEMP_FILE, "wb", "Error al abrir el archivo temporal");
    if (!file || !tempFile)
        return 0;

    Product product;
    int deleted = 0;

    while (fread(&product, sizeof(Product), 1, file))
    {
        if (product.id != id)
        {
            fwrite(&product, sizeof(Product), 1, tempFile);
        }
        else
        {
            deleted = 1;
        }
    }

    fclose(file);
    fclose(tempFile);
    return deleted ? replaceFile(PRODUCTS_FILE, TEMP_FILE) : 0;
}

int removeFileProducts()
{
    if (!openFile(PRODUCTS_FILE, "rb", "Error al abrir el archivo de productos"))
        return 0;

    remove(PRODUCTS_FILE);
    return 1;
}