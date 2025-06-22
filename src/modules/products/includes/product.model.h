#ifndef PRODUCT_MODEL_H
#define PRODUCT_MODEL_H

typedef enum {
    PROMO_NONE,          // 0
    PROMO_2X1,           // 1
    PROMO_3X2,           // 2
    PROMO_NO_TAX,        // 3
    PROMO_FIXED_DISCOUNT // 4
} PromoType;


typedef struct {
    int id;
    char barcode[14];
    char name[20];
    char description[200];
    float price;
    PromoType promo_type;    // Tipo de promoción
    float promo_value; // Valor relacionado (descuento o porcentaje)
} Product;

#endif