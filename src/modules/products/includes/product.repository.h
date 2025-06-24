#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_H

#include "product.model.h"

int save_product_repository(Product product);
Product* get_product_by_id_repository(int id);
Product* get_product_by_barcode_repository(char* barcode);
Product* get_product_by_name_repository(char* name);
Product** list_products_repository(int* count);
int update_product_repository(Product product);
int delete_product_repository(int id);

#endif