#include "utils.h"

const char *role_to_string(UserRole role) {
  switch (role) {
  case ADMIN:
    return "ADMIN";
  case CASHIER:
    return "CAJERO";
  case SUPERADMIN:
    return "SUPERADMIN";
  default:
    return "DESCONOCIDO";
  }
}

// Nueva y mejorada get_line_input
void get_line_input(char *buffer, size_t size) {
  // Intentar leer la línea completa
  if (fgets(buffer, size, stdin) == NULL) {
    // Manejo de error si fgets falla (ej. EOF, error de lectura)
    buffer[0] = '\0'; // Asegurar que el buffer esté vacío
    // Opcional: imprimir un mensaje de error o manejar de otra forma
    printf("Error de lectura de entrada.\n");
    // Asegurarse de limpiar stdin si falló
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    return;
  }

  // Buscar el salto de línea
  char *newline_pos = strchr(buffer, '\n');

  if (newline_pos != NULL) {
    // Si se encuentra el salto de línea, reemplazarlo por el terminador nulo
    *newline_pos = '\0';
  } else {
    // Si no se encontró el salto de línea, significa que la línea era más larga
    // que 'size - 1' caracteres. Es necesario limpiar el resto de stdin.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
      // Consumir el resto de la línea
    }
  }
}

void clear_input() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Función auxiliar para convertir el tipo de promoción a cadena
const char *promo_type_to_string(PromoType type) {
  switch (type) {
  case PROMO_NONE:
    return "Ninguna";
  case PROMO_2X1:
    return "2x1";
  case PROMO_3X2:
    return "3x2";
  case PROMO_NO_TAX:
    return "Sin Impuesto";
  case PROMO_FIXED_DISCOUNT:
    return "Descuento Fijo";
  default:
    return "Desconocido";
  }
}
