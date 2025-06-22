#ifndef POS_CONTROLLER_H
#define POS_CONTROLLER_H

#include "pos.model.h"
#include "pos.service.h"
#include "../../products/includes/product.model.h"
#include "../../configSystem/includes/config.model.h"

void remove_product_flow(Cart* cart, ConfigSystem* config);
void finalize_sale_flow(Cart* cart, ConfigSystem* config);
void run_pos_controller();

#endif
