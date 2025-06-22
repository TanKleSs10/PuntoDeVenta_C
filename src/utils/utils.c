#include "utils.h"

const char* role_to_string(UserRole role) {
    switch (role) {
        case ADMIN: return "ADMIN";
        case CASHIER: return "CAJERO";
        case SUPERADMIN: return "SUPERADMIN";
        default: return "DESCONOCIDO";
    }
}

void get_line_input(char* buffer, size_t size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Elimina salto de línea
}

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función auxiliar para convertir el tipo de promoción a cadena
const char* promo_type_to_string(PromoType type) {
    switch (type) {
        case PROMO_NONE: return "Ninguna";
        case PROMO_2X1: return "2x1";
        case PROMO_3X2: return "3x2";
        case PROMO_NO_TAX: return "Sin Impuesto";
        case PROMO_FIXED_DISCOUNT: return "Descuento Fijo";
        default: return "Desconocido";
    }
}