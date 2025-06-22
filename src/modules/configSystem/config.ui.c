#include "includes/config.ui.h"
#include "../../utils/utils.h"
#include "../users/includes/user.ui.h"
#include "includes/config.model.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100

int create_config_ui(ConfigSystem *config, int isUpdate) {
  char input[MAX_INPUT];
  bool valid_input;

  // Nombre de empresa
  do {
    printf("Ingresa el nombre de la empresa (entre 3 y 50 caracteres): ");
    get_line_input(config->bussinesName, sizeof(config->bussinesName));
    size_t len = strlen(config->bussinesName);
    valid_input = (len >= 3 && len <= 50);
    if (!valid_input) {
      printf("El nombre de la empresa debe tener entre 3 y 50 caracteres.\n");
    }
  } while (!valid_input);

  // Porcentaje de impuestos
  do {
    printf("Ingresa el porcentaje de impuesto (ejemplo: 16.00 para 16%%): ");
    get_line_input(input, MAX_INPUT);
    valid_input = (sscanf(input, "%2f", &config->taxes) == 1 &&
                   config->taxes >= 0 && config->taxes <= 100);
    if (!valid_input) {
      printf("El porcentaje de impuesto debe ser un número entre 0.00 y "
             "100.00.\n");
    }
  } while (!valid_input);

  // Moneda
  do {
    printf("Selecciona la moneda:\n 1: MXN\n 2: USD\n 3: EUR\n");
    printf("Ingresa el número correspondiente a la moneda: ");
    get_line_input(input, MAX_INPUT);

    int currency_input;
    valid_input = (sscanf(input, "%d", &currency_input) == 1 &&
                   (currency_input >= 1 && currency_input <= 3));

    if (valid_input) {
      switch (currency_input) {
      case 1:
        strcpy(config->currency, "MXN");
        break;
      case 2:
        strcpy(config->currency, "USD");
        break;
      case 3:
        strcpy(config->currency, "EUR");
        break;
      }
    } else {
      printf(
          "Moneda inválida. Por favor, ingresa 1 (MXN), 2 (USD) o 3 (EUR).\n");
    }
  } while (!valid_input);

  if (isUpdate != 1) {
    // Superadmin
    create_user_ui(&config->admin, 1);
  }

  return 0;
}

void update_config_ui(ConfigSystem *config) {
  printf("Actualizando configuración de sistema...\n");
  create_config_ui(config, 0);
}

void get_config_ui(ConfigSystem *config) {
  printf("Nombre de la empresa: %s\n", config->bussinesName);
  printf("Porcentaje de impuestos: %.2f%%\n", config->taxes);
  printf("Moneda: %s\n", config->currency);
  printf("Superadmin: %s\n", config->admin.username);
}

int delete_config_ui() {
  char input[MAX_INPUT];
  bool valid_input = false;
  int confirm = 0;

  do {
    printf("¿Estás seguro de que quieres eliminar la configuración del "
           "sistema?\n");
    printf("Esto eliminará TODOS los datos de usuarios y productos.\n");
    printf("Escribe 'S' para confirmar o 'N' para cancelar: ");
    get_line_input(input, MAX_INPUT);

    if (strcmp(input, "S") == 0 || strcmp(input, "s") == 0) {
      confirm = 1;
      valid_input = true;
    } else if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0) {
      confirm = 0;
      valid_input = true;
    } else {
      printf("Entrada inválida. Escribe 'S' para confirmar o 'N' para "
             "cancelar.\n");
    }
  } while (!valid_input);

  return confirm;
}

void menu_config_ui() {
  printf("==== Menu de configuración del sistema ====\n");
  printf("1. Ver configuración\n");
  printf("2. Actualizar configuración\n");
  printf("3. Eliminar configuración\n");
  printf("0. Salir\n");
}
