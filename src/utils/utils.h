#ifndef UTILS_H
#define UTILS_H
#include "../modules/users/includes/user.model.h"
#include "../modules/products/includes/product.model.h"
#include <string.h>
#include <stdio.h>

const char* role_to_string(UserRole role);
void get_line_input(char* buffer, size_t size);
void clear_input();
const char* promo_type_to_string(PromoType type);

#endif