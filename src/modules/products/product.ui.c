#include "includes/product.ui.h"
#include "../../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT 256 // Aumentar el tamaño para descripciones más largas

void create_product_ui(Product *product) {
  char input[MAX_INPUT];
  bool valid_input;

  // Solicitar ID
  do {
    printf("Ingrese el ID del producto: ");
    get_line_input(input, MAX_INPUT);
    valid_input = (sscanf(input, "%d", &product->id) == 1);
    if (!valid_input) {
      printf("El ID debe ser un número entero válido.\n");
    }
  } while (!valid_input);

  // Solicitar barcode
  do {
    printf("Ingrese el barcode del producto (13 caracteres): ");
    get_line_input(product->barcode, sizeof(product->barcode));
    valid_input = (strlen(product->barcode) == 13);
    if (!valid_input) {
      printf("El barcode debe tener exactamente 13 caracteres.\n");
    }
  } while (!valid_input);

  // Solicitar nombre
  do {
    printf("Ingrese el nombre del producto (min. 3 caracteres): ");
    get_line_input(product->name, sizeof(product->name));
    valid_input = (strlen(product->name) >= 3 &&
                   strlen(product->name) < sizeof(product->name));
    if (!valid_input) {
      printf("El nombre debe tener al menos 3 caracteres y no exceder %zu.\n",
             sizeof(product->name) - 1);
    }
  } while (!valid_input);

  // Solicitar descripción
  do {
    printf("Ingrese la descripción del producto (min. 10 caracteres): ");
    get_line_input(product->description, sizeof(product->description));
    valid_input = (strlen(product->description) >= 10 &&
                   strlen(product->description) < sizeof(product->description));
    if (!valid_input) {
      printf("La descripción debe tener al menos 10 caracteres y no exceder "
             "%zu.\n",
             sizeof(product->description) - 1);
    }
  } while (!valid_input);

  // Solicitar precio
  do {
    printf("Ingrese el precio del producto: ");
    get_line_input(input, MAX_INPUT);
    valid_input = (sscanf(input, "%f", &product->price) == 1);
    if (!valid_input) {
      printf("El precio debe ser un número válido.\n");
    }
  } while (!valid_input);

  // Solicitar tipo de promoción
  do {
    printf("Ingrese el tipo de promoción (0: ninguna, 1: 2x1, 2: 3x2, 3: sin "
           "impuesto, 4: descuento fijo): ");
    get_line_input(input, MAX_INPUT);
    valid_input = (sscanf(input, "%d", (int *)&product->promo_type) == 1 &&
                   product->promo_type >= PROMO_NONE &&
                   product->promo_type <= PROMO_FIXED_DISCOUNT);
    if (!valid_input) {
      printf("El tipo de promoción debe ser un número entre 0 y 4.\n");
    }
  } while (!valid_input);

  // Solicitar valor de promoción
  if (product->promo_type != PROMO_NONE) {
    do {
      printf("Ingrese el valor de promoción del producto: ");
      get_line_input(input, MAX_INPUT);
      valid_input = (sscanf(input, "%f", &product->promo_value) == 1);
      if (!valid_input) {
        printf("El valor de promoción debe ser un número válido.\n");
      }
    } while (!valid_input);
  } else {
    product->promo_value =
        0.0f; // Asegurar que el valor sea 0 si no hay promoción
  }
}

void update_product_ui(Product *product) {
  printf("==== Actualizar Producto ====\n");
  // Puedes optar por solicitar solo los campos que se van a actualizar
  // Por simplicidad, aquí volvemos a solicitar todos los campos
  create_product_ui(product);
}

void find_product_by_id_ui(Product *product) {
  char input[MAX_INPUT];
  bool valid_input;
  do {
    printf("Ingrese el ID del producto a buscar: ");
    get_line_input(input, MAX_INPUT);
    valid_input = (sscanf(input, "%d", &product->id) == 1);
    if (!valid_input) {
      printf("Entrada inválida. Por favor, ingrese un número entero.\n");
    }
  } while (!valid_input);
}

void get_barcode_input_ui(Product *product) {
  bool valid_input;
  do {
    printf("Ingrese el barcode del producto a buscar (13 caracteres): ");
    get_line_input(product->barcode, sizeof(product->barcode));
    valid_input = (strlen(product->barcode) == 13);
    if (!valid_input) {
      printf("El barcode debe tener exactamente 13 caracteres.\n");
    }
  } while (!valid_input);
}

void find_product_by_name_ui(Product *product) {
  bool valid_input;
  do {
    printf("Ingrese el nombre del producto a buscar (min. 3 caracteres): ");
    get_line_input(product->name, sizeof(product->name));
    valid_input = (strlen(product->name) >= 3 &&
                   strlen(product->name) < sizeof(product->name));
    if (!valid_input) {
      printf("El nombre debe tener al menos 3 caracteres y no exceder %zu.\n",
             sizeof(product->name) - 1);
    }
  } while (!valid_input);
}

void delete_product_ui(Product *product) { find_product_by_id_ui(product); }

void menu_products_ui() {
  printf("==== Menu de Productos ====\n");
  printf("1. Crear producto\n");
  printf("2. Ver productos\n");
  printf("3. Buscar producto por ID\n");
  printf("4. Buscar producto por barcode\n");
  printf("5. Actualizar producto\n");
  printf("6. Eliminar producto\n");
  printf("0. Salir\n");
}

void show_product_ui(Product *product) {
  printf("ID: %d\n", product->id);
  printf("Barcode: %s\n", product->barcode);
  printf("Nombre: %s\n", product->name);
  printf("Descripción: %s\n", product->description);
  printf("Precio: %.2f\n", product->price);
  printf("Promoción: %s", promo_type_to_string(product->promo_type));
  if (product->promo_type != PROMO_NONE) {
    printf(" (Valor: %.2f)", product->promo_value);
  }
  printf("\n");
}

void list_products_ui(Product *products[], int count) {
  printf("=== Listado de productos (%d encontrados) ===\n\n", count);
  for (int i = 0; i < count; i++) {
    show_product_ui(products[i]);
    printf("----------------------------\n");
  }
}
