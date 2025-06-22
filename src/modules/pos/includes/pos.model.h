#ifndef POS_MODEL_C
#define POS_MODEL_C

#include "../../products/includes/product.model.h"

typedef struct {
    Product* product;
    int quantity;
} CartItem;

typedef struct {
    CartItem** items;
    int count;
    float total; // Total del carrito
} Cart;

#endif