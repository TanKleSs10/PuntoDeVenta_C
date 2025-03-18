#ifndef PRODUCTVIEW_H
#define PRODUCTVIEW_H

#include "ProductModel.h"
#include <stdio.h>
#include <string.h>

// Declaraciones para ProductView (view)

void showProduct(Product p);
void inputProductData(Product *p);
void inputUpdateProductData(Product *p);
void inputSearchProductUpdateData(int *id, const char *action);
void showAllProducts(Product products[], int count);

#endif
