#include "includes/pos.controller.h"
#include "../../utils/logger.h"
#include "../../utils/utils.h"
#include "../configSystem/includes/config.model.h"
#include "../configSystem/includes/config.service.h"
#include "../products/includes/product.service.h"
#include "includes/pos.service.h"
#include "includes/pos.ui.h"
#include <stdbool.h> // bool, true, false
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_product_flow(Cart *cart, ConfigSystem *config) {
  char *barcode = pos_get_barcode_input_ui();

  if (!barcode) {
    show_error_ui("Error de memoria.");
    return;
  }

  if (barcode[0] == '0') {
    show_message_ui("Regresando al menú principal...");
    free(barcode);
    return; // Usuario decidió no agregar producto
  }

  if (strlen(barcode) != 13) {
    show_error_ui("Código de barras inválido.");
    free(barcode);
    add_product_flow(cart, config);
    return;
  }

  Product *product = get_product_by_barcode_service(barcode);
  if (!product) {
    show_error_ui("Producto no encontrado.");
    free(barcode);
    return;
  }
  if (show_confirm_product(product) != 1) {
    free(barcode);
    return; // Usuario decidió no agregar el producto
  }

  int quantity = get_quantity_input_ui(1);

  Breakdown breakdown;

  int result = add_product_by_barcode_service(cart, barcode, quantity, config,
                                              &breakdown);
  free(barcode);

  switch (result) {
  case 0:
    show_message_ui("Producto agregado correctamente.");
    show_cart_invoice_ui(breakdown.subtotal, breakdown.tax, breakdown.savings,
                         breakdown.total);
    break;
  case -1:
    show_error_ui("Parámetros inválidos.");
    break;
  case -2:
    show_error_ui("Producto no encontrado.");
    break;
  case -3:
  default:
    show_error_ui("Error al agregar producto al carrito.");
    break;
  }

  add_product_flow(cart, config); // Permitir agregar más productos
}

void remove_product_flow(Cart *cart, ConfigSystem *config) {
  char *barcode = pos_get_barcode_input_ui();
  if (!barcode || strlen(barcode) != 13) {
    show_error_ui("Código de barras inválido.");
    free(barcode);
    return;
  }

  int quantity = get_quantity_input_ui(0);
  Breakdown breakdown;

  int result = remove_product_by_barcode_service(cart, barcode, quantity,
                                                 config, &breakdown);

  free(barcode);

  switch (result) {
  case 0:
    show_message_ui("Producto eliminado correctamente.");
    show_cart_invoice_ui(breakdown.subtotal, breakdown.tax, breakdown.savings,
                         breakdown.total);
    break;
  case -1:
    show_error_ui("Parámetros inválidos.");
    break;
  case -2:
    show_error_ui("Producto no encontrado.");
    break;
  case -3:
  default:
    show_error_ui("Error al eliminar el producto del carrito.");
    break;
  }
}

void finalize_sale_flow(Cart *cart, ConfigSystem *config) {
  if (!cart || !cart->items || cart->count == 0) {
    printf("[DEBUG]: Carrito vacío o no inicializado.\n");
    press_enter_to_continue();
    return;
  }

  Breakdown breakdown;
  float payment = 0.0f, change = -1.0f;

  while (change < 0) {
    payment = get_payment_amount_ui(cart->total);

    int result =
        finalize_cart_sale_service(cart, config, payment, &breakdown, &change);

    switch (result) {
    case -2:
      show_error_ui("Pago insuficiente. Intente de nuevo.");
      break;
    case -1:
      show_error_ui("Error interno al procesar la venta.");
      press_enter_to_continue();
      return;
    case 0:
      generate_ticket_ui(cart, breakdown, payment, change,
                         config->bussinesName);

      LOG_INFO("Venta finalizada correctamente.");
      press_enter_to_continue(); // 👈 Esperar antes de limpiar
      free_cart_service(cart);
      return;
    default:
      show_error_ui("Error desconocido al finalizar la venta.");
      press_enter_to_continue();
      return;
    }
  }
}

void run_pos_controller() {
  LOG_INFO("Sistema POS iniciado.");

  ConfigSystem *config = get_config_service();
  Cart *cart = create_cart_service();
  int option;
  bool venta_finalizada = false;

  while (true) {
    option = show_pos_menu_ui(); // Muestra menú y obtiene opción

    switch (option) {
    case 1: // Agregar producto
      clear_screen();
      add_product_flow(cart, config);
      break;

    case 2: // Eliminar producto
      clear_screen();
      remove_product_flow(cart, config);
      break;

    case 3: // Ver carrito
      clear_screen();
      Breakdown breakdown = calculate_breakdown_service(cart, config->taxes);
      show_cart_detail_ui(cart);
      show_cart_invoice_ui(breakdown.subtotal, breakdown.tax, breakdown.savings,
                           breakdown.total);
      break;

    case 4: // Terminar venta
      clear_screen();
      finalize_sale_flow(cart, config);
      venta_finalizada = true; // ← Activamos la flag
      break;

    case 5: // Cancelar venta
      clear_screen();
      show_message_ui("Venta cancelada.");
      press_enter_to_continue(); // ← UX-friendly
      free_cart_service(cart);
      clear_screen();
      return;

    default:
      show_error_ui("Opción no válida. Intente de nuevo.");
      break;
    }

    // 💡 Si fue venta, salimos del loop
    if (venta_finalizada) {
      press_enter_to_continue(); // ← Espera antes de salir
      clear_screen();            // ← Limpia ya con seguridad
      return;
    }
  }
}
