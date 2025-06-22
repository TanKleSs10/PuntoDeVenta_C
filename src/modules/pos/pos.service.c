#include "includes/pos.service.h"
#include "../../utils/logger.h"
#include "includes/pos.repository.h"
#include <stdlib.h>

Cart *create_cart_service() { return create_cart_repository(); }

void clear_cart_service(Cart *cart) { clear_cart_repository(cart); }

void free_cart_service(Cart *cart) {
  if (!cart)
    return;
  clear_cart_service(cart);
  free(cart);
}

int add_product_to_cart_service(Cart *cart, Product *product, int quantity) {
  if (!cart || !product || quantity <= 0) {
    LOG_ERROR("Parámetros inválidos en add_product_to_cart_service.");
    return -1;
  }
  return add_product_to_cart_repository(cart, product, quantity);
}

int remove_product_from_cart_service(Cart *cart, int product_id, int quantity) {
  if (!cart || quantity <= 0) {
    LOG_ERROR("Parámetros inválidos en remove_product_from_cart_service.");
    return -1;
  }
  return remove_product_from_cart_repository(cart, product_id, quantity);
}

CartItem *find_product_in_cart_service(Cart *cart, int product_id) {
  if (!cart) {
    LOG_ERROR("Parámetros inválidos en find_product_in_cart_service.");
    return NULL;
  }
  return find_product_in_cart_repository(cart, product_id);
}

Breakdown calculate_breakdown_service(Cart *cart, float tax_rate) {
  Breakdown breakdown = {0};

  if (!cart) {
    LOG_ERROR("Carrito inválido en calculate_breakdown_service.");
    return breakdown;
  }

  for (int i = 0; i < cart->count; i++) {
    CartItem *item = cart->items[i];
    Product *product = item->product;
    int quantity = item->quantity;
    float item_subtotal = 0.0f;
    float item_savings = 0.0f;

    switch (product->promo_type) {
    case PROMO_NONE:
      item_subtotal = product->price * quantity;
      break;

    case PROMO_2X1:
      item_subtotal = product->price * ((quantity / 2) + (quantity % 2));
      item_savings = product->price * (quantity / 2);
      break;

    case PROMO_3X2:
      item_subtotal = product->price * ((2 * (quantity / 3)) + (quantity % 3));
      item_savings = product->price * (quantity / 3);
      break;

    case PROMO_NO_TAX:
      item_subtotal = product->price * quantity;
      // IVA no se suma para este producto
      breakdown.tax -= (product->price * quantity) * tax_rate;
      break;

    case PROMO_FIXED_DISCOUNT:
      item_subtotal = (product->price - product->promo_value) * quantity;
      item_savings = product->promo_value * quantity;
      break;
    }

    breakdown.subtotal += item_subtotal;
    breakdown.savings += item_savings;
  }

  // Calculamos el impuesto de lo normal:
  breakdown.tax += ((breakdown.subtotal) * tax_rate) / 100.0f;
  ;

  // Total final:
  breakdown.total = breakdown.subtotal + breakdown.tax;
  return breakdown;
}

float calculate_change_service(float amount_paid, float total_to_pay) {
  if (amount_paid < total_to_pay) {
    LOG_ERROR("Pago insuficiente en calculate_change_service.");
    return -1.0f;
  }
  return amount_paid - total_to_pay;
}

int remove_product_by_barcode_service(Cart *cart, char *barcode, int quantity,
                                      ConfigSystem *config,
                                      Breakdown *out_breakdown) {
  if (!cart || !barcode || quantity <= 0 || !config || !out_breakdown) {
    LOG_ERROR("Parámetros inválidos en remove_product_by_barcode_service.");
    return -1;
  }

  Product *product = get_product_by_barcode_service(barcode);
  if (!product) {
    LOG_WARNING("Producto no encontrado en remove_product_by_barcode_service.");
    return -2;
  }

  int result = remove_product_from_cart_service(cart, product->id, quantity);
  if (result != 0) {
    LOG_ERROR("No se pudo eliminar el producto del carrito.");
    return -3;
  }

  *out_breakdown = calculate_breakdown_service(cart, config->taxes);
  return 0;
}

int finalize_cart_sale_service(Cart *cart, ConfigSystem *config, float payment,
                               Breakdown *out_breakdown, float *out_change) {
  if (!cart || !config || !out_breakdown || !out_change)
    return -1;

  *out_breakdown = calculate_breakdown_service(cart, config->taxes);
  if (payment < out_breakdown->total) {
    return -2; // Pago insuficiente
  }

  *out_change = payment - out_breakdown->total;

  // Aquí continuar con guardar venta, limpiar carrito, etc.

  return 0; // OK
}

int add_product_by_barcode_service(Cart *cart, char *barcode, int quantity,
                                   ConfigSystem *config,
                                   Breakdown *out_breakdown) {
  if (!cart || !barcode || quantity <= 0 || !config || !out_breakdown) {
    LOG_ERROR("Parámetros inválidos en add_product_by_barcode_service.");
    return -1;
  }

  Product *product = get_product_by_barcode_service(barcode);
  if (!product) {
    LOG_WARNING("Producto no encontrado en add_product_by_barcode_service.");
    return -2;
  }

  int result = add_product_to_cart_service(cart, product, quantity);
  if (result != 0) {
    LOG_ERROR("No se pudo agregar el producto al carrito.");
    return -3;
  }

  *out_breakdown = calculate_breakdown_service(cart, config->taxes);
  cart->total = out_breakdown->total;

  return 0;
}
