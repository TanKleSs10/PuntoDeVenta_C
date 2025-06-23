#ifndef UTILS_H
#define UTILS_H
#include "../modules/products/includes/product.model.h"
#include "../modules/users/includes/user.model.h"
#include <stdbool.h> // Para el tipo bool, si lo necesitas
#include <stdio.h>
#include <stdlib.h> // Para size_t
#include <string.h>
#include <string.h> // Para strcspn, strchr

#define MAX_INPUT 100

const char *role_to_string(UserRole role);
void get_line_input(char *buffer, size_t size);
void clear_input();
const char *promo_type_to_string(PromoType type);

#endif
