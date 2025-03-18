#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H

#include "../helpers/helpers.h"

// Declaraciones para ProductModel (model)
#define PRODUCTS_FILE "../data/products.dat"
#define TEMP_FILE "../data/temp.dat"

typedef struct
{
    int id;
    char name[50];
    char desc[100];
    int bar_code[13];
    float price;
} Product;

// Funciones CRUD (ProductModel)
int saveProduct(const Product *product);            // Guarda un producto en el archivo de productos
int getAllProducts(Product *products, int maxSize); // Obtiene todos los productos del archivo de productos
Product *getProductById(int id);
Product *getProductByName(const char *name);          // Obtiene un producto dinámico por ID
Product *getProductByBarCode(const int *barCode);     // Obtiene un producto dinámico por ID
int modifyProduct(int id, const Product *newProduct); // Actualiza un producto en el archivo de productos
int removeProduct(int id);                            // Elimina un producto del archivo de productos

#endif
