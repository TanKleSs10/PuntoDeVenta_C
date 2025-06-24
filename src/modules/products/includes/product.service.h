#ifndef PRODUCT_SERVICE_H
#define PRODUCT_SERVICE_H

#include "product.repository.h"
#include "product.model.h"

int create_product_service(Product product);
int update_product_service(Product product);
Product* find_product_by_id_service(int id);
Product* get_product_by_barcode_service(char* barcode);
Product* find_product_by_name_service(char* name);
Product** list_products_service(int* count);
int delete_product_service(int id);

#endif