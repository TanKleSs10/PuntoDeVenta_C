#ifndef PRODUCT_UI_H
#define PRODUCT_UI_H

#include "product.model.h"

void create_product_ui(Product* product);
void update_product_ui(Product* product);
void find_product_by_id_ui(Product* product);
void get_barcode_input_ui(Product* product);
void find_product_by_name_ui(Product* product);
void delete_product_ui(Product* product);
void menu_products_ui();
void show_product_ui(Product* product);
void list_products_ui(Product* products[], int count);

#endif