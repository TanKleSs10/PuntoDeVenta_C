#ifndef POS_SERVICE_H
#define POS_SERVICE_H

#include "../../configSystem/includes/config.model.h"
#include "../../products/includes/product.service.h"
#include "pos.model.h"

// Estructura para desglose de compra
typedef struct {
  float subtotal; // Monto sin IVA
  float tax;      // IVA
  float savings;  // Ahorro por promociones
  float total;    // Total a pagar
} Breakdown;

// Agregar producto al carrito
Cart *create_cart_service();
void clear_cart_service(Cart *cart);
void free_cart_service(Cart *cart);
int add_product_to_cart_service(Cart *cart, Product *product, int quantity);
int remove_product_from_cart_service(Cart *cart, int product_id, int quantity);
CartItem *find_product_in_cart_service(Cart *cart, int product_id);
Breakdown calculate_breakdown_service(Cart *cart,
                                      float tax_rate); // 🛠️ actualizado
float calculate_change_service(float amount_paid, float total_to_pay);

int remove_product_by_barcode_service(Cart *cart, char *barcode, int quantity,
                                      ConfigSystem *config,
                                      Breakdown *out_breakdown);
int finalize_cart_sale_service(Cart *cart, ConfigSystem *config, float payment,
                               Breakdown *out_breakdown, float *out_change);
int add_product_by_barcode_service(Cart *cart, char *barcode, int quantity,
                                   ConfigSystem *config,
                                   Breakdown *out_breakdown);

#endif
