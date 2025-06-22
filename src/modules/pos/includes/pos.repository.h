#ifndef POS_REPOSITORY_H
#define POS_REPOSITORY_H

#include "../../products/includes/product.model.h"
#include "../includes/pos.model.h"

Cart *create_cart_repository();
int add_product_to_cart_repository(Cart *cart, Product *product, int quantity);
int remove_product_from_cart_repository(Cart *cart, int product_id,
                                        int quantity);
void clear_cart_repository(Cart *cart);
CartItem *find_product_in_cart_repository(Cart *cart, int product_id);

#endif
