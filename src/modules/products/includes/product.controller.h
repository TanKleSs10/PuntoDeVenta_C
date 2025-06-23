#ifndef PRODUCT_CONTROLLER_H
#define PRODUCT_CONTROLLER_H

#include "../../authentication/includes/auth.model.h"
#include "../../authorization/includes/authz.h"
#include "product.model.h"
#include "product.ui.h"

void create_product_controller();
void find_product_by_id_controller();
void find_product_by_barcode_controller();
void find_product_by_name_controller();
void list_products_controller();
void update_product_controller();
void delete_product_controller();
void menu_products_controller(Auth *session);

#endif
