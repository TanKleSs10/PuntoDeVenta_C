#include "includes/product.service.h"
#include "../../utils/logger.h"
#include "includes/product.repository.h"

#include <stdlib.h>
#include <string.h>

// Definiciones de validaciones
#define MIN_ID 1
#define MAX_ID 10000

#define MIN_BARCODE_LEN 13
#define MAX_BARCODE_LEN 13

#define MIN_NAME_LEN 3
#define MAX_NAME_LEN 50

#define MIN_DESCRIPTION_LEN 10
#define MAX_DESCRIPTION_LEN 200

#define MIN_PRICE 1
#define MAX_PRICE 100000

static int validate_product_data(Product product, int check_id_existence) {
  if (product.id < MIN_ID || product.id > MAX_ID) {
    LOG_WARNING("El ID debe estar entre %d y %d", MIN_ID, MAX_ID);
    return -1;
  }

  if (strlen(product.barcode) < MIN_BARCODE_LEN ||
      strlen(product.barcode) > MAX_BARCODE_LEN) {
    LOG_WARNING("El barcode debe tener entre %d y %d caracteres",
                MIN_BARCODE_LEN, MAX_BARCODE_LEN);
    return -1;
  }

  if (strlen(product.name) < MIN_NAME_LEN ||
      strlen(product.name) > MAX_NAME_LEN) {
    LOG_WARNING("El nombre debe tener entre %d y %d caracteres", MIN_NAME_LEN,
                MAX_NAME_LEN);
    return -1;
  }

  if (strlen(product.description) < MIN_DESCRIPTION_LEN ||
      strlen(product.description) > MAX_DESCRIPTION_LEN) {
    LOG_WARNING("La descripción debe tener entre %d y %d caracteres",
                MIN_DESCRIPTION_LEN, MAX_DESCRIPTION_LEN);
    return -1;
  }

  if (product.price < MIN_PRICE || product.price > MAX_PRICE) {
    LOG_WARNING("El precio debe estar entre %d y %d", MIN_PRICE, MAX_PRICE);
    return -1;
  }

  if (product.promo_type != PROMO_NONE && product.promo_type != PROMO_2X1 &&
      product.promo_type != PROMO_3X2 && product.promo_type != PROMO_NO_TAX &&
      product.promo_type != PROMO_FIXED_DISCOUNT) {
    LOG_WARNING("Tipo de promoción inválido: %d", product.promo_type);
    return -1;
  }

  if (check_id_existence) {
    Product *existing = get_product_by_id_repository(product.id);
    if (existing != NULL) {
      LOG_WARNING("Ya existe un producto con ID %d", product.id);
      free(existing); // solo si get_product_by_id_repository usa malloc
      return -1;
    }
  }

  return 0;
}

int create_product_service(Product product) {
  if (validate_product_data(product, 1) != 0)
    return -1;

  int result = save_product_repository(product);
  if (result == 0) {
    LOG_INFO("Producto con ID %d creado correctamente.", product.id);
  }
  return result;
}

int update_product_service(Product product) {
  if (get_product_by_id_repository(product.id) == NULL) {
    LOG_WARNING("No existe producto con ID %d para actualizar.", product.id);
    return -1;
  }

  if (validate_product_data(product, 0) != 0)
    return -1;

  int result = update_product_repository(product);
  if (result == 0) {
    LOG_INFO("Producto con ID %d actualizado correctamente.", product.id);
  } else {
    LOG_ERROR("Error al actualizar el producto con ID %d", product.id);
  }
  return result;
}

Product *find_product_by_id_service(int id) {
  Product *product = get_product_by_id_repository(id);
  if (!product) {
    LOG_WARNING("No se encontró producto con ID %d", id);
  }
  return product;
}

Product *get_product_by_barcode_service(char *barcode) {
  if (!barcode || barcode[0] == '\0') {
    LOG_ERROR("Código de barras inválido.");
    return NULL;
  }
  return get_product_by_barcode_repository(barcode);
}

Product *find_product_by_name_service(char *name) {
  Product *product = get_product_by_name_repository(name);
  if (!product) {
    LOG_WARNING("No se encontró producto con nombre '%s'", name);
  }
  return product;
}

Product **list_products_service(int *count) {
  Product **products = list_products_repository(count);
  if (!products) {
    LOG_ERROR("No se pudo obtener la lista de productos.");
  } else {
    LOG_INFO("Se listaron %d productos correctamente.", *count);
  }
  return products;
}

int delete_product_service(int id) {
  Product *product = get_product_by_id_repository(id);
  if (!product) {
    LOG_WARNING("No se encontró producto con ID %d para eliminar.", id);
    return -1;
  }

  free(product); // solo si get_product_by_id_repository usa malloc

  int result = delete_product_repository(id);
  if (result == 0) {
    LOG_INFO("Producto con ID %d eliminado correctamente.", id);
  } else {
    LOG_ERROR("Error al eliminar el producto con ID %d", id);
  }
  return result;
}
