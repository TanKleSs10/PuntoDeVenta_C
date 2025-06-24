#include "includes/pos.ui.h"
#include "../../utils/utils.h"
#include <stdbool.h> // bool, true, false
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *pos_get_barcode_input_ui() {
  char *barcode = (char *)malloc(14 * sizeof(char));
  if (!barcode) {
    show_error_ui("Error de memoria.");
    return NULL;
  }

  printf("Ingrese el código de barras del producto (13 caracteres o '0' para "
         "terminar): ");
  scanf("%13s", barcode);

  return barcode;
}

int get_quantity_input_ui(int isAdd) {
  int quantity = 0;
  if (isAdd) {
    printf("Ingrese la cantidad a agregar: ");
  } else {
    printf("Ingrese la cantidad a eliminar: ");
  }
  scanf("%d", &quantity);
  while (getchar() != '\n')
    ; // Limpiar el buffer de entrada
  if (quantity <= 0) {
    show_error_ui("Cantidad inválida. Debe ser mayor que 0.");
    return -1; // Indicar error
  }

  if (quantity > 100) {
    show_error_ui("Cantidad demasiado alta. Por favor, ingrese un valor menor "
                  "o igual a 100.");
    return -1; // Indicar error
  }

  return quantity;
}

void show_cart_summary_ui(Cart *cart) {
  if (!cart || cart->count == 0) {
    printf("\nCarrito vacío.\n");
    return;
  }

  printf("\n--- RESUMEN DEL CARRITO ---\n");
  for (int i = 0; i < cart->count; i++) {
    CartItem *item = cart->items[i];
    printf("Producto: %s | Cantidad: %d | Precio Unitario: %.2f\n",
           item->product->name, item->quantity, item->product->price);
  }
}

void show_message_ui(const char *message) { printf("\n%s\n", message); }

void show_error_ui(const char *error_message) {
  printf("\n[ERROR]: %s\n", error_message);
}

float get_payment_amount_ui(float total) {
  float payment;
  printf("\nTotal a pagar: %.2f\n", total);
  printf("Ingrese el monto con el que va a pagar: ");
  scanf("%f", &payment);
  return payment;
}

int show_confirm_product(Product *product) {
  printf("\nEstas agreando el producto:\n");
  printf("%s\nprecio: %.2f\nPromoción: %s\n", product->name, product->price,
         promo_type_to_string(product->promo_type));
  if (product->promo_type != PROMO_NONE) {
    printf("Valor de promoción: %.2f\n", product->promo_value);
  }
  printf("¿Desea agregar este producto al carrito? (s/n): ");
  char confirm;
  while (true) {
    scanf(" %c", &confirm);
    if (confirm == 's' || confirm == 'S') {
      printf("Agregando producto al carrito.\n");
      break;
    } else if (confirm == 'n' || confirm == 'N') {
      printf("Producto no agregado al carrito.\n");
      break;
    } else {
      printf(
          "Entrada inválida. Por favor, ingrese 's' para sí o 'n' para no: ");
    }
  }
  return (confirm == 's' || confirm == 'S') ? 1 : 0;
}

void show_change_ui(float change) {
  printf("\nCambio a entregar: $%.2f\n", change);
}

void show_cart_invoice_ui(float subtotal, float tax, float savings,
                          float total) {
  printf("\nSubtotal: %.2f | IVA: %.2f | Ahorros: %.2f | Total: %.2f\n",
         subtotal, tax, savings, total);
}

int show_pos_menu_ui() {
  printf("\n=== MENÚ DE VENTA ===\n");
  printf("1. Agregar producto\n");
  printf("2. Eliminar producto\n");
  printf("3. Ver carrito\n");
  printf("4. Terminar venta\n");
  printf("5. Cancelar venta\n");
  printf("Seleccione una opción: ");

  int option;
  char input[MAX_INPUT];

  get_line_input(input, MAX_INPUT);
  if (sscanf(input, "%d", &option) != 1) {
    option = -1;
  }

  return option;
}

void show_cart_detail_ui(Cart *cart) {
  printf("\n--- Carrito ---\n");
  for (int i = 0; i < cart->count; i++) {
    CartItem *item = cart->items[i];
    printf("%s x%d - $%.2f\n", item->product->name, item->quantity,
           item->product->price * item->quantity);
  }
}

void generate_ticket_ui(Cart *cart, Breakdown breakdown, float payment,
                        float change, char *nameBusiness) {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);

  printf("\n========================================\n");
  printf("          %s - Punto de Venta\n", nameBusiness);
  printf("         Ticket de compra - %02d/%02d/%d %02d:%02d\n", t->tm_mday,
         t->tm_mon + 1, t->tm_year + 1900, t->tm_hour, t->tm_min);
  printf("========================================\n");

  printf("Producto                Cant  P.U.    Total\n");
  printf("----------------------------------------\n");

  for (int i = 0; i < cart->count; i++) {
    CartItem *item = cart->items[i];
    Product *product = item->product;

    printf("%-22s %3d  $%.2f  $%.2f\n", product->name, item->quantity,
           product->price, product->price * item->quantity);
  }

  printf("----------------------------------------\n");
  printf("Subtotal:                   $%.2f\n", breakdown.subtotal);
  printf("IVA (%.0f%%):                $%.2f\n",
         breakdown.tax / breakdown.subtotal * 100, breakdown.tax);
  if (breakdown.savings > 0.0f) {
    printf("Ahorros:                   -$%.2f\n", breakdown.savings);
  }
  printf("TOTAL A PAGAR:             $%.2f\n", breakdown.total);
  printf("Pago con:                  $%.2f\n", payment);
  printf("Cambio:                    $%.2f\n", change);
  printf("========================================\n");
  printf("        ¡Gracias por su compra!\n");
  printf("        ¡Vuelva pronto!\n");
  printf("========================================\n");
}
