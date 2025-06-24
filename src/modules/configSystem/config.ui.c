#include "includes/config.ui.h"
#include "../../utils/utils.h"
#include "includes/config.model.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int create_config_ui(ConfigSystem *config) {
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

  return 0;
}

void update_config_ui(ConfigSystem *update) {
  char input[MAX_INPUT];
  bool valid_input;

  printf("\n=== Actualización de Configuración del Sistema ===\n");

  // Por defecto, marcar todos los campos como "sin cambios"
  strcpy(update->bussinesName, ""); // <- "" indica que no se quiere actualizar
  update->taxes = -1.0f;            // <- valor inválido como marcador
  strcpy(update->currency, "");     // <- "" indica que no se quiere actualizar

  // Nombre de empresa
  printf("¿Deseas actualizar el nombre de la empresa? (S/N): ");
  get_line_input(input, MAX_INPUT);
  if (input[0] == 'S' || input[0] == 's') {
    do {
      printf("Ingresa el nuevo nombre (3 a 50 caracteres): ");
      get_line_input(update->bussinesName, sizeof(update->bussinesName));
      size_t len = strlen(update->bussinesName);
      valid_input = (len >= 3 && len <= 50);
      if (!valid_input) {
        printf("El nombre debe tener entre 3 y 50 caracteres.\n");
      }
    } while (!valid_input);
  }

  // Impuestos
  printf("¿Deseas actualizar el porcentaje de impuestos? (S/N): ");
  get_line_input(input, MAX_INPUT);
  if (input[0] == 'S' || input[0] == 's') {
    do {
      printf("Ingresa el nuevo porcentaje de impuestos (0.00 - 100.00): ");
      get_line_input(input, MAX_INPUT);
      valid_input = (sscanf(input, "%f", &update->taxes) == 1 &&
                     update->taxes >= 0 && update->taxes <= 100);
      if (!valid_input) {
        printf("Porcentaje inválido. Intenta de nuevo.\n");
      }
    } while (!valid_input);
  }

  // Moneda
  printf("¿Deseas actualizar la moneda? (S/N): ");
  get_line_input(input, MAX_INPUT);
  if (input[0] == 'S' || input[0] == 's') {
    int option = 0;
    do {
      printf("Selecciona la nueva moneda:\n 1: MXN\n 2: USD\n 3: EUR\n");
      printf("Tu opción: ");
      get_line_input(input, MAX_INPUT);
      valid_input =
          (sscanf(input, "%d", &option) == 1 && option >= 1 && option <= 3);
      if (!valid_input) {
        printf("Opción inválida. Intenta de nuevo.\n");
      }
    } while (!valid_input);

    switch (option) {
    case 1:
      strcpy(update->currency, "MXN");
      break;
    case 2:
      strcpy(update->currency, "USD");
      break;
    case 3:
      strcpy(update->currency, "EUR");
      break;
    }
  }

  // admin_id nunca se actualiza desde la UI
  update->admin_id = -1; // El service usará el actual
}

void get_config_ui(ConfigSystem *config, const char *username) {
  printf("Nombre de la empresa: %s\n", config->bussinesName);
  printf("Porcentaje de impuestos: %.2f%%\n", config->taxes);
  printf("Moneda: %s\n", config->currency);
  printf("Superadmin: %s\n", username);
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
