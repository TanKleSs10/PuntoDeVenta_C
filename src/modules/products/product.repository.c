#include "includes/product.repository.h"
#include "../../components/file.component.h"
#include "../../utils/logger.h"
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define PRODUCT_FILE "data/products.dat"
#define TEMP_FILE "data/products_tmp.dat"

int save_product_repository(Product product) {
  FILE *f = open_file(PRODUCT_FILE, "ab");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para guardar el producto.",
              PRODUCT_FILE);
    return -1;
  }

  int r = write_record(f, &product, sizeof(Product));
  fclose(f);

  if (r != 0) {
    LOG_ERROR("Fallo al escribir el producto en %s", PRODUCT_FILE);
    return -1;
  }

  LOG_INFO("Producto con ID %d guardado correctamente.", product.id);
  return 0;
}

Product *get_product_by_id_repository(int id) {
  FILE *f = open_file(PRODUCT_FILE, "rb");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para obtener el producto.",
              PRODUCT_FILE);
    return NULL;
  }

  Product temp;
  while (read_record(f, &temp, sizeof(Product)) == 0) {
    if (temp.id == id) {
      Product *found_product = malloc(sizeof(Product));
      if (!found_product) {
        fclose(f);
        LOG_CRITICAL("Fallo al reservar memoria para el producto con ID %d.",
                     id);
        return NULL;
      }
      *found_product = temp;
      fclose(f);
      LOG_INFO("Producto con ID %d encontrado en el repositorio.", id);
      return found_product;
    }
  }

  fclose(f);
  LOG_WARNING("No se encontró el producto con ID %d.", id);
  return NULL;
}

Product *get_product_by_barcode_repository(char *barcode) {
  FILE *f = open_file(PRODUCT_FILE, "rb");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para buscar el producto.",
              PRODUCT_FILE);
    return NULL;
  }

  Product temp;
  while (read_record(f, &temp, sizeof(Product)) == 0) {
    if (strcmp(temp.barcode, barcode) == 0) {
      Product *found_product = malloc(sizeof(Product));
      if (!found_product) {
        fclose(f);
        LOG_CRITICAL(
            "Fallo al reservar memoria para el producto con barcode '%s'.",
            barcode);
        return NULL;
      }
      *found_product = temp;
      fclose(f);
      LOG_INFO("Producto con barcode '%s' encontrado.", barcode);
      return found_product;
    }
  }

  fclose(f);
  LOG_WARNING("No se encontró el producto con barcode '%s'.", barcode);
  return NULL;
}

Product *get_product_by_name_repository(char *name) {
  FILE *f = open_file(PRODUCT_FILE, "rb");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para buscar el producto.",
              PRODUCT_FILE);
    return NULL;
  }

  Product temp;
  while (read_record(f, &temp, sizeof(Product)) == 0) {
    if (strcmp(temp.name, name) == 0) {
      Product *found_product = malloc(sizeof(Product));
      if (!found_product) {
        fclose(f);
        LOG_CRITICAL(
            "Fallo al reservar memoria para el producto con nombre '%s'.",
            name);
        return NULL;
      }
      *found_product = temp;
      fclose(f);
      LOG_INFO("Producto con nombre '%s' encontrado.", name);
      return found_product;
    }
  }

  fclose(f);
  LOG_WARNING("No se encontró el producto con nombre '%s'.", name);
  return NULL;
}

Product **list_products_repository(int *count) {
  FILE *f = open_file(PRODUCT_FILE, "rb");
  if (!f) {
    LOG_ERROR("No se pudo abrir el archivo %s para listar productos.",
              PRODUCT_FILE);
    return NULL;
  }

  Product **list = malloc(sizeof(Product *) * MAX_PRODUCTS);
  if (!list) {
    fclose(f);
    LOG_CRITICAL("Fallo al reservar memoria para la lista de productos.");
    return NULL;
  }

  *count = 0;
  int read_result;
  while (*count < MAX_PRODUCTS) {
    Product *p = malloc(sizeof(Product));
    if (!p) {
      LOG_CRITICAL("Fallo al reservar memoria para el producto en índice %d.",
                   *count);
      break;
    }

    read_result = read_record(f, p, sizeof(Product));
    if (read_result != 0) {
      free(p);
      if (read_result == -1) {
        LOG_ERROR("Error al leer un registro de producto desde el archivo.");
      }
      break;
    }

    list[*count] = p;
    (*count)++;
  }

  fclose(f);

  LOG_INFO("Se listaron %d producto(s) desde el repositorio.", *count);
  return list;
}

int update_product_repository(Product product) {
  FILE *original = open_file(PRODUCT_FILE, "rb");
  FILE *temp = open_file(TEMP_FILE, "wb");
  if (!original || !temp) {
    LOG_ERROR("Error al abrir archivos para actualizar el producto con ID %d.",
              product.id);
    return -1;
  }

  Product current;
  int updated = 0;

  while (read_record(original, &current, sizeof(Product)) == 0) {
    if (current.id == product.id) {
      write_record(temp, &product, sizeof(Product));
      updated = 1;
    } else {
      write_record(temp, &current, sizeof(Product));
    }
  }

  fclose(original);
  fclose(temp);

  if (remove(PRODUCT_FILE) != 0 || rename(TEMP_FILE, PRODUCT_FILE) != 0) {
    LOG_ERROR("Error al reemplazar el archivo original tras actualizar "
              "producto con ID %d.",
              product.id);
    return -1;
  }

  if (updated) {
    LOG_INFO("Producto con ID %d actualizado correctamente.", product.id);
    return 0;
  } else {
    LOG_WARNING("No se encontró el producto con ID %d para actualizar.",
                product.id);
    return -1;
  }
}

int delete_product_repository(int id) {
  FILE *original = open_file(PRODUCT_FILE, "rb");
  FILE *temp = open_file(TEMP_FILE, "wb");
  if (!original || !temp) {
    LOG_ERROR("No se pudo abrir archivos para eliminar el producto con ID %d.",
              id);
    return -1;
  }

  Product current;
  int deleted = 0;

  while (read_record(original, &current, sizeof(Product)) == 0) {
    if (current.id == id) {
      deleted = 1;
      continue;
    }
    write_record(temp, &current, sizeof(Product));
  }

  fclose(original);
  fclose(temp);

  if (remove(PRODUCT_FILE) != 0 || rename(TEMP_FILE, PRODUCT_FILE) != 0) {
    LOG_ERROR("Error al reemplazar archivo tras eliminar producto con ID %d.",
              id);
    return -1;
  }

  if (deleted) {
    LOG_INFO("Producto con ID %d eliminado correctamente.", id);
    return 0;
  } else {
    LOG_WARNING("No se encontró el producto con ID %d para eliminar.", id);
    return -1;
  }
}
