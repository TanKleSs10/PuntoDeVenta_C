#ifndef UTILS_H
#define UTILS_H
#include "../modules/products/includes/product.model.h"
#include "../modules/users/includes/user.model.h"
#include <stdbool.h> // Para el tipo bool, si lo necesitas
#include <stdio.h>
#include <stdlib.h> // Para size_t
#include <string.h>

// Necesario para el delay
#ifdef _WIN32
#include <windows.h> // Para Sleep() en Windows
#else
#include <errno.h>  // ¡NECESARIO para 'errno' y 'EINTR'!
#include <time.h>   // Para nanosleep() o usleep() si queremos mayor precisión
#include <unistd.h> // Para sleep() en Unix-like
#endif

#define MAX_INPUT 100

const char *role_to_string(UserRole role);
void get_line_input(char *buffer, size_t size);
void clear_input();
const char *promo_type_to_string(PromoType type);
void clear_screen();
void press_enter_to_continue();
void art_adminCore();
void delay_ms(int ms);

#endif
