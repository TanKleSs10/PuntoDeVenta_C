#ifndef PRODUCTCONTROLLER_H
#define PRODUCTCONTROLLER_H

#include <stdio.h>
#include "../helpers/helpers.h"
#include "../models/ProductModel.h"
#include "../views/ProductView.h"
// Declaraciones para ProductController (controller)

void createProduct();
void readProducts();
void updateProduct();
void deleteProduct();
void handleMenuProduct(int rol);
#endif
