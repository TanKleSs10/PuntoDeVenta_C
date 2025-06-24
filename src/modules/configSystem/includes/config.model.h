#ifndef CONFIG_MODEL_H
#define CONFIG_MODEL_H

#include "../../../modules/users/includes/user.model.h"

typedef struct {
  char bussinesName[50]; // Nombre de la empresa
  float taxes;           // Porcentaje de impuesto (ej. 16.0 para 16%)
  char currency[4];      // "MXN", "USD", etc.
  int admin_id;          // Usuario ID del administrador
} ConfigSystem;          // Estructura de la configuración

#endif
