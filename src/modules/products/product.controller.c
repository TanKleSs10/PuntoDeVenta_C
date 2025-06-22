#include "includes/product.controller.h"
#include "includes/product.service.h"
#include "includes/product.ui.h"
#include <stdio.h>
#include <stdlib.h> // Para free()

void create_product_controller() {
  Product *product = (Product *)malloc(sizeof(Product));
  if (!product) {
    perror("Error al asignar memoria para el producto");
    return;
  }
  Product *found_product;

  create_product_ui(product);

  found_product = find_product_by_id_service(product->id);
  if (found_product != NULL) {
    printf("Error: Ya existe un producto con ID %d.\n", product->id);
    free(product);
    free(found_product);
    return;
  }

  if (create_product_service(*product) != 0) {
    printf("Error: No se pudo crear el producto.\n");
  } else {
    printf("Producto creado exitosamente.\n");
  }

  free(product);
  if (found_product != NULL) {
    free(found_product);
  }
}

void find_product_by_id_controller() {
  Product product_to_find;
  find_product_by_id_ui(&product_to_find);
  Product *found_product = find_product_by_id_service(product_to_find.id);

  if (found_product == NULL) {
    printf("Error: No se pudo encontrar el producto.\n");
    return;
  }

  printf("Producto encontrado exitosamente.\n");
  show_product_ui(found_product);
  free(found_product); // ¡Liberar la memoria devuelta por el Service!
}

void find_product_by_barcode_controller() {
  Product product_to_find;
  get_barcode_input_ui(&product_to_find);
  Product *found_product =
      get_product_by_barcode_service(product_to_find.barcode);

  if (found_product == NULL) {
    printf("Error: No se pudo encontrar el producto.\n");
    return;
  }

  printf("Producto encontrado exitosamente.\n");
  show_product_ui(found_product);
  free(found_product); // ¡Liberar la memoria devuelta por el Service!
}

void find_product_by_name_controller() {
  Product product_to_find;
  find_product_by_name_ui(&product_to_find);
  Product *found_product = find_product_by_name_service(product_to_find.name);

  if (found_product == NULL) {
    printf("Error: No se pudo encontrar el producto.\n");
    return;
  }

  printf("Producto encontrado exitosamente.\n");
  show_product_ui(found_product);
  free(found_product); // ¡Liberar la memoria devuelta por el Service!
}

void list_products_controller() {
  int count = 0;
  Product **products =
      list_products_service(&count); // Pasar la dirección de count

  if (!products || count < 1) {
    printf("Hubo un error al obtener el listado de productos.\n");
    return;
  }

  list_products_ui(products, count);

  // Liberar memoria
  for (int i = 0; i < count; i++) {
    free(products[i]);
    products[i] = NULL;
  }
  free(products);
}

void update_product_controller() {
  Product *product = (Product *)malloc(sizeof(Product));
  if (!product) {
    perror("Error al asignar memoria para el producto");
    return;
  }
  update_product_ui(product);
  if (update_product_service(*product) != 0) {
    printf("No se pudo actualizar el producto.\n");
  } else {
    printf("Producto actualizado exitosamente.\n");
  }
  free(product);
}

void delete_product_controller() {
  Product product_to_delete;
  delete_product_ui(&product_to_delete);
  if (delete_product_service(product_to_delete.id) != 0) {
    printf("No se pudo eliminar el producto.\n");
  } else {
    printf("Producto eliminado exitosamente.\n");
  }
}

void menu_products_controller(Auth *session) {
  int option = 0;
  do {
    menu_products_ui();
    scanf("%d", &option);
    getchar(); // Limpiar newline

    switch (option) {
    case 1:
      if (has_permission(session, PERM_PRODUCT_CREATE)) {
        create_product_controller();
      } else {
        printf("No tienes permiso para crear productos.\n");
      }
      break;
    case 2:
      if (has_permission(session, PERM_PRODUCT_READ)) {
        list_products_controller();
      } else {
        printf("No tienes permiso para ver productos.\n");
      }
      break;
    case 3:
      if (has_permission(session, PERM_PRODUCT_READ)) {
        find_product_by_id_controller();
      } else {
        printf("No tienes permiso para buscar por ID.\n");
      }
      break;
    case 4:
      if (has_permission(session, PERM_PRODUCT_READ)) {
        find_product_by_barcode_controller();
      } else {
        printf("No tienes permiso para buscar por código de barras.\n");
      }
      break;
    case 5:
      if (has_permission(session, PERM_PRODUCT_UPDATE)) {
        update_product_controller();
      } else {
        printf("No tienes permiso para actualizar productos.\n");
      }
      break;
    case 6:
      if (has_permission(session, PERM_PRODUCT_DELETE)) {
        delete_product_controller();
      } else {
        printf("No tienes permiso para eliminar productos.\n");
      }
      break;
    case 0:
      printf("Volviendo al menú anterior...\n");
      break;
    default:
      printf("Opción inválida.\n");
      break;
    }
  } while (option != 0);
}
